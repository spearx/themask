#pragma once

#include "abathur.h"

namespace World
{
	class CPlayerComponent : public Abathur::TComponent, public Abathur::Input::InputListener
	{
	private: 
		enum class EState
		{
			Inactive, 
			Active,
		};
	public:
		CPlayerComponent();

		virtual void Load(Json::Value &json_data) override;
		virtual void Destroy() override;

		virtual void Start() override;
		virtual void Stop() override;

	private:
		virtual bool OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent) override;
		virtual bool OnDirection(const Abathur::Input::EDirection direction, const Vector2& value) override;

		void Update(const Abathur::SUpdateContext& context);
    void UpdatePostPhysX(const Abathur::SUpdateContext& context);

	private: 
		EState                 m_state;
		Vector3                m_inputDirection;
		Vector3                m_alignment;
    Abathur::CScopedUpdate m_update;
    Abathur::CScopedUpdate m_update_post_physx;
		float                  m_speed;
    float                  m_yaw;
    Matrix33               m_matrix_original;
    std::string            m_room_name;
    Matrix44               m_viewMatrix;
    bool                   m_playerChangeRoom;
	};
}