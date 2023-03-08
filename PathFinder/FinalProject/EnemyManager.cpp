#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager& EnemyManager::Get()
{
	static EnemyManager instance;
	return instance;
}

void EnemyManager::Load()
{
	for (int i = 0; i < 3; i++)
	{
		Enemy enemy;
		enemy.Load();
		//enemies.push_back(enemy);
	}
}

//void EnemyManager::Render()
//{
//	for (int i = 0; i < 3; i++)
//	{
//		Enemy enemy;
//		enemy.Render();
//		enemies.push_back(enemy);
//	}
//}
//
//void EnemyManager::Update(float deltaTime)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		Enemy enemy;
//		enemy.Update(deltaTime);
//		enemies.push_back(enemy);
//	}
//}

//
//std::vector<Enemy> EnemyManager::GetAllEneimes()
//{
//	return enemies;
//}