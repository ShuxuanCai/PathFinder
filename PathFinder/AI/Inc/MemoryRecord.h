#pragma once

#include <XEngine.h>

namespace AI
{
	struct MemoryRecord
	{
		uint64_t entityId = 0;
		X::Math::Vector2 lastSeenPosition;
		float lastRecordedTime = 0.0f;
		float importance = 0.0f;
	};

	using MemoryRecords = std::list<MemoryRecord>;
}