#include "world.h"

#include "player_component.h"

namespace World
{

  struct TRoomAABB {
    std::string name;
    Vector3 min;
    Vector3 max;
  };

  typedef std::vector<TRoomAABB> VRoomsAbbs;
  VRoomsAbbs rooms_aabbs;

	void testGrid(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
	{
		Abathur::renderGrid(8, 8, 2, 0xffffffff, 0xff00ffff);
		Abathur::renderAxis(2.0f);
	}

	CCamera::CCamera()
		: m_roomIndex(0u)
		, m_cameraPosition(MathUtils::ZERO)
		, m_cameraTarget(MathUtils::ZERO)
	{}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_pRenderTarget = Abathur::createRenderTarget(512,512);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(70.f), 0.1f, 10000.0f);
		m_viewParameters.SetRenderTarget(m_pRenderTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(1u));
		m_viewParameters.SetBeforeCallback(Abathur::TViewCallback::SetFunction<&testGrid>());
    
		m_cameraPosition = Vector3(5.0f);

		m_viewParameters.SetLookAt(m_cameraPosition, m_cameraTarget);
		Abathur::SetViewParameters(m_viewId, m_viewParameters);
    
		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::AddRoom(const SRoom& room)
	{
		m_rooms.push_back(room);
	}

	void CCamera::SetRoomByTrigger(const std::string &triggerName)
	{
		for (int32 i = 0u, sz = m_rooms.size(); i < sz; ++i)
		{
			if (triggerName == m_rooms[i].triggerName)
			{
				m_roomIndex = i;
				return;
			}
		}
	}

	void CCamera::SetNextRoom()
	{
		m_roomIndex = m_rooms.empty()? 0u : (m_roomIndex + 1) % m_rooms.size();
	}
	
	void CCamera::SetPreviousRoom()
	{
		m_roomIndex = m_rooms.empty() ? 0u : (m_roomIndex - 1 + m_rooms.size())%m_rooms.size();
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		const SRoom room = GetCurrentRoom();

		if (Abathur::TAbathurEntity* pCameraEntity = Abathur::GetEntity(room.cameraId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pCameraEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				m_cameraPosition = pLocationComponent->mtx.GetTranslation();
			}
		}

		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(room.targetId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pPlayerEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				m_cameraTarget = pLocationComponent->mtx.GetTranslation() + Vector3(0.0f,1.5f,0.0f);
			}
		}

