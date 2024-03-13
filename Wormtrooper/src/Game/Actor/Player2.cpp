#include "Player2.h"

#include <SFML/Window/Keyboard.hpp>

Player2::Player2(JPhysics::JWorld* world)
	: JActor(world)
{
	JPhysics::RigidBodyf* rigid = JPhysics::RigidBodyf::CreateBoxBody(20.f, 20.f, 10.f, false, 0);

	if (getWorld())
	{
		getWorld()->AddRigidbody(rigid);
	}
	AddObjectComponent(rigid);
}

Player2::~Player2()
{
}

void Player2::Update(const float& deltaTime)
{
	JActor::Update(deltaTime);

	JPhysics::RigidBodyf* rigid = GetObjectComponent<JPhysics::RigidBodyf>("Rigidbody");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// TODO
		if (rigid)
		{
			rigid->Move(JMaths::Vector2Df{ 5.f,0 });
		}
	}

	// ALLOWS TO MOVE PLAYER TO LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (rigid)
		{
			rigid->Move(JMaths::Vector2Df{ -5.f,0 });
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		if (rigid)
		{
			rigid->AddForce(JMaths::Vector2Df{ 0,-20.f });
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		if (timer >= fireRate)
		{
			JPhysics::RigidBodyf* Ball = JPhysics::RigidBodyf::CreateCircleBody(10.f, 2.f, false, .6f);
			Ball->MoveTo(rigid->collider->position + JMaths::Vector2Df{ -10.f,0.f });
			if (getWorld())
			{
				getWorld()->AddRigidbody(Ball);
			}
			Ball->AddForce(JMaths::Vector2Df{ -250.f, -250.f });

			timer = 0.f;
		}
		else
		{
			timer += deltaTime;
		}
	}
}
