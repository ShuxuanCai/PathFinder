#include "Mushroom.h"

Mushroom& Mushroom::Get()
{
	static Mushroom instance;
	return instance;
}

void Mushroom::Load()
{
	isEaten.resize(mushroomCount, true);

	for (int i = 0; i < mushroomCount; ++i)
	{
		X::Math::Vector2 minPosition = { 100.0f, 100.0f };
		X::Math::Vector2 maxPosition = { 1180.0f, 620.0f };
		mPosition.push_back(X::RandomVector2(minPosition, maxPosition));
	}

	mTextureId = X::LoadTexture("mushroom.png");
}

void Mushroom::Unload()
{
	mTextureId = 0;
}

void Mushroom::Render()
{
	for (int i = 0; i < mPosition.size(); ++i)
	{
		if(isEaten[i])
			X::DrawSprite(mTextureId, mPosition[i]);
		if (!isEaten[i])
			MushroomEaten(i);
	}
}