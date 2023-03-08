#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class WanderBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		X::Math::Vector2 localWanderTarget = X::Math::Vector2::YAxis();
		float wanderJitter = 1.0f;
		float wanderRadius = 50.0f;
		float wanderDistance = 100.0f;
	};
}