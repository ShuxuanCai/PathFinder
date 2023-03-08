#include "Precompiled.h"
#include "HideBehavior.h"

#include "Agent.h"
#include "AIWorld.h"

using namespace AI;

X::Math::Vector2 HideBehavior::Calculate(Agent& agent)
{
	AIWorld::Obstacles obstacles = agent.world.GetObstacles();
	X::Math::Vector2 obstaclesPositions = { 300.0f, 300.0f };
	X::Math::Vector2 posToObstacles = obstaclesPositions - agent.target;
	X::Math::Vector2 direction = X::Math::Normalize(posToObstacles);
	X::Math::Vector2 desiredVelocity = (obstaclesPositions + direction * 100.0f * 2) * agent.maxSpeed;
	agent.destination = desiredVelocity;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	return seekForce;
}
