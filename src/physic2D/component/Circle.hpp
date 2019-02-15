#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Circle {
		Circle() {
			_radius = 0;
		}

		Circle(float radius, bool trigger, bool collidable) {
			_radius = radius;
			_trigger = trigger;
			_collidable = collidable;
		}

		float _radius;
		bool _trigger;
		bool _collidable;
	};
}}