#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 ArriveBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 posToGoal = agent.destination - agent.position;
	double dist = X::Math::Magnitude(posToGoal);
	if (dist > 0)
	{
		const double DecelTweaker = 1.0;
		double speed = dist / ((double)decel * DecelTweaker);
		speed = X::Math::Min(speed, (double)agent.maxSpeed);
		X::Math::Vector2 DesiredVelocity = posToGoal * speed / dist;
		return (DesiredVelocity - agent.velocity);
	}
	return X::Math::Vector2();
}
