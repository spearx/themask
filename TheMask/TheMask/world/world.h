#pragma once

#include "abathur.h"

namespace World
{
	struct SRoom
	{
		SRoom( const Abathur::TEntityId _cameraId  = Abathur::TEntityId::s_invalid
		     , const Abathur::TEntityId _targetId  = Abathur::TEntityId::s_invalid
			 , const Abathur::TEntityId _triggerId = Abathur::TEntityId::s_invalid)
			: triggerId(_triggerId)
			, cameraId(_cameraId)
			, targetId(_targetId)
		{}

		Abathur::TEntityId triggerId;
		Abathur::TEntityId cameraId;
		Abathur::TEntityId targetId;
	};
	typedef std::vector<SRoom> TRooms;

	class CCamera
	{
	public:
		CCamera();

		void Init(const Abathur::TSceneId sceneId);

		void Update(const Abathur::SUpdateContext& context);

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

		void AddRoom(const SRoom& room);

		void SetRoomByTrigger(const Abathur::TEntityId triggerId);
		void SetNextRoom();
		void SetPreviousRoom();

	private: 
		SRoom GetCurrentRoom() const;

	private: 
		int32                     m_roomIndex;
		Abathur::TViewId          m_viewId;
		Abathur::CViewParameters  m_viewParameters;
		Abathur::CScopedUpdate    m_update;
		Abathur::TAbathurTexture* m_pRenderTarget;
		Vector3                   m_cameraPosition;
		Vector3                   m_cameraTarget;
		TRooms                    m_rooms;
	};

	class CWorld
	{
	public:
		static CWorld& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		inline CCamera& GetPlayerCamera() { return m_playerCamera; }
		inline CCamera& GetWitcherCamera() { return m_witcherCamera; }

		inline Abathur::TEntityId GetPlayerEntityId() const { return m_playerId; }

	private: 
		static CWorld& CreateInstance() { m_pInstance = new CWorld(); return *m_pInstance; }

		CWorld();

		void SpawnPlayer();
		void SetupCameras();

	private: 
		static CWorld*     m_pInstance;

		CCamera            m_playerCamera;
		CCamera            m_witcherCamera;
		Abathur::TSceneId  m_sceneId;
		Abathur::TEntityId m_playerId;
	};
}