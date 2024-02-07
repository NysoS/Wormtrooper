#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	template<typename Type>
	class Collisions
	{
	public:
		static bool IntersectCircles(
			const JMaths::Vector2D<Type>& _centerA, const Type& _radiusA,
			const JMaths::Vector2D<Type>& _centerB, const Type& _radiusB,
			JMaths::Vector2D<Type>& _normal, Type& _depth)
		{
			_normal = JMaths::Vector2D<Type>::Zero;
			_depth = 0.f;

			Type distance = JMaths::Vector2D<Type>::Distance(_centerA, _centerB);
			Type radius = _radiusA + _radiusB;

			if(distance >= radius)
			{
				return false;
			}

			_normal = _centerB - _centerA;
			_normal.getNormarlized();

			_depth = radius - distance;

			return true;
		}
	};
}
