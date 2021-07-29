#include "Actor.h"
#include "Graphics/Shape.h"
#include "Math/MathUtils.h"
#include <algorithm>

namespace gme {
	void Actor::Update(float dt){
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Core::Graphics& graphics){
		if (shape) {
			shape->Draw(graphics, transform);
		}
		std::for_each(children.begin(), children.end(), [graphics](auto& child) mutable {if (child->shape)child->shape->Draw(graphics, child->transform); });

	}

	void Actor::addChild(std::unique_ptr<Actor> actor){
		actor->parent = this;
		children.push_back(std::move(actor));
	}

	float Actor::GetRadius(){
		return shape->radius * transform.scale.x;
	}
	float Actor::GetWidth(bool recursion)
	{
		if (transform.rotation == HalfPi && recursion) return GetHeight(false);
		return shape->width * transform.scale.x;
	}
	float Actor::GetHeight(bool recursion)
	{
		if (transform.rotation == HalfPi && recursion) return GetWidth(false);
		return shape->height * transform.scale.y;
	}
}