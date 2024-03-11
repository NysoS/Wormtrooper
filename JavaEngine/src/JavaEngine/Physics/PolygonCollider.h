#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Physics/ColliderBase.h"

namespace JavaEngine
{
	class JE_API PolygonCollider : public ColliderBase
	{
	public:
		explicit PolygonCollider(float width = 0, float height = 0, const JMaths::Vector2Df& pos = JMaths::Vector2Df::Zero, float angle = 0);
		~PolygonCollider();

		float width;
		float height;

		std::vector<JMaths::Vector2Df> getTransformVertices();
		size_t getVerticesCount() const;

		std::vector<JMaths::Vector2Df> createBoxVertices();
	private:
		std::vector<JMaths::Vector2Df> m_vertices;
		std::vector<float> Triangles;
		std::vector<JMaths::Vector2Df> m_transformVertices;
	};
}
