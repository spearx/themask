#include "world.h"
#include "player_component.h"
#include "triggers.h"

#include "abathur_gui.h"

namespace World
{
  float gDistance = 5.0f;
  Abathur::TAbathurEntity* pTotemEntity = nullptr;
  Matrix44 matrixOriginal;

	CCamera::CCamera()
	{}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_pRenderTarget = Abathur::createRenderTarget(1024,1024);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(70.f), 0.1f, 10000.0f);
		m_viewParameters.SetRenderTarget(m_pRenderTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(1u));
    
		m_orientation = Vector2(0.0f,gfPI*0.1f);
		m_input = Vector2(MathUtils::ZERO);
		
		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();

    pTotemEntity = Abathur::GetEntityByName("Centinel_Head_1", sceneId);
    ASSERT(pTotemEntity);
    Abathur::TLocationComponent* pLocComponent = pTotemEntity->QueryComponent<Abathur::TLocationComponent>();
    matrixOriginal = pLocComponent->mtx;
    matrixOriginal.SetTranslation(Vector3(0.0f));

	}

	bool CCamera::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		if (direction == Abathur::Input::EDirection::GamepadRight)
		{
			m_input = value; 
		}
		return false;
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
    ImGui::SliderFloat("Camera Distance:", &gDistance, 0.0f, 50.0f);
    //static float rot_totem = 0.0f;
    ////rot_totem += 1.0f * context.frameTime;
    //bool changed = ImGui::SliderFloat("Rotation Totem:", &rot_totem, -2.0f, 2.0f);
    //if (changed) {
    //  Matrix33 mtx;
    //  mtx.SetIdentity();
    //  Abathur::TLocationComponent* pLocComponent = pTotemEntity->QueryComponent<Abathur::TLocationComponent>();
    //  mtx.SetRotationY(rot_totem);
    //  Vector3 loc = pLocComponent->mtx.GetTranslation();
    //  pLocComponent->mtx = mtx * matrixOriginal;
    //  pLocComponent->mtx.SetTranslation(loc);
    //}

		Vector3 target(MathUtils::ZERO);

		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(m_targetId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pPlayerEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				target = pLocationComponent->mtx.GetTranslation() + Vector3(0.0f, 0.5f, 0.0f);
			}
		}

		m_orientation += Vector2(-m_input.x,m_input.y)*context.frameTime*5.0f;
		m_orientation.y = MathUtils::ClampTpl(m_orientation.y, -gfPI*0.4f, gfPI*0.4f);

		Vector3 offset = Vector3(sinf( m_orientation.x ), 0.0f, cosf(m_orientation.x));
		offset *= cosf(m_orientation.y);
		offset.y = sinf(m_orientation.y);

		offset *= gDistance;

		m_viewParameters.SetLookAt(target + offset, target);
		Abathur::SetViewParameters(m_viewId, m_viewParameters);
	}
	
	/////////////////////////////////////////////////////////////

	CWorld* CWorld::m_pInstance = nullptr;

	CWorld::CWorld(){}

	void CWorld::Init()
	{
		//Init world
		Abathur::RegisterEntityComponent<CPlayerComponent>("comp_player");
		Abathur::InitPhysX(Vector3(0.0f, -9.8f, 0.0f));
		//Abathur::AddPhysXPlane(Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		//Load scene
		m_sceneId = Abathur::LoadScene("data/level0/scenes/level0.scene");

		//Spawn Player
		SpawnPlayer();

		//Cameras
		SetupCameras();

		Abathur::StartScene(m_sceneId);

    //Triggers
    RegisterTriggers();

    //Lasers
    RegisterLasers();

    //Centinels
    RegisterCentinels();
  }

  void CWorld::SetCentinelsSpeedFactor(float factor)
  {
    m_centinels.SetSpeedSpeed(factor);
  }

  void CWorld::AfterRenderCallback(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
  {
    /*
    Abathur::renderGrid(8, 8, 2, 0xffffffff, 0xff00ffff);
    Abathur::renderAxis(2.0f);
    */
    CWorld::Get().GetLasers().Render();
    Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(CWorld::Get().GetPlayerEntityId());
    ASSERT(pPlayerEntity);
    CPlayerComponent* pComponent = pPlayerEntity->AddComponent<CPlayerComponent>();
    ASSERT(pComponent);
    if (pComponent->m_currentInteraction != "")
    {
    }
  }

	void CWorld::SpawnPlayer()
	{
		Abathur::TAbathurEntity* pPlayerEntity = Abathur::SpawnEnitity("Player", m_sceneId);
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

		/*
		{
			Abathur::TVisualComponent* pComponent = pPlayerEntity->AddComponent<Abathur::TVisualComponent>();
			Abathur::loadTexture("data/textures/Mask_Diffuse.tga");
			Abathur::loadMaterials("data/scenes/mask.mat");
			pComponent->mesh     = Abathur::loadMesh("data/meshes/Mask.mesh");
			pComponent->material = Abathur::getMaterial("Material_Mask");
			ASSERT(pComponent->material);
		}
		*/

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

		{
			CPlayerComponent* pComponent = pPlayerEntity->AddComponent<CPlayerComponent>();
			pComponent->CreateChildEntities(m_sceneId);
		}

		m_playerId = pPlayerEntity->GetId();
	}

	void CWorld::SetupCameras()
	{
    m_playerCamera.Init(m_sceneId);
		m_playerCamera.SetTargetId(m_playerId);
    Abathur::CViewParameters& m_viewParameters = m_playerCamera.GetViewParameters();
    m_viewParameters.SetBeforeCallback(Abathur::TViewCallback::SetMethod<CWorld, &CWorld::AfterRenderCallback>(this));

	}

  void CWorld::RegisterTriggers() {
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Centinel_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Unlock_Totem");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Laser_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Unlock_Laser_1");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Laser_B", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Unlock_Laser_2");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Cauldron", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 2.5f, "Interact_Cauldron");
    }
    {

      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_1");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_2", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_2");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_3", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_3");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_4", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_4");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_5", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_5");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_6", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.6f, "Interact_Item_6");
    }
    {
      Vector3 min(-7.0f, 0.0f, -5.0f);
      Vector3 max(7.0f, 0.0f, 5.0f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_1");
    }
    {
      Vector3 min(-24.0f, 0.0f, -2.7f);
      Vector3 max(-9.0f, 0.0f, 5.0f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_2");
    }
    {
      Vector3 min(-36.0f, 0.0f, -8.0f);
      Vector3 max(-26.0f, 0.0f, 7.5f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_3");
    }
    {
      Vector3 min(-36.0f, 0.0f, -9.6f);
      Vector3 max(-26.0f, 0.0f, -25.0f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_4");
    }
    {
      Vector3 min(-24.0f, 0.0f, -22.8f);
      Vector3 max(-1.0f, 0.0f, -11.5f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_5");
    }
    {
      Vector3 min(0.0f, 0.0f, -22.8f);
      Vector3 max(31.0f, 0.0f, -11.5f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_6");
    }
    {
      Vector3 min(8.5f, 0.0f, -6.0f);
      Vector3 max(19.1f, 0.0f, 5.5f);
      CTriggers::Get().RegisterTriggerBox(min, max, "Room_7");
    }
    CTriggers::Get().RegisterListenner(CTriggers::TTriggerEventCallback::SetMethod<CWorld, &CWorld::OnTriggerEvent>(this));
  }
  
  void CWorld::RegisterLasers() {
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_001", m_sceneId);      
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_A002", m_sceneId), Abathur::GetEntityIdByName("Laser_A005", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_A001", m_sceneId), Abathur::GetEntityIdByName("Laser_A004", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_A", m_sceneId), Abathur::GetEntityIdByName("Laser_A003", m_sceneId));
    }
    
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_001", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_B", m_sceneId), Abathur::GetEntityIdByName("Laser_B004", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_B001", m_sceneId), Abathur::GetEntityIdByName("Laser_B003", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_B002", m_sceneId), Abathur::GetEntityIdByName("Laser_B005", m_sceneId));
    }

    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_002", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_A009", m_sceneId), Abathur::GetEntityIdByName("Laser_A007", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_A008", m_sceneId), Abathur::GetEntityIdByName("Laser_A006", m_sceneId));
    }

    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_002", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_B008", m_sceneId), Abathur::GetEntityIdByName("Laser_B007", m_sceneId));
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_B009", m_sceneId), Abathur::GetEntityIdByName("Laser_B006", m_sceneId));
    }

    //Room 6
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_003", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_011", m_sceneId), Abathur::GetEntityIdByName("Laser_011.Target", m_sceneId));
    }
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_003", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_012", m_sceneId), Abathur::GetEntityIdByName("Laser_012.Target", m_sceneId));
    }
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_004", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_013", m_sceneId), Abathur::GetEntityIdByName("Laser_013.Target", m_sceneId));
    }

    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_004", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_016", m_sceneId), Abathur::GetEntityIdByName("Laser_016.Target", m_sceneId));
    }
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_005", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_017", m_sceneId), Abathur::GetEntityIdByName("Laser_017.Target", m_sceneId));
    }
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_005", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_018", m_sceneId), Abathur::GetEntityIdByName("Laser_018.Target", m_sceneId));
    }

    //Room 7
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Red_006", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::RED_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_015", m_sceneId), Abathur::GetEntityIdByName("Laser_015.Target", m_sceneId));
    }
    {
      Abathur::TEntityId entity_collision = Abathur::GetEntityIdByName("Laser_Collision_Blue_006", m_sceneId);
      CLasers::TLaserData *data = m_lasers.RegistreTypeLaser(CLasers::ELaserType::BLUE_LASER, entity_collision);
      data->AddRayLaser(Abathur::GetEntityIdByName("Laser_014", m_sceneId), Abathur::GetEntityIdByName("Laser_014.Target", m_sceneId));
    }

  }

  void CWorld::OnTriggerEvent(const std::string &event_name, CTriggers::ETriggerEvent event_type)
  {
    if (event_type == CTriggers::ETriggerEvent::ON_ENTER)
      printf("On Trigger Event %s ON ENTER\n", event_name.c_str());
    else if (event_type == CTriggers::ETriggerEvent::ON_EXIT)
      printf("On Trigger Event %s ON EXIT\n", event_name.c_str());

    static bool first_time_caldero_room = true;
    if (event_name == "Room_5" && first_time_caldero_room) {
      first_time_caldero_room = false;
      Abathur::playAudio("data/audio/caldero_enter.wav");
    }

    if (event_name.find("Room_") == std::string::npos) {
      Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(CWorld::Get().GetPlayerEntityId());
      ASSERT(pPlayerEntity);
      CPlayerComponent* pComponent = pPlayerEntity->AddComponent<CPlayerComponent>();
      ASSERT(pComponent);
      pComponent->OnTriggerEvent(event_name, event_type);
      return;
    }

    if (event_type == CTriggers::ETriggerEvent::ON_ENTER)
    {
      m_currentRoomId = Abathur::GetEntityIdByName(event_name.c_str(), m_sceneId);
      m_centinels.SetCentinelsStateInRoom(event_name, CCentinels::EState::AWAKE);
    }
    else if (event_type == CTriggers::ETriggerEvent::ON_EXIT)
    {
      m_centinels.SetCentinelsStateInRoom(event_name, CCentinels::EState::SLEEPING);
    }
  }

  void CWorld::RegisterCentinels( ) {
    CCentinels::TCentinelsParams params;
    params.m_turnSpeed = 1.0f;
    params.m_timeFactorPlayer = 10.0f;

    {
      params.m_roomName = "Room_1";
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Centinel_Head_1", m_sceneId);
      m_centinels.RegisterCentinel(entity, params);
    }
    {
      params.m_roomName = "Room_4";
      params.m_turnSpeed = 1.0f;
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Centinel_Head_003", m_sceneId);
      m_centinels.RegisterCentinel(entity, params);
      params.m_turnSpeed = 1.5f;
      entity = Abathur::GetEntityIdByName("Centinel_Head_005", m_sceneId);
      m_centinels.RegisterCentinel(entity, params);
    }
    {
      params.m_roomName = "Room_6";
      params.m_turnSpeed = 1.0f;
      params.m_timeFactorPlayer = 20.0f;
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Centinel_Head_002", m_sceneId);
      m_centinels.RegisterCentinel(entity, params);
      params.m_turnSpeed = 1.5f;
      entity = Abathur::GetEntityIdByName("Centinel_Head_004", m_sceneId);
      m_centinels.RegisterCentinel(entity, params);
    }
  }

}

