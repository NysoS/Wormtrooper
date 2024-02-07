#pragma once

#include "JavaEngine/Core/Core.h"

namespace JMaths
{
	template <typename Type>
	class JE_API Point2D
	{
	public:
		explicit Point2D(const Type& _x = 0, const Type& _y = 0)
			: x(_x), y(_y)
		{
		}

		Type x, y;
	};

	template <typename Type>
	std::ostream& operator<<(std::ostream& os, const Point2D<Type>& point)
	{
		os << "(" << point.x << ", " << point.y << ")";
		return os;
	}

	using Point2Df = Point2D<float>;
	using Point2Di = Point2D<int>;
	using Point2Dd = Point2D<double>;
}