#include "Enemy.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	transform.position += gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor){
	if (dynamic_cast<Projectile*>(actor)) {
		scene->engine->Get<gme::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 200, 1, gme::Color::orange, 50);
		destroy = true;
		actor->destroy = true;

	}
}

