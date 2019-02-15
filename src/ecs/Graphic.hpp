/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>
#include "Vector2.hpp"
#include "system/control/ControlsSFML.hpp"

namespace ecs {

	class Graphic {
		public:

			Graphic(bool fullscreen = false) : _lastId(0) {
				sf::VideoMode mode;
				mode.width = 1280;
				mode.height = 720;
				mode.bitsPerPixel = 32;
				if (fullscreen)
					_window = new sf::RenderWindow(mode, "Game", sf::Style::Fullscreen | sf::Style::Resize | sf::Style::Close);
				else
					_window = new sf::RenderWindow(mode, "Game", sf::Style::Resize | sf::Style::Close);
				_window->setFramerateLimit(120);

				pixels.resize(mode.width * mode.height * 4, 0);
			}

			static Graphic &get();
			static sf::RenderWindow *getWindow();
			void update();
			bool isOpen();


			/// Tools
			static core::Vector2<float> getTextureSize(std::string path) {
				sf::Texture tmp;

				if (!tmp.loadFromFile(path))
					return core::Vector2<float>();
				auto size = tmp.getSize();
				return core::Vector2<float>((float) size.x, (float) size.y);
			}

			std::vector<char> &getPixels();

		private:
			sf::RenderWindow		*_window;
			sf::Event			_event;
			std::vector<unsigned int>	_controllers;

			std::vector<char>		pixels;

			unsigned long			_lastId;
	};
}



