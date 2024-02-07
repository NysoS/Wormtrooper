#pragma once

#include "jepch.h"
#include "JObjectComponent.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Math/Vector2D.h"

namespace JavaEngine 
{
	template<typename Type>
	class Transform : public JObjectComponent
	{
	public:
		Transform(const std::string& name);

		void SetPosition(JMaths::Vector2D<Type>& pos);
		void SetPosition(Type _x, Type _y);

	private:
		JMaths::Vector2Df m_position;
		JMaths::Vector2Df m_rotation;
		JMaths::Vector2Df m_scale;
	};

	//Transform de matrix
}
