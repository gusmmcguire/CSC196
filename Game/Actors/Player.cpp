#include "Player.h"
#include "Enemy.h"
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

	transform.position += gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * thrust * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);
	


	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		fireTimer = fireRate;
		std::shared_ptr<gme::Shape> shape = std::make_shared<gme::Shape>();
		shape->Load("bullet.txt");
		gme::Transform t = transform;
		t.scale = 0.5f;
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, shape, 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
		
	}

	//generate particle trail
	if (thrust > 0) {
		scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 2, 0.5, gme::Color::white, 50);
	}
}

void Player::OnCollision(Actor* actor) {
	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")) {
		scene->engine->Get<gme::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 200, 1, gme::Color::orange, 50);
		destroy = true;
		actor->destroy = true;

		gme::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes i'm dead!");
		scene->engine->Get<gme::EventSystem>()->Notify(event);
	}
}