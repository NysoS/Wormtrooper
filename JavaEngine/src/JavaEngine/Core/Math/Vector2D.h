#pragma once

#include "JavaEngine/Core/Core.h"
#include <cmath>

namespace Maths
{
	template<typename Type>
	class JE_API Vector2D
	{
	public:

		explicit Vector2D(const Type& _x = 0, const Type& _y);

		Type dotProduct(const Vector2D& vector);
		Vector2D getNormarlized() const;
		Vector2D& normalilze() const;
		Type squareLength() const;
		Type getLength() const;

		Type x, y;
	};

	template <typename Type>
	Vector2D<Type>::Vector2D(const Type& _x, const Type& _y)
		: x(_x), y(_y)
	{
	}

	template <typename Type>
	Type Vector2D<Type>::dotProduct(const Vector2D& otherVector)
	{
		return x * otherVector.x + y * otherVector.y;
	}

	template <typename Type>
	Vector2D<Type> Vector2D<Type>::getNormarlized() const
	{
		const auto lenght = getLength();
		return Vector2D{ x / lenght, y / lenght };
	}

	template <typename Type>
	Vector2D<Type>& Vector2D<Type>::normalilze() const
	{
		const auto lenght = getLength();
		x /= lenght;
		y /= lenght;
		return *this;
	}

	template <typename Type>
	Type Vector2D<Type>::squareLength() const
	{
		return x * x + y * y;
	}

	template <typename Type>
	Type Vector2D<Type>::getLength() const
	{
		return std::sqrt(squareLength());
	}

	template <typename Type>
	Vector2D<Type> operator+(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>{lhs.x + rhs.x, lhs.y + rhs.y};
	}

	template <typename Type>
	Vector2D<Type> operator-(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template <typename Type>
	Vector2D<Type> operator*(const Type& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>{lhs* rhs.x, lhs* rhs.y};
	}

	template <typename Type>
	Vector2D<Type> operator*(const Vector2D<Type>& lhs, const Type& rhs)
	{
		return Vector2D<Type>{lhs.x * rhs, lhs.y * rhs};
	}

	template <typename Type>
	std::ostream& operator<<(std::ostream& os, const Vector2D<Type>& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Vector2Dd = Vector2D<double>;
}
