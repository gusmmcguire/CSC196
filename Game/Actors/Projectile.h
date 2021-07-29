#pragma once
#include "Base/Actor.h"

class Projectile : public gme::Actor {
public:
	Projectile(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape, float speed) : gme::Actor{ transform,shape }, speed{ speed }{}

	void Initialize() override;

	void Update(float dt) override;

	void OnCollisionBox(Actor* actor) override;

private:
	float lifetime{ 1 };
	float speed{ 250 };
	bool hitWall{ false };
};