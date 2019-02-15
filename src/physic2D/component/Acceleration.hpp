#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Acceleration {
		Acceleration() {
			_accel = Vec2(0, 0);
		}

		Acceleration(Vec2 accel) {
			_accel = accel;
		}

		Vec2 _accel;
	};
}}