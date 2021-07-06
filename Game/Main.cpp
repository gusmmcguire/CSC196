#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <vector>


gme::Vector2 position{ 400,300 };
std::vector<gme::Vector2> points = { {-5,-5}, {5,-5}, {0,5}, {-5,-5} };
gme::Shape shape{ points, gme::Color{.79f,.23f,.90f} };
const float speed = 250;
float timer = 0;
gme::ParticleSystem particleSystem;


float deltaTime;
float gameTime = 0;

bool Update(float dt) {
	deltaTime = dt;
	gameTime += dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	timer += dt * 5;

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);
		gme::Vector2 psPosition;
		psPosition.x = static_cast<float>(x);
		psPosition.y = static_cast<float>(y);
		std::vector<gme::Color> colors{ gme::Color::white, gme::Color::red, gme::Color::green,gme::Color::blue, gme::Color::purple, gme::Color::cyan,gme::Color::orange,gme::Color::yellow };
		particleSystem.Create(psPosition, 100, 3, colors[gme::RandomRangeInt(0,colors.size())], 150);
	}

	particleSystem.Update(dt);

	gme::Vector2 input;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) {input.x = -1;}
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { input.x = 1;}
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) {input.y = -1;}
	if (Core::Input::IsPressed('S') || Core::Input::IsPressed(Core::Input::KEY_DOWN)) {input.y = 1;}
	position += input * speed * dt;
	return quit;
}

void Draw(Core::Graphics& graphics) {
	//float scale = 1 + (std::sin(timer) + 1) * 2;
	float scale = 3;
	shape.Draw(graphics,position, scale);
	particleSystem.Draw(graphics);

	graphics.SetColor(gme::Color::white);
	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 25, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(1/deltaTime).c_str());
}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();
	particleSystem.Shutdown();
}