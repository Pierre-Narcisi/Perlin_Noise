#pragma once

#include <functional>
#include "../../ecs/Ecs.hpp"
#include "../Vec2/vec2.hpp"

namespace physic2D { namespace component {
	struct Script {
		Script() {
			_script = NULL;
		}

		Script(std::function<void(ID id)> script) {
			_script = script;
		}

		std::function<void(ID id)> _script;
	};
}}