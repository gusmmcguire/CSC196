#pragma once
#include "Base/Actor.h"


class Player : public gme::Actor {
public:
	Player(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape,float speed) : gme::Actor{ transform,shape }, speed{ speed }{}

	void Update(float dt) override;

private:
	float fireTimer{ 0 };
	float fireRate{ .2f };
	float speed{ 250 };
};