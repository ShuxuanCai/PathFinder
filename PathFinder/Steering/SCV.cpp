#include "SCV.h"

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

SCV::SCV(AI::AIWorld& world)
	: AI::Agent(world, 0)
{

}

void SCV::Initialize()
{
	// Set agent attributes
	maxSpeed = 200.0f;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mFleeBehavior = mSteeringModule->AddBehavior<AI::FleeBehavior>();
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();


	for (size_t i = 0; i < mTextureIds.size(); ++i)
	{
		char name[256];
		sprintf_s(name, "scv_%02zu.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}
}

void SCV::Update(float deltaTime)
{
	// Apply tuning
	mWanderBehavior->wanderJitter = wanderJitter;
	mWanderBehavior->wanderRadius = wanderRadius;
	mWanderBehavior->wanderDistance = wanderDistance;

	auto force = mSteeringModule->Calculate();

	auto acceleration = force / mass;
	velocity += acceleration * deltaTime;

	// Make sure we don't go above the speed limit
	if (X::Math::MagnitudeSqr(velocity) >= X::Math::Sqr(maxSpeed))
		velocity = X::Math::Normalize(velocity) * maxSpeed;

	position += velocity * deltaTime;

	// If we have any movement at all, update the heading direction
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
		heading = X::Math::Normalize(velocity);

	// Screen wrapping
	auto screenWidth = X::GetScreenWidth();
	auto screenHeight = X::GetScreenHeight();
	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x >= screenWidth)
		position.x -= screenWidth;
	if (position.y < 0.0f)
		position.y += screenHeight;
	if (position.y >= screenHeight)
		position.y -= screenHeight;
}

void SCV::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi;					// 0 to 2Pi
	float percent = angle / X::Math::kTwoPi;									// 0 to 1
	int frame = (int)(percent * mTextureIds.size()) % mTextureIds.size();		// 0 to 15
	X::DrawSprite(mTextureIds[frame], position);
}

void SCV::SetDecel(AI::ArriveBehavior::Deceleration decel)
{
	if (decel == AI::ArriveBehavior::Deceleration::fast)
	{
		mArriveBehavior->SetDecel(AI::ArriveBehavior::Deceleration::fast);
	}

	if (decel == AI::ArriveBehavior::Deceleration::normal)
	{
		mArriveBehavior->SetDecel(AI::ArriveBehavior::Deceleration::normal);
	}

	if (decel == AI::ArriveBehavior::Deceleration::slow)
	{
		mArriveBehavior->SetDecel(AI::ArriveBehavior::Deceleration::slow);
	}
}
