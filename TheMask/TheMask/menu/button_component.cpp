#include "button_component.h"

#include "menu/menu.h"

namespace Menu
{
	void CButtonComponent::Load(Json::Value &json_data)
	{
		//TODO ~ ramonv ~ to be implemented
	}

	void CButtonComponent::Destroy()
	{
	}

	void CButtonComponent::Start()
	{
		//TODO ~ ramonv ~ to be implemented
	}

	void CButtonComponent::Stop()
	{
		//TODO ~ ramonv ~ to be implemented
	}

	bool CButtonComponent::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		return false;
	}

	bool CButtonComponent::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		return false;
	}

	bool CButtonComponent::IsMouseHover() const
	{
		const Vector2 mousePosition = Abathur::Input::GetMousePosition();
		
		Abathur::CViewParameters& viewParameters = CMenu::Get().GetCamera().GetViewParameters();

		const Vector3 direction = viewParameters.Unproject(mousePosition);
		const Vector3 origin    = viewParameters.GetTransform().t;


		//PLACEHOLDER ~ TODO FINISH
		return false; 
	}
}