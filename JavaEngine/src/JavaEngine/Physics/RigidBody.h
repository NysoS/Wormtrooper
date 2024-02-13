#pragma once

#include "jepch.h"
#include "JWorld.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Math.h"
#include "JavaEngine/Core/Math/Vector2D.h"
#include "JavaEngine/Gameplay/Components/Transform.h"

namespace JPhysics
{
	constexpr float M_PI = 3.14f;

	enum ShapeType
	{
		Circle,
		Box
	};

	template<typename Type>
	class JE_API RigidBody
	{
	public:
		RigidBody() = default;

		RigidBody(
			JMaths::Vector2D<Type> _position, Type _density, Type _mass, Type _resistution, Type area,
			bool _isStatic, Type _radius, Type _width, Type _height, ShapeType _shapeType
		);
		virtual ~RigidBody() = default;

		static RigidBody* CreateCircleBody(Type _radius, JMaths::Vector2D<Type> _position, Type _density,
			bool _isStatic, Type _resitution);

		static RigidBody* CreateBoxBody(Type _width, Type _height, JMaths::Vector2D<Type> _position, Type _density,
			bool _isStatic, Type _resitution);

		JMaths::Vector2D<Type> GetPosition();
		Type GetRotation();

		static std::vector<JMaths::Vector2D<Type>> CreateBoxVertices(Type _width, Type _height);
		static std::vector<Type> CreateBoxTriangles();
		std::vector<JMaths::Vector2D<Type>> GetTransformVertices();

		void Move(JMaths::Vector2D<Type> _amount);
		void MoveTo(JMaths::Vector2D<Type> _position);
		void Rotate(Type _amount);

	protected:
		JMaths::Vector2D<Type> m_position;
		JMaths::Vector2D<Type> m_linearVelocity;
		Type m_rotation;
		Type m_rotationVelocity;

		std::vector<JMaths::Vector2D<Type>> m_vertices;
		std::vector<Type> Triangles;
		std::vector<JMaths::Vector2D<Type>> m_transformVertices;

		bool m_transformUpdateRequired = false;

	public:
		Type mass;
		Type density;
		Type restitution;
		Type area;

		bool isStatic;

		Type radius;
		Type width;
		Type height;

		ShapeType shapeType;
	};

	template <typename Type>
	RigidBody<Type>::RigidBody(JMaths::Vector2D<Type> _position, Type _density, Type _mass,
		Type _resistution, Type _area, bool _isStatic, Type _radius, Type _width, Type _height, ShapeType _shapeType)
			: m_position(_position), m_linearVelocity(JMaths::Vector2D<Type>::Zero), m_rotation(0.f), m_rotationVelocity(0.f), density(_density), mass(_mass), restitution(_resistution), area(_area), isStatic(_isStatic),
			radius(_radius), width(_width), height(_height), shapeType(_shapeType)
	{
		if(shapeType == ShapeType::Box)
		{
			m_vertices = CreateBoxVertices(width, height);
			m_transformVertices.resize(m_vertices.size());
		}

		m_transformUpdateRequired = true;
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

		return new RigidBody(_position, _density, mass, _resitution, area, _isStatic, _radius, 0.f, 0.f, ShapeType::Circle);
	}

	template <typename Type>
	RigidBody<Type>* RigidBody<Type>::CreateBoxBody(Type _width, Type _height, JMaths::Vector2D<Type> _position,
		Type _density, bool _isStatic, Type _resitution)
	{
		Type area = _width * _height;
		if (area < JWorld::MinBodySize || area > JWorld::MaxBodySize)
		{
			return nullptr;
		}

		if (_density < JWorld::MinDensity || _density > JWorld::MaxDensity)
		{
			return nullptr;
		}

		_resitution = JMaths::JMath<Type>::Clamp(_resitution, .0f, 1.f);

		Type mass = area * _density;

		return new RigidBody(_position, _density, mass, _resitution, area, _isStatic, 0.f, _width, _height, ShapeType::Box);
	}

	template <typename Type>
	JMaths::Vector2D<Type> RigidBody<Type>::GetPosition()
	{
		return m_position;
	}

	template <typename Type>
	Type RigidBody<Type>::GetRotation()
	{
		return m_rotation;
	}

	template <typename Type>
	std::vector<JMaths::Vector2D<Type>> RigidBody<Type>::CreateBoxVertices(Type _width, Type _height)
	{	
		Type left = - _width / 2.f;
		Type right = left + _width;
		Type bottom = - _height / 2.f;
		Type top = bottom + _height;

		return std::vector<JMaths::Vector2D<Type>>{
			JMaths::Vector2D<Type>{left, top},
			JMaths::Vector2D<Type>{right, top},
			JMaths::Vector2D<Type>{right, bottom},
			JMaths::Vector2D<Type>{left, bottom},
		};
	}

	template <typename Type>
	std::vector<Type> RigidBody<Type>::CreateBoxTriangles()
	{
		return std::vector<Type>{0, 1, 2, 0, 2, 3};
	}

	template <typename Type>
	std::vector<JMaths::Vector2D<Type>> RigidBody<Type>::GetTransformVertices()
	{
		if(m_transformUpdateRequired)
		{
			JavaEngine::Transform<Type>* transform = new JavaEngine::Transform<Type>();
			transform->setPosition(m_position);
			transform->setRotation(m_rotation);

			for(int i = 0; i < m_vertices.size(); ++i)
			{
				JMaths::Vector2D<Type> vector = m_vertices[i];
				m_transformVertices[i] = transform->vector(vector);
			}
		}

		return m_transformVertices;
	}

	template <typename Type>
	void RigidBody<Type>::Move(JMaths::Vector2D<Type> amount)
	{
		JE_INFO("x {0}, y {1}", amount.x, amount.y);
		m_position.x += amount.x;
		m_position.y += amount.y;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::MoveTo(JMaths::Vector2D<Type> _position)
	{
		m_position = _position;
		m_transformUpdateRequired = true;
	}

	template <typename Type>
	void RigidBody<Type>::Rotate(Type _amount)
	{
		m_rotation += _amount;
		m_transformUpdateRequired = true;
	}

	using RigidBodyf = RigidBody<float>;
	using RigidBodyd = RigidBody<double>;
	using RigidBodyi = RigidBody<int>;
}
