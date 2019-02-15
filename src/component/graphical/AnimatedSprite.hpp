//
// Created by seb on 14/01/19.
//

#pragma once

#include <vector>
#include <set>
#include <ecs/Time.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <ecs/Graphic.hpp>
#include "Sprite.hpp"

namespace ecs { namespace component {
	struct AnimatedSprite {
		AnimatedSprite(){}
		AnimatedSprite(std::string path) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path); itr != endItr; ++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}

				if (sorted.empty()) {
					std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
					exit(84);
				}

				this->size = ecs::Graphic::getTextureSize(*sorted.begin());
				this->sprites.reserve(sorted.size());
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					this->sprites.emplace_back(*it, ecs::core::Vector2<unsigned int>(static_cast<unsigned int>(this->size.x), static_cast<unsigned int>(this->size.y)));
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			this->delta = static_cast<long>(1000000 / this->sprites.size());
			this->last = ecs::Time::get(TimeUnit::MicroSeconds);
			this->frame = sprites.size();
			this->pos = 0;
		}

		AnimatedSprite(std::string path, ecs::core::Vector2<float> size) {
			this->size = size;
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path); itr != endItr; ++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}

				if (sorted.empty()) {
					std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
					exit(84);
				}

				this->sprites.reserve(sorted.size());
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					this->sprites.emplace_back(*it, ecs::core::Vector2<unsigned int>(static_cast<unsigned int>(this->size.x), static_cast<unsigned int>(this->size.y)));
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			this->delta = static_cast<long>(1000000 / this->sprites.size());
			this->last = ecs::Time::get(TimeUnit::MicroSeconds);
			this->frame = sprites.size();
			this->pos = 0;
		}

		std::vector<Sprite>	sprites;
		int 			frame;
		int			pos;
		long 			delta;
		long 			last;

		ecs::core::Vector2<float> size;
	};
}}