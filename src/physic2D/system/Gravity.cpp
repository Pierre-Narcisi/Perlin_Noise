#include "Gravity.hpp"

namespace physic2D { namespace system {
	void Gravity::updateGravity() {
		auto &forces = ecs::Ecs::get().getComponentMap<component::Forces>();
		
		for (auto id : _object) {
			if (!ecs::Ecs::get().idHasComponents<component::Forces>(id)) {
				ecs::Ecs::get().addComponent<component::Forces>(id);
				forces = ecs::Ecs::get().getComponentMap<component::Forces>();
			}
			forces[id]._forces.push_back(Vec2(0, 9.8 * 4));
		}
	}

	void Gravity::addObject(ID id) {
		_object.push_back(id);
	}
}}