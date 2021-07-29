#pragma once
#include "Base/Actor.h"


class RoomBlock : public gme::Actor {
public:
	RoomBlock(const gme::Transform& transform, std::shared_ptr<gme::Shape> shape) : gme::Actor{ transform,shape } {
		tag = "room";
	}
};