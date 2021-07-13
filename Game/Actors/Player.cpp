#include "Player.h"
#include "Math/MathUtils.h"

void Player::Update(float dt){
	Actor::Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) { transform.rotation -= gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { transform.rotation += gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) { thrust = speed; }

	transform.position += gme::Vector2::Rotate(gme::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);

	//code for generating particle trail
	//if (thrust > 0) {
	//	engine.Get<gme::ParticleSystem>()->Create(transform.position, 2, 0.5, gme::Color::white, 50);
	//}
}

