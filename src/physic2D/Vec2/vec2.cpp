#include "vec2.hpp"

namespace physic2D {
	Vec2::Vec2() {
		this->x = 0;
		this->y = 0;
	}

	Vec2::Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void Vec2::operator=(Vec2 v) {
		this->x = v.x;
		this->y = v.y;
	}

	bool Vec2::operator==(Vec2 v) {
		return (this->x == v.x && this->y == v.y);
	}

	Vec2 Vec2::operator+(Vec2 v) {
		Vec2 res = Vec2(this->x + v.x, this->y + v.y);
		return res;
	}

	Vec2 Vec2::operator-(Vec2 v) {
		Vec2 res = Vec2(this->x - v.x, this->y - v.y);
		return res;
	}

	Vec2 Vec2::operator-() {
		Vec2 res = Vec2(-this->x, -this->y);
		return res;
	}

	void Vec2::operator-=(Vec2 v) {
		this->x -= v.x;
		this->y -= v.y;
	}

	void Vec2::operator+=(Vec2 v) {
		this->x += v.x;
		this->y += v.y;
	}

	Vec2 Vec2::operator/(float v) {
		Vec2 res = Vec2(this->x / v, this->y / v);
		return res;
	}

	Vec2 Vec2::operator*(float v) {
		Vec2 res = Vec2(this->x * v, this->y * v);
		return res;
	}

	float Vec2::dot(Vec2 v) {
		return (this->x * v.x + this->y * v.y);
	}

	float Vec2::length() {
		return std::sqrt(this->x * this->x + this->y * this->y);
	}

	float Vec2::lengthSquared() {
		return this->x * this->x + this->y * this->y;
	}

	Vec2 Vec2::cross(float s, bool way) {
		if (way)
			return Vec2(s * this->y, -s * this->x);
		return Vec2(-s * this->y, s * this->x);
	}
	
	float Vec2::cross(Vec2 &v) {
		return this->x * v.y - this->y * v.x;
	}
}