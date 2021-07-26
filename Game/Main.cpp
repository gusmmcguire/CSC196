#include "Game.h"
#include <variant>

Game game;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	/*int x, y;
	Core::Input::GetMousePos(x, y);
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);
	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {

		std::vector<gme::Color> colors{ gme::Color::white, gme::Color::red, gme::Color::green,gme::Color::blue, gme::Color::purple, gme::Color::cyan,gme::Color::orange,gme::Color::yellow };
		engine.Get<gme::ParticleSystem>()->Create(psPosition, 150, 2, colors[gme::RandomRangeInt(0,colors.size())], 150);
		engine.Get<gme::AudioSystem>()->PlayAudio("explosion");
	}*/
	game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics) {
	game.Draw(graphics);
}

int main() {

	//system("pause");

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}