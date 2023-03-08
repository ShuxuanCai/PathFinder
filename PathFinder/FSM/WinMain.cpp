#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "Mushroom.h"
#include "Mario.h"

Mario mario;

void GameInit()
{
	Mushroom::Get().Load();
	mario.Initialize();
}

bool GameLoop(float deltaTime)
{
	Mushroom::Get().Render();
	mario.Render();

	mario.Update(deltaTime);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	Mushroom::Get().Unload();
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}