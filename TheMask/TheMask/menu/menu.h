#pragma once

#include "abathur.h"

#include "offline_game.h"

#include "utils/ease_interpolators.h"

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

		void Start();
		void Stop();

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

	private: 
		void Update(const Abathur::SUpdateContext& context);

	private: 
		Abathur::TViewId         m_viewId;
		Abathur::CViewParameters m_viewParameters;
		Abathur::CScopedUpdate   m_update;

		Interpolations::InterpolableFixed<Vector3, Interpolations::EaseInOutCubicInterpolation> m_camPos;
		Interpolations::InterpolableFixed<Vector3, Interpolations::EaseInOutCubicInterpolation> m_camTarget;
		Interpolations::InterpolableFixed<float,   Interpolations::EaseInOutCubicInterpolation> m_fov;

		Vector3                  m_cameraPos;
		Vector3                  m_cameraTarget;
		float                    m_totalTime;
	};

	class CMenu : public Abathur::Input::InputListener
	{
	public:

		enum EButton
		{
			Totem, 
			Laser1, 
			Laser2,
			ButtonCount
		};

		enum class EState
		{
			Intro = 0, 
			Playing, 
			Success,
			Failed
		};

	public:
		static CMenu& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		Abathur::TSceneId GetSceneId() const { return m_sceneId; }

		bool IsButtonEnabled(const EButton button) const;
		void EnableButton(const EButton button);

		CCamera& GetCamera() { return m_camera; }
		COfflineGame& GetOfflineGame() { return m_offlineGame; }

		Abathur::TEntityId AddButton(const char* entityName, const Vector2& areaMin, const Vector2& areaMax, const Vector3& hoverOffset, const Vector4& baseTintColor, const Vector4& tintColor);

	private: 
		static CMenu& CreateInstance() { m_pInstance = new CMenu();  return *m_pInstance; }

		void SetState(const EState newState);

		CMenu();

		void PreRenderUpdate(const Abathur::SUpdateContext& context);
		void LogicUpdate(const Abathur::SUpdateContext& context);
		void InitButtons();
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;

	private:
		static CMenu*            m_pInstance;

		Interpolations::InterpolableFixed<float, Interpolations::EaseInOutCubicInterpolation> m_introThreshold;

		COfflineGame             m_offlineGame;
		CCamera                  m_camera;
		Abathur::TSceneId        m_sceneId;
		Abathur::CScopedUpdate   m_preRenderUpdate;
		Abathur::CScopedUpdate   m_logicUpdate;
		EState                   m_state;

		const char*              m_buttonNames[ButtonCount];
	};

}