#include "world.h"

#include "player_component.h"

namespace World
{
	/*
	CPlayer::CPlayer() {}

	void CPlayer::Init() {}
	*/

	/////////////////////////////////////////////////////////////

	//CCamera::CCamera(){}
	/*
	void testGrid(const Abathur::TViewId viewId, const Abathur::CViewParameters& params)
	{
		Abathur::renderGrid(8, 8, 2, 0xffffffff, 0xff00ffff);
		Abathur::renderAxis(2.0f);
	}
	*/

	void CCamera::Init(const Abathur::TSceneId sceneId)
	{
		m_pRenderTarget = Abathur::createRenderTarget(512,512);

		m_viewId = Abathur::AddSceneView(sceneId);
		m_viewParameters.SetProjection(DEG2RAD(60.f), 0.1f, 1000.0f);
		m_viewParameters.SetRenderTarget(m_pRenderTarget);
		m_viewParameters.SetPriority(Abathur::TViewPriority(1u));
		//m_viewParameters.SetBeforeCallback(Abathur::TViewCallback::SetFunction<&testGrid>());

		m_viewParameters.SetLookAt(Vector3(5.0f), MathUtils::ZERO);

		Abathur::SetViewParameters(m_viewId, m_viewParameters);


		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CCamera, &CCamera::Update>(this));
		m_update.Register();
	}

	void CCamera::Update(const Abathur::SUpdateContext& context)
	{
		//hack 
		Matrix44 mtx = MathUtils::IDENTITY; 
		Abathur::setMatrix(Abathur::MATRIX_WORLD, &mtx);

		//TODO ~ ramonv ~ look at player
		m_viewParameters.SetLookAt(Vector3(5.0f),Vector3(0.0f,1.0f,0.0f));

		Abathur::SetViewParameters(m_viewId, m_viewParameters);
	}

	/////////////////////////////////////////////////////////////

	CWorld::CWorld(){}

	void CWorld::Init()
	{
		Abathur::RegisterEntityComponent<CPlayerComponent>("comp_player");
		Abathur::InitPhysX(Vector3(0.0f, -9.8f, 0.0f));

		m_sceneId = Abathur::LoadScene("data/collision_test/scenes/collision_test.scene");
		m_camera.Init(m_sceneId);

		if (Abathur::TAbathurEntity* pPlayerEntity = Abathur::GetEntityByName("mask", m_sceneId))
		{
			m_playerId = pPlayerEntity->GetId();
		}

		Abathur::StartScene(m_sceneId); //TODO ~ ramonv ~ move this away in order to start the game on our demand instead of startup
	}

}