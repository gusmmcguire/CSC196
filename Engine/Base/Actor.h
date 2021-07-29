#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "core.h"
#include <vector>
#include <memory>

namespace gme {
	class Shape;
	class Scene;

	class Actor : public Object {
	public:
		Actor() {}
		Actor(const Transform& transform, std::shared_ptr<Shape> shape = {}) : transform{ transform }, shape{ shape }{}

		virtual void Initialize() {};

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor){}
		virtual void OnCollisionBox(Actor* actor){}

		void addChild(std::unique_ptr<Actor> actor);

		float GetRadius();

		float GetWidth(bool recursion);
		float GetHeight(bool recursion);
		float GetCorner();

	public:
		bool destroy{ false };
		std::string tag = "";

		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{ nullptr };

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;
	};
}