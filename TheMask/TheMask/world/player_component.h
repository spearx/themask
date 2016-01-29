#pragma once

#include "abathur.h"

namespace World
{
	class CPlayerComponent : public Abathur::TComponent, public Abathur::Input::InputListener
	{
	public:
		CPlayerComponent(){}

		virtual void Load(Json::Value &json_data) override;
		virtual void Destroy() override;

		virtual void Start() override;
		virtual void Stop() override;

	private:
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;
		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

	private: 


	};
}