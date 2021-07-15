#include "Scene.h"
#include "Actor.h"

namespace gme {
	void Scene::Update(float dt){
		for (auto& actor : actors) {
			actor->Update(dt);
		}
	}
	void Scene::Draw(Core::Graphics& graphics){
		for (auto& actor : actors) {
			actor->Draw(graphics);
		}
	}
	void Scene::AddActor(std::unique_ptr<Actor> actor){
		actor.get()->scene = this;
		actors.push_back(std::move(actor));
	}
}

