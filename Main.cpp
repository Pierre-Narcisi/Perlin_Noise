//
// Created by seb on 07/01/19.
//

#include <iostream>
#include <ecs/Ecs.hpp>
#include <ecs/Time.hpp>
#include <thread>
#include <ecs/ThreadPool.hpp>
#include <ecs/Graphic.hpp>
#include <system/Update.hpp>
#include <ecs/DataBank.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/graphical/Pixel.hpp>
#include <component/graphical/Drawable.hpp>
#include <zconf.h>
#include "src/physic2D/system/Hitbox.hpp"
#include "src/physic2D/system/Physic2D.hpp"
#include "src/physic2D/system/Gravity.hpp"
#include "src/physic2D/component/AABB.hpp"
#include "src/physic2D/component/Poly.hpp"
#include "src/physic2D/component/Circle.hpp"
#include "src/physic2D/component/Mass.hpp"
#include "src/physic2D/Vec2/vec2.hpp"
#include "src/noise/system/UpdateNoise.hpp"

int main() {
	auto &game = ecs::Ecs::get();
	auto &screen = ecs::Graphic::get();

	ecs::DataBank<std::string, sf::Texture>::get().creator = [](std::string path){
		sf::Texture texture;
		texture.loadFromFile(path);
		return (texture);
	};

	physic2D::system::Physic2D physic = physic2D::system::Physic2D();
	game.addUpdate(2, [&physic](){physic.UpdatePhysic();});
	physic2D::system::Gravity grav = physic2D::system::Gravity();
	game.addUpdate(2, [&grav](){grav.updateGravity();});
	game.addUpdate(1, [](){
		physic2D::system::Hitbox hit;
		hit.UpdateHitbox();
		});
	noise::system::Noise noise;
	game.addUpdate(1, [&noise](){noise.updateNoise();});
	game.addUpdate(100, [](){ecs::Update::UpdateGraphical();});
	game.addUpdate(110, [&screen](){screen.update();});

	while(screen.isOpen()) {

		long time = ecs::Time::get(TimeUnit::MicroSeconds);

		game.update();
		// std::this_thread::sleep_for (std::chrono::seconds(1));
		auto x = static_cast<unsigned int>(16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
		// std::cout << 100 * (16666 - x) / 16666 << std::endl;
	}
	
	return 0;
}
