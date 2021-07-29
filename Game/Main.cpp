#include "Game.h"
#include <variant>

Game game;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics) {
	game.Draw(graphics);
}

int main() {

	//system("pause");

	char name[] = "Maze Type Game";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}