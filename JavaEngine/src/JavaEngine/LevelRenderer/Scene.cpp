#include "Scene.h"

#include <random>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "JavaEngine/Core/Application.h"
#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Gameplay/JActor.h"
#include "JavaEngine/Physics/Collisions.h"

namespace JavaEngine
{
	Scene::Scene()
	{
		//TODO: Remove test
		JObject* tomate = AddObjectToScene<JActor>();
		tomate->m_Name = "Tomate";

		//TODO: Remove test
		JObject* pomme = AddObjectToScene<JActor>();
		pomme->m_Name = "Pomme";

		for(int i = 0; i < 6; ++i)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dist(10, 400);

			float x = dist(gen);
			float y = dist(gen);

			/*if(i%2==0)
			{
				rigidBodyList.push_back(JPhysics::RigidBodyf::CreateCircleBody(10.f, JMaths::Vector2Df(x, y), 2.f, false, 0.5f));
			}else*/
			//{
				rigidBodyList.push_back(JPhysics::RigidBodyf::CreateBoxBody(20.f, 20.f , JMaths::Vector2Df(x, y), 2.f, false, 0.5f));
			//}
		}
	}

	Scene::~Scene()
	{
		for (auto* object : m_ObjectList)
		{
			delete object;
		}
		m_ObjectList.clear();

		for (auto body : rigidBodyList)
		{
			delete body;
		}
		rigidBodyList.clear();
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
		float speed = 2.f;
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
			JMaths::Vector2Df direction = JMaths::Vector2Df(dx, dy).normalilze();
			JMaths::Vector2Df velocity = direction * speed;
			
			rigidBodyList[0]->Move(velocity);
		}

		for(int i = 0; i < rigidBodyList.size(); ++i)
		{
			JPhysics::RigidBodyf* bodyA = rigidBodyList[i];
			//bodyA->Rotate(0.01f * 0.01f);
		}

		for(int i = 0; i < rigidBodyList.size() - 1; ++i)
		{
			JPhysics::RigidBodyf* bodyA = rigidBodyList[i];
			for (int j = 1; j < rigidBodyList.size(); ++j)
			{
				JPhysics::RigidBodyf* bodyB = rigidBodyList[j];

				JMaths::Vector2Df normal{};
				float depth{0};

				if (JPhysics::Collisions<float>::IntersectPolygons(bodyA->GetTransformVertices(), bodyB->GetTransformVertices(), normal, depth))
				{
					JE_INFO("depth {0}", depth);
					bodyA->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
					bodyB->Move(normal * (depth / 2.f));
				}

				//if(JPhysics::Collisions<float>::IntersectCircles(
				//	bodyA->GetPosition(), bodyA->radius,
				//	bodyB->GetPosition(), bodyB->radius,
				//	normal, depth))
				//{
				//	JE_INFO("depth {0} {1}", normal.x, normal.y);
				//	bodyA->Move(JMaths::Vector2Df(-normal.x, -normal.y) * (depth / 2.f));
				//	bodyB->Move(normal * (depth / 2.f));
				//}
			}
		}
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

		for(auto* body : rigidBodyList)
		{
			if(body->shapeType == JPhysics::Circle)
			{
				sf::CircleShape shape{ body->radius };
				shape.setOutlineThickness(3);
				shape.setPosition(body->GetPosition().x, body->GetPosition().y);
				shape.setOutlineColor(sf::Color(250, 150, 100));
				window.Draw(shape);
			}else if(body->shapeType == JPhysics::Box)
			{
				sf::ConvexShape shape{ 4 };
				shape.setOrigin(body->GetPosition().x, body->GetPosition().y);
				for(int i = 0; i < 4; ++i)
				{
					shape.setPoint(i, sf::Vector2f(body->GetTransformVertices()[i].x, body->GetTransformVertices()[i].y));
				}
				shape.setOutlineThickness(3);
				shape.setPosition(body->GetPosition().x, body->GetPosition().y);
				shape.setOutlineColor(sf::Color(250, 150, 100));
				window.Draw(shape);
			}
			
		}
	}

	void Scene::OnEvent(Event& event)
	{
		//JE_TRACE("Scene event {0}", event.ToString()); //TODO: Remove test
	}
}
