#pragma once

#include "abathur.h"

namespace Menu
{
	class CInput : public Abathur::Input::InputListener
	{
	public:
		CInput();

	private:
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;
		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

	private:


	};

	class CCamera
	{
	public: 
		CCamera();

		void Init(const Abathur::TSceneId sceneId);
	private: 

		void Update(const Abathur::SUpdateContext& context);

	private: 
		Abathur::TViewId         m_viewId;
		Abathur::CViewParameters m_viewParameters;
		Abathur::CScopedUpdate   m_update;
		Vector3                  m_cameraPos;
		Vector3                  m_cameraTarget;
	};

	class CMenu
	{
	public:
		CMenu();

		void Init();

	private:
		CCamera                  m_camera;
		CInput                   m_input;
		Abathur::TSceneId        m_sceneId;
	};

}