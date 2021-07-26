#pragma once
#include "Engine.h"

class Game {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void OnAddPoints(const gme::Event& event);
	void OnPlayerDead(const gme::Event& event);

public:
	std::unique_ptr<gme::Engine> engine;
	std::unique_ptr<gme::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	size_t score = 0;
	size_t lives = 0;

};