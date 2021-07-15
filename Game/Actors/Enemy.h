#pragma once
#include "Base/Actor.h"

class Enemy : public gme::Actor {
public:
	Enemy(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape, float speed) : gme::Actor{ transform,shape }, speed{ speed }{}

	void Update(float dt) override;

private:
	float speed = 250;
};