#pragma once

#include "abathur.h"

#include "utils/ease_interpolators.h"

namespace Menu
{
	class CButtonComponent : public Abathur::TComponent, public Abathur::Input::InputListener
	{
	public: 
		enum class EMode
		{
			Transform,
			Texture,
		};

	public:
		CButtonComponent();

		virtual void Load(Json::Value &json_data) override;
		virtual void Destroy() override;

		virtual void Start() override;
		virtual void Stop() override;

		bool IsEnabled() const;
		void SetEnable(const bool isEnabled);

		inline void SetArea(const Vector2& min, const Vector2& max) { m_areaMin = min; m_areaMax = max; }

		inline void SetHoverOffset(const Vector3& offset) { m_hoverOffsetTarget = offset; }
		inline void SetPressedColor(const Vector4& base_color, const Vector4& color) { m_baseColor = base_color; m_pressedColor = color; }

		inline void SetMode(const EMode input) { m_mode = input; }

		bool IsPressed(const bool input);
		bool JustPressed() const;
		bool JustReleased() const;

	private:
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;
		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

		bool IsMouseHover() const;
		void Update(const Abathur::SUpdateContext& context);

	private: 
		float   m_logicRadius; 

		Matrix44  m_initTransform;
		Vector3   m_hoverOffsetTarget;
		Vector4   m_pressedColor;
		Vector4   m_baseColor;

		Interpolations::InterpolableFixed<float, Interpolations::EaseOutBackInterpolation> m_hover;
		Interpolations::InterpolableFixed<float, Interpolations::EaseOutBackInterpolation> m_press;
		Interpolations::InterpolableFixed<float, Interpolations::EaseOutBackInterpolation> m_enable;

		Vector2 m_areaMin; 
		Vector2 m_areaMax;

		Abathur::CScopedUpdate m_update;

		EMode m_mode;

		bool m_isPressed; 
		bool m_isPrevPressed;

		bool    m_prevIsHover;
		bool    m_isHover;
		bool   m_isEnabled;
	};
}