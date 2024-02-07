#pragma once

#include "jepch.h"
#include "JWorld.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Point2D.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JPhysics
{
	constexpr float M_PI = 3.14f;

	template<typename Type>
	class JE_API RigidBody
	{
	public:
		RigidBody() = default;

		RigidBody(
			JMaths::Vector2D<Type> _position, Type _density, Type _mass, Type _resistution, Type area,
			bool _isStatic, Type _radius, Type _width, Type _height
		);
		virtual ~RigidBody() = default;

		static RigidBody* CreateCircleBody(Type _radius, JMaths::Vector2D<Type> _position, Type _density,
			bool _isStatic, Type _resitution);

		JMaths::Vector2D<Type> GetPosition();

		void Move(JMaths::Vector2D<Type> _amount);
		void MoveTo(JMaths::Vector2D<Type> _position);

	protected:
		JMaths::Vector2D<Type> m_position;
		JMaths::Vector2D<Type> m_linearVelocity;
		Type m_rotation;
		Type m_rotationVelocity;

	public:
		Type mass;
		Type density;
		Type restitution;
		Type area;

		bool isStatic;

		Type radius;
		Type width;
		Type height;

		//ShapeType shapeType;
	};

	template <typename Type>
	RigidBody<Type>::RigidBody(JMaths::Vector2D<Type> _position, Type _density, Type _mass,
		Type _resistution, Type _area, bool _isStatic, Type _radius, Type _width, Type _height)
			: m_position(_position), m_linearVelocity(JMaths::Vector2D<Type>::Zero), m_rotation(0.f), m_rotationVelocity(0.f), density(_density), mass(_mass), restitution(_resistution), area(_area), isStatic(_isStatic),
			radius(_radius), width(_width), height(_height)
	{
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateCircleBody(Type _radius, JMaths::Vector2D<Type> _position, Type _density,
		bool _isStatic, Type _resitution)
	{
		Type area = _radius * _radius * M_PI;
		if(area < JWorld::MinBodySize || area > JWorld::MaxBodySize)
		{
			return nullptr;
		}

		if(_density < JWorld::MinDensity || _density > JWorld::MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = area * 1.f * _density;

		return new RigidBody(_position, _density, mass, _resitution, area, _isStatic, _radius, 0.f, 0.f);
	}

	template <typename Type>
	JMaths::Vector2D<Type> RigidBody<Type>::GetPosition()
	{
		return m_position;
	}

	template <typename Type>
	void RigidBody<Type>::Move(JMaths::Vector2D<Type> amount)
	{
		m_position.x += amount.x;
		m_position.y += amount.y;
	}

	template <typename Type>
	void RigidBody<Type>::MoveTo(JMaths::Vector2D<Type> _position)
	{
		m_position = _position;
	}

	using RigidBodyf = RigidBody<float>;
	using RigidBodyd = RigidBody<double>;
	using RigidBodyi = RigidBody<int>;
}
