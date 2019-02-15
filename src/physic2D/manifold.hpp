#pragma once

#include "Vec2/vec2.hpp"
#include "../ecs/Ecs.hpp"

namespace physic2D {
	struct manifold {
		ID A;
		ID B;
		float penetration;
		Vec2 normal;
		float j;
	};
}
