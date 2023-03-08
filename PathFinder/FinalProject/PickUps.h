#pragma once

#include <XEngine.h>

class PickUps
{
public:
	static PickUps& Get();

public:
	void Load();
	void Unload();
	void Render();

	void PickUp();

	// Improvement: To support multiple pickups, Update PickUp and GetPosition to take
	// an index, then use the following function to compute distance and return the closest
	// pickup that's active.
	//int GetClosestPickupPosition(Vector2 characterPosition);

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	void SetPosition(X::Math::Vector2& position) { mPosition = position; }

	const int GetNumbers() const { return numberOfPickUps; }

private:
	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
	
	bool mActive = false;

	int numberOfPickUps = 0;
};