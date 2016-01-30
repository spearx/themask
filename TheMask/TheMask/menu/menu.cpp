#include "menu.h"

#include "world/world.h"

namespace Menu
{
	CInput::CInput(){}

	bool CInput::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		//printf("Button: %d - event %d\n", button, buttonEvent);
		return false; 
	}

	bool CInput::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		//printf("Dir: %d - value %.2f %.2f\n", direction, value.x, value.y);
		const Vector2 mousePosition = Abathur::Input::GetMousePosition();
		//printf("Mouse Position: %.2f %.2f\n", mousePosition.x, mousePosition.y);

		return false;
	}

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

		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntityByName("Camera001.target", sceneId))
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
	}

	////////////////////////////////////////////////////////////////////////////

	CMenu::CMenu()
	{}

	void CMenu::Init()
	{
		//Load scene
		m_sceneId = Abathur::LoadScene("data/menu/scenes/themask_menu.scene");

		//Cameras
		m_camera.Init(m_sceneId);

		//Input
		//TODO ~ ramonv ~ to be implemented ( mouse clicks and buttons ) 
		
		//Register Updates
		m_preRenderUpdate.SetCallback(Abathur::TUpdateCallback::SetMethod<CMenu,&CMenu::PreRenderUpdate>(this));
		m_preRenderUpdate.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));

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
}