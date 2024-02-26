#pragma once

#include "JavaEngine/Physics/IntersectInfo.h"
#include "JavaEngine/Physics/CircleCollider.h"
#include "JavaEngine/Physics/PolygonCollider.h"

template <typename Type>
void ProjectVertices(const std::vector<JMaths::Vector2D<Type>>& _vertices, const JMaths::Vector2D<Type>& _axis,
	Type& _min, Type& _max)
{
	_min = std::numeric_limits<Type>::max();
	_max = std::numeric_limits<Type>::min();

	for (int i = 0; i < _vertices.size(); ++i)
	{
		JMaths::Vector2D<Type> vertices = _vertices[i];
		Type projection = vertices.dotProduct(_axis);

		if (projection < _min)
		{
			_min = projection;
		}

		if (projection > _max)
		{
			_max = projection;
		}
	}
}

namespace JPhysics
{
	template <typename Type>
	using Vec2D = JMaths::Vector2D<Type>;

	template <typename ValueType, typename ShapeColliderA, typename ShapeColliderB = ShapeColliderA>
	struct ColliderIntersect
	{
	};

	template <typename ValueType>
	struct ColliderIntersect<ValueType, JavaEngine::CircleCollider>
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

	template <typename ValueType>
	struct ColliderIntersect<ValueType, JavaEngine::PolygonCollider>
	{
		IntersectInfo<ValueType> intersect(
			const Vec2D<ValueType>& firstShapeCenter, const std::vector<JMaths::Vector2D<ValueType>>& firstShapeVertices,
			const Vec2D<ValueType>& secondShapeCenter, const std::vector<JMaths::Vector2D<ValueType>>& secondShapeVertices)
		{
			IntersectInfo<ValueType> intersectInfo{};

			for (int firstShapeVerticesIndex = 0; firstShapeVerticesIndex < firstShapeVertices.size(); ++firstShapeVerticesIndex)
			{
				Vec2D<ValueType> currentVertices = firstShapeVertices[firstShapeVerticesIndex];
				Vec2D<ValueType> nextVertices = firstShapeVertices[(firstShapeVerticesIndex+1) % firstShapeVertices.size()];

				Vec2D<ValueType> edge = nextVertices - currentVertices;
				Vec2D<ValueType> axis = edge.normalilze();

				ValueType firstMin;
				ValueType firstMax;
				ValueType secondMin;
				ValueType secondMax;

				ProjectVertices(firstShapeVertices, axis, firstMin, firstMax);
				ProjectVertices(secondShapeVertices, axis, secondMin, secondMax);

				if (firstMin >= secondMax || secondMin >= firstMax)
				{
					return intersectInfo;
				}

				ValueType axisDepth = std::min(secondMax - firstMin, firstMax - secondMin);
				intersectInfo.depth = std::numeric_limits<ValueType>::max();
				if (axisDepth < intersectInfo.depth)
				{
					intersectInfo.depth = axisDepth;
					intersectInfo.normal = axis;
				}
			}

			for (int secondShapeVerticesIndex = 0; secondShapeVerticesIndex < secondShapeVertices.size(); ++secondShapeVerticesIndex)
			{
				Vec2D<ValueType> currentVertices = secondShapeVertices[secondShapeVerticesIndex];
				Vec2D<ValueType> nextVertices = secondShapeVertices[(secondShapeVerticesIndex + 1) % secondShapeVertices.size()];

				Vec2D<ValueType> edge = nextVertices - currentVertices;
				Vec2D<ValueType> axis = edge.normalilze();

				ValueType firstMin;
				ValueType firstMax;
				ValueType secondMin;
				ValueType secondMax;

				ProjectVertices(firstShapeVertices, axis, firstMin, firstMax);
				ProjectVertices(secondShapeVertices, axis, secondMin, secondMax);

				if (firstMin >= secondMax || secondMin >= firstMax)
				{
					return intersectInfo;
				}

				ValueType axisDepth = std::min(secondMax - firstMin, firstMax - secondMin);
				
				if (axisDepth < intersectInfo.depth)
				{
					intersectInfo.depth = axisDepth;
					intersectInfo.normal = axis;
				}
			}

			Vec2D<ValueType> direction = secondShapeCenter - firstShapeCenter;
			if (direction.dotProduct(intersectInfo.normal) < 0.f)
			{
				intersectInfo.normal = { -intersectInfo.normal.x, -intersectInfo.normal.y };
			}

			intersectInfo.isIntersect = true;
			return intersectInfo;
		}
	};
}
