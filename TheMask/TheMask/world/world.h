#pragma once

#include "abathur.h"

namespace World
{
	class CCamera
	{
	public:
		CCamera();

		void Init(const Abathur::TSceneId sceneId);

		void Update(const Abathur::SUpdateContext& context);

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

	private: 
		Abathur::TViewId          m_viewId;
		Abathur::CViewParameters  m_viewParameters;
		Abathur::CScopedUpdate    m_update;
		Abathur::TAbathurTexture* m_pRenderTarget;
		Vector3                   m_cameraPosition;
		Vector3                   m_cameraTarget;
	};

	class CWorld
	{
	public:
		static CWorld& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		inline CCamera& GetPlayerCamera() { return m_playerCamera; }

		inline Abathur::TEntityId GetPlayerEntityId() const { return m_playerId; }

	private: 
		static CWorld& CreateInstance() { m_pInstance = new CWorld(); return *m_pInstance; }

		CWorld();

		void SpawnPlayer();

	private: 
		static CWorld*     m_pInstance;

		CCamera            m_playerCamera;
		Abathur::TSceneId  m_sceneId;
		Abathur::TEntityId m_playerId;
	};
}