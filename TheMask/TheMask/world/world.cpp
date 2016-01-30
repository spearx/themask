#include "world.h"

#include "player_component.h"

namespace World
{
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

	void CCamera::SetRoomByTrigger(const Abathur::TEntityId triggerId)
	{
		for (int32 i = 0u, sz = m_rooms.size(); i < sz; ++i)
		{
			if (triggerId == m_rooms[i].triggerId)
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

		return SRoom();
	}

	/////////////////////////////////////////////////////////////

	CWorld* CWorld::m_pInstance = nullptr;

	CWorld::CWorld(){}

	void CWorld::Init()
	{
		//Init world
		Abathur::RegisterEntityComponent<CPlayerComponent>("comp_player");
		Abathur::InitPhysX(Vector3(0.0f, -9.8f, 0.0f));
		Abathur::AddPhysXPlane(Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		//Load scene
		m_sceneId = Abathur::LoadScene("data/level0/scenes/level0.scene");

		//Spawn Player
		SpawnPlayer();

		//Cameras
		SetupCameras();

		Abathur::StartScene(m_sceneId); //TODO ~ ramonv ~ move this away in order to start the game on our demand instead of startup
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
			const Abathur::TEntityId cameraId = Abathur::GetEntityIdByName("Camera_Room_1", m_sceneId);
			m_playerCamera.AddRoom(SRoom(cameraId, m_playerId, Abathur::GetEntityIdByName("Trigger_Room_1", m_sceneId)));
			m_witcherCamera.AddRoom(SRoom(cameraId, Abathur::GetEntityIdByName("Camera_Room_1.Target", m_sceneId)));
		}

		// ....
		
		m_playerCamera.Init(m_sceneId);
		m_witcherCamera.Init(m_sceneId);

	}

}