#pragma once

#include "jepch.h"
#include "Vector2D.h"
#include "JavaEngine/Core/Core.h"

namespace JMaths
{
	template<typename Type>
	class JE_API JMath
	{
		static constexpr Type VerySmallAmount = 0.0005f;
		static constexpr Type TwoPi = 6.28f;

	public:
		static Type Clamp(Type _value, const Type _min, const Type _max);
		static Type Min(Type _value, const Type _min);
		static Type Max(Type _value, const Type _max);
		static bool NearlyEqual(const Type _a, const Type _b);
		static bool NearlyEqual(const JMaths::Vector2D<Type>& _a, const JMaths::Vector2D<Type>& _b);
	};

	template <typename Type>
	Type JMath<Type>::Clamp(Type _value, const Type _min, const Type _max)
	{
		if(_min == _max)
		{
			return _min;
		}

		//assert(_min > _max, "min is greater than max");
		
		if(_value < _min)
		{
			return _min;
		}

		if(_value > _max)
		{
			return _max;
		}

		return _value;
	}

	template <typename Type>
	Type JMath<Type>::Min(Type _value, Type _min)
	{
		if(_value < _min)
		{
			return _min;
		}

		return _value;
	}

	template <typename Type>
	Type JMath<Type>::Max(Type _value, const Type _max)
	{
		if(_value > _max)
		{
			return _max;
		}

		return _value;
	}

	template <typename Type>
	bool JMath<Type>::NearlyEqual(const Type _a, const Type _b)
	{
		return std::abs(_a - _b) < VerySmallAmount;
	}

	template <typename Type>
	bool JMath<Type>::NearlyEqual(const JMaths::Vector2D<Type>& _a, const JMaths::Vector2D<Type>& _b)
	{
		return NearlyEqual(_a.x, _b.x) && NearlyEqual(_a.y, _b.y);
	}
}
