#pragma once

#include "abathur.h"

namespace Menu
{
	class COfflineGame
	{
	public: 
		enum class EState
		{
			Disabled,
			Running,
			Success,
			Failed,
		};

	private: 
		enum { SEQUENCE_LENGTH = 4};

		enum Buttons 
		{
			First = 0, 
			Second, 
			Third, 
			Fourth, 
			Fifth, 
			Sixth,

			Count
		};

	public:
		COfflineGame();

		void Init();
		void Enable();
		void Disable();

		inline EState GetState() const { return m_state; }

	private: 
		void Update(const Abathur::SUpdateContext& context);

	private: 
		const char* m_buttons[Buttons::Count];

		Abathur::CScopedUpdate m_update;

		Buttons m_sequence[SEQUENCE_LENGTH];
		int     m_sequenceIndex;
		EState  m_state;
	};
}