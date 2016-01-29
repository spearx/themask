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
	CCamera::CCamera(){}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(60.f), 0.1f, 1000.0f);
		m_viewParameters.SetLookAt(Vector3(5.0f), MathUtils::ZERO);
		m_viewParameters.SetPriority(Abathur::TViewPriority(100));
		Abathur::SetViewParameters(m_viewId, m_viewParameters);

		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		//TODO ~ ramonv ~ move the camera

		m_viewParameters.SetLookAt(Vector3(200.0f), MathUtils::ZERO);
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