		m_viewParameters.SetLookAt(m_cameraPosition, m_cameraTarget);
		Abathur::SetViewParameters(m_viewId, m_viewParameters);
	}

	SRoom CCamera::GetCurrentRoom() const
	{
		if (m_roomIndex < m_rooms.size())
		{
			return m_rooms[m_roomIndex];
		}

		return SRoom(Abathur::TEntityId::s_invalid, Abathur::TEntityId::s_invalid, "");
	}

  void onPhysXTrigger(Abathur::TEntityId entity_id, Abathur::ETriggerEvent event)
  {
    if (event == Abathur::ETriggerEvent::ON_ENTER_EVENT)
    {
      printf("onPhysXTrigger On Enter to Entity '%s'\n", Abathur::GetEntity(entity_id)->GetName());
    }
    else if (event == Abathur::ETriggerEvent::ON_EXIT_EVENT)
    {
      printf("onPhysXTrigger On Exit to Entity '%s'\n", Abathur::GetEntity(entity_id)->GetName());
    }
  }

	/////////////////////////////////////////////////////////////

	CWorld* CWorld::m_pInstance = nullptr;

	CWorld::CWorld(){}

  void addRoomWithMaxCoords(const std::string &name, const Vector3 &min, const Vector3 &max) 
  {
    TRoomAABB room;
    room.name = name;
    room.min = Vector3(min.x, min.z, -min.y);
    room.min.MinBound(Vector3(max.x, max.z, -max.y));
    room.max = Vector3(min.x, min.z, -min.y);
    room.max.MaxBound(Vector3(max.x, max.z, -max.y));
    rooms_aabbs.push_back(room);
  }

	void CWorld::Init()
	{
		//Init world
		Abathur::RegisterEntityComponent<CPlayerComponent>("comp_player");
		Abathur::InitPhysX(Vector3(0.0f, -9.8f, 0.0f));
		//Abathur::AddPhysXPlane(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
    Abathur::RegisterPhysXTrigger(Abathur::TPhysXTriggerCallback::SetFunction<&onPhysXTrigger>());

		//Load scene
		m_sceneId = Abathur::LoadScene("data/level0/scenes/level0.scene");

		//Spawn Player
		SpawnPlayer();

		//Cameras
		SetupCameras();

		Abathur::StartScene(m_sceneId); //TODO ~ ramonv ~ move this away in order to start the game on our demand instead of startup

    //Bounding Boxes Rooms
    addRoomWithMaxCoords("Room_1", Vector3(-7.41f, 4.977f, 0.0f), Vector3(7.41f, -4.977f, 0.0f));
    addRoomWithMaxCoords("Room_2", Vector3(-24.5f, 2.577f, 0.0f), Vector3(-8.0f, -4.977f, 0.0f));
    addRoomWithMaxCoords("Room_3", Vector3(-36.6f, 7.39f, 0.0f), Vector3(-26.6f, -7.35f, 0.0f));
    addRoomWithMaxCoords("Room_4", Vector3(-36.6f, 24.39f, 0.0f), Vector3(-26.6f, 9.35f, 0.0f));

    addRoomWithMaxCoords("Room_5", Vector3(-25.0f, 22.39f, 0.0f), Vector3(-1.2f, 12.0f, 0.0f));
    addRoomWithMaxCoords("Room_6", Vector3(0.5f, 22.39f, 0.0f), Vector3(30.0f, 12.0f, 0.0f));
    addRoomWithMaxCoords("Room_7", Vector3(9.0f, 6.0f, 0.0f), Vector3(20.6f, -6.0f, 0.0f));
  }

	void CWorld::SpawnPlayer()
	{
		Abathur::TAbathurEntity* pPlayerEntity = Abathur::SpawnEnitity("player", m_sceneId);
		ASSERT(pPlayerEntity);

		{
			Abathur::TLocationComponent* pComponent = pPlayerEntity->AddComponent<Abathur::TLocationComponent>();
			pComponent->mtx.SetIdentity();

			if (Abathur::TAbathurEntity* pSpawnPoint = Abathur::GetEntityByName("SpawnPoint", m_sceneId))
			{
				if (Abathur::TLocationComponent* pSpawnLocation = pSpawnPoint->QueryComponent<Abathur::TLocationComponent>())
				{
					pComponent->mtx = pSpawnLocation->mtx;
				}
			}
		}
		
		{
			Abathur::TVisualComponent* pComponent = pPlayerEntity->AddComponent<Abathur::TVisualComponent>();
			Abathur::loadTexture("data/textures/Mask_Diffuse.tga");
			Abathur::loadMaterials("data/scenes/mask.mat");
			pComponent->mesh     = Abathur::loadMesh("data/meshes/Mask.mesh");
			pComponent->material = Abathur::getMaterial("Material_Mask");
			ASSERT(pComponent->material);
		}

		{
			Abathur::TPhysXComponent* pComponent = pPlayerEntity->AddComponent<Abathur::TPhysXComponent>();
			pComponent->mBodyType        = Abathur::TPhysXComponent::EBodyType::CharacterController; 
			pComponent->mOffsetLoc       = Vector3(MathUtils::ZERO);
			pComponent->mHeight          = 0.1f; 
			pComponent->mRadius          = 0.37f;
			pComponent->mStaticFriction  = 0.5f; 
			pComponent->mDynamicFriction = 0.5f; 
			pComponent->mSlopeLimit      = 0.2f; 
			pComponent->mStepOffset      = 0.175f;
			pComponent->mMinDistance     = 0.01f;
			pComponent->mRestitution     = 0.001f;
		}

		pPlayerEntity->AddComponent<CPlayerComponent>();
		m_playerId = pPlayerEntity->GetId();
	}

	void CWorld::SetupCameras()
	{
		//Room 1
		{
			Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_1", m_sceneId);
			m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_1"));
      m_witcherCamera.AddRoom(SRoom(cameraId, Abathur::GetEntityIdByName("Camera_Room_1.Target", m_sceneId), ""));
		}

    //Room 2
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_2", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_2"));
    }

    //Room 3
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_3", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_3"));
    }

    //Room 4
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_4", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_4"));
    }

    //Room 5
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_5", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_4"));
    }

    //Room 6
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_6", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_6"));
    }

    //Room 7
    {
      Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_7", m_sceneId);
      m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, "Room_7"));
    }




    // ....
		
		m_playerCamera.Init(m_sceneId);
		m_witcherCamera.Init(m_sceneId);

	}

  bool CWorld::getRoomInside(const Vector3 &pos, std::string &room_name) {
    for (auto &r : rooms_aabbs)
    {
      if (r.min.x < pos.x && r.max.x > pos.x && r.min.z < pos.z && r.max.z > pos.z) {
        room_name = r.name;
        return true;
      }
    }
    return false;
  }


}

