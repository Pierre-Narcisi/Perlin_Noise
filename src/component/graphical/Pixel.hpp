//
// Created by seb on 09/01/19.
//

#pragma once

#include "ecs/Vector2.hpp"
#include <string.h>
#ifndef SERVER
#include <SFML/Graphics.hpp>
#endif
namespace ecs { namespace component {
	struct Pixel {
		Pixel() {}

		Pixel(sf::Vector2u size) {
			_pixels = new sf::Uint8[size.x * size.y * 4];
			memset(_pixels, 0x00, size.x * size.y * 4);
			_size = size;
		}

		void setPixel(sf::Vector2u pos, sf::Color color) {
			_pixels[(_size.x * pos.y) * 4 + pos.x * 4] = color.r;
			_pixels[(_size.x * pos.y) * 4 + pos.x * 4 + 1] = color.g;
			_pixels[(_size.x * pos.y) * 4 + pos.x * 4 + 2] = color.b;
			_pixels[(_size.x * pos.y) * 4 + pos.x * 4 + 3] = color.a;
		}

#ifndef SERVER
		sf::Uint8 *_pixels;
		sf::Vector2u _size;
#endif
	};
}}