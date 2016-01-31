#include "menu.h"
#include "popup.h"

#include "button_component.h"
#include "world/world.h"
#include "abathur_gui.h"

namespace Menu
{

	Vector2 gCameraMoveFreq(0.197f, 0.591f);
	Vector2 gCameraMoveAmp(0.551f, 0.906f);
	Vector2 gCameraMovePhase(0.5f, 0.0f);

	Vector3 gCameraPositionStart(20.194f, 159.921f, 269.434f);
	Vector3 gCameraTargetStart(139.766f, 47.967f, -46.528f);
	float   gCameraFovStart = DEG2RAD(26.231f);
	float   gTotalTime = 0.0f;
  float   gElapsedTime = 0.0f;


	STitle::STitle()
		: m_initTransform(MathUtils::IDENTITY)
		, m_type(EType::Title)
	{
	}

	void STitle::Init(const Abathur::TSceneId sceneId)
	{
		if (Abathur::TAbathurEntity* pEntity = Abathur::GetEntityByName("", sceneId))
		{
			m_entityId = pEntity->GetId();
			m_initTransform = pEntity->QueryComponent<Abathur::TLocationComponent>()->mtx;
		}

		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<STitle, &STitle::Update>(this));
		m_update.Register();

		m_scale.Reset(1.0f);

