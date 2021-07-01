#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <vector>


gme::Vector2 position{ 400,300 };
std::vector<gme::Vector2> points = { {-5,-5}, {5,-5}, {0,5}, {-5,-5} };
gme::Shape shape{ points, gme::Color{.79f,.23f,.90f} };
const float speed = 5;
float timer = 0;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	timer += dt * 5;
	gme::Vector2 input;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) {input.x = -1;}
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { input.x = 1;}
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) {input.y = -1;}
	if (Core::Input::IsPressed('S') || Core::Input::IsPressed(Core::Input::KEY_DOWN)) {input.y = 1;}
	input *= speed;
	position += input;
	return quit;
}

void Draw(Core::Graphics& graphics) {
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics,position,scale);
	
}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();
}