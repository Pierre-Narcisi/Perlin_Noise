#pragma once

#include "../component/AABB.hpp"
#include "../component/Speed.hpp"
#include "../component/Pos.hpp"
#include "../component/Materials.hpp"
#include "../component/Mass.hpp"
#include "../component/Forces.hpp"
#include "../../ecs/Ecs.hpp"
#include "../manifold.hpp"

namespace physic2D { namespace system {
	class Gravity {
		public:
			void updateGravity();
			void addObject(ID id);
		private:
			std::vector<ID> _object;
	};
}}