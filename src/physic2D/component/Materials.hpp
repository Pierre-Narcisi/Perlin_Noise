#pragma once

#include "../Vec2/vec2.hpp"
#include <string>
#include <unordered_map>

namespace physic2D {
	struct material {
		float _density;
		float _boing;
		float _fricS;
		float _fricD;
	};

	static std::unordered_map<std::string, material> Mat = {
		{ "Rock", {0.6, 0.1, 0.6, 0.4}},
		{ "Wood", {0.3, 0.2, 0.35, 0.20}},
		{ "Metal", {1.2, 0.05, 0.60, 0.45}},
		{ "BouncyBall", {0.3, 0.8, 1, 0.8}},
		{ "SuperBall", {0.3, 0.95, 1, 0.8}},
		{ "Pillow", {0.1, 0.2, 0.5, 0.3}},
		{ "Static", {0.0, 0.4, 0.5, 0.3}}
	};
	namespace component {

		struct Materials {
			Materials() {
				_name = "Rock";
			}

			Materials(std::string name) {
				_name = name;
			}

			std::string _name;
		};
	}
}