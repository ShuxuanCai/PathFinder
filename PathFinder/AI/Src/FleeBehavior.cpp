#include "Precompiled.h"
#include "FleeBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 FleeBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.position - agent.destination;
	X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
	X::Math::Vector2 desiredVelocity = direction * agent.maxSpeed;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	return seekForce;
}
