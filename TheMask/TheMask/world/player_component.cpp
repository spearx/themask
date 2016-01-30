#include "player_component.h"

#include "world/world.h"
#include "abathur_gui.h"
#include "utils/math/Angle3.h"

namespace World
{
	CPlayerComponent::CPlayerComponent()
		: m_inputDirection(MathUtils::ZERO)
		, m_alignment(Vector3(0.0f,0.0f,1.0f))
		, m_speed(8.0f)
    , m_yaw(0.0f)
	{
    m_matrix_original.SetIdentity();
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

			const float inputMagnitude = value.GetLength();

			Matrix44 viewMatrix; 
			cameraParameters.GetViewMatrix(viewMatrix);
			const Vector3 forward = viewMatrix.GetFront();
			const Vector3 left    = viewMatrix.GetLeft();
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
		}
		return false; 
	}

	void CPlayerComponent::Update(const Abathur::SUpdateContext& context)
	{
		ImGui::SliderFloat("Player Speed:", &m_speed, 0.0f,50.0f);

		if (Abathur::TPhysXComponent* pPhysicsComponent= entity->QueryComponent<Abathur::TPhysXComponent>())
		{
      //m_inputDirection
			pPhysicsComponent->MoveActor(m_inputDirection*m_speed*context.frameTime,context.frameTime);
      
		}
	}
}