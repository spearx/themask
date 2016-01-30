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
		Abathur::RegisterEntityComponent<CPlayerComponent>("comp_player");
		Abathur::InitPhysX(Vector3(0.0f, -9.8f, 0.0f));

		Abathur::AddPhysXPlane(Vector3(0.0f, 1.0f, 0.0f), 0.0f);

		m_sceneId = Abathur::LoadScene("data/collision_test/scenes/collision_test.scene");
		m_camera.Init(m_sceneId);

		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntityByName("Cylinder001", m_sceneId))
		{
			pPlayerEntity->AddComponent<CPlayerComponent>();
			m_playerId = pPlayerEntity->GetId();
		}

		Abathur::StartScene(m_sceneId); //TODO ~ ramonv ~ move this away in order to start the game on our demand instead of startup
	}

}