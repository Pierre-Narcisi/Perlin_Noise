//
// Created by seb on 09/01/19.
//

#pragma once

enum class GraphicalMethod {
	None,
	Pixel,
	Sprite,
	NSSprite,
	AnimatedSprite,
	AnimatedSpriteList,
	AnimatedSpriteMap
};

namespace ecs { namespace component {
	struct Drawable {
		Drawable() {
			this->layer = -10;
			this->method = GraphicalMethod::None;
		}
		Drawable(bool drawable, int layer, GraphicalMethod method) {
			this->drawable = drawable;
			this->layer = layer;
			this->rotation = 0;
			this->method = method;
		}
		Drawable(bool drawable, int layer, float rotation, GraphicalMethod method) {
			this->drawable = drawable;
			this->layer = layer;
			this->rotation = rotation;
			this->method = method;
		}
		bool		drawable;
		int 		layer;
		float		rotation;
		GraphicalMethod	method;
	};
}}