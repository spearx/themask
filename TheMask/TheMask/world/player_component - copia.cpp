#include "player_component.h"

#include "world/world.h"
#include "world/triggers.h"
#include "abathur_gui.h"
#include "utils/math/Angle3.h"

namespace World
{
	CPlayerComponent::CPlayerComponent()
		: m_inputDirection(MathUtils::ZERO)
		, m_alignment(Vector3(0.0f,0.0f,1.0f))
		, m_speed(5.0f)
    , m_yaw(0.0f)
    , m_playerChangeRoom(false)
	{
    m_matrix_original.SetIdentity();
    m_viewMatrix.SetIdentity();
  }

	void CPlayerComponent::Load(Json::Value &json_data)
	{
		//TODO ~ ramonv ~ 

	}

	void CPlayerComponent::Destroy()
	{
		//TODO ~ ramonv ~ 
	}

	void CPlayerComponent::Start()
	{
		//TODO ~ ramonv ~ 
		m_state = EState::Active;
		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CPlayerComponent, &CPlayerComponent::Update>(this));
		m_update.Register();

    m_update_post_physx.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
    m_update_post_physx.SetCallback(Abathur::TUpdateCallback::SetMethod<CPlayerComponent, &CPlayerComponent::UpdatePostPhysX>(this));
    m_update_post_physx.Register();

    if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
    {
      m_matrix_original = Matrix33(pLocComponent->mtx);
    }
	}

	void CPlayerComponent::Stop()
	{
		//TODO ~ ramonv ~ 
		m_state = EState::Inactive; 
		m_inputDirection = MathUtils::ZERO;
		m_update.Unregister();
	}

	bool CPlayerComponent::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		//TODO ~ ramonv ~ player controller
		return false; 
	}

	bool CPlayerComponent::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		if (m_state != EState::Inactive && direction == Abathur::Input::EDirection::GamepadLeft)
		{
			Abathur::CViewParameters& cameraParameters = CWorld::Get().GetPlayerCamera().GetViewParameters();

			m_inputDirection = value;

			/*
			const float inputMagnitude = value.GetLength();
      if (!m_playerChangeRoom) {
        Abathur::CViewParameters& cameraParameters = CWorld::Get().GetPlayerCamera().GetViewParameters();
        cameraParameters.GetViewMatrix(m_viewMatrix);
      }
	  
			const Vector3 forward = m_viewMatrix.GetFront();
			const Vector3 left    = m_viewMatrix.GetLeft();
      //Vector3 left = Vector3(1.0f, 0.0f, 0.0f);
      //Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
			m_inputDirection = left*value.x + forward*value.y;
			m_inputDirection.y = 0.0f; 
			m_inputDirection.GetNormalizedSafe(MathUtils::ZERO);
			m_inputDirection *= inputMagnitude;
			
      if (m_inputDirection.GetLengthSquared() > 0.0f) 
      {
        m_yaw = atan2f(m_inputDirection.z, -m_inputDirection.x);
        if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
        {
          Matrix33 mtx;
          mtx.SetIdentity();
          Vector3 t = pLocComponent->mtx.GetTranslation();
          mtx.SetRotationY(m_yaw);
          pLocComponent->mtx = mtx * m_matrix_original;
          pLocComponent->mtx.SetTranslation(t);
        }
      }
	  */
		}
		return false; 
	}

	void CPlayerComponent::Update(const Abathur::SUpdateContext& context)
	{
		ImGui::SliderFloat("Player Speed:", &m_speed, 0.0f,50.0f);    
		/*
		const Vector3 forward = m_viewMatrix.GetFront();
		const Vector3 left    = m_viewMatrix.GetLeft();
		//Vector3 left = Vector3(1.0f, 0.0f, 0.0f);
		//Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
		const float inputMagnitude = m_inputDirection.GetLength();
		Vector3 moveDir = left*m_inputDirection.x + forward*m_inputDirection.y;
		moveDir.y = 0.0f;
		moveDir.GetNormalizedSafe(MathUtils::ZERO);
		moveDir *= inputMagnitude;

		if (Abathur::TPhysXComponent* pPhysicsComponent= entity->QueryComponent<Abathur::TPhysXComponent>())
		{
      //m_inputDirection
			pPhysicsComponent->MoveActor(moveDir*m_speed*context.frameTime,context.frameTime);
		}


		//alignment

		if (moveDir.GetLengthSquared() > 0.0f)
		{
			m_yaw = atan2f(moveDir.z, -moveDir.x);
			if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
			{
				Matrix33 mtx;
				mtx.SetIdentity();
				Vector3 t = pLocComponent->mtx.GetTranslation();
				mtx.SetRotationY(m_yaw);
				pLocComponent->mtx = mtx * m_matrix_original;
				pLocComponent->mtx.SetTranslation(t);
				/*
				std::string curr_room_name;
				bool inside = CWorld::Get().getRoomInside(t, curr_room_name);
				printf("Player pos x:'%1.3f',y:'%1.3f',z:'%1.3f'\n", t.x, t.y, t.z);

				if (inside && curr_room_name != m_room_name) {
					m_room_name = curr_room_name;
					printf("Enter Room '%s'\n", m_room_name.c_str());
					CWorld::Get().GetPlayerCamera().SetRoomByTrigger(m_room_name);
					m_playerChangeRoom = true;
				}
			}
    }
    */

	}

  void CPlayerComponent::UpdatePostPhysX(const Abathur::SUpdateContext& context)
  {    

    float len = m_inputDirection.GetLengthSquared();
    if (len < 0.01f )
    {
      //if (m_playerChangeRoom) {
      //  //Matrix44 viewMatrix;
      //  printf("We need view matrix next frame\n");
      //  m_playerChangeRoom = false;
      //}
    }
     else {
       if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
       {
         Matrix33 mtx;
         mtx.SetIdentity();
         Vector3 t = pLocComponent->mtx.GetTranslation();
         CTriggers::Get().SetPlayerPosition(t);
         //std::string curr_room_name;
         //bool inside = CWorld::Get().getRoomInside(t, curr_room_name);
         //printf("Player pos x:'%1.3f',y:'%1.3f',z:'%1.3f'\n", t.x, t.y, t.z);

         //if (inside && curr_room_name != m_room_name) {
         //  m_room_name = curr_room_name;
         //  printf("Enter Room '%s'\n", m_room_name.c_str());
         //  CWorld::Get().GetPlayerCamera().SetRoomByTrigger(m_room_name);
         //  m_playerChangeRoom = true;
         //}
       }
     }
  }
}