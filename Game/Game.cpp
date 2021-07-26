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
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		std::shared_ptr<gme::Shape> playerShape = std::make_shared<gme::Shape>();
		playerShape->Load("player.txt");
		std::shared_ptr<gme::Shape> enemyShape = std::make_shared<gme::Shape>();
		enemyShape->Load("enemy.txt");


		scene->AddActor(std::make_unique<Player>(gme::Transform{ gme::Vector2{400.0f,300.0f}, 0.0f, 3.0f }, playerShape, 250.0f));
		for (size_t i = 0; i < 2; i++) {
			scene->AddActor(std::make_unique<Enemy>(gme::Transform{ gme::Vector2{gme::RandomRange(0.0f,800.0f),gme::RandomRange(0.0f,600.0f)}, gme::RandomRange(0,gme::TwoPi), 2.0f }, enemyShape, 250.0f));
		}

		state = eState::Game;
	}
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
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
		graphics.DrawString(350, 290 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Shooty Game");
		graphics.SetColor(gme::Color::red);
		graphics.DrawString(322, 305 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Press Space To Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(gme::Color::red);
		graphics.DrawString(322, 305 + static_cast<int>(std::sin(stateTimer * 4) * 10), "Game Over");
		break;
	default:
		break;
	}

	graphics.SetColor(gme::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(770, 20, std::to_string(lives).c_str());

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
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
}
