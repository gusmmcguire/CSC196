#include "Player.h"
#include "Enemy.h"
#include "RoomBlock.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Engine.h"
#include <memory>
#include <vector>

Player::Player(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape, float speed) : gme::Actor{ transform,shape }, speed{ speed }{}

void Player::Initialize() {
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = gme::Vector2{ 5,0 };
	addChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = gme::Vector2{ -6,0 };
	locator->transform.localRotation = gme::DegToRad(180);
	addChild(std::move(locator));
}

void Player::Update(float dt){
	Actor::Update(dt);
	dT = dt;

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) { transform.rotation -= gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { transform.rotation += gme::DegToRad(180) * dt; }
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) { thrust = speed; }

	gme::Vector2 acceleration;
	acceleration = gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * thrust;

	//gme::Vector2 gravity = (gme::Vector2{400, 300} - transform.position).Normalized() * 50;
	/*gme::Vector2 gravity = gme::Vector2::down * 100;
	acceleration += gravity;*/


	velocity += acceleration * dt;
	//velocity = gme::Clamp(velocity.x, -500.0f, 500.0f);
	//velocity = gme::Clamp(velocity.y, -500.0f, 500.0f);
	transform.position += velocity * dt;

	velocity *= .93f;


	transform.position.x = gme::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Clamp(transform.position.y, 0.0f, 600.0f);
	


	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		fireTimer = fireRate;

		std::shared_ptr<gme::Shape> shape = std::make_shared<gme::Shape>();
		shape->Load("bullet.txt");
		gme::Transform t = children[0]->transform;
		t.scale = 5;
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape, 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
		
	}

	//generate particle trail
	if (thrust > 0) {
		std::vector<gme::Color> colors = { gme::Color::white, gme::Color::blue, gme::Color::red };
		scene->engine->Get<gme::ParticleSystem>()->Create(children[1]->transform.position, 2, 0.5, colors, 50, children[1]->transform.localRotation, gme::DegToRad(30));
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

void Player::OnCollisionBox(Actor* actor) {
	if (dynamic_cast<RoomBlock*>(actor)) {
		//std::cout << "hit" << std::endl;
		velocity = -velocity;
	}
}