#include "Scene.h"
#include "Actor.h"
#include "Graphics/Shape.h"
#include "Math/MathUtils.h"
#include <algorithm>

namespace gme {
	void Scene::Update(float dt){
		//add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		//update actors
		std::for_each(actors.begin(), actors.end(), [dt](auto& actor) {actor->Update(dt); });

		//check collision
		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				if (actors[i]->tag == "room" || actors[j]->tag == "room") continue;
				if (actors[i]->destroy || actors[j]->destroy) continue;
				Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();
				if (distance < actors[i]->GetRadius() + actors[j]->GetRadius()) {
					actors[i]->OnCollision(actors[j].get());
					actors[j]->OnCollision(actors[i].get());
				}
			}
		}

		//check wall collision
		// assumes 4 point wall
		//delete when not needed
		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				if (actors[i]->tag != "room" && actors[j]->tag != "room") continue;
				if(actors[i]->tag == "room" && actors[j]->tag == "room") continue;
				if (actors[i]->destroy || actors[j]->destroy) continue;

				float a1LeftX = actors[i]->shape->topLeftCorner.x * actors[i]->transform.scale.x + actors[i]->transform.position.x;
				float a1TopY = actors[i]->shape->topLeftCorner.y * actors[i]->transform.scale.y + actors[i]->transform.position.y;
				float a2LeftX = actors[j]->shape->topLeftCorner.x * actors[j]->transform.scale.x + actors[j]->transform.position.x;
				float a2TopY = actors[j]->shape->topLeftCorner.y * actors[j]->transform.scale.y + actors[j]->transform.position.y;

				Vector2 a1 = { a1LeftX,a1TopY };
				Vector2 a2 = { a2LeftX,a2TopY };


				if ((a1.x < a2.x + actors[j]->GetWidth(true) )&&
					(a1.x + actors[i]->GetWidth(true) > a2.x)&&
					(a1.y < a2.y + actors[j]->GetHeight(true)) &&
					(a1.y + actors[i]->GetHeight(true) > a2.y)) {
					
					//std::cout << "reached point" << std::endl;
					actors[i]->OnCollisionBox(actors[j].get());
					actors[j]->OnCollisionBox(actors[i].get());
				}
			}
		}



		//destroy actors
		auto iter = actors.begin();
		while (iter != actors.end()) {
			if ((*iter)->destroy) {
				iter = actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Draw(Core::Graphics& graphics){
		std::for_each(actors.begin(), actors.end(), [graphics](auto& actor) mutable {actor->Draw(graphics); });
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor){
		actor->scene = this;
		actor->Initialize();
		newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor){

	}

	void Scene::RemoveAllActors(){
		actors.clear();
	}
}

