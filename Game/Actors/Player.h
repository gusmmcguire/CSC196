#pragma once
#include "Base/Actor.h"

class Player : public gme::Actor {
public:
	Player(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
	void OnCollisionBox(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ .2f };
	float speed{ 750 };
	float dT{ 0 };
	gme::Vector2 velocity;
};