#pragma once

namespace gme {
	struct Vector2 {
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {};
		Vector2(float x, float y) : x{ x }, y{ y }{};
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{};

		Vector2 operator + (const Vector2& v) const { return { v.x + x, v.y + y }; }
		
		Vector2 operator - (const Vector2& v) const { return {  x- v.x ,y-v.y }; }

		Vector2 operator * (const float s) const { return { s * x, s * y }; }
		
		Vector2 operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		
		Vector2 operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }

		Vector2 operator *= (const float s) { x *= s; y *= s; return *this; }
	};
}