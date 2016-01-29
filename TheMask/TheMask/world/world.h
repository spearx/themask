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

	private: 
		Abathur::TViewId          m_viewId;
		Abathur::CViewParameters  m_viewParameters;
		Abathur::CScopedUpdate    m_update;
		Abathur::TAbathurTexture* m_pRenderTarget;
	};

	class CWorld
	{
	public:
		CWorld();
		void Init();

	private: 
		CCamera           m_camera;
		Abathur::TSceneId m_sceneId; 
	};
}