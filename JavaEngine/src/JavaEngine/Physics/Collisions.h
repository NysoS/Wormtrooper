#pragma once

#include "CircleCollider.h"
#include "jepch.h"
#include "ColliderIntersect.h"
#include "ContactPoints.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
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

		static void FindContactPoints(
			const RigidBody<Type>& _bodyA, const RigidBody<Type>& _bodyB,
			JMaths::Vector2D<Type>& _contact1, JMaths::Vector2D<Type>& _contact2, Type& _contactCount);

		static void FindContactPointsPolygon(
			const std::vector<JMaths::Vector2D<Type>>& _verticesA, const std::vector<JMaths::Vector2D<Type>>& _verticesB,
			JMaths::Vector2D<Type>& _contact1, JMaths::Vector2D<Type>& _contact2, Type& _countactCount);

		static void FindContactPointPolygonCircle(const JMaths::Vector2D<Type>& _circleCenter, const Type& _circleRadius,
			const JMaths::Vector2D<Type>& _polygonCenter, const std::vector<JMaths::Vector2D<Type>>& _polygonVertices,
			JMaths::Vector2D<Type>& _contactPoint);

		static bool Collide(const RigidBody<Type>& _bodyA, const RigidBody<Type>& _bodyB, JMaths::Vector2D<Type>& _normal, Type& _depth);

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
	void Collisions<Type>::FindContactPoints(const RigidBody<Type>& _bodyA, const RigidBody<Type>& _bodyB,
		JMaths::Vector2D<Type>& _contact1, JMaths::Vector2D<Type>& _contact2, Type& _contactCount)
	{
		_contact1 = JMaths::Vector2D<Type>::Zero;
		_contact2 = JMaths::Vector2D<Type>::Zero;
		_contactCount = 0;

		ShapeType shapeTypeA = _bodyA.shapeType;
		ShapeType shapeTypeB = _bodyB.shapeType;

		RigidBody<Type> bodyA = _bodyA;
		RigidBody<Type> bodyB = _bodyB;

		if (shapeTypeA == ShapeType::Box)
		{
			if (shapeTypeB == ShapeType::Box)
			{
				FindContactPointsPolygon(bodyA.GetTransformVertices(), bodyB.GetTransformVertices(), _contact1, _contact2, _contactCount);
				/*ContactPointsInfo<Type> contactPointsInfo = ContactPoints<Type, JavaEngine::PolygonCollider>().find(bodyA.GetTransformVertices(), bodyB.GetTransformVertices());
				_contactCount = contactPointsInfo.contactCount;
				_contact1 = contactPointsInfo.contact1;
				_contact2 = contactPointsInfo.contact2;*/
			}
			else if (shapeTypeB == ShapeType::Circle)
			{
				Collisions::FindContactPointPolygonCircle(bodyB.GetPosition(), bodyB.radius, bodyA.GetPosition(), bodyA.GetTransformVertices(), _contact1);
				_contactCount = 1;
			}
		}
		else if (shapeTypeA == ShapeType::Circle)
		{
			if (shapeTypeB == ShapeType::Box)
			{
				Collisions::FindContactPointPolygonCircle(bodyA.GetPosition(), bodyA.radius, bodyB.GetPosition(), bodyB.GetTransformVertices(), _contact1);
				_contactCount = 1;
			}
			else if (shapeTypeB == ShapeType::Circle)
			{
				ContactPointsInfo<Type> contactPointsInfo = ContactPoints<Type, JavaEngine::CircleCollider>().find(bodyA.GetPosition(), bodyA.radius, bodyB.GetPosition());
				_contactCount = contactPointsInfo.contactCount;
				_contact1 = contactPointsInfo.contact1;
				_contact2 = contactPointsInfo.contact2;
			}
		}
	}

	template <typename Type>
	void Collisions<Type>::FindContactPointsPolygon(const std::vector<JMaths::Vector2D<Type>>& _verticesA,
		const std::vector<JMaths::Vector2D<Type>>& _verticesB, JMaths::Vector2D<Type>& _contact1,
		JMaths::Vector2D<Type>& _contact2, Type& _countactCount)
	{
		_contact1 = JMaths::Vector2D<Type>::Zero;
		_contact2 = JMaths::Vector2D<Type>::Zero;
		_countactCount = 0;

		Type minDistanceSqrt = std::numeric_limits<Type>::max();

		for(int i = 0; i < _verticesA.size(); ++i)
		{
			JMaths::Vector2D<Type> p = _verticesA[i];

			for(int j = 0; j < _verticesB.size(); ++j)
			{
				JMaths::Vector2D<Type> va = _verticesB[j];
				JMaths::Vector2D<Type> vb = _verticesB[(j+1) % _verticesB.size()];

				Type distanceSqrt = 0.f;
				JMaths::Vector2D<Type> contact;
				PointSegmentDistance(p, va, vb, distanceSqrt, contact);

				if (JMaths::JMath<Type>::NearlyEqual(distanceSqrt, minDistanceSqrt))
				{
					if(!JMaths::JMath<Type>::NearlyEqual(contact, _contact1))
					{
						_contact2 = contact;
						_countactCount = 2;
					}
				}
				else if(distanceSqrt < minDistanceSqrt)
				{
					minDistanceSqrt = distanceSqrt;
					_countactCount = 1;
					_contact1 = contact;
				}
			}
		}

		for (int i = 0; i < _verticesB.size(); ++i)
		{
			JMaths::Vector2D<Type> p = _verticesB[i];

			for (int j = 0; j < _verticesA.size(); ++j)
			{
				JMaths::Vector2D<Type> va = _verticesA[j];
				JMaths::Vector2D<Type> vb = _verticesA[(j + 1) % _verticesA.size()];

				Type distanceSqrt = 0.f;
				JMaths::Vector2D<Type> contact;
				PointSegmentDistance(p, va, vb, distanceSqrt, contact);

				if (JMaths::JMath<Type>::NearlyEqual(distanceSqrt, minDistanceSqrt))
				{
					if (!JMaths::JMath<Type>::NearlyEqual(contact, _contact1))
					{
						_contact2 = contact;
						_countactCount = 2;
					}
				}
				else if (distanceSqrt < minDistanceSqrt)
				{
					minDistanceSqrt = distanceSqrt;
					_countactCount = 1;
					_contact1 = contact;
				}
			}
		}
	}

	template <typename Type>
	void Collisions<Type>::FindContactPointPolygonCircle(const JMaths::Vector2D<Type>& _circleCenter,
		const Type& _circleRadius, const JMaths::Vector2D<Type>& _polygonCenter,
		const std::vector<JMaths::Vector2D<Type>>& _polygonVertices, JMaths::Vector2D<Type>& _contactPoint)
	{
		Type minDistanceSqrt = std::numeric_limits<Type>::max();
		_contactPoint = JMaths::Vector2D<Type>::Zero;

		for (int i = 0; i < _polygonVertices.size(); ++i)
		{
			JMaths::Vector2D<Type> va = _polygonVertices[i];
			JMaths::Vector2D<Type> vb = _polygonVertices[(i + 1) % _polygonVertices.size()];

			Type distanceSqrt = 0.f;
			JMaths::Vector2D<Type> contact;
			PointSegmentDistance(_circleCenter, va, vb, distanceSqrt, contact);

			if (distanceSqrt < minDistanceSqrt)
			{
				minDistanceSqrt = distanceSqrt;
				_contactPoint = contact;
			}
		}
	}

	template <typename Type>
	bool Collisions<Type>::Collide(const RigidBody<Type>& _bodyA, const RigidBody<Type>& _bodyB, JMaths::Vector2D<Type>& _normal, Type& _depth)
	{
		_normal = JMaths::Vector2D<Type>::Zero;
		_depth = 0.f;

		ShapeType shapeTypeA = _bodyA.shapeType;
		ShapeType shapeTypeB = _bodyB.shapeType;

		RigidBody<Type> bodyA = _bodyA;
		RigidBody<Type> bodyB = _bodyB;

		if (shapeTypeA == ShapeType::Box)
		{
			if (shapeTypeB == ShapeType::Box)
			{
				IntersectInfo<Type> info = ColliderIntersect<Type, JavaEngine::PolygonCollider>().intersect(bodyA.GetPosition(), bodyA.GetTransformVertices(), bodyB.GetPosition(), bodyB.GetTransformVertices());
				_normal = info.normal;
				_depth = info.depth;
				return info.isIntersect;
			}
			else if (shapeTypeB == ShapeType::Circle)
			{
				IntersectInfo<Type> info = ColliderIntersect<Type, JavaEngine::PolygonCollider, JavaEngine::CircleCollider>().intersect(bodyB.GetPosition(), bodyB.radius, bodyA.GetPosition(), bodyA.GetTransformVertices());
				_normal = info.normal;
				_normal = JMaths::Vector2Df{ -_normal.x, -_normal.y };

				_depth = info.depth;
				return info.isIntersect;
			}
		}
		else if (shapeTypeA == ShapeType::Circle)
		{
			if (shapeTypeB == ShapeType::Box)
			{
				IntersectInfo<Type> info = ColliderIntersect<Type, JavaEngine::CircleCollider, JavaEngine::PolygonCollider>().intersect(bodyA.GetPosition(), bodyA.radius, bodyB.GetPosition(), bodyB.GetTransformVertices());
				_normal = info.normal;
				_depth = info.depth;
				return info.isIntersect;
			}
			else if (shapeTypeB == ShapeType::Circle)
			{
				IntersectInfo<Type> info = JPhysics::ColliderIntersect<Type, JavaEngine::CircleCollider>().intersect(bodyA.GetPosition(), bodyA.radius, bodyB.GetPosition(), bodyB.radius);
				_normal = info.normal;
				_depth = info.depth;
				return info.isIntersect;
			}
		}

		return false;
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
