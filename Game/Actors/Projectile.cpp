#include "Projectile.h"
#include "Engine.h"

void Projectile::Update(float dt) {
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);

	std::vector<gme::Color> colors{ gme::Color::white, gme::Color::red, gme::Color::green,gme::Color::blue, gme::Color::purple, gme::Color::cyan,gme::Color::orange,gme::Color::yellow };
	scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 10, .5f, colors[gme::RandomRangeInt(0, colors.size())], 10);
}

