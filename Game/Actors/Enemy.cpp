#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	if (scene->GetActor<Player>()) {
		gme::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		transform.rotation = gme::Lerp(transform.rotation, direction.Angle(), dt * 5);
	}

	fireTimer -= dt;
	if (fireTimer <= 0) {
		fireTimer = fireRate;
		std::shared_ptr<gme::Shape> shape = std::make_shared<gme::Shape>();
		shape->Load("bullet.txt");
		gme::Transform t = transform;
		t.scale = 0.5f;
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, shape, 600.0f);
		projectile->tag = "Enemy";
		scene->AddActor(std::move(projectile));

	}

	transform.position += gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor){
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		scene->engine->Get<gme::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 200, 1, gme::Color::orange, 50);
		destroy = true;
		actor->destroy = true;

		gme::Event event;
		event.name = "AddPoints";
		event.data = pointsWorth;
		scene->engine->Get<gme::EventSystem>()->Notify(event);
	}
}

