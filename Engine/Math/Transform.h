#pragma once
#include "Vector2.h"

namespace gme {
	struct Transform {
		Vector2 position;
		float rotation{ 0 };
		float scale{ 1 };

		Transform() {}
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale }{}
	};
}