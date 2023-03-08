#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class ArriveBehavior : public AI::SteeringBehavior
	{
	public:

		enum class Deceleration
		{
			fast = 1,
			normal,
			slow
		};

		Deceleration decel = Deceleration::slow;
		void SetDecel(Deceleration mDecel) { decel = mDecel; }
		
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}
