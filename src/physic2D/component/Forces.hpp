#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Forces {
		Forces() {
		}

		std::vector<Vec2> _forces;
	};
}}