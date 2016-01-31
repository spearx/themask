#include "offline_game.h"

#include "menu.h"
#include "button_component.h"

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
		const Vector4 needleHightlightColor = Vector4(0.65f, 0.06f, 0.06f, 1.0f);

		CMenu::Get().AddButton("Needle_1", Vector2(0.58f, 0.31f), Vector2(0.62f, 0.38f), Vector3(5.0f,  -3.0f, -1.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);
		CMenu::Get().AddButton("Needle_2", Vector2(0.85f, 0.04f), Vector2(0.89f, 0.11f), Vector3(-7.0f,-7.0f, 0.0f),   Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);
		CMenu::Get().AddButton("Needle_3", Vector2(0.51f, 0.14f), Vector2(0.54f, 0.21f), Vector3(6.5f,  -1.0f, 0.0f),  Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);
		CMenu::Get().AddButton("Needle_4", Vector2(0.82f, 0.25f), Vector2(0.86f, 0.34f), Vector3(-2.0f, -5.0f, 0.0f),  Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);
		CMenu::Get().AddButton("Needle_5", Vector2(0.80f, 0.37f), Vector2(0.83f, 0.44f), Vector3(-1.0f,  -8.0f, 0.0f), Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);
		CMenu::Get().AddButton("Needle_6", Vector2(0.50f, 0.35f), Vector2(0.52f, 0.40f), Vector3(6.0f,  -2.0f, 0.0f),  Vector4(0.321f, 0.352f, 0.415f, 1.0f), needleHightlightColor);

		m_buttons[First]  = "Needle_1";
		m_buttons[Second] = "Needle_2";
		m_buttons[Third] = "Needle_3";
		m_buttons[Fourth] = "Needle_4";
		m_buttons[Fifth] = "Needle_5";
		m_buttons[Sixth] = "Needle_6";

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
		m_update.Unregister();
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
		for (int i = 0u; i < Count; ++i)
		{
			CButtonComponent* pButton = GetButtonComponent(m_buttons[i]);
			if (pButton && pButton->JustPressed())
			{
				m_sequenceIndex = m_sequence[m_sequenceIndex] == i? MathUtils::ClampTpl(m_sequenceIndex + 1,0,static_cast<int>(SEQUENCE_LENGTH)) : 0;

				if (m_sequenceIndex == 0u)
				{
					m_state = EState::Failed;
          Abathur::playAudio("data/audio/bad_click.wav", false);
          printf("FAILURE~~~~\n");
					break;
				}
				else if (m_sequenceIndex >= SEQUENCE_LENGTH)
				{
					m_state = EState::Success;
					printf("AWESOME~~~~\n");
					break;
				}
        else  //Good click
        { 
          Abathur::playAudio("data/audio/good_click.wav", false);
        }

			}
		}
	}

}