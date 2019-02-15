cmake_minimum_required(VERSION 3.10)
project(Noise)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)

include_directories(${SFML_INCLUDE_DIR})
include_directories(src)
include_directories(component)
include_directories(system)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Noise
        src/ecs/DataBank.hpp
        src/ecs/Ecs.hpp
        src/ecs/Entity.cpp
        src/ecs/Entity.hpp
        src/ecs/ComponentList.hpp
        src/ecs/Time.cpp
        src/ecs/Time.hpp
        src/ecs/TimedEvent.cpp
        src/ecs/TimedEvent.hpp
        src/ecs/TimedEventAdmin.cpp
        src/ecs/TimedEventAdmin.hpp
		src/ecs/Vector2.hpp

        src/ecs/ThreadPool.cpp
        src/ecs/ThreadPool.hpp

		src/ecs/Graphic.cpp
		src/ecs/Graphic.hpp

		src/physic2D/system/Gravity.cpp
		src/physic2D/system/Gravity.hpp
		src/physic2D/system/Physic2D.cpp
		src/physic2D/system/Physic2D.hpp
		src/physic2D/system/Hitbox.cpp
		src/physic2D/system/Hitbox.hpp
		src/physic2D/Vec2/vec2.cpp
		src/physic2D/Vec2/vec2.hpp

		src/component/graphical/AnimatedSprite.hpp
		src/component/graphical/Drawable.hpp
		src/component/graphical/Pixel.hpp
		src/component/graphical/Sprite.hpp
		src/component/graphical/NSSprite.hpp

		src/component/control/Controller.hpp
		src/component/control/Keyboard.hpp
		src/component/control/Mouse.hpp

		src/system/Update.cpp
		src/system/Update.hpp

		src/system/control/ControlsSFML.cpp
		src/system/control/ControlsSFML.hpp
		src/system/control/Controls.cpp
		src/system/control/Controls.cpp

		src/noise/system/UpdateNoise.cpp
		src/noise/system/UpdateNoise.hpp

		Main.cpp)

target_link_libraries(Noise ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(Noise ${Boost_LIBRARIES})
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libsfml-audio.so)
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libsfml-graphics.so)
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libsfml-window.so)
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libsfml-system.so)
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libboost_filesystem.so)
target_link_libraries(Noise /usr/lib/x86_64-linux-gnu/libboost_system.so)
