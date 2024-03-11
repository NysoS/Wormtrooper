#pragma once

#include "jepch.h"
#include "ColliderIntersect.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	template<typename Type>
	class JE_API Collisions
	{
	public:
		static void PointSegmentDistance(
			const JMaths::Vector2D<Type>& _p, const JMaths::Vector2D<Type>& _a, const JMaths::Vector2D<Type>& _b,
			Type& _distanceSqrt, JMaths::Vector2D<Type>& _contact);

		static bool IntersectAABB(const AABB<Type>& _bodyA, const AABB<Type>& _bodyB);

		static JMaths::Vector2D<Type> FindArithmeticMean(const std::vector<JMaths::Vector2D<Type>>& _vertices);
		static Type FindClosePointOnPolygon(const JMaths::Vector2D<Type>& _circleCenter, const std::vector<JMaths::Vector2D<Type>>& _vertices);
	};

	template <typename Type>
	void Collisions<Type>::PointSegmentDistance(const JMaths::Vector2D<Type>& _p, const JMaths::Vector2D<Type>& _a,
		const JMaths::Vector2D<Type>& _b, Type& _distanceSqrt, JMaths::Vector2D<Type>& _contact)
	{
		JMaths::Vector2D<Type> ab = _b - _a;
		JMaths::Vector2D<Type> ap = _p - _a;

		Type projection = ap.dotProduct(ab);
		Type abLengSqrt = ab.squareLength();
		Type distance = projection / abLengSqrt;

		if(distance <= 0.f)
		{
			_contact = _a;
		}else if(distance >= 1.f)
		{
			_contact = _b;
		}else
		{
			_contact = _a + ab * distance;
		}

		_distanceSqrt = JMaths::Vector2D<Type>::DistanceSquare(_p, _contact);
	}

	template <typename Type>
	bool Collisions<Type>::IntersectAABB(const AABB<Type>& _bodyA, const AABB<Type>& _bodyB)
	{
		if(_bodyA.max.x <= _bodyB.min.x || _bodyB.max.x <= _bodyA.min.x || _bodyA.max.y <= _bodyB.min.y || _bodyB.max.y <= _bodyA.min.y)
		{
			return false;
		}

		return true;
	}

	template <typename Type>
	JMaths::Vector2D<Type> Collisions<Type>::FindArithmeticMean(const std::vector<JMaths::Vector2D<Type>>& _vertices)
	{
		Type sumX = 0.f;
		Type sumY = 0.f;

		for(int i = 0; i < _vertices.size(); ++i)
		{
			JMaths::Vector2D<Type> vertices = _vertices[i];

			sumX += vertices.x;
			sumY += vertices.y;
		}

		return JMaths::Vector2D<Type>{sumX / _vertices.size(), sumY / _vertices.size()};
	}

	template <typename Type>
	Type Collisions<Type>::FindClosePointOnPolygon(const JMaths::Vector2D<Type>& _circleCenter,
		const std::vector<JMaths::Vector2D<Type>>& _vertices)
	{
		Type result = -1.f;
		Type minDistance = std::numeric_limits<Type>::max();

		for(int i = 0; i < _vertices.size(); i++)
		{
			JMaths::Vector2D<Type> vertices = _vertices[i];
			Type distance = JMaths::Vector2D<Type>::Distance(vertices, _circleCenter);

			if(distance < minDistance)
			{
				minDistance = distance;
				result = i;
			}
		}

		return result;
	}
}
