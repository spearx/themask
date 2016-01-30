#include "menu.h"


namespace Menu
{
	CInput::CInput(){}

	bool CInput::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		printf("Button: %d - event %d\n", button, buttonEvent);
		return false; 
	}

	bool CInput::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		printf("Dir: %d - value %.2f %.2f\n", direction, value.x, value.y);
		const Vector2 mousePosition = Abathur::Input::GetMousePosition();
		printf("Mouse Position: %.2f %.2f\n", mousePosition.x, mousePosition.y);

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
        //m_cameraTarget = pLocationComponent->mtx.GetFront() + m_cameraPos;
        /*Matrix34 mtx(pLocationComponent->mtx);
        Quat q(mtx);
        const Vector3 p = q * pLocationComponent->mtx.GetTranslation();
        m_cameraPos = Vector3(p.x, p.y, p.z);*/
      }
		}

		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntityByName("Camera001.Target", sceneId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pCameraEntity->QueryComponent<Abathur::TLocationComponent>())
			{       
        m_cameraTarget = pLocationComponent->mtx.GetTranslation();
        //Matrix34 mtx(pLocationComponent->mtx);
        //Quat q(mtx);
        //const Vector3 p = q * pLocationComponent->mtx.GetTranslation();
        //m_cameraTarget = Vector3(p.x, p.y, p.z);
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

	CMenu::CMenu()
	{}

	void CMenu::Init()
	{
		//Load scene
		m_sceneId = Abathur::LoadScene("data/menu/scenes/themask_menu.scene");

		//Cameras
		m_camera.Init(m_sceneId);

		//Input

		//Start Scene
		Abathur::StartScene(m_sceneId);
	}
}