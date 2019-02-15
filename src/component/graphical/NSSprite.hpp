//
// Created by seb on 26/12/18.
//

#pragma once

#ifndef SERVER
#include <SFML/Graphics.hpp>
#endif /// SERVER
#include <ecs/Vector2.hpp>
#include <ecs/DataBank.hpp>

namespace ecs { namespace component {
	struct NSSprite {
		NSSprite() {}

	#ifndef SERVER
		NSSprite(std::string const &path) {
			this->sprite = new sf::Sprite();
			this->sprite->setTexture(ecs::DataBank<std::string, sf::Texture>::get()[path]);

			auto sizeT = this->sprite->getTexture()->getSize();
			this->size.x = sizeT.x;
			this->size.y = sizeT.y;

			this->boxSize = this->size;
		}

		NSSprite(std::string path, ecs::core::Vector2<unsigned int> size) {
			this->sprite = new sf::Sprite();
			this->sprite->setTexture(ecs::DataBank<std::string, sf::Texture>::get()[path]);

			auto sizeT = this->sprite->getTexture()->getSize();
			this->size.x = sizeT.x;
			this->size.y = sizeT.y;

			float y = size.y / this->size.y;
			float x = size.x / this->size.x;

			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);

			this->sprite->setScale(x, y);
			this->size.x = this->size.x * x;
			this->size.y = this->size.y * y;


			this->boxSize = this->size;
		}

		sf::Sprite *sprite;

	#endif /// SERVER

	#ifdef SERVER
		Sprite(ecs::core::Vector2<unsigned int> size) {
			this->size.x = static_cast<float>(size.x);
			this->size.y = static_cast<float>(size.y);
			this->boxSize.x = static_cast<float>(size.x);
			this->boxSize.y = static_cast<float>(size.y);
		}
	#endif /// SERVER

		ecs::core::Vector2<float> size;
		ecs::core::Vector2<float> boxSize;
	};
}}
