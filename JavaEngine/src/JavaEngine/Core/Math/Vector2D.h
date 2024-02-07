#pragma once

#include "JavaEngine/Core/Core.h"
#include <cmath>

namespace JMaths
{
	template<typename Type>
	class JE_API Vector2D
	{
	public:

		explicit Vector2D(const Type& _x = 0, const Type& _y = 0);

		Type dotProduct(const Vector2D& vector);
		Vector2D getNormarlized() const;
		Vector2D& normalilze();
		Type squareLength() const;
		Type getLength() const;

		Type x, y;

		static Type Distance(const Vector2D& one, const Vector2D& two);

		static const Vector2D Zero;
		static const Vector2D Up;
		static const Vector2D Forward;
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
	Vector2D<Type>& Vector2D<Type>::normalilze()
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
	Type Vector2D<Type>::Distance(const Vector2D& one, const Vector2D& two)
	{
		Type dx = one.x - two.x;
		Type dy = one.y - two.y;
		return std::sqrt(dx * dx + dy * dy);
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

	template <typename Type>
	Vector2D<Type> operator+=(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template <typename Type> const Vector2D<Type> Vector2D<Type>::Zero(0, 0);
	template <typename Type> const Vector2D<Type> Vector2D<Type>::Up(0, 1);
	template <typename Type> const Vector2D<Type> Vector2D<Type>::Forward(1, 0);

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Vector2Dd = Vector2D<double>;
}
