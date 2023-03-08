#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class HideBehavior : public AI::SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}