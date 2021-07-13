#include "Actor.h"
#include "Graphics/Shape.h"

namespace gme {
	void Actor::Update(float dt){

	}

	void Actor::Draw(Core::Graphics& graphics){
		shape->Draw(graphics, transform);
	}
}