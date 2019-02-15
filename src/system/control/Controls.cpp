/*
** EPITECH PROJECT, 2021
** server
** File description:
** Created by seb,
*/

#include "Controls.hpp"
#include "ecs/Ecs.hpp"
#include "component/control/Keyboard.hpp"
#include "component/control/Mouse.hpp"
namespace ecs { namespace system {

	void Controls::UpdateKeyboards() {
		auto &keyboards = ecs::Ecs::get().getComponentMap<component::Keyboard>();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.second.keyMap.begin(); it != keyboard.second.keyMap.end(); it++) {
				if (keyboard.second.keyMap[it->first].second)
					keyboard.second.keyMap[it->first].second(keyboard.first);
			}
		}
	}

	void Controls::UpdateMouses() {
		auto &mouses = ecs::Ecs::get().getComponentMap<component::Mouse>();

		for (auto &mouse : mouses) {
			for (auto it = mouse.second.mouseMap.begin(); it != mouse.second.mouseMap.end(); it++) {
				if (mouse.second.mouseMap[it->first].second)
					mouse.second.mouseMap[it->first].second(mouse.first);
			}
		}
	}

}}