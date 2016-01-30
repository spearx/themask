#pragma once

#include "abathur.h"

namespace World
{
	struct SRoom
	{
		SRoom( const Abathur::TEntityId _cameraId
		     , const Abathur::TEntityId _targetId
			 , const std::string &_triggerName)
			: triggerName(_triggerName)
			, cameraId(_cameraId)
			, targetId(_targetId)
		{}

    std::string        triggerName;
		Abathur::TEntityId cameraId;
		Abathur::TEntityId targetId;
	};
	typedef std::vector<SRoom> TRooms;

	class CCamera : public Abathur::Input::InputListener
	{
	public:
		CCamera();

		void Init(const Abathur::TSceneId sceneId);

		void Update(const Abathur::SUpdateContext& context);

		Abathur::CViewParameters& GetViewParameters() { return m_viewParameters; }

		/*
		void AddRoom(const SRoom& room);

		void SetRoomByTrigger(const std::string &triggerName);
		void SetNextRoom();
		void SetPreviousRoom();
		*/

		inline void SetTargetId(const Abathur::TEntityId input) { m_targetId = input;  }

	private: 
		//SRoom GetCurrentRoom() const;

		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

	private: 
		Abathur::TViewId          m_viewId;
		Abathur::CViewParameters  m_viewParameters;
		Abathur::CScopedUpdate    m_update;
		Abathur::TAbathurTexture* m_pRenderTarget;
		Abathur::TEntityId        m_targetId;
		Vector2                   m_orientation;
		Vector2                   m_input;
	};

	class CWorld
	{
	public:
		static CWorld& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		void Init();

		inline CCamera& GetPlayerCamera() { return m_playerCamera; }

		inline Abathur::TEntityId GetPlayerEntityId() const { return m_playerId; }
    
    bool getRoomInside(const Vector3 &pos, std::string &room_name);

	private: 
		static CWorld& CreateInstance() { m_pInstance = new CWorld(); return *m_pInstance; }

		CWorld();

		void SpawnPlayer();
		void SetupCameras();

	private: 
		static CWorld*     m_pInstance;

		CCamera            m_playerCamera;
		Abathur::TSceneId  m_sceneId;
		Abathur::TEntityId m_playerId;
	};
}