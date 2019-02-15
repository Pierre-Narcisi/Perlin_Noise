#pragma once

#include "Pos.hpp"
#include "../Vec2/vec2.hpp"
#include "../../ecs/Ecs.hpp"
#include <vector>

namespace physic2D { namespace component {
	struct Poly {
		Poly(): _size(0, 0) {
		}

		Poly(ID id, Vec2 size): _size(size) {
			auto pos = ecs::Ecs::get().getComponentMap<component::Pos>();

			_vertices.push_back(Vec2(-size.x / 2, -size.y / 2));
			_vertices.push_back(Vec2(size.x / 2, -size.y / 2));
			_vertices.push_back(Vec2(size.x / 2, size.y / 2));
			_vertices.push_back(Vec2(-size.x / 2, size.y / 2));
			_normales.push_back(Vec2(0, -1));
    		_normales.push_back(Vec2(1, 0));
    		_normales.push_back(Vec2(0, 1));
			_normales.push_back(Vec2(-1, 0));
		}

		Vec2 getSupport(const Vec2 &dir) {
			float bestDist = -__FLT_MAX__;
			Vec2 bestV;

			for (auto v : _vertices) {
				auto dist = v.dot(dir);
				if (dist > bestDist) {
					bestV = v;
					bestDist = dist;
				}
			}
			return bestV;
		}

		Vec2 _size;
		std::vector<Vec2> _vertices;
		std::vector<Vec2> _normales;
	};
}}