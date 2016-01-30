#include "world.h"
#include "player_component.h"
#include "triggers.h"

#include "abathur_gui.h"

namespace World
{
  float gDistance = 5.0f;

  void OnTriggerEvent(const std::string &event_name, CTriggers::ETriggerEvent event_type) {
    if (event_type == CTriggers::ETriggerEvent::ON_ENTER) {
      printf("On Trigger Event %s ON ENTER\n", event_name.c_str());
      CWorld::Get().GetLasers().DisableTypeLaser(CLasers::ELaserType::RED_LASER, false);
    }
    else if (event_type == CTriggers::ETriggerEvent::ON_EXIT) {
      printf("On Trigger Event %s ON EXIT\n", event_name.c_str());

    }
  }

	void testGrid(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
	{
		/*
    Abathur::renderGrid(8, 8, 2, 0xffffffff, 0xff00ffff);
		Abathur::renderAxis(2.0f);
    */
    CWorld::Get().GetLasers().Render();
  }

	CCamera::CCamera()
	{}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_pRenderTarget = Abathur::createRenderTarget(1024,1024);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(70.f), 0.1f, 10000.0f);
		m_viewParameters.SetRenderTarget(m_pRenderTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(1u));
    m_viewParameters.SetBeforeCallback(Abathur::TViewCallback::SetFunction<&testGrid>());
    
		m_orientation = Vector2(MathUtils::ZERO);
		m_input = Vector2(MathUtils::ZERO);
		
		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
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

		Vector3 target(MathUtils::ZERO);

		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(m_targetId))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pPlayerEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				target = pLocationComponent->mtx.GetTranslation() + Vector3(0.0f, 1.5f, 0.0f);
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
	}

  void CWorld::RegisterTriggers() {
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Centinel_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Unlock_Totem");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Laser_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Unlock_Laser_1");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Button_Laser_B", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Unlock_Laser_2");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Cauldron", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 2.5f, "Interact_Cauldron");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_1", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_1");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_2", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_2");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_3", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_3");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_4", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_4");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_5", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_5");
    }
    {
      Abathur::TEntityId entity = Abathur::GetEntityIdByName("Item_6", m_sceneId);
      CTriggers::Get().RegisterTriggerSphere(entity, 1.0f, "Interact_Item_6");
    }
    CTriggers::Get().RegisterListenner(CTriggers::TTriggerEventCallback::SetFunction<&OnTriggerEvent>());
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

  }



}

