#include "Physic2D.hpp"

namespace physic2D { namespace system {
	Physic2D::Physic2D() {
		_lastTime = ecs::Time::get(TimeUnit::NanoSeconds);
	}

	void Physic2D::UpdatePos() {
		auto AABBIds = ecs::Ecs::get().filter<component::AABB>();
		auto polyIds = ecs::Ecs::get().filter<component::Poly>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &AABB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &poly = ecs::Ecs::get().getComponentMap<component::Poly>();

		for (auto id : AABBIds) {
			if (!ecs::Ecs::get().idHasComponents<component::Pos>(id)) {
				ecs::Ecs::get().addComponent<component::Pos>(id);
				pos = ecs::Ecs::get().getComponentMap<component::Pos>();
			}
			AABB[id]._max = pos[id]._pos + AABB[id]._size / 2;
			AABB[id]._min = pos[id]._pos - AABB[id]._size / 2;
		}

		// for (auto id : polyIds) {
		// 	if (!ecs::Ecs::get().idHasComponents<component::Pos>(id)) {
		// 		ecs::Ecs::get().addComponent<component::Pos>(id);
		// 		pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		// 	}
		// 	poly[id]._max = pos[id]._pos + poly[id]._size / 2;
		// 	poly[id]._min = pos[id]._pos - poly[id]._size / 2;
		// }
	}

	void Physic2D::UpdateSpeed() {
		auto ids = ecs::Ecs::get().filter<component::Speed>();
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();

		for (auto id : ids) {
			if (!ecs::Ecs::get().idHasComponents<component::Pos>(id)) {
				ecs::Ecs::get().addComponent<component::Pos>(id);
				pos = ecs::Ecs::get().getComponentMap<component::Pos>();
			}
			pos[id]._pos.x += speed[id]._speed.x * _deltaTime;
			pos[id]._pos.y += speed[id]._speed.y * _deltaTime;
		}

	}

	void Physic2D::UpdateAcceleration() {
		auto ids = ecs::Ecs::get().filter<component::Acceleration>();
		auto &accel = ecs::Ecs::get().getComponentMap<component::Acceleration>();
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();

		for (auto id : ids) {
			if (!ecs::Ecs::get().idHasComponents<component::Speed>(id)) {
				ecs::Ecs::get().addComponent<component::Speed>(id);
				speed = ecs::Ecs::get().getComponentMap<component::Speed>();
			}
			speed[id]._speed.x += accel[id]._accel.x * _deltaTime;
			speed[id]._speed.y += accel[id]._accel.y * _deltaTime;
		}
	}

	void Physic2D::UpdateForces() {
		auto ids = ecs::Ecs::get().filter<component::Forces>();
		auto &forces = ecs::Ecs::get().getComponentMap<component::Forces>();
		auto &accel = ecs::Ecs::get().getComponentMap<component::Acceleration>();

		for (auto id : ids) {
			Vec2 tmp = Vec2(0, 0);
			for (auto force : forces[id]._forces) {
				tmp += force;
			}
			accel[id]._accel = tmp;
			forces[id]._forces.clear();
		}
	}

	void Physic2D::UpdatePhysic() {
		long newTime = ecs::Time::get(TimeUnit::NanoSeconds);
	
		_deltaTime = (newTime - _lastTime) / 1000000000.f;
		_lastTime = newTime;
		UpdateForces();
		UpdateAcceleration();
		UpdateSpeed();
		UpdatePos();
	}
}}