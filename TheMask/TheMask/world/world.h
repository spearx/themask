#pragma once

#include "abathur.h"

namespace World
{
	/*
	class CPlayer
	{

	public: 
		CPlayer();
		void Init();
	};
	*/
	class CCamera
	{
	public:
		//CCamera(const CWorld& worldRef);

		void Init(const Abathur::TSceneId sceneId);

		void Update(const Abathur::SUpdateContext& context);

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

	private: 
		Abathur::TViewId          m_viewId;
		Abathur::CViewParameters  m_viewParameters;
		Abathur::CScopedUpdate    m_update;
		Abathur::TAbathurTexture* m_pRenderTarget;
	};

	class CWorld
	{
	public:
		static CWorld& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		inline CCamera& GetPlayerCamera() { return m_camera; }

	private: 
		static CWorld& CreateInstance() { m_pInstance = new CWorld(); return *m_pInstance; }

		CWorld();

	private: 
		static CWorld*     m_pInstance;

		CCamera            m_camera;
		Abathur::TSceneId  m_sceneId; 
		Abathur::TEntityId m_playerId;
	};
}