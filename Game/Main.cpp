#include "core.h"
#include <iostream>
#include <vector>

struct Vector2 {
	float x, y;

	Vector2() : x{ 0 }, y{ 0 } {};
	Vector2(float x, float y) : x{ x }, y{ y }{};
	Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{};

	Vector2 operator + (const Vector2& v) const { return { v.x + x, v.y + y }; }
	Vector2 operator * (const float s) const { return { s * x, s * y }; }
	Vector2 operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2 operator *= (const float s) { x *= s; y *= s; return *this; }
};

Vector2 position{ 400,300 };
std::vector<Vector2> points = { {-5,-5}, {5,-5}, {0,5}, {-5,-5} };
const float speed = 5;
float timer = 0;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	timer += dt * 5;
	/*int x, y;
	Core::Input::GetMousePos(x, y);
	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);*/
	Vector2 input;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) {
		input.x = -1;
	}
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) {
		input.x = 1;
	}
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) {
		input.y = -1;
	}
	if (Core::Input::IsPressed('S') || Core::Input::IsPressed(Core::Input::KEY_DOWN)) {
		input.y = 1;
	}
	input *= speed;
	position += input;
	return quit;
}

void Draw(Core::Graphics& graphics) {

	for (int i = 0; i < 30; i++) {
		graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	}

	graphics.SetColor(RGB(255, 255, 255));
	//graphics.DrawLine(0,0, position.x,position.y);
	float scale = 1 + (std::sin(timer) + 1) * 2;
	for (size_t i = 0; i < points.size()-1; i++) {
		Vector2 p1 = (position + (points[i] * scale));
		Vector2 p2 = (position + (points[i + 1] * scale) );
		graphics.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();
}