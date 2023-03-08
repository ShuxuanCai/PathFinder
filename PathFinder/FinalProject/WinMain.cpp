#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "TileMap.h"
#include "AICharacter.h"
#include "PickUps.h"
//#include "Enemy.h"
#include "EnemyManager.h"

AI::AIWorld aiWorld;

void GameInit()
{
	TileMap::Get().LoadMap("level.txt", "map.txt");
	PickUps::Get().Load();
	AICharacter::Get().Load();
	//EnemyManager::Get().Load();
}

bool GameLoop(float deltaTime)
{
	TileMap::Get().Render();

	PickUps::Get().Render();
	AICharacter::Get().Render();

	//EnemyManager::Get().Render();

	std::string currentScore = "Number: " + std::to_string(PickUps::Get().GetNumbers());
	X::DrawScreenText(currentScore.c_str(), 500.0f, 30.0f, 20.0f, X::Colors::White);

	if (PickUps::Get().GetNumbers() == 5)
	{
		X::DrawScreenText(" AI WIN ", 150, 70, 70, X::Colors::Red);
	}
	else if (AICharacter::Get().GetLose() == true)
	{
		X::DrawScreenText(" ENEMY WIN ", 70, 70, 70, X::Colors::Red);
	}
	else
	{
		AICharacter::Get().Update(deltaTime);
		//EnemyManager::Get().Update(deltaTime);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}