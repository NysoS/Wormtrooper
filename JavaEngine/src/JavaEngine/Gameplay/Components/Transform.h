#pragma once

#include "jepch.h"
#include "JObjectComponent.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"
#include "JavaEngine/Physics/RigidBody.h"
#include "JavaEngine/Physics/RigidBody.h"
#include "JavaEngine/Physics/RigidBody.h"

namespace JavaEngine
{
	template <typename Type>
	class JE_API Transform : public JObjectComponent
	{
	public:
		Transform();
		~Transform();

		void setPosition(const JMaths::Vector2D<Type>& position);
		void setRotation(const Type& angle);

		JMaths::Vector2D<Type> getPosition() const;
		JMaths::Vector2D<Type> getRotation() const;

		JMaths::Vector2D<Type> vector(const JMaths::Vector2D<Type>& vector);

	protected:
		JMaths::Vector2D<Type> m_position;
		JMaths::Vector2D<Type> m_rotation;
	};

	template <typename Type>
	Transform<Type>::Transform()
		: JObjectComponent("Transform")
	{
	}

	template <typename Type>
	Transform<Type>::~Transform()
	{
	}

	template <typename Type>
	void Transform<Type>::setPosition(const JMaths::Vector2D<Type>& position)
	{
		m_position = position;
	}

	template <typename Type>
	void Transform<Type>::setRotation(const Type& angle)
	{
		m_rotation = JMaths::Vector2D<Type>{ std::cos(angle), std::sin(angle) };
	}

	template <typename Type>
	JMaths::Vector2D<Type> Transform<Type>::getPosition() const
	{
		return m_position;
	}

	template <typename Type>
	JMaths::Vector2D<Type> Transform<Type>::getRotation() const
	{
		return m_rotation;
	}

	template <typename Type>
	JMaths::Vector2D<Type> Transform<Type>::vector(const JMaths::Vector2D<Type>& vector)
	{
		//m_rotation.x = cos, m_rotation.y = sin
		Type rx = m_rotation.x * vector.x - m_rotation.y * vector.y;
		Type ry = m_rotation.y * vector.x + m_rotation.x * vector.y;

		Type tx = rx + m_position.x;
		Type ty = ry + m_position.y;

		return JMaths::Vector2D<Type>(tx, ty);
	}
}
