#pragma once

#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	template <typename Type>
	struct IntersectInfo
	{
		JMaths::Vector2D<Type> normal = JMaths::Vector2D<Type>::Zero;
		Type depth = 0.f;
		bool isIntersect = false;
	};
}
