#include "world.h"

#include "player_component.h"

namespace World
{
	/*
	void testGrid(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
	{
		Abathur::renderGrid(8, 8, 2, 0xffffffff, 0xff00ffff);
		Abathur::renderAxis(2.0f);
	}
	*/

	CCamera::CCamera()
		: m_cameraPosition(MathUtils::ZERO)
		, m_cameraTarget(MathUtils::ZERO)
	{}

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_pRenderTarget = Abathur::createRenderTarget(512,512);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(60.f), 0.1f, 1000.0f);
		m_viewParameters.SetRenderTarget(m_pRenderTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(1u));
		//m_viewParameters.SetBeforeCallback(Abathur::TViewCallback::SetFunction<&testGrid>());

		m_cameraPosition = Vector3(5.0f); 

		m_viewParameters.SetLookAt(m_cameraPosition, m_cameraTarget);
		Abathur::SetViewParameters(m_viewId, m_viewParameters);


		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntity(CWorld::Get().GetPlayerEntityId()))
		{
			if (Abathur::TLocationComponent* pLocationComponent = pPlayerEntity->QueryComponent<Abathur::TLocationComponent>())
			{
				m_cameraTarget = pLocationComponent->mtx.GetTranslation();
			}
		}

		m_viewParameters.SetLookAt(m_cameraPosition, m_cameraTarget);
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
		Abathur::AddPhysXPlane(Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		//Load scene
		m_sceneId = Abathur::LoadScene("data/collision_test/scenes/collision_test.scene");

		//Spawn Player
		SpawnPlayer();

		//Cameras
		m_playerCamera.Init(m_sceneId);

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
			pComponent->mesh     = Abathur::loadMesh("data/collision_test/meshes/Cylinder001.mesh");
			pComponent->material = Abathur::getMaterial("_09 - Default");
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

}