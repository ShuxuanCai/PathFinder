#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	// 1) Apply random jitter
	localWanderTarget.x += X::RandomFloat(-wanderJitter, wanderJitter);
	localWanderTarget.y += X::RandomFloat(-wanderJitter, wanderJitter);

	// 2) Swap target to the wander circle
	localWanderTarget = X::Math::Normalize(localWanderTarget) * wanderRadius;

	// 3) Project target in front of agent
	X::Math::Vector2 localSeekTarget = localWanderTarget;
	localSeekTarget.y += wanderDistance;

	// 4) Transform into world space
	X::Math::Matrix3 worldMatrix = agent.WorldMatrix();
	X::Math::Vector2 worldSeekTarget = X::Math::TransformCoord(localSeekTarget, worldMatrix);

	// 5) Seek to target
	X::Math::Vector2 posToGoal = worldSeekTarget - agent.position;
	X::Math::Vector2 direction = X::Math::Normalize(posToGoal);
	X::Math::Vector2 desiredVelocity = direction * agent.maxSpeed;
	X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
	
	// Debug draw
	X::Math::Vector2 localWanderCenter(0.0f, wanderDistance);
	X::Math::Vector2 worldWanderCenter = X::Math::TransformCoord(localWanderCenter, worldMatrix);
	X::DrawScreenCircle(worldWanderCenter, wanderRadius, X::Colors::Green);
	X::DrawScreenLine(agent.position, worldSeekTarget, X::Colors::Yellow);
	X::DrawScreenCircle(worldSeekTarget, 5.0f, X::Colors::Red);

	return seekForce;
}
