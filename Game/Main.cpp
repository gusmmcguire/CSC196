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
std::vector<gme::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
gme::Shape shape{ points, gme::Color{0 , 1 , 0 } };
const float speed = 250;
float timer = 0;
gme::ParticleSystem particleSystem;
gme::Vector2 psPosition;
float angle = 0;

float deltaTime;
float gameTime = 0;

bool Update(float dt) {
	deltaTime = dt;
	gameTime += dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	timer += dt * 5;

	int x, y;
	Core::Input::GetMousePos(x, y);
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);
	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {

		std::vector<gme::Color> colors{ gme::Color::white, gme::Color::red, gme::Color::green,gme::Color::blue, gme::Color::purple, gme::Color::cyan,gme::Color::orange,gme::Color::yellow };
		particleSystem.Create(psPosition, 150, 2, colors[gme::RandomRangeInt(0,colors.size())], 150);
	}

	particleSystem.Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) {angle -= 5 * dt;}
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) {angle += 5 * dt;}
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) {thrust = speed;}
	
	//if (Core::Input::IsPressed('S') || Core::Input::IsPressed(Core::Input::KEY_DOWN)) {input.y = 1;}
	position += gme::Vector2::Rotate(gme::Vector2::down, angle) * thrust * dt;
	particleSystem.Create(position, 2, 0.5, gme::Color::white, 200);
	return quit;
}

void Draw(Core::Graphics& graphics) {
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics, position, angle, 3);
	particleSystem.Draw(graphics);

	graphics.SetColor(gme::Color::white);
	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 25, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(1/deltaTime).c_str());

	graphics.DrawString(10, 55, std::to_string(psPosition.Length()).c_str());
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