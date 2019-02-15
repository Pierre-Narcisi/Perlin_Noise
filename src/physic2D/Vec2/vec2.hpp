#pragma once

#include <math.h>

namespace physic2D {
	class Vec2 {
		public:
			Vec2();
			Vec2(float x, float y);
			void operator=(Vec2 v);
			Vec2 operator+(Vec2 v);
			Vec2 operator-(Vec2 v);
			void operator-=(Vec2 v);
			void operator+=(Vec2 v);
			bool operator==(Vec2 v);
			Vec2 operator-();
			Vec2 operator/(float v);
			Vec2 operator*(float v);
			Vec2 cross(float s, bool way);
			float cross(Vec2 &v);
			float dot(Vec2 v);
			float length();
			float lengthSquared();
			float x;
			float y;
	};
}