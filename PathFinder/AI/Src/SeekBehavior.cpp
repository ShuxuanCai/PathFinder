#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeekBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.destination - agent.position;
	X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
	X::Math::Vector2 desiredVelocity = direction * agent.maxSpeed;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	return seekForce;
}
