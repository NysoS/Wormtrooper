#pragma once

#include "RigidBody.h"
#include "JavaEngine/Core/Math/VectorProjection.h"
#include "JavaEngine/Physics/IntersectInfo.h"
#include "JavaEngine/Physics/CircleCollider.h"

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

	template <typename ValueType>
	struct ColliderIntersect
	{
		template <typename Lhs, typename Rhs>
		IntersectInfo<float> OnColliderIntersectCallback(Lhs&, Rhs&)
		{
			return IntersectInfo<float>{};
		}

		IntersectInfo<ValueType> OnCircleColliderIntersectCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			IntersectInfo<float> intersectInfo{};

			JavaEngine::CircleCollider& circleColliderLhs = dynamic_cast<JavaEngine::CircleCollider&>(lhs);
			JavaEngine::CircleCollider& circleColliderRhs = dynamic_cast<JavaEngine::CircleCollider&>(rhs);

			float distance = Vec2D<float>::Distance(circleColliderLhs.position, circleColliderRhs.position);
			float radius = circleColliderLhs.radius + circleColliderRhs.radius;

			if (distance >= radius)
			{
				return intersectInfo;
			}

			Vec2D<float> normal = circleColliderRhs.position - circleColliderLhs.position;
			normal.normalilze();

			intersectInfo.normal = normal;
			intersectInfo.depth = radius - distance;
			intersectInfo.isIntersect = true;

			return intersectInfo;
		}

		IntersectInfo<ValueType> OnPolygonColliderIntersectCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			IntersectInfo<ValueType> intersectInfo{};

			JavaEngine::PolygonCollider& lshPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(lhs);
			JavaEngine::PolygonCollider& rshPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(rhs);

			auto firstShapeVertices = lshPolygon.getTransformVertices();
			auto secondShapeVertices= rshPolygon.getTransformVertices();

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

			Vec2D<ValueType> direction = rshPolygon.position - lshPolygon.position;
			if (direction.dotProduct(intersectInfo.normal) < 0.f)
			{
				intersectInfo.normal = { -intersectInfo.normal.x, -intersectInfo.normal.y };
			}

			intersectInfo.isIntersect = true;
			return intersectInfo;
		}

		IntersectInfo<ValueType> OnCircleToPolygonColliderIntersectCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			IntersectInfo<ValueType> intersectInfo{};
			intersectInfo.depth = std::numeric_limits<ValueType>::max();

			JavaEngine::CircleCollider lshCircle = dynamic_cast<JavaEngine::CircleCollider&>(lhs);
			JavaEngine::PolygonCollider rshPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(rhs);

			Vec2D<ValueType> axis = Vec2D<ValueType>::Zero;

			VecProjectionInfo<ValueType> polygonProjectionInfo{}; //= VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
			VecProjectionInfo<ValueType> circleProjectionInfo{}; //= VecProjection<ValueType>().circleProjection(circleCenter, circleRadius, axis);

			ValueType axisDepth = 0.f;

			auto polygonVertices = rshPolygon.getTransformVertices();

			for (int i = 0; i < polygonVertices.size(); ++i)
			{
				Vec2D<ValueType> currentVertices = polygonVertices[i];
				Vec2D<ValueType> nextVertices = polygonVertices[(i + 1) % polygonVertices.size()];

				Vec2D<ValueType> edge = nextVertices - currentVertices;
				axis = edge.GetLeftNormal();
				axis.normalilze();

				polygonProjectionInfo = VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
				circleProjectionInfo = VecProjection<ValueType>().circleProjection(lshCircle.position, lshCircle.radius, axis);

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

			auto cpIndex = static_cast<int>(FindClosePointOnPolygon(lshCircle.position, polygonVertices));
			if (cpIndex <= -1)
			{
				return intersectInfo;
			}

			Vec2D<ValueType> cp = polygonVertices[cpIndex];
			axis = cp - lshCircle.position;
			axis.normalilze();

			polygonProjectionInfo = VecProjection<ValueType>().polygonProjection(polygonVertices, axis);
			circleProjectionInfo = VecProjection<ValueType>().circleProjection(lshCircle.position, lshCircle.radius, axis);

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

			Vec2D<ValueType> direction = lshCircle.position - rshPolygon.position;
			if (direction.dotProduct(intersectInfo.normal) < 0.f)
			{
				intersectInfo.normal = Vec2D<ValueType>{ -intersectInfo.normal.x, -intersectInfo.normal.y };
			}

			intersectInfo.isIntersect = true;
			return intersectInfo;
		}

		IntersectInfo<ValueType> OnPolygonToCircleColliderIntersectCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			return ColliderIntersect::OnCircleToPolygonColliderIntersectCallback(rhs, lhs);
		}
	};
}
