#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Graphics/Shape.h"
#include "Engine.h"
#include <iostream>
#include <string>
#include <vector>


std::vector<gme::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
gme::Shape shape{ points, gme::Color{0 , 1 , 0 } };
gme::Transform transform{ {400,300}, 0, 3 };

const float speed = 250;
float timer = 0;
gme::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

gme::Engine engine;

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
		engine.Get<gme::ParticleSystem>()->Create(psPosition, 150, 2, colors[gme::RandomRangeInt(0,colors.size())], 150);
	}

	float thrust = 0;
	if (Core::Input::IsPressed('A') || Core::Input::IsPressed(Core::Input::KEY_LEFT)) {transform.rotation -= gme::DegToRad(180) * dt;}
	if (Core::Input::IsPressed('D') || Core::Input::IsPressed(Core::Input::KEY_RIGHT)) {transform.rotation += gme::DegToRad(180) * dt;}
	if (Core::Input::IsPressed('W') || Core::Input::IsPressed(Core::Input::KEY_UP)) {thrust = speed;}
	
	transform.position += gme::Vector2::Rotate(gme::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = gme::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Wrap(transform.position.y, 0.0f, 600.0f);
	
	engine.Get<gme::ParticleSystem>()->Create(transform.position, 2, 0.5, gme::Color::white, 50);

	engine.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics) {
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics,transform);
	engine.Get<gme::ParticleSystem>()->Draw(graphics);

	gme::Color color = gme::Lerp(gme::Color::green, gme::Color::orange, transform.position.x / 800);
	graphics.SetColor(color);
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
	
	engine.Startup();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}