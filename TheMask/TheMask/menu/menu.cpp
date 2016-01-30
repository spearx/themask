#include "menu.h"

#include "menu/button_component.h"
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
		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntityByName("Camera001",sceneId))
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
	{}

	void CMenu::Init()
	{
		Abathur::RegisterEntityComponent<CButtonComponent>("comp_player");

		//Load scene
		m_sceneId = Abathur::LoadScene("data/menu/scenes/themask_menu.scene");

		//Cameras
		m_camera.Init(m_sceneId);

		//Register Updates
		m_preRenderUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu,&CMenu::PreRenderUpdate>(this));
		m_preRenderUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));

		//Button Setup
		{
			const char* entityName = "button_1"; 
			if (Abathur::TAbathurEntity* pEntity = Abathur::GetEntityByName(entityName,m_sceneId))
			{
				CButtonComponent* pComponent = pEntity->AddComponent<CButtonComponent>();
				pComponent->SetArea(Vector2(0.07f, 0.75f), Vector2(0.23f,0.92f));
				pComponent->SetHoverOffset(Vector3(0.0f, 5.0f, 0.0f));
				pComponent->SetPressedColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}

		//Start Scene
		Abathur::StartScene(m_sceneId);
	}

	void CMenu::PreRenderUpdate(const Abathur::SUpdateContext& context)
	{
		//Map other scene viewport
		if (Abathur::TAbathurEntity* pCristalPlayer = Abathur::GetEntityByName("Ball_Up", m_sceneId))
		{
			if (Abathur::TVisualComponent* pVisualComponent = pCristalPlayer->QueryComponent<Abathur::TVisualComponent>())
			{
				Abathur::CViewParameters& viewParameters = World::CWorld::Get().GetPlayerCamera().GetViewParameters(); 
				Abathur::setMaterialParam(pVisualComponent->material, "diffuse", viewParameters.GetRenderTarget());
			}
		}
	}

	bool CMenu::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		//TODO ~ ramonv ~ Start game event catch here
		//printf("Button: %d - event %d\n", button, buttonEvent);
		return false;
	}
}
