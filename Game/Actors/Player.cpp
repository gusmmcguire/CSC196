#include "Player.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Engine.h"
#include <memory>
#include <vector>

void Player::Update(float dt){
	Actor::Update(dt);

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) { transform.rotation -= gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { transform.rotation += gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) { thrust = speed; }

	transform.position += gme::Vector2::Rotate(gme::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);
	


	//fire
	if (Core::Input::IsPressed(VK_SPACE)) {
		std::shared_ptr<gme::Shape> shape = std::make_shared<gme::Shape>();
		shape->Load("bullet.txt");
		gme::Transform t = transform;
		t.scale = 0.5f;
		scene->AddActor(std::make_unique<Projectile>(transform, shape, 600.0f));
		
	}

	//code for generating particle trail
	//if (thrust > 0) {
	//	engine.Get<gme::ParticleSystem>()->Create(transform.position, 2, 0.5, gme::Color::white, 50);
	//}
}

