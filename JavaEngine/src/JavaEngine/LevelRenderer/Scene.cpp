#include "Scene.h"

#include <random>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "JavaEngine/Core/Application.h"
#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Gameplay/JActor.h"
#include "JavaEngine/Physics/Collisions.h"
#include "JavaEngine/Physics/RigidBody.h"

namespace JavaEngine
{
	Scene::Scene()
		:	m_Name("Scene"), m_World(std::make_unique<JPhysics::JWorld>())
	{
		////TODO: Remove test
		//JObject* tomate = AddObjectToScene<JActor>();
		//tomate->m_Name = "Tomate";

		////TODO: Remove test
		//JObject* pomme = AddObjectToScene<JActor>();
		//pomme->m_Name = "Pomme";



		for(int i = 0; i < 10; ++i)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dist(10, 600);

			std::uniform_int_distribution<> bo(0, 1);

			float x = dist(gen);
			float y = dist(gen);

			bool isStatic = false;

			if(i > 0)
				isStatic = bo(gen)==0?false:true;

			if(i%2==0)
			{
				m_World->AddRigidbody(JPhysics::RigidBodyf::CreateCircleBody(10.f, JMaths::Vector2Df(x, y), 2.f, isStatic, 0.5f));
			}else
			{
				m_World->AddRigidbody(JPhysics::RigidBodyf::CreateBoxBody(20.f, 20.f , JMaths::Vector2Df(x, y), 2.f, isStatic, 0.5f));
			}
		}
	}

	Scene::~Scene()
	{
		for (auto* object : m_ObjectList)
		{
			delete object;
		}
		m_ObjectList.clear();

		/*for (auto body : rigidBodyList)
		{
			delete body;
		}
		rigidBodyList.clear();*/
	}

	void Scene::OnUpate()
	{
		//JE_INFO("Scene Update");
		/*for(const auto& object : m_ObjectList)
		{
			if(object->IsTickableObject())
			{
				object->Update();
			}
		}*/


		float dx = 0.f;
		float dy = 0.f;
		float forceMagnitude = 25.f;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dx--;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dx++;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dy--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dy++;
		}

		if (dx != .0f || dy != .0f)
		{
			JMaths::Vector2Df forceDirection = JMaths::Vector2Df(dx, dy).normalilze();
			JMaths::Vector2Df force = forceDirection * forceMagnitude;

			auto* body = m_World->GetRigidbody(0);
			if(body != nullptr)
			{
				body->AddForce(force);
			}
		}

		m_World->Step(0.5f);
	}

	void Scene::OnRenderer(Window& window)
	{
		//JE_INFO("Scene Renderer");
		/*const std::vector<JObject*> objectListCopy = m_ObjectList;
		for (auto* object : objectListCopy)
		{
			object->Renderer();
		}*/

		//JE_INFO("Move {0} {1}", rigidBodyList[0]->GetPosition().x, rigidBodyList[0]->GetPosition().y);

		for(int i = 0; i < m_World->RigidbodyCount(); ++i)
		{
			auto* body = m_World->GetRigidbody(i);
			if(body == nullptr)
			{
				continue;
			}

			if(body->shapeType == JPhysics::Circle)
			{
				sf::CircleShape shape{};
				shape.setRadius(10.f);
				shape.setOutlineThickness(1);
				shape.setPosition(body->GetPosition().x, body->GetPosition().y);
				shape.setOutlineColor(sf::Color(250, 150, 100));

				if(body->isStatic)
				{
					shape.setFillColor(sf::Color::Red);
				}

				window.Draw(shape);
			}else if(body->shapeType == JPhysics::Box)
			{
				sf::ConvexShape shape{ 4 };
				for(int i = 0; i < 4; ++i)
				{
					shape.setPoint(i, sf::Vector2f(body->GetTransformVertices()[i].x, body->GetTransformVertices()[i].y));
				}
				shape.setOrigin(body->GetPosition().x - 10.f, body->GetPosition().y - 10.f);
				shape.setOutlineThickness(1);
				shape.setPosition(body->GetPosition().x, body->GetPosition().y);
				shape.setOutlineColor(sf::Color(250, 150, 100));

				if (body->isStatic)
				{
					shape.setFillColor(sf::Color::Red);
				}
				window.Draw(shape);
			}
			
		}
	}

	void Scene::OnEvent(Event& event)
	{
		//JE_TRACE("Scene event {0}", event.ToString()); //TODO: Remove test
	}
}
