#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<gme::Vector2> points = { {-5,-7}, {0,-4}, {5,-7}, {0,7},{-5,-7} };
gme::Shape shape{ points, gme::Color{0 , 1 , 0 } };
gme::Shape shape2{ points, gme::Color{1 , 0 , 0 } };
gme::Transform transform{ {400,300}, 0, 3 };

float timer = 0;
gme::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

gme::Engine engine;
gme::Scene scene;



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
		engine.Get<gme::AudioSystem>()->PlayAudio("explosion");
	}

	scene.Update(dt);
	engine.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics) {
	scene.Draw(graphics);
	engine.Get<gme::ParticleSystem>()->Draw(graphics);

	gme::Color color = gme::Lerp(gme::Color::green, gme::Color::orange, transform.position.x / 800);
	graphics.SetColor(color);
	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 25, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(1/deltaTime).c_str());
	graphics.DrawString(10, 55, std::to_string(psPosition.Length()).c_str());

}

void Init() {
	engine.Get<gme::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(new Player{ { {400,300}, 0, 3 }, &shape, 250 });
	for (size_t i = 0; i < 100; i++) {
		scene.AddActor(new Enemy{ { {gme::RandomRange(0,800),gme::RandomRange(0,600)}, gme::RandomRange(0,gme::TwoPi), 2 }, &shape2, 250 });
	}
}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	engine.Startup();
	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}