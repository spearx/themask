#include "menu.h"
#include "popup.h"

#include "button_component.h"
#include "world/world.h"

namespace Menu
{

	////////////////////////////////////////////////////////////////////////////
	CCamera::CCamera()
		: m_cameraPos(5.0f)
		, m_cameraTarget(MathUtils::ZERO)
	{}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntityByName("Camera001", sceneId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pCameraEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				m_cameraPos = pLocationComponent->mtx.GetTranslation();
			}
		}

		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntityByName("Camera001.Target", sceneId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pCameraEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				m_cameraTarget = pLocationComponent->mtx.GetTranslation();
			}
		}

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(55.f), 0.1f, 1000.0f);
		m_viewParameters.SetLookAt(m_cameraPos, m_cameraTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(100));

		Abathur::SetViewParameters(m_viewId, m_viewParameters);

		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		//TODO ~ ramonv ~ move the camera

		m_viewParameters.SetLookAt(m_cameraPos, m_cameraTarget);
		Abathur::SetViewParameters(m_viewId, m_viewParameters);
	}

	////////////////////////////////////////////////////////////////////////////

	CMenu* CMenu::m_pInstance = nullptr;

  CMenu::CMenu()
    : m_pFont(nullptr)
    , m_totalTime(0.0f)
    , m_timeFactor(1.0f)
	{}

	void CMenu::Init()
	{

		Abathur::RegisterEntityComponent<CButtonComponent>("comp_player");

		//Load scene
		m_sceneId = Abathur::LoadScene("data/menu/scenes/themask_menu.scene");

		//Cameras
		m_camera.Init(m_sceneId);
    m_camera.GetViewParameters().SetAfterCallback(Abathur::TViewCallback::SetMethod<CMenu, &CMenu::AfterRender>(this));

		//Register Updates
		//m_offlineGame.Init();

		InitButtons();

		m_preRenderUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu, &CMenu::PreRenderUpdate>(this));
		m_preRenderUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));

		//Start Scene
		Abathur::StartScene(m_sceneId);

		SetState(EState::Playing);

		//Load Font and configure Popup
    m_pFont = Abathur::loadFont("data/fonts/mask_font.fnt", "data/fonts/mask_font.tga");
		ASSERT(m_pFont);
		CPopup::Get().Init(m_pFont);

	}

	void CMenu::SetState(const EState newState)
	{
		switch (newState)
		{
		case EState::Intro: break;
		case EState::Playing:
		{
      m_totalTime = 2 * 60;
			m_logicUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu, &CMenu::LogicUpdate>(this));
			m_logicUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PostPhysics, Abathur::EUpdateStage::Default));
		}
		break;
		case EState::Success:
		case EState::Failed:
		{
			m_logicUpdate.Unregister();
		}
		break;
		}

		m_state = newState;
	}

  void CMenu::AfterRender(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
  {
    //CPopup::Get().AddTextLine("Hola mundo");
    //CPopup::Get().AddTextLine("Adios...");
    CPopup::Get().Render();
    int minutes = m_totalTime / 60;
    int seconds = m_totalTime - minutes * 60;
    char timerText[12];
    sprintf(timerText, "%02d:%02d", minutes, seconds);
    Abathur::renderText(m_pFont, 10.0f, 30.0f, 0xffffffff, timerText);
  }

	void CMenu::PreRenderUpdate(const Abathur::SUpdateContext& context)
	{
		//Map other scene viewport
		//TODO ~ intro transition proper

		if (Abathur::TAbathurEntity* pCristalPlayer = Abathur::GetEntityByName("Ball", m_sceneId))
		{
			if (Abathur::TVisualComponent* pVisualComponent = pCristalPlayer->QueryComponent<Abathur::TVisualComponent>())
			{
				Abathur::CViewParameters& viewParameters = World::CWorld::Get().GetPlayerCamera().GetViewParameters();
				Abathur::setMaterialParam(pVisualComponent->material, "diffuse", viewParameters.GetRenderTarget());
			}
		}
	}

	void CMenu::LogicUpdate(const Abathur::SUpdateContext& context)
	{
    m_totalTime -= context.frameTime * m_timeFactor;
    if (m_totalTime < 0.0f) {
      SetState(EState::Failed);
    }

    /*
		COfflineGame::EState state = m_offlineGame.GetState();
		if (state == COfflineGame::EState::Success)
		{
			SetState(EState::Success);
		}
		else if (state == COfflineGame::EState::Failed)
		{
			SetState(EState::Failed);
		}
    */
    for (int i = 0; i < ButtonCount;++i) {
      const char *button_name = m_buttonNames[i];
      CButtonComponent *button_comp = Abathur::GetEntityByName(button_name, m_sceneId)->QueryComponent<CButtonComponent>();
      if (button_comp->JustPressed())
      {
        if (i == Laser1)
        {
          World::CWorld::Get().GetLasers().DisableTypeLaser(World::CLasers::ELaserType::RED_LASER, true);
        }
        else if (i == Laser2)
        {
          World::CWorld::Get().GetLasers().DisableTypeLaser(World::CLasers::ELaserType::BLUE_LASER, true);
        }
        else if (i == Totem)
        {
          World::CWorld::Get().GetLasers().DisableTypeLaser(World::CLasers::ELaserType::BLUE_LASER, true);
        }
      }
      else if (button_comp->JustReleased())
      {
        if (i == Laser1)
        {
          World::CWorld::Get().GetLasers().EnableTypeLaser(World::CLasers::ELaserType::RED_LASER);
        }
        else if (i == Laser2)
        {
          World::CWorld::Get().GetLasers().EnableTypeLaser(World::CLasers::ELaserType::BLUE_LASER);
        }
        else if (i == Totem)
        {
          World::CWorld::Get().GetLasers().DisableTypeLaser(World::CLasers::ELaserType::BLUE_LASER, true);
        }
      }
    }
	}

	bool CMenu::IsButtonEnabled(const EButton button) const
	{
		return Abathur::GetEntityByName(m_buttonNames[button], m_sceneId)->QueryComponent<CButtonComponent>()->IsEnabled();
	}

	void CMenu::EnableButton(const EButton button)
	{
		Abathur::GetEntityByName(m_buttonNames[button], m_sceneId)->QueryComponent<CButtonComponent>()->SetEnable(true);
	}

	void CMenu::InitButtons()
	{
		AddButton("button_1", Vector2(0.07f, 0.75f), Vector2(0.23f, 0.92f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		AddButton("button_2", Vector2(0.0f, 0.0f), Vector2(0.1f, 0.1f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		AddButton("button_3", Vector2(0.1f, 0.1f), Vector2(0.2f, 0.2f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));

		m_buttonNames[Totem]  = "button_1";
		m_buttonNames[Laser1] = "button_2";
		m_buttonNames[Laser2] = "button_3";

		for (int i = 0; i < ButtonCount; ++i) 
		{
			const char *button_name = m_buttonNames[i];
			Abathur::TVisualComponent *comp = Abathur::GetEntityByName(button_name, m_sceneId)->QueryComponent<Abathur::TVisualComponent>();
			if (comp)
			{
				comp->visible = false;
			}
		}

	}

	Abathur::TEntityId CMenu::AddButton(const char* entityName, const Vector2& areaMin, const Vector2& areaMax, const Vector3& hoverOffset, const Vector4& baseTintColor, const Vector4& tintColor)
	{
		if (Abathur::TAbathurEntity* pEntity = Abathur::GetEntityByName(entityName, m_sceneId))
		{
			CButtonComponent* pComponent = pEntity->AddComponent<CButtonComponent>();
			pComponent->SetArea(areaMin, areaMax);
			pComponent->SetHoverOffset(hoverOffset);
			pComponent->SetPressedColor(baseTintColor,tintColor);
			pComponent->SetEnable(false);
			return pEntity->GetId();
		}
		return Abathur::TEntityId::s_invalid;
	}

	bool CMenu::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		if (m_state == EState::Intro && button == Abathur::Input::EButton::GamepadStart)
		{
			SetState(EState::Playing);
		}
		return false;
	}
}
