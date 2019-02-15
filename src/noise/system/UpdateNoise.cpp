#include "UpdateNoise.hpp"
# include <numeric>
# include <cstdint>
# include <algorithm>
#include <random>

namespace noise { namespace system {
	Noise::Noise() {
		auto &game = ecs::Ecs::get();
		auto &screen = ecs::Graphic::get();
		auto size = screen.getWindow()->getSize();

		_id = ecs::entity::Entity::getId();
		game.addComponent<physic2D::component::Pos>(_id, physic2D::Vec2(0, 0));
		game.addComponent<ecs::component::Pixel>(_id, size);
		game.addComponent<ecs::component::Drawable>(_id, true, 10, GraphicalMethod::Pixel);
	}

	float Noise::octaveNoise(float x, float y, std::int32_t octaves)
		{
			float result = 0.0;
			float amp = 1.0;

			for (std::int32_t i = 0; i < octaves; ++i)
			{
				result += perlin(x, y) * amp;
				x *= 2.0;
				y *= 2.0;
				amp *= 0.5;
			}

			return result * 0.5 + 0.5;
		}


		void Noise::updateNoise() {
			auto &game = ecs::Ecs::get();
			auto &pixels = game.getComponentMap<ecs::component::Pixel>();
			auto &pixel = pixels[_id];
			
			double freq, octaves, seed;
			std:: cout << "frequence: " << std::endl;
			std::cin >> freq;
			// std::cin >> seed;
			createP(0);

			octaves = std::clamp(octaves, 1.0, 16.0);
			freq = std::clamp(freq, 0.1, 64.0);
			float fx = pixel._size.x / freq;
			float fy = pixel._size.x / freq;
			for (int i = 0; i < pixel._size.x; i++) {
				for (int j = 0; j < pixel._size.y; j++) {
					float value = octaveNoise(i / fx, j / fy, 4);
					if (value < 0) {
						value = 0;
					}
					pixel.setPixel(sf::Vector2u(i, j), sf::Color(value * 255, value * 255, value * 255, 255));
				}
			}
		}

		void Noise::createP(double seed) {
		std::vector<unsigned int> perm;

		for (unsigned int i = 0; i < 256; i++) {
			perm.push_back(i);
		}
		std::random_shuffle(perm.begin(), perm.end());
		for (unsigned int i = 0; i < 512; i++) {
			_p.push_back(perm[i%256]);
		}
	}

	float Noise::perlin(float x, float y) {
		float xf = x - (int)x;
		float yf = y - (int)y;
		int xi = (int)x & 255;
		int yi = (int)y & 255;
		float u = fade(xf);
		float v = fade(yf);

		int aa = _p[_p[xi] + yi];
		int ab = _p[_p[xi] + yi + 1];
		int ba = _p[_p[xi + 1] + yi];
		int bb = _p[_p[xi + 1] + yi + 1];

		return lerp(v, lerp(u, grad(aa, xf, yf), grad(ba, xf - 1, yf)), lerp(u, grad(ab, xf, yf - 1), grad(bb, xf - 1, yf - 1)));
	}

	float Noise::grad(int hash, float x, float y) {
		const std::int32_t h = hash & 15;
		double z = 0;
		const float u = h < 8 ? x : y;
		const float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	float Noise::lerp(float x, float a, float b) {
		return a + x * (b - a);
	}

	float Noise::fade(float t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
}}
