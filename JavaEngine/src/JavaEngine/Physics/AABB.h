#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{

	template <typename Type>
	struct AABB
	{
		JMaths::Vector2D<Type> min;
		JMaths::Vector2D<Type> max;

		AABB(const JMaths::Vector2D<Type>& _min, const JMaths::Vector2D<Type>& _max);
		AABB(const Type& _minX, const Type& _minY, const Type& _maxX, const Type& _maxY);
	};

	template <typename Type>
	AABB<Type>::AABB(const JMaths::Vector2D<Type>& _min, const JMaths::Vector2D<Type>& _max)
		: min(_min), max(_max)
	{
	}

	template <typename Type>
	AABB<Type>::AABB(const Type& _minX, const Type& _minY, const Type& _maxX, const Type& _maxY)
		: min(JMaths::Vector2D<Type>(_minX, _minY)), max(JMaths::Vector2D<Type>(_maxX, _maxY))
	{
	}
}
