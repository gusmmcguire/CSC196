#pragma once
#include "Base/Actor.h"

class Enemy : public gme::Actor {
public:
	Enemy(const gme::Transform& transform, gme::Shape* shape, float speed) : gme::Actor{ transform,shape }, speed{ speed }{}

	void Update(float dt) override;

private:
	float speed = 250;
};