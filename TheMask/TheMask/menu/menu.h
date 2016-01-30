#pragma once

#include "abathur.h"

//declaration forward
namespace World
{
	class CWorld;
}

namespace Menu
{
	class CCamera
	{
	public: 
		CCamera();

		void Init(const Abathur::TSceneId sceneId);

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

	private: 
		void Update(const Abathur::SUpdateContext& context);

	private: 
		Abathur::TViewId         m_viewId;
		Abathur::CViewParameters m_viewParameters;
		Abathur::CScopedUpdate   m_update;
		Vector3                  m_cameraPos;
		Vector3                  m_cameraTarget;
	};

	class CMenu : public Abathur::Input::InputListener
	{
	public:

		static CMenu& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		CCamera& GetCamera() { return m_camera; }

		Abathur::TEntityId AddButton(const char* entityName, const Vector2& areaMin, const Vector2& areaMax, const Vector3& hoverOffset, const Vector4& baseTintColor, const Vector4& tintColor);

	private: 
		static CMenu& CreateInstance() { m_pInstance = new CMenu();  return *m_pInstance; }

		CMenu();

		void PreRenderUpdate(const Abathur::SUpdateContext& context);
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;

	private:
		static CMenu*            m_pInstance;

		CCamera                  m_camera;
		Abathur::TSceneId        m_sceneId;
		Abathur::CScopedUpdate   m_preRenderUpdate;
	};

}