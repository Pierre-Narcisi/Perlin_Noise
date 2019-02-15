#pragma once

#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Pos {
		Pos() {
			_pos = Vec2(0, 0);
		}

		Pos(Vec2 pos) {
			_pos = pos;
		}

		Vec2 _pos;
	};
}}