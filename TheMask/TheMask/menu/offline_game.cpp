#include "offline_game.h"

#include "menu/menu.h"
#include "menu/button_component.h"

namespace Menu
{
	CButtonComponent* GetButtonComponent(const char* entityName)
	{
		return Abathur::GetEntityByName(entityName,CMenu::Get().GetSceneId())->QueryComponent<CButtonComponent>();
	}

	COfflineGame::COfflineGame()
		: m_sequenceIndex(0)
		, m_state(EState::Disabled)
	{}

	void COfflineGame::Init()
	{
		CMenu::Get().AddButton("button_1", Vector2(0.07f, 0.75f), Vector2(0.23f, 0.92f), Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		CMenu::Get().AddButton("button_2", Vector2(0.0f, 0.0f),   Vector2(0.1f, 0.1f),   Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		CMenu::Get().AddButton("button_3", Vector2(0.1f, 0.1f),   Vector2(0.2f, 0.2f),   Vector3(0.0f, 5.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f));

		m_buttons[First]  = "button_1";
		m_buttons[Second] = "button_2";
		m_buttons[Third]  = "button_3";

		//hack HARDCODED sequence
		m_sequence[0] = First; 
		m_sequence[1] = Third;
		m_sequence[2] = Second;
		m_sequence[3] = Third;
	}

	void COfflineGame::Enable()
	{
		for (const char* buttonName : m_buttons)
		{
			if (CButtonComponent* pButton = GetButtonComponent(buttonName))
			{
				pButton->SetEnable(true);
			}
		}
		m_sequenceIndex = 0u;
		m_state = EState::Running;

		m_update.Register(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PostPhysics,Abathur::EUpdateStage::Default),Abathur::TUpdateCallback::SetMethod<COfflineGame,&COfflineGame::Update>(this));
	}

	void COfflineGame::Disable()
	{
		for (const char* buttonName : m_buttons)
		{
			if (CButtonComponent* pButton = GetButtonComponent(buttonName))
			{
				pButton->SetEnable(false);
			}
		}
		m_sequenceIndex = 0u;
		m_state = EState::Disabled;
		m_update.Unregister();
	}

	void COfflineGame::Update(const Abathur::SUpdateContext& context)
	{
		printf("sequence %d\n", m_sequenceIndex);

		for (int i = 0u; i < Count; ++i)
		{
			CButtonComponent* pButton = GetButtonComponent(m_buttons[i]);
			if (pButton && pButton->JustPressed())
			{
				m_sequenceIndex = m_sequence[m_sequenceIndex] == i? MathUtils::ClampTpl(m_sequenceIndex + 1,0,static_cast<int>(SEQUENCE_LENGTH)) : 0;

				if (m_sequenceIndex == 0u)
				{
					m_state = EState::Failed;
					printf("FAILURE~~~~\n");
				}
				else if (m_sequenceIndex >= SEQUENCE_LENGTH)
				{
					m_state = EState::Success;
					printf("AWESOME~~~~\n");
				}

				break;
			}
		}
	}

}