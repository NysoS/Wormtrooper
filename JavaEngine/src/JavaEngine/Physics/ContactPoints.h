#pragma once

#include "CircleCollider.h"
#include "jepch.h"
#include "JavaEngine/Core/Math/Math.h"

namespace JPhysics
{
	template <typename Type>
	using Vect2D = JMaths::Vector2D<Type>;

	template <typename Type>
	struct ContactPointsInfo
	{
		Vect2D<Type> contact1 = Vect2D<Type>::Zero;
		Vect2D<Type> contact2 = Vect2D<Type>::Zero;
		Type contactCount = 0;
	};

	template <typename Type>
	struct ContactPoints
	{
		template <typename Lhs, typename Rhs>
		ContactPointsInfo<Type> OnContactPointsCallback(Lhs&, Rhs&)
		{
			return ContactPointsInfo<Type>{};
		}

		ContactPointsInfo<Type> OnCircleContactPointsCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			ContactPointsInfo<Type> contactPointsInfo{};

			JavaEngine::CircleCollider lhsCircle = dynamic_cast<JavaEngine::CircleCollider&>(lhs);
			JavaEngine::CircleCollider rhsCircle = dynamic_cast<JavaEngine::CircleCollider&>(rhs);

			Vect2D<Type> ab = rhsCircle.position - lhsCircle.position;
			Vect2D<Type> direction = ab.getNormarlized();
			contactPointsInfo.contact1 = lhsCircle.position + direction * lhsCircle.radius;
			contactPointsInfo.contactCount = 1;

			return contactPointsInfo;
		}

		ContactPointsInfo<Type> OnPolygonContactPointsCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			ContactPointsInfo<Type> contactPointsInfo{};

			JavaEngine::PolygonCollider lhsPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(lhs);
			JavaEngine::PolygonCollider rhsPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(rhs);

			Type minDistanceSqrt = std::numeric_limits<Type>::max();

			auto polygonVerticesA = lhsPolygon.getTransformVertices();
			auto polygonVerticesB = rhsPolygon.getTransformVertices();

			for (int i = 0; i < polygonVerticesA.size(); ++i)
			{
				Vect2D<Type> currentVerticeA = polygonVerticesA[i];

				for (int j = 0; j < polygonVerticesB.size(); ++j)
				{
					Vect2D<Type> va = polygonVerticesB[j];
					Vect2D<Type> vb = polygonVerticesB[(j + 1) % polygonVerticesB.size()];

					Type distanceSqrt = 0.f;
					Vect2D<Type> contact;
					Vect2D<Type>::PointSegmentDistance(currentVerticeA, va, vb, distanceSqrt, contact);

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
				Vect2D<Type> currentVerticeB = polygonVerticesB[i];

				for (int j = 0; j < polygonVerticesA.size(); ++j)
				{
					Vect2D<Type> va = polygonVerticesA[j];
					Vect2D<Type> vb = polygonVerticesA[(j + 1) % polygonVerticesA.size()];

					Type distanceSqrt = 0.f;
					Vect2D<Type> contact;
					Vect2D<Type>::PointSegmentDistance(currentVerticeB, va, vb, distanceSqrt, contact);

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

		ContactPointsInfo<Type> OnCircleToPolygonContactPointsCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			ContactPointsInfo<Type> contactPointsInfo{};

			JavaEngine::CircleCollider lhsCircle = dynamic_cast<JavaEngine::CircleCollider&>(lhs);
			JavaEngine::PolygonCollider rhsPolygon = dynamic_cast<JavaEngine::PolygonCollider&>(rhs);

			Type minDistanceSqrt = std::numeric_limits<Type>::max();

			auto polygonVertices = rhsPolygon.getTransformVertices();

			for (int i = 0; i < polygonVertices.size(); ++i)
			{
				Vect2D<Type> va = polygonVertices[i];
				Vect2D<Type> vb = polygonVertices[(i + 1) % polygonVertices.size()];

				Type distanceSqrt = 0.f;
				Vect2D<Type> contact;
				Vect2D<Type>::PointSegmentDistance(lhsCircle.position, va, vb, distanceSqrt, contact);

				if (distanceSqrt < minDistanceSqrt)
				{
					minDistanceSqrt = distanceSqrt;
					contactPointsInfo.contact1 = contact;
					contactPointsInfo.contactCount = 1;
				}
			}

			return contactPointsInfo;
		}

		ContactPointsInfo<Type> OnPolygonToCirlceContactPointsCallback(JavaEngine::ColliderBase& lhs, JavaEngine::ColliderBase& rhs)
		{
			return OnCircleToPolygonContactPointsCallback(rhs, lhs);
		}
	};
}
