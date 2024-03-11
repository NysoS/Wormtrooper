#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Physics/ColliderBase.h"

namespace JavaEngine
{
	class JE_API CircleCollider : public ColliderBase
	{
	public:
		explicit CircleCollider(float radius = 0, const JMaths::Vector2Df& pos = JMaths::Vector2Df::Zero, float angle = 0);
		~CircleCollider();

		float radius;
	};
}
