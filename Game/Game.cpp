#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize() {
	engine = std::make_unique<gme::Engine>();
	engine->Startup();
	scene = std::make_unique<gme::Scene>();
	scene->engine = engine.get();

	engine->Get<gme::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<gme::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints,this,std::placeholders::_1));
	engine->Get<gme::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead,this,std::placeholders::_1));
}

void Game::Shutdown(){
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt){
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		scene->RemoveAllActors();
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel1;
		break;
	case Game::eState::StartLevel1:
	{
		gme::Vector2 playerPosition = { 100.0f, 100.0f };
		if (scene->GetActor<Player>()) playerPosition = { scene->GetActor<Player>()->transform.position.x, 599.0f };
		scene->RemoveAllActors();

		scene->AddActor(std::make_unique<Player>(gme::Transform{ playerPosition, -gme::HalfPi, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("player.txt"), 250.0f));


		scene->AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{700.0f,101.0f}, gme::HalfPi, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("enemy.txt"), 10.0f));
		scene->AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{201.0f,300.0f}, 0.0f, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("enemy.txt"), 10.0f));
		
		MakeRoomOne();
		state = eState::Game1;
	}
		break;
	case Game::eState::Game1:
		if (scene->GetActor<Player>() && scene->GetActor<Player>()->transform.position.y >= 600.0f)state = eState::StartLevel2;
		break;
	case Game::eState::StartLevel2:
	{
		gme::Vector2 playerPosition = { 100.0f, 100.0f };
		if (scene->GetActor<Player>()) playerPosition = { scene->GetActor<Player>()->transform.position.x, 1.0f };
		scene->RemoveAllActors();

		scene->AddActor(std::make_unique<Player>(gme::Transform{ playerPosition, gme::HalfPi, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("player.txt"), 250.0f));

		scene->AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{700.0f,101.0f}, gme::HalfPi, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("enemy.txt"), 10.0f));
		scene->AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{201.0f,300.0f}, 0.0f, 3.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("enemy.txt"), 10.0f));


		MakeRoomTwo();
		state = eState::Game2;
	}
		break;
	case Game::eState::Game2:
		if (scene->GetActor<Player>() && scene->GetActor<Player>()->transform.position.y <= 0.0f)state = eState::StartLevel1;
		break;
	case Game::eState::GameOver:
		scene->RemoveAllActors();
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics){
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(gme::Color::cyan);
		graphics.DrawString(345, 290 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Maze Type Game");
		graphics.SetColor(gme::Color::red);
		graphics.DrawString(322, 305 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Press Space To Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel1:

		break;
	case Game::eState::Game1:
		break;
	case Game::eState::StartLevel2:
		break;
	case Game::eState::Game2:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(gme::Color::red);
		graphics.DrawString(380, 290 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Game Over");
		graphics.SetColor(gme::Color::cyan);
		graphics.DrawString(322, 305 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Press Space To Play Again");
		break;
	default:
		break;
	}

	/*graphics.SetColor(gme::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(770, 20, std::to_string(lives).c_str());*/

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
}

void Game::UpdateStartLevel(float dt)
{
}

void Game::OnAddPoints(const gme::Event& event){
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const gme::Event& event) {
	//std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
}

void Game::MakeRoomOne() {
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,175.0f}, 0.0f,30.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,425.0f}, 0.0f,30.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));

	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{-50.0f,300.0f}, 0.0f,40.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block.txt")));
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{850.0f,300.0f}, 0.0f,40.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block.txt")));

	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,-50.0f}, 0.0f,46.1f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));

}

void Game::MakeRoomTwo() {
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,175.0f}, 0.0f,30.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,425.0f}, 0.0f,30.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));

	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{-50.0f,300.0f}, 0.0f,40.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block.txt")));
	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{850.0f,300.0f}, 0.0f,40.0f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block.txt")));

	scene->AddActor(std::make_unique<RoomBlock>(gme::Transform{ gme::Vector2{400.0f,650.0f}, 0.0f,46.1f }, engine->Get<gme::ResourceSystem>()->Get<gme::Shape>("room_block2.txt")));

}