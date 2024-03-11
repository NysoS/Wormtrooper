#include "PolygonCollider.h"

#include "JavaEngine/Gameplay/Components/Transform.h"

namespace JavaEngine
{
	PolygonCollider::PolygonCollider(float width, float height, const JMaths::Vector2Df& pos, float angle)
		: ColliderBase(pos, angle), width(width), height(height), m_vertices(createBoxVertices())
	{
		m_transformVertices.resize(m_vertices.size());
	}

	PolygonCollider::~PolygonCollider()
	{
	}

	std::vector<JMaths::Vector2Df> PolygonCollider::createBoxVertices()
	{
		float left = -width / 2.f;
		float right = left + width;
		float bottom = -height / 2.f;
		float top = bottom + height;

		return std::vector<JMaths::Vector2Df>{
			JMaths::Vector2Df{left, top},
				JMaths::Vector2Df{right, top},
				JMaths::Vector2Df{right, bottom},
				JMaths::Vector2Df{left, bottom},
		};
	}

	std::vector<JMaths::Vector2Df> PolygonCollider::getTransformVertices()
	{
		if (transformUpdateRequired)
		{
			Transform<float> transform = JavaEngine::Transform<float>();
			transform.setPosition(position);
			transform.setRotation(angle);

			for (int i = 0; i < m_vertices.size(); ++i)
			{
				JMaths::Vector2Df vector = m_vertices[i];
				m_transformVertices[i] = transform.vector(vector);
			}
		}

		return m_transformVertices;
	}

	size_t PolygonCollider::getVerticesCount() const
	{
		return m_transformVertices.size();
	}
}
