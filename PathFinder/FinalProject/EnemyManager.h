#pragma once

#include <AI.h>
#include <XEngine.h>

#include "Enemy.h"

class EnemyManager
{
public:
	static EnemyManager& Get();

public:
	using Enemies = std::vector<std::unique_ptr<Enemy>>;

	void Load();
	/*void Render();
	void Update(float deltaTime);*/

	const Enemies& GetAllEneimes() const { return enemies; }

private:
	Enemies enemies;

	// vector<Enemy> - erase will shuffle enmey (requires copying)
	// [  Enemy  ][  Enemy  ][  Enemy  ][  Enemy  ][  Enemy  ]
	// [_________][_________][_________][_________][_________]
	// [_________][_________][_________][_________][_________]
	// [_________][_________][_________][_________][_________]

	// vector<Enemy*> - erase will shuffle pointers (no copying required)
	// [  Enemy* ][  Enemy* ][  Enemy* ][  Enemy* ][  Enemy* ]
	//     |
	//     V
	// [  Enemy  ]
	// [_________]
	// [_________]
	// [_________]
};