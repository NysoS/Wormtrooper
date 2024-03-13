#include "MainScene.h"

#include "../Actor/FlatGround.h"
#include "../Actor/Player.h"
#include "../Actor/Wall.h"
#include "JavaEngine/Gameplay/JActor.h"

MainScene::MainScene()
{
	AddObjectToScene<FlatGround>();
	AddObjectToScene<Wall>();

	Player* player = AddObjectToScene<Player>();
	JPhysics::RigidBodyf* playerRigidBody = player->GetObjectComponent<JPhysics::RigidBodyf>("Rigidbody");
	if(playerRigidBody)
		playerRigidBody->MoveTo(JMaths::Vector2Df(400., 400.f));

	Player* player2 = AddObjectToScene<Player>();
	JPhysics::RigidBodyf* player2RigidBody = player2->GetObjectComponent<JPhysics::RigidBodyf>("Rigidbody");
	if(player2RigidBody)
		player2RigidBody->MoveTo(JMaths::Vector2Df(900., 400.f));
} 

MainScene::~MainScene()
{
}
