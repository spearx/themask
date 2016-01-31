// Abathur SDK  
#pragma once

#include "abathur_render.h"
#include "abathur_scene.h"
#include "abathur_input.h"
#include "abathur_update.h"
#include "abathur_audio.h"
#include "abathur_physics.h"

namespace Abathur 
{
	typedef CFunctionCaller1<const char *> TLogCallback;

	void Init(const char *title, int xres, int yres, bool fullscreen);
	void Run();
	void Stop();
  int  GetWidthApp();
  int  GetHeightApp();

	void SetLogCallback(TLogCallback callback);
};

