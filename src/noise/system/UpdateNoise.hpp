#pragma once

#include "../../ecs/Ecs.hpp"
#include "../../component/graphical/Pixel.hpp"
#include "../../component/graphical/Drawable.hpp"
#include "../../ecs/Graphic.hpp"
#include "../../physic2D/system/Physic2D.hpp"
#include <random>
#include <algorithm>

namespace noise { namespace system {
	class Noise {
		public:
			Noise();
			void createP();
			void updateNoise();	
			float perlin(float x, float y);
			float fade(float t);
			float grad(int hash, float x, float y);
			float lerp(float a, float b, float x);
			float octaveNoise(float x, float y, std::int32_t octaves);
			void createP(double seed);
		private:
			ID _id;
			std::vector<int> _p;
	};
}}