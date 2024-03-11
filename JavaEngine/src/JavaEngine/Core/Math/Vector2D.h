#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"

namespace JMaths
{
	template<typename Type>
	struct JE_API Vector2D
	{
		explicit Vector2D(const Type& _x = 0.f, const Type& _y = 0.f);

		Type dotProduct(const Vector2D& vector);
		Type crossProduct(const Vector2D& vector);
		Vector2D getNormarlized() const;
		Vector2D& normalilze();
		Type squareLength() const;
		Type getLength() const;

		Vector2D GetLeftNormal() const;
		Vector2D GetRightNormal() const;

		Type x, y;

		static Type Distance(const Vector2D& one, const Vector2D& two);
		static Type DistanceSquare(const Vector2D& a, const Vector2D& b);
		static Type Cross(const Vector2D& a, const Vector2D& b);

		static void PointSegmentDistance(const JMaths::Vector2D<Type>& _p, const JMaths::Vector2D<Type>& _a,
			const JMaths::Vector2D<Type>& _b, Type& _distanceSqrt, JMaths::Vector2D<Type>& _contact);

		static const Vector2D Zero;
		static const Vector2D Up;
		static const Vector2D Forward;

		Vector2D& operator+=(const Vector2D& rhs);
		Vector2D& operator+=(Type rhs);
		Vector2D& operator-=(const Vector2D& rhs);
		Vector2D& operator-=(Type rhs);
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
	Type Vector2D<Type>::crossProduct(const Vector2D& vector)
	{
		return x * vector.y - y * vector.x;
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
	Vector2D<Type> Vector2D<Type>::GetLeftNormal() const
	{
		return JMaths::Vector2D<Type>{-y, x};
	}

	template <typename Type>
	Vector2D<Type> Vector2D<Type>::GetRightNormal() const
	{
		return JMaths::Vector2D<Type>{y, -x};
	}


	template <typename Type>
	Type Vector2D<Type>::Distance(const Vector2D& one, const Vector2D& two)
	{
		return std::sqrt(DistanceSquare(one, two));
	}

	template <typename Type>
	Type Vector2D<Type>::DistanceSquare(const Vector2D& a, const Vector2D& b)
	{
		Type dx = a.x - b.x;
		Type dy = a.y - b.y;
		return dx * dx + dy * dy;
	}

	template <typename Type>
	Type Vector2D<Type>::Cross(const Vector2D& a, const Vector2D& b)
	{
		return a.x * b.y - a.y + b.x;
	}

	template <typename Type>
	void Vector2D<Type>::PointSegmentDistance(const Vector2D<Type>& _p, const Vector2D<Type>& _a,
		const Vector2D<Type>& _b, Type& _distanceSqrt, Vector2D<Type>& _contact)
	{
		Vector2D<Type> ab = _b - _a;
		Vector2D<Type> ap = _p - _a;

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

		_distanceSqrt = Vector2D<Type>::DistanceSquare(_p, _contact);
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
	Vector2D<Type> operator*(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>{lhs.x * rhs.x, lhs.y * rhs.y};
	}

	template <typename Type>
	std::ostream& operator<<(std::ostream& os, const Vector2D<Type>& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	template <typename Type>
	Vector2D<Type>& Vector2D<Type>::operator+=(const Vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <typename Type>
	Vector2D<Type>& Vector2D<Type>::operator+=(Type rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	template <typename Type>
	Vector2D<Type>& Vector2D<Type>::operator-=(const Vector2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template <typename Type>
	Vector2D<Type>& Vector2D<Type>::operator-=(Type rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	template <typename Type>
	Vector2D<Type> operator+=(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template <typename Type>
	Vector2D<Type> operator-=(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template <typename Type>
	Vector2D<Type> operator/(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	template <typename Type>
	Vector2D<Type> operator/(const Vector2D<Type>& lhs, const Type& rhs)
	{
		return Vector2D<Type>(lhs.x / rhs, lhs.y / rhs);
	}

	template <typename Type>
	Vector2D<Type> operator/(const Type& lhs, const Vector2D<Type>& rhs)
	{
		return Vector2D<Type>(lhs / rhs.x, lhs / rhs.y);
	}

	template <typename Type>
	bool operator==(const Vector2D<Type>& lhs, const Vector2D<Type>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template <typename Type> const Vector2D<Type> Vector2D<Type>::Zero(0, 0);
	template <typename Type> const Vector2D<Type> Vector2D<Type>::Up(0, 1);
	template <typename Type> const Vector2D<Type> Vector2D<Type>::Forward(1, 0);

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Vector2Dd = Vector2D<double>;
}
