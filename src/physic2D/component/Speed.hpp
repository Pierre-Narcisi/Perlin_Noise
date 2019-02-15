#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Speed {
		Speed() {
			_speed = Vec2(0, 0);
		}

		Speed(Vec2 speed) {
			_speed = speed;
		}

		Vec2 _speed;
	};
}}