#pragma once

#include "CircleCollider.h"
#include "jepch.h"
#include "JavaEngine/Core/Math/Math.h"

namespace JPhysics
{
	template <typename Type>
	void PointSegmentDistance(const JMaths::Vector2D<Type>& _p, const JMaths::Vector2D<Type>& _a,
		const JMaths::Vector2D<Type>& _b, Type& _distanceSqrt, JMaths::Vector2D<Type>& _contact)
	{
		JMaths::Vector2D<Type> ab = _b - _a;
		JMaths::Vector2D<Type> ap = _p - _a;

		Type projection = ap.dotProduct(ab);
		Type abLengSqrt = ab.squareLength();
		Type distance = projection / abLengSqrt;

		if (distance <= 0.f)
		{
			_contact = _a;
		}
		else if (distance >= 1.f)
		{
			_contact = _b;
		}
		else
		{
			_contact = _a + ab * distance;
		}

		_distanceSqrt = JMaths::Vector2D<Type>::DistanceSquare(_p, _contact);
	}

	template <typename Type>
	using Vect2D = JMaths::Vector2D<Type>;

	template <typename Type>
	struct ContactPointsInfo
	{
		Vect2D<Type> contact1 = Vect2D<Type>::Zero;
		Vect2D<Type> contact2 = Vect2D<Type>::Zero;
		int contactCount = 0;
	};

	template <typename Type, typename ColliderTypeA, typename ColliderTypeB = ColliderTypeA>
	struct ContactPoints
	{
	};

	template <typename Type>
	struct ContactPoints<Type, JavaEngine::CircleCollider>
	{
		ContactPointsInfo<Type> find(const Vect2D<Type>& circleCenterA, const Type& circleRadiusA, const Vect2D<Type>& circleCenterB)
		{
			ContactPointsInfo<Type> contactPointsInfo{};

			Vect2D<Type> ab = circleCenterB - circleCenterA;
			Vect2D<Type> direction = ab.GetLeftNormal();
			contactPointsInfo.contact1 = circleCenterA + direction * circleRadiusA;
			contactPointsInfo.contactCount = 1;

			return contactPointsInfo;
		}
	};

	template <typename Type>
	struct ContactPoints<Type, JavaEngine::PolygonCollider>
	{
		ContactPointsInfo<Type> find(const std::vector<JMaths::Vector2D<Type>>& polygonVerticesA, const std::vector<JMaths::Vector2D<Type>>& polygonVerticesB)
		{
			ContactPointsInfo<Type> contactPointsInfo{};

			Type minDistanceSqrt = std::numeric_limits<Type>::max();

			for (int i = 0; i < polygonVerticesA.size(); ++i)
			{
				JMaths::Vector2D<Type> currentVerticeA = polygonVerticesA[i];

				for (int j = 0; j < polygonVerticesB.size(); ++j)
				{
					JMaths::Vector2D<Type> va = polygonVerticesB[j];
					JMaths::Vector2D<Type> vb = polygonVerticesB[(j + 1) % polygonVerticesB.size()];

					Type distanceSqrt = 0.f;
					JMaths::Vector2D<Type> contact;
					PointSegmentDistance(currentVerticeA, va, vb, distanceSqrt, contact);

					if (JMaths::JMath<Type>::NearlyEqual(distanceSqrt, minDistanceSqrt))
					{
						if (!JMaths::JMath<Type>::NearlyEqual(contact, contactPointsInfo.contact1))
						{
							contactPointsInfo.contact2 = contact;
							contactPointsInfo.contactCount = 2;
						}
					}
					else if (distanceSqrt < minDistanceSqrt)
					{
						minDistanceSqrt = distanceSqrt;
						contactPointsInfo.contact1 = contact;
						contactPointsInfo.contactCount = 1;
					}
				}
			}

			for (int i = 0; i < polygonVerticesB.size(); ++i)
			{
				JMaths::Vector2D<Type> currentVerticeB = polygonVerticesB[i];

				for (int j = 0; j < polygonVerticesA.size(); ++j)
				{
					JMaths::Vector2D<Type> va = polygonVerticesA[j];
					JMaths::Vector2D<Type> vb = polygonVerticesA[(j + 1) % polygonVerticesA.size()];

					Type distanceSqrt = 0.f;
					JMaths::Vector2D<Type> contact;
					PointSegmentDistance(currentVerticeB, va, vb, distanceSqrt, contact);

					if (JMaths::JMath<Type>::NearlyEqual(distanceSqrt, minDistanceSqrt))
					{
						if (!JMaths::JMath<Type>::NearlyEqual(contact, contactPointsInfo.contact1))
						{
							contactPointsInfo.contact2 = contact;
							contactPointsInfo.contactCount = 2;
						}
					}
					else if (distanceSqrt < minDistanceSqrt)
					{
						minDistanceSqrt = distanceSqrt;
						contactPointsInfo.contact1 = contact;
						contactPointsInfo.contactCount = 1;
					}
				}
			}

			return contactPointsInfo;
		}
	};
}
