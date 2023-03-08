#pragma once

#include "Common.h"

namespace AI
{
	class Entity;
	class AIWorld;

	using Entities = std::vector<Entity*>;

	class Entity
	{
	public:
		// Special member functions are functions that the compiler
		// may create auto to you
		Entity(AIWorld& world, uint32_t typeId);
		virtual ~Entity();

		// = delete means not auto for you
		Entity(const Entity&) = delete;
		Entity operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity operator=(Entity&&) = delete;

		X::Math::Matrix3 WorldMatrix() const;

		AIWorld& world;
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		const uint64_t id;
		float radius = 1.0f;
	};
}