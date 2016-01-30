#pragma once

#include "abathur.h"

namespace Menu
{
	class CButtonComponent : public Abathur::TComponent, public Abathur::Input::InputListener
	{
	public:
		virtual void Load(Json::Value &json_data) override;
		virtual void Destroy() override;

		virtual void Start() override;
		virtual void Stop() override;

	private:
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;
		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

		bool IsMouseHover() const;
	};
}