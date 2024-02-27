#pragma once

#include "JavaEngine/Core/Math/VectorProjection.h"
#include "JavaEngine/Physics/IntersectInfo.h"
#include "JavaEngine/Physics/CircleCollider.h"
#include "JavaEngine/Physics/PolygonCollider.h"

template <typename Type>
Type FindClosePointOnPolygon(const JMaths::Vector2D<Type>& _circleCenter,
	const std::vector<JMaths::Vector2D<Type>>& _vertices)
{
	Type result = -1.f;
	Type minDistance = std::numeric_limits<Type>::max();

	for (int i = 0; i < _vertices.size(); i++)
	{
		JMaths::Vector2D<Type> vertices = _vertices[i];
		Type distance = JMaths::Vector2D<Type>::Distance(vertices, _circleCenter);

		if (distance < minDistance)
		{
			minDistance = distance;
			result = i;
		}
	}

	return result;
}


namespace JPhysics
{
	template <typename Type>
	using Vec2D = JMaths::Vector2D<Type>;

	template <typename Type>
	using VecProjectionInfo = JMaths::VectorProjectionInfo<Type>;
	template <typename Type>
	using VecProjection = JMaths::VectorProjection<Type>;

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

				VecProjectionInfo<ValueType> firstPolygonProjectionInfo = VecProjection<ValueType>().polygonProjection(firstShapeVertices, axis);
				VecProjectionInfo<ValueType> secondPolygonProjectionInfo = VecProjection<ValueType>().polygonProjection(secondShapeVertices, axis);

				if (firstPolygonProjectionInfo.min >= secondPolygonProjectionInfo.max || secondPolygonProjectionInfo.min >= firstPolygonProjectionInfo.max)
				{
					return intersectInfo;
				}

				ValueType axisDepth = std::min(secondPolygonProjectionInfo.max - firstPolygonProjectionInfo.min, firstPolygonProjectionInfo.max - secondPolygonProjectionInfo.min);
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

				VecProjectionInfo<ValueType> firstPolygonProjectionInfo = VecProjection<ValueType>().polygonProjection(firstShapeVertices, axis);
				VecProjectionInfo<ValueType> secondPolygonProjectionInfo = VecProjection<ValueType>().polygonProjection(secondShapeVertices, axis);

				if (firstPolygonProjectionInfo.min >= secondPolygonProjectionInfo.max || secondPolygonProjectionInfo.min >= firstPolygonProjectionInfo.max)
				{
					return intersectInfo;
				}

				ValueType axisDepth = std::min(secondPolygonProjectionInfo.max - firstPolygonProjectionInfo.min, firstPolygonProjectionInfo.max - secondPolygonProjectionInfo.min);
				
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

	template <typename ValueType>
	struct ColliderIntersect<ValueType, JavaEngine::CircleCollider, JavaEngine::PolygonCollider>
	{
		IntersectInfo<ValueType> intersect(const Vec2D<ValueType>& circleCenter, const ValueType& circleRadius, const Vec2D<ValueType>& polygonCenter, const std::vector<Vec2D<ValueType>>& polygonVertices)
		{
			IntersectInfo<ValueType> intersectInfo{};
			intersectInfo.depth = std::numeric_limits<ValueType>::max();

			Vec2D<ValueType> axis = Vec2D<ValueType>::Zero;

			VecProjectionInfo<ValueType> polygonProjectionInfo{}; //= VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
			VecProjectionInfo<ValueType> circleProjectionInfo{}; //= VecProjection<ValueType>().circleProjection(circleCenter, circleRadius, axis);

			ValueType axisDepth = 0.f;

			for (int i = 0; i < polygonVertices.size(); ++i)
			{
				Vec2D<ValueType> currentVertices = polygonVertices[i];
				Vec2D<ValueType> nextVertices = polygonVertices[(i + 1) % polygonVertices.size()];

				Vec2D<ValueType> edge = nextVertices - currentVertices;
				axis = edge.GetLeftNormal();
				axis.normalilze();

				polygonProjectionInfo = VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
				circleProjectionInfo = VecProjection<ValueType>().circleProjection(circleCenter, circleRadius, axis);

				if (polygonProjectionInfo.min >= circleProjectionInfo.max || circleProjectionInfo.min >= polygonProjectionInfo.max)
				{
					return intersectInfo;
				}

				axisDepth = std::min(circleProjectionInfo.max - polygonProjectionInfo.min, polygonProjectionInfo.max - circleProjectionInfo.min);
				if (axisDepth < intersectInfo.depth)
				{
					intersectInfo.depth = axisDepth;
					intersectInfo.normal = axis;
				}
			}

			auto cpIndex = static_cast<int>(FindClosePointOnPolygon(circleCenter, polygonVertices));
			if (cpIndex <= -1)
			{
				return intersectInfo;
			}

			Vec2D<ValueType> cp = polygonVertices[cpIndex];
			axis = cp - circleCenter;
			axis.normalilze();

			polygonProjectionInfo = VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
			circleProjectionInfo = VecProjection<ValueType>().circleProjection(circleCenter, circleRadius, axis);

			if (polygonProjectionInfo.min >= circleProjectionInfo.max || circleProjectionInfo.min >= polygonProjectionInfo.max)
			{
				return intersectInfo;
			}

			axisDepth = std::min(circleProjectionInfo.max - polygonProjectionInfo.min, polygonProjectionInfo.max - circleProjectionInfo.max);
			if (axisDepth < intersectInfo.depth)
			{
				intersectInfo.depth = axisDepth;
				intersectInfo.normal = axis;
			}

			Vec2D<ValueType> direction = polygonCenter - circleCenter;
			if (direction.dotProduct(intersectInfo.normal) < 0.f)
			{
				intersectInfo.normal = Vec2D<ValueType>{ -intersectInfo.normal.x, -intersectInfo.normal.y };
			}

			intersectInfo.isIntersect = true;
			return intersectInfo;
		}
	};

	template <typename ValueType>
	struct ColliderIntersect<ValueType, JavaEngine::PolygonCollider, JavaEngine::CircleCollider>
	{
		IntersectInfo<ValueType> intersect(const Vec2D<ValueType>& circleCenter, const ValueType& circleRadius, const Vec2D<ValueType>& polygonCenter, const std::vector<Vec2D<ValueType>>& polygonVertices)
		{
			return ColliderIntersect<ValueType, JavaEngine::CircleCollider, JavaEngine::PolygonCollider>().intersect(circleCenter, circleRadius, polygonCenter, polygonVertices);
		}
	};
}
