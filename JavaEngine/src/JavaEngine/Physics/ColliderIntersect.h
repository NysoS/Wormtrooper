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

template <typename TypeProjectCircle>
void ProjectCircle(const JMaths::Vector2D<TypeProjectCircle>& _center, const TypeProjectCircle& _radius, 
	const JMaths::Vector2D<TypeProjectCircle>& _axis, TypeProjectCircle& _min, TypeProjectCircle& _max)
{
	JMaths::Vector2D<TypeProjectCircle> axis = _axis;
	JMaths::Vector2D<TypeProjectCircle> direction = _axis.getNormarlized();
	JMaths::Vector2D<TypeProjectCircle> radiusDirection = direction * _radius;

	JMaths::Vector2D<TypeProjectCircle> pA = _center - radiusDirection;
	JMaths::Vector2D<TypeProjectCircle> pB = _center + radiusDirection;

	_min = axis.dotProduct(pA);
	_max = axis.dotProduct(pB);

	if (_min > _max)
	{
		TypeProjectCircle temp = _min;
		_min = _max;
		_max = temp;
	}
}

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

	template <typename ValueType>
	struct ColliderIntersect<ValueType, JavaEngine::CircleCollider, JavaEngine::PolygonCollider>
	{
		IntersectInfo<ValueType> intersect(const Vec2D<ValueType>& circleCenter, const ValueType& circleRadius, const Vec2D<ValueType>& polygonCenter, const std::vector<Vec2D<ValueType>>& polygonVertices)
		{
			IntersectInfo<ValueType> intersectInfo{};
			intersectInfo.depth = std::numeric_limits<ValueType>::max();

			Vec2D<ValueType> axis = Vec2D<ValueType>::Zero;

			ValueType polygonMin;
			ValueType polygonMax;
			ValueType circleMin;
			ValueType circleMax;
			ValueType axisDepth = 0.f;

			for (int i = 0; i < polygonVertices.size(); ++i)
			{
				Vec2D<ValueType> currentVertices = polygonVertices[i];
				Vec2D<ValueType> nextVertices = polygonVertices[(i + 1) % polygonVertices.size()];

				Vec2D<ValueType> edge = nextVertices - currentVertices;
				axis = edge.GetLeftNormal();
				axis.normalilze();

				ProjectVertices(polygonVertices, axis, polygonMin, polygonMax);
				ProjectCircle(circleCenter, circleRadius, axis, circleMin, circleMax);

				if (polygonMin >= circleMax || circleMin >= polygonMax)
				{
					return intersectInfo;
				}

				axisDepth = std::min(circleMax - polygonMin, polygonMax - circleMin);
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

			ProjectVertices(polygonVertices, axis, polygonMin, polygonMax);
			ProjectCircle(circleCenter, circleRadius, axis, circleMin, circleMax);

			if (polygonMin >= circleMax || circleMin >= polygonMax)
			{
				return intersectInfo;
			}

			axisDepth = std::min(circleMax - polygonMin, polygonMax - circleMin);
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
