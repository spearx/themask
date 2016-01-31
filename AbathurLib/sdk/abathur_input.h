#pragma once

#include "utils/math/Math.h"

namespace Abathur
{
	namespace Input
	{
		enum class EDevice
		{
			Mouse, 
			Keyboard, 
			Gamepad,
			Unknown,
		};

		enum class EButton
		{
			//Mouse 
			MOUSE_BEGIN,
			MouseLeft = MOUSE_BEGIN,
			MouseMiddle,
			MouseRight,
			
			MouseUnknown,
			MOUSE_END = MouseUnknown,

			//Keybaord
			KEYBOARD_BEGIN, 
			KeyboardUp = KEYBOARD_BEGIN,
			KeyboardDown,
			KeyboardLeft,
			KeyboardRight,

			KeyboardW,
			KeyboardA,
			KeyboardS,
			KeyboardD,

			KeyboardUnknown,
			KEYBOARD_END = KeyboardUnknown,

			//Gamepad
			GAMEPAD_BEGIN, 
			GamepadA = GAMEPAD_BEGIN, 
			GamepadB, 
			GamepadX, 
			GamepadY, 
			GamepadUp, 
			GamepadDown, 
			GamepadLeft, 
			GamepadRight, 
			GamepadLB, 
			GamepadRB, 
			GamepadThumbLeft, 
			GamepadThumbRight, 
			GamepadStart, 
			GamepadBack,

			GamepadUnknown,
			GAMEPAD_END = GamepadUnknown,
		};

		enum class EButtonEvent
		{
			Unknown = 0,
			Press,
			Release,
		};

		enum class EDirection
		{
			MouseMove,
			MouseWheel,
			KeyboardArrows,
			KeyboardWASD,
			GamepadLeft,
			GamepadRight,
		};

		enum class EAnalog
		{
			GamepadTriggerLeft, 
			GamepadTriggerRight,
		};

		struct InputListener
		{
			InputListener();
			~InputListener();

			void Register();
			void Unregister();

			virtual bool OnButton(const EButton button, const EButtonEvent buttonEvent) { return false; }
			virtual bool OnDirection(const EDirection direction, const Vector2& value) { return false; }
			virtual bool OnAnalog(const EAnalog analog, const float value) { return false; }
		};

		EDevice GetDevice(const EButton button); 
		EDevice GetDevice(const EDirection direction);
		EDevice GetDevice(const EAnalog analog);

		Vector2 GetMousePosition(); 

		void SetGamepadStickDeadZone(const float threshold);
	}
}