#pragma once

#include "../../ecs/Ecs.hpp"
#include "AABB.hpp"
#include "Circle.hpp"
#include "Materials.hpp"
#include <cmath>

namespace physic2D { namespace component {
	struct Mass {
		Mass() {
			_mass = 0;
			_invMass = 0;
		}

		Mass(ID id) {
			auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
	
			if (ecs::Ecs::get().idHasComponents<AABB>(id)) {
				auto &aabb = ecs::Ecs::get().getComponentMap<component::AABB>();

				_mass = aabb[id]._size.x * aabb[id]._size.y * Mat[mat[id]._name]._density;
				if (_mass == 0)
					_invMass = 0;
				else
					_invMass = 1 / _mass;
				
			} else if (ecs::Ecs::get().idHasComponents<Circle>(id)) {
				auto &circ = ecs::Ecs::get().getComponentMap<component::Circle>();

				_mass = circ[id]._radius * circ[id]._radius * M_PI * Mat[mat[id]._name]._density;
				if (_mass == 0)
					_invMass = 0;
				else
					_invMass = 1 / _mass;
			} else {
				_mass = 0;
				_invMass = 0;
			}
		}

		float _mass;
		float _invMass;
		float _inertie;
		float _invInertie;
	};
}}