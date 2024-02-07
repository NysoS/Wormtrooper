#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

namespace JMaths
{
	template<typename Type>
	class JE_API JMath
	{
	public:
		static Type Clamp(Type _value, const Type _min, const Type _max);
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
}
