#pragma once

#include "IntersectInfo.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"

namespace JPhysics
{
	template <typename Type>
	using Vec2D = JMaths::Vector2D<Type>;

	template <typename ValueType, typename ShapeA, typename ShapeB = ShapeA>
	struct ShapeIntersect
	{
	};

	template <typename CircleShape, typename ValueType>
	struct ShapeIntersect<ValueType,CircleShape>
	{
		IntersectInfo<ValueType> intersect(
			const Vec2D<ValueType>& firstShapeCenter, const ValueType& firstShapeRadius,
			const Vec2D<ValueType>& secondShapeCenter, const ValueType& secondShapeRadius)
		{
			IntersectInfo<ValueType> intersectInfo{};

			ValueType distance = Vec2D<ValueType>::Distance(firstShapeCenter, secondShapeCenter);
			ValueType radius = firstShapeRadius + secondShapeRadius;

			if (distance >= radius)
			{
				return intersectInfo;
			}

			Vec2D<ValueType> normal = secondShapeCenter - firstShapeCenter;
			normal.normalilze();

			intersectInfo.normal = normal;
			intersectInfo.depth = radius - distance;
			intersectInfo.isIntersect = true;

			return intersectInfo;
		}
	};
}
