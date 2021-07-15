#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <vector>

std::vector<gme::Vector2> points = { {-5,-7}, {0,-4}, {5,-7}, {0,7},{-5,-7} };

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

	scene.GetActor<Player>()->shape->color = gme::Color{ gme::RandomRange(0.0f,1.0f),gme::RandomRange(0.0f,1.0f),gme::RandomRange(0.0f,1.0f) };
	scene.GetActor<Enemy>()->shape->color = gme::Color{ gme::RandomRange(0,1),gme::RandomRange(0,1),gme::RandomRange(0,1) };

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
	std::shared_ptr<gme::Shape> shape1 = std::make_shared<gme::Shape>(points, gme::Color{ 0 , 1 , 0 });
	std::shared_ptr<gme::Shape> shape2 = std::make_shared<gme::Shape>( points, gme::Color{1 , 0 , 0 } );

	Player pl{ gme::Transform{ gme::Vector2{400.0f,300.0f}, 0.0f, 3.0f }, shape1, 250 };
	engine.Get<gme::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(std::make_unique<Player>( gme::Transform{ gme::Vector2{400.0f,300.0f}, 0.0f, 3.0f }, shape1, 250.0f ));
	for (size_t i = 0; i < 100; i++) {
		scene.AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{gme::RandomRange(0.0f,800.0f),gme::RandomRange(0.0f,600.0f)}, gme::RandomRange(0,gme::TwoPi), 2.0f }, shape2, 250.0f ));
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