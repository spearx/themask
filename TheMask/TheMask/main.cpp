// Game Jam 2016 Main - Barcelona - Ruben / Ramon / Arturo
//

#include "abathur_gui.h"

#include "menu/menu.h"
#include "world/world.h"

// tell the framework to output in the console
void sys_printf(const char* input)
{
	printf(input);
}

int main()
{
	Abathur::Init("The Incredible Mask", 1920, 1080, true);
	Abathur::SetLogCallback(Abathur::TLogCallback::SetFunction<&sys_printf>());
	Abathur::InitGui();

	Abathur::TDepthState depthState; 
	depthState.enable_culling = true;
	depthState.apply();

	World::CWorld& world = World::CWorld::Get();
	world.Init();
	
	Menu::CMenu menu;
	menu.Init();
	
	Abathur::Run();

	return 0;
}