		m_type = EType::Title;

	}

	void STitle::Show(const EType type)
	{
		m_scale.SetValue(1.0f, 1.0f);

		m_type = type;
	}

	void STitle::Hide()
	{
		m_scale.SetValue(0.0f, 1.0f);
	}

	void STitle::Update(const Abathur::SUpdateContext& context)
	{
		m_scale.Update(context.frameTime);

		Matrix44 scaleMtx;
		scaleMtx.SetScale(m_scale.GetValue());

		if (Abathur::TAbathurEntity* pEntity = Abathur::GetEntity(m_entityId))
		{
			pEntity->QueryComponent<Abathur::TLocationComponent>()->mtx = scaleMtx*m_initTransform;

			float selector = m_type == EType::Title ? 0.0f : m_type == EType::Win ? 1.0f : 2.0f;
			Abathur::setMaterialParam(pEntity->QueryComponent<Abathur::TVisualComponent>()->material, "texture_selector", selector);
		}
	}


	void afterRender(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
	{
		//CPopup::Get().AddTextLine("Hola mundo");
		//CPopup::Get().AddTextLine("Adios...");
		CPopup::Get().Render();
	}

	////////////////////////////////////////////////////////////////////////////
	CCamera::CCamera()
		: m_cameraPos(5.0f)
		, m_cameraTarget(MathUtils::ZERO)
		, m_totalTime(0.0f)
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

		gCameraTargetStart = Vector3(360.0f, m_cameraTarget.y, m_cameraTarget.z);
		gCameraFovStart = DEG2RAD(55.f);
		m_camPos.Reset(gCameraPositionStart);
		m_camTarget.Reset(gCameraTargetStart);
		m_fov.Reset(gCameraFovStart);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(gCameraFovStart, 0.1f, 1000.0f);
		m_viewParameters.SetLookAt(m_camPos.GetValue(), m_camTarget.GetValue());
		m_viewParameters.SetPriority(Abathur::TViewPriority(100));

		Abathur::SetViewParameters(m_viewId, m_viewParameters);

		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::Start()
	{
		m_camPos.SetValue(m_cameraPos,2.0f);
		m_camTarget.SetValue(m_cameraTarget, 2.0f);
		m_fov.SetValue(DEG2RAD(55.f),2.0f);
    CMenu::Get().PlayBGMMusic("data/audio/bgm_horror.wav");

	}

	void CCamera::Stop()
	{
		m_camPos.SetValue(gCameraPositionStart, 2.0f);
		m_camTarget.SetValue(gCameraTargetStart, 2.0f);
		m_fov.SetValue(gCameraFovStart);
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		ImGui::SliderFloat("Camera Move Freq X", &gCameraMoveFreq.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Camera Move Freq Y", &gCameraMoveFreq.y, 0.0f, 10.0f);

		ImGui::SliderFloat("Camera Move Amp X", &gCameraMoveAmp.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Camera Move Amp Y", &gCameraMoveAmp.y, 0.0f, 10.0f);

		ImGui::SliderFloat("Camera Move Phase X", &gCameraMovePhase.x, 0.0f, 10.0f);
		ImGui::SliderFloat("Camera Move Phase Y", &gCameraMovePhase.y, 0.0f, 10.0f);

		m_camPos.Update(context.frameTime);
		m_camTarget.Update(context.frameTime);
		m_fov.Update(context.frameTime);

		m_totalTime += context.frameTime;
		m_viewParameters.SetProjection(m_fov.GetValue(), 0.1f, 1000.0f);
		m_viewParameters.SetLookAt(m_camPos.GetValue(), m_camTarget.GetValue()+Vector3(gCameraMoveAmp.x*sinf(gCameraMovePhase.x+gCameraMoveFreq.x*gfPI2*m_totalTime), gCameraMoveAmp.y*cosf(gCameraMovePhase.y + gCameraMoveFreq.y*gfPI2*m_totalTime),0.0f));
		Abathur::SetViewParameters(m_viewId, m_viewParameters);
	}

	////////////////////////////////////////////////////////////////////////////

	CMenu* CMenu::m_pInstance = nullptr;

  CMenu::CMenu()
    : m_pFont(nullptr)
    , m_totalTime(0.0f)
    , m_timeFactor(1.0f)
    , m_totemIcon(nullptr)
    , m_awakeTotem(false)
	{}

	void CMenu::Init()
	{

		Abathur::RegisterEntityComponent<CButtonComponent>("comp_player");

		//Load scene
		m_sceneId = Abathur::LoadScene("data/menu/scenes/themask_menu.scene");

		m_introThreshold.Reset(0.0f);

		m_title.Init(m_sceneId);

		//Cameras
		m_camera.Init(m_sceneId);
    m_camera.GetViewParameters().SetAfterCallback(Abathur::TViewCallback::SetMethod<CMenu, &CMenu::AfterRender>(this));

		//Register Updates
		m_offlineGame.Init();

		InitButtons();

		m_preRenderUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu, &CMenu::PreRenderUpdate>(this));
		m_preRenderUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));

		//Start Scene
		Abathur::StartScene(m_sceneId);

		SetState(EState::Intro);

		//Load Font and configure Popup
    m_pFont = Abathur::loadFont("data/fonts/mask_font.fnt", "data/fonts/mask_font.tga");
		ASSERT(m_pFont);
		CPopup::Get().Init(m_pFont);

    PlayBGMMusic("data/audio/bgm_menu.wav");
    
    m_totemIcon = Abathur::loadTexture("data/textures/totem_head.tga");
    ASSERT(m_totemIcon);
	}

	void CMenu::SetState(const EState newState)
	{
		switch (newState)
		{
		case EState::Intro: break;
		case EState::Playing:
		{
			m_title.Hide();
			m_totalTime = 8 * 60;
			m_logicUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu, &CMenu::LogicUpdate>(this));
			m_logicUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PostPhysics, Abathur::EUpdateStage::Default));
			m_camera.Start();
			m_introThreshold.SetValue(1.0f, 4.0f);
		}
		break;
		case EState::Success:
		{
			m_title.Show(STitle::EType::Win);
			m_logicUpdate.Unregister();
			m_camera.Stop();
			m_introThreshold.SetValue(0.0f, 1.0f);
      Abathur::playAudio("data/audio/laughter.wav", false);
    }
		break;
		case EState::Failed:
		{
			m_title.Show(STitle::EType::Lose);
			m_logicUpdate.Unregister();
			m_camera.Stop();
			m_introThreshold.SetValue(0.0f, 1.0f);
      Abathur::playAudio("data/audio/game_over.wav", false);
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
    
    //Render
    static unsigned color = COLOR_ARGB(0xff, 0xff, 0xff, 0xff);
    static float acum_time = 0.0f;
    
    static Vector4 quadIcon(0.007f, 0.048f, 0.026f, 0.038f);
    //ImGui::SliderFloat4("Pos", &quadIcon.x, 0.0f, 0.05f);

    if( m_awakeTotem )
    {
      CPopup::Get().ApplyOrthoMatrix();

      Abathur::DisableDepthState.apply();
      Abathur::AlphaBlendState.apply();


      float time = 0.3f;
      acum_time += gElapsedTime;
      if (acum_time > time) {
        if( color == 0x0 )
          color = COLOR_ARGB(0xff, 0xff, 0xff, 0xff);
        else
          color = 0x0;
        acum_time = 0.0f;
      }

      Abathur::renderQuad2D(quadIcon.x, quadIcon.y, quadIcon.z, quadIcon.w, color, m_totemIcon);

      Abathur::NoneBlendState.apply();
      Abathur::DefaultDepthState.apply();
    }
    else {
      acum_time = 0.0f;
      color = COLOR_ARGB(0xff, 0xff, 0xff, 0xff);
    }

  }

	void CMenu::PreRenderUpdate(const Abathur::SUpdateContext& context)
	{
		//TODO ~ intro transition proper
		gTotalTime += context.frameTime*2.0f;
    gElapsedTime = context.frameTime;

		m_introThreshold.Update(context.frameTime);

		if (Abathur::TAbathurEntity* pCristalPlayer = Abathur::GetEntityByName("Ball", m_sceneId))
		{
			if (Abathur::TVisualComponent* pVisualComponent = pCristalPlayer->QueryComponent<Abathur::TVisualComponent>())
			{
				//Vector3 cameraPosition = m_camera.GetViewParameters().GetTransform().t;

				Abathur::CViewParameters& viewParameters = World::CWorld::Get().GetPlayerCamera().GetViewParameters();
				Abathur::setMaterialParam(pVisualComponent->material, "diffuse", viewParameters.GetRenderTarget());
				//Abathur::setMaterialParam(pVisualComponent->material, "eye_pos", cameraPosition);
				Abathur::setMaterialParam(pVisualComponent->material, "global_time", gTotalTime);
				Abathur::setMaterialParam(pVisualComponent->material, "threshold", const_cast<float&>(m_introThreshold.GetValue()));

				if (ImGui::Button("Reload Ball Material"))
				{
					Abathur::reloadMaterial(pVisualComponent->material);
				}
			}
		}
    UpdateMusicFade(context.frameTime);
	}

	void CMenu::LogicUpdate(const Abathur::SUpdateContext& context)
	{
    m_totalTime -= context.frameTime * m_timeFactor;
    if (m_totalTime < 0.0f) {
      SetState(EState::Failed);
    }

		COfflineGame::EState state = m_offlineGame.GetState();
		if (state == COfflineGame::EState::Success)
		{
			SetState(EState::Success);
			return;
		}
		else if (state == COfflineGame::EState::Failed)
		{
			SetState(EState::Failed);
			return;
		}
		

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
          World::CWorld::Get().SetCentinelsSpeedFactor(0.35f);
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
          World::CWorld::Get().SetCentinelsSpeedFactor(1.0f);
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
		AddButton("button_1", Vector2(0.27f, 0.72f), Vector2(0.41f, 0.93f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		AddButton("button_2", Vector2(0.47f, 0.68f), Vector2(0.59f, 0.86f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		AddButton("button_3", Vector2(0.64f, 0.73f), Vector2(0.76f, 0.93f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));

		m_buttonNames[Totem]  = "button_1";
		m_buttonNames[Laser1] = "button_2";
		m_buttonNames[Laser2] = "button_3";

		for (int i = 0; i < ButtonCount; ++i) 
		{
			const char *button_name = m_buttonNames[i];
			if (Abathur::TAbathurEntity* pEntity = Abathur::GetEntityByName(button_name, m_sceneId))
			{
				/*
				if (Abathur::TVisualComponent *comp = pEntity->QueryComponent<Abathur::TVisualComponent>())
				{
					comp->visible = false;
				}
				*/
				if (CButtonComponent *comp = pEntity->QueryComponent<CButtonComponent>())
				{
					comp->SetMode(CButtonComponent::EMode::Texture);
				}
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

  void CMenu::PlayBGMMusic(const char *filename)
  {
    if (!m_bgmMusic.IsValid())
    {
      m_bgmMusic = Abathur::playAudio(filename, true);
    }
    else
    {
      m_nextBgmMusic = Abathur::playAudio(filename, true);
      Abathur::setVolumeAudio(m_nextBgmMusic, 0.0f);
      m_volumnFactor = 1.0f;
    }
  }

  void CMenu::SetTotemIconState(bool is_enabled)
  {
    m_awakeTotem = is_enabled;
  }

  void CMenu::UpdateMusicFade(float elapsed)
  {
    if (m_nextBgmMusic.IsValid()) {
      m_volumnFactor -= elapsed;
      if (m_volumnFactor > 0) 
      {
        Abathur::setVolumeAudio(m_bgmMusic, m_volumnFactor);
        Abathur::setVolumeAudio(m_nextBgmMusic, 1.0f - m_volumnFactor);
      }
      else 
      {
        m_bgmMusic = m_nextBgmMusic;
        Abathur::setVolumeAudio(m_bgmMusic, 1.0f);
        m_nextBgmMusic.Invalidate();
      }
    }
  }


}
