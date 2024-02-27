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
}
