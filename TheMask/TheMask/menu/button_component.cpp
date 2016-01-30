#include "button_component.h"

#include "menu/menu.h"

namespace Menu
{
	CButtonComponent::CButtonComponent()
		: m_logicRadius(1.0f)
		, m_areaMin(MathUtils::ZERO)
		, m_areaMax(MathUtils::ZERO)
		, m_initTransform(MathUtils::ZERO)
		, m_hoverOffsetTarget(MathUtils::ZERO)
		, m_pressedColor(MathUtils::ZERO)
		, m_prevIsHover(false)
		, m_isHover(false)
		, m_isPrevPressed(false)
		, m_isPressed(false)
		, m_isEnabled(true)
	{
		m_baseColor = Vector4(1.0f);
	}

	void CButtonComponent::Load(Json::Value &json_data)
	{
		//TODO ~ ramonv ~ to be implemented
	}

	void CButtonComponent::Destroy()
	{

	}

	void CButtonComponent::Start()
	{
		m_prevIsHover = false;
		m_isHover = false; 
		m_initTransform = entity->QueryComponent<Abathur::TLocationComponent>()->mtx.GetTranslation();
		m_color.Reset(m_baseColor);
		m_transform.Reset(m_initTransform);
		m_update.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default), Abathur::TUpdateCallback::SetMethod<CButtonComponent,&CButtonComponent::Update>(this));
	}

	void CButtonComponent::Stop()
	{
		m_update.Unregister();
	}

	bool CButtonComponent::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		if (button == Abathur::Input::EButton::MouseLeft && m_isHover)
		{
			m_isPressed = buttonEvent == Abathur::Input::EButtonEvent::Press ? m_isEnabled : false;
		}

		if (button == Abathur::Input::EButton::MouseRight )
		{
			SetEnable(false);
		}

		if (button == Abathur::Input::EButton::MouseMiddle )
		{
			SetEnable(true);
		}

		return false;
	}

	
	bool CButtonComponent::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		/*
		if (direction == Abathur::Input::EDirection::MouseMove)
		{
			printf("We are hoving %d!!!!\n", IsMouseHover());
		}
		*/
		return false;
	}

	void CButtonComponent::SetEnable(const bool isEnabled)
	{
		m_isEnabled = isEnabled;
	}
	
	bool CButtonComponent::IsPressed(const bool input)
	{
		return m_isPressed;
	}

	bool CButtonComponent::JustPressed() const
	{
		return m_isPressed && !m_isPrevPressed; 
	}

	bool CButtonComponent::JustReleased() const
	{
		return !m_isPressed && m_isPrevPressed;
	}

	void CButtonComponent::Update(const Abathur::SUpdateContext& context)
	{
		m_prevIsHover = m_isHover;
		m_isHover = m_isEnabled && IsMouseHover();

		if (!m_isEnabled)
		{
			m_isPressed = false;
		}

		if (!m_isPressed )
		{
			if (m_isHover && !m_prevIsHover)
			{
				m_transform.SetValue(m_initTransform+m_hoverOffsetTarget, 0.5f);
			}
			else if (!m_isHover && m_prevIsHover)
			{
				m_transform.SetValue(m_initTransform, 0.5f);
			}
		}
		else
		{
			m_isPressed = m_isHover;
		}

		if (JustPressed())
		{
			m_color.SetValue(m_pressedColor, 0.2f);
		}
		else if (JustReleased())
		{
			m_color.SetValue(m_baseColor, 0.2f);
		}

		m_isPrevPressed = m_isPressed;
		
		m_transform.Update(context.frameTime);
		m_color.Update(context.frameTime);

		entity->QueryComponent<Abathur::TLocationComponent>()->mtx.SetTranslation(m_transform.GetValue());

		Vector4 value = m_color.GetValue();

		Abathur::setMaterialParam(entity->QueryComponent<Abathur::TVisualComponent>()->material, "diffuse_color", const_cast<Vector4&>(m_color.GetValue()));
	
	}

	bool CButtonComponent::IsMouseHover() const
	{
		const Vector2 mousePosition = Abathur::Input::GetMousePosition();
		//printf("Normalized Position: %.2f %.2f\n", mousePosition.x, mousePosition.y);
		return mousePosition.x > m_areaMin.x && mousePosition.x < m_areaMax.x && mousePosition.y > m_areaMin.y && mousePosition.y < m_areaMax.y;
	}
}