#include "Scene.h"

#include <random>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

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



		//for(int i = 0; i < 10; ++i)
		//{
		//	std::random_device rd;
		//	std::mt19937 gen(rd());
		//	std::uniform_real_distribution<> dist(10, 600);

		//	std::uniform_int_distribution<> bo(0, 1);

		//	float x = dist(gen);
		//	float y = dist(gen);

		//	bool isStatic = false;

		//	if(i > 0)
		//		isStatic = bo(gen)==0?false:true;


		//	JPhysics::RigidBodyf* simpleBall = JPhysics::RigidBodyf::CreateCircleBody(10.f, 10.f, isStatic, 0.5f);
		//	simpleBall->MoveTo(JMaths::Vector2Df(x, y));
		//	m_World->AddRigidbody(simpleBall);
		//}

		float maxWidth = Application::Get().GetWindow().GetWidth();
		float maxHeight = Application::Get().GetWindow().GetHeight();

		JPhysics::RigidBodyf* flatGround = JPhysics::RigidBodyf::CreateBoxBody(1000.f, 20.f, 10.f, true, 0);
		flatGround->MoveTo(JMaths::Vector2Df(640.f, 500.f));
		m_World->AddRigidbody(flatGround);

		JPhysics::RigidBodyf* rotatePlateform = JPhysics::RigidBodyf::CreateBoxBody(400, 20.f, 10.f, true, 0);
		rotatePlateform->MoveTo(JMaths::Vector2Df(240.f, 400.f));
		rotatePlateform->Rotate(6.28f / 30.f);
		m_World->AddRigidbody(rotatePlateform);

		JPhysics::RigidBodyf* rotatePlateform2 = JPhysics::RigidBodyf::CreateBoxBody(400, 20.f, 10.f, true, 0);
		rotatePlateform2->MoveTo(JMaths::Vector2Df(840.f, 200.f));
		rotatePlateform2->Rotate(6.28f / -30.f);
		m_World->AddRigidbody(rotatePlateform2);
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


		/*float dx = 0.f;
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
		}*/

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dist(10.f, 50.f);

			float width = dist(gen);
			float height = dist(gen);

			JMaths::Vector2Df mouseP(sf::Mouse::getPosition().x - 320.f, sf::Mouse::getPosition().y - 250.f);

			JPhysics::RigidBodyf* Box = JPhysics::RigidBodyf::CreateBoxBody(width, height, 2.f, false, .6f);
			Box->MoveTo(mouseP);
			m_World->AddRigidbody(Box);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			/*std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dist(5.f, 20.f);

			float radius = dist(gen);*/

			JMaths::Vector2Df mouseP(sf::Mouse::getPosition().x - 320.f, sf::Mouse::getPosition().y - 250.f);

			JPhysics::RigidBodyf* Ball = JPhysics::RigidBodyf::CreateCircleBody(10.f, 2.f, false, .6f);
			Ball->MoveTo(mouseP);
			m_World->AddRigidbody(Ball);

		}

		/*if(clock.s > 1)
		{
			totalBodyCount = 0;
			totalWorldStepTime = 0;
			totalSampleCount = 0;
			clock.reset;
		}*/

		m_World->Step(0.08f, 20);
		totalWorldStepTime += 0.08f;
		totalBodyCount += m_World->RigidbodyCount();
		totalSampleCount++;

		for(int i =0; i < m_World->RigidbodyCount(); ++i)
		{
			JPhysics::RigidBodyf* body = m_World->GetRigidbody(i);
			if(!body || body->isStatic)
			{
				continue;
			}

			JPhysics::AABB<float> box = body->GetAABB();
			if(box.max.y > Application::Get().GetWindow().GetHeight())
			{
				JE_INFO("body removed, max body {0}", m_World->RigidbodyCount());
				m_World->RemoveRigidbody(body);
			}
			JE_CORE_INFO("body angularVelocity {0}", body->angularVelocity);
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
				shape.setRadius(body->radius);
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

		/*for(auto& contactPoints : m_World->m_contactPointsList)
		{
			sf::CircleShape debugContactPoint{ 5.f };
			debugContactPoint.setPosition(contactPoints.x + 5.f, contactPoints.y + 5.f);
			debugContactPoint.setOutlineThickness(2);
			debugContactPoint.setOutlineColor(sf::Color::Magenta);
			window.Draw(debugContactPoint);
		}*/
	}

	void Scene::OnEvent(Event& event)
	{
		//JE_TRACE("Scene event {0}", event.ToString()); //TODO: Remove test
	}
}
