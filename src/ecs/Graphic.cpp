/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include "Graphic.hpp"

namespace ecs {
	Graphic& Graphic::get() {
		thread_local static Graphic graphic;

		return graphic;
	}

	sf::RenderWindow* Graphic::getWindow() {
		return (get()._window);
	}

	void Graphic::update() {
		while (_window->pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				_window->close();

			system::ControlsSFML::UpdateKeyboardsEvent(_event);
			system::ControlsSFML::UpdateMousesEvents(_event);
			system::ControlsSFML::UpdateControllers(_event);
		}

		_window->display();
		_window->clear(sf::Color::Black);
	}

	bool Graphic::isOpen() {
		return _window->isOpen();
	}

	std::vector<char> &Graphic::getPixels() {
		return pixels;
	}
}