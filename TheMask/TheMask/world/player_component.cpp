#include "player_component.h"

namespace World
{
	void CPlayerComponent::Load(Json::Value &json_data)
	{
		//TODO ~ ramonv ~ 
	}

	void CPlayerComponent::Destroy()
	{
		//TODO ~ ramonv ~ 
	}

	void CPlayerComponent::Start()
	{
		//TODO ~ ramonv ~ 
	}

	void CPlayerComponent::Stop()
	{
		//TODO ~ ramonv ~ 
	}

	bool CPlayerComponent::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		//TODO ~ ramonv ~ player controller
		return false; 
	}

	bool CPlayerComponent::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		//TODO ~ ramonv ~ player movement
		return false; 
	}
}