#include "Hitbox.hpp"

namespace physic2D { namespace system {
	Vec2 Hitbox::Normalize(Vec2 v) {
		auto d = v.length();
		if (d == 0)
			return v;
		return v / d;
	}

	void Hitbox::Correction(manifold *col, const float percent) {
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();

		Vec2 correct = col->normal * percent * (col->penetration / (mas[col->A]._invMass + mas[col->B]._invMass));
		pos[col->A]._pos -= correct * mas[col->A]._invMass;
		pos[col->B]._pos += correct * mas[col->B]._invMass;
	}

	void Hitbox::UpdateHitbox() {
		auto AABBIds = ecs::Ecs::get().filter<component::AABB>();
		auto poly = ecs::Ecs::get().filter<component::Poly>();
		auto circ = ecs::Ecs::get().filter<component::Circle>();
		auto &AABB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &Circle = ecs::Ecs::get().getComponentMap<component::Circle>();
		auto &Script = ecs::Ecs::get().getComponentMap<component::Script>();

		for (auto it = AABBIds.begin(); it != AABBIds.end();++it) {
			for (auto it2 = it+1; it2 != AABBIds.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (AABBToAABB(&col) == true)  {
					if (AABB[col.A]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.A))
							Script[col.A]._script(col.B);
					} else if (AABB[col.B]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.B))
							Script[col.B]._script(col.A);
					}
					if (AABB[col.A]._collidable && AABB[col.B]._collidable) {
						ImpulseResolution(&col);
						Correction(&col, 0.5);
						FrictionResolution(&col);
					}
				}
			}
			for (auto it2 = circ.begin(); it2 != circ.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (AABBToCircle(&col) == true)  {
					if (AABB[col.A]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.A))
							Script[col.A]._script(col.B);
					} else if (Circle[col.B]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.B))
							Script[col.B]._script(col.A);
					}
					if (AABB[col.A]._collidable && Circle[col.B]._collidable) {
						ImpulseResolution(&col);
						Correction(&col, 0.5);
						// FrictionResolution(&col);
					}
				}
			}
		}
		// for (auto it = poly.begin(); it != poly.end();++it) {
		// 	for (auto it2 = it+1; it2 != poly.end();++it2) {
		// 		manifold col;
		// 		col.A = *it;
		// 		col.B = *it2;
		// 		if (PolyToPoly(&col) == true)  {
		// 			ImpulseResolution(&col);
		// 			Correction(&col, 0.5);
		// 			FrictionResolution(&col);
		// 		}
		// 	}
		// }
		for (auto it = circ.begin(); it != circ.end();++it) {
			for (auto it2 = it+1; it2 != circ.end();++it2) {
				manifold col;
				col.A = *it;
				col.B = *it2;
				if (CircleToCircle(&col) == true) {
					if (Circle[col.A]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.A))
							Script[col.A]._script(col.B);
					} else if (Circle[col.B]._trigger) {
						if (ecs::Ecs::get().idHasComponents<component::Script>(col.B))
							Script[col.B]._script(col.A);
					}
					if (Circle[col.A]._collidable && Circle[col.B]._collidable) {
						ImpulseResolution(&col);
						Correction(&col, 0.5);
						FrictionResolution(&col);
					}
				}
			}
		}
	}

	void Hitbox::FrictionResolution(manifold *col) {
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();

		auto rv = speed[col->B]._speed - speed[col->A]._speed;
		auto dot = rv.dot(col->normal);
		auto t = rv - col->normal * dot;
		t = Normalize(t);
		auto jt = -t.dot(rv) / (mas[col->A]._invMass + mas[col->A]._invMass);

		float coef = Vec2(Mat[mat[col->B]._name]._fricS, Mat[mat[col->A]._name]._fricS).length();
		Vec2 impulse;
		if (coef * col->j > abs(jt)) {
			impulse = t * jt;
		} else {
			float coefD = Vec2(Mat[mat[col->B]._name]._fricD, Mat[mat[col->A]._name]._fricD).length();
			impulse = t * -col->j * coefD;
		}
		speed[col->A]._speed -= impulse * mas[col->A]._invMass;
		speed[col->B]._speed += impulse * mas[col->B]._invMass;
	}

	void Hitbox::ImpulseResolution(manifold *col) {
		auto &speed = ecs::Ecs::get().getComponentMap<component::Speed>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &mat = ecs::Ecs::get().getComponentMap<component::Materials>();
		auto &mas = ecs::Ecs::get().getComponentMap<component::Mass>();

		auto rv = speed[col->B]._speed - speed[col->A]._speed;
		auto dot = rv.dot(col->normal);
		if (dot > 0) {
			return;
		}
		float coef;
		if (Mat[mat[col->A]._name]._boing > Mat[mat[col->B]._name]._boing)
			coef = Mat[mat[col->B]._name]._boing;
		else 
			coef = Mat[mat[col->A]._name]._boing;
		auto j = (-(1 + coef) * dot) / (mas[col->A]._invMass + mas[col->B]._invMass);
		col->j = j;
		auto impulse = col->normal * j;
		speed[col->A]._speed -= impulse * mas[col->A]._invMass;
		speed[col->B]._speed += impulse * mas[col->B]._invMass;
	}

	bool Hitbox::AABBToAABB(manifold *col) {
		auto &AB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		Vec2 v = pos[col->B]._pos - pos[col->A]._pos;


		float extentXA = (AB[col->A]._max.x - AB[col->A]._min.x) / 2;
		float extentXB = (AB[col->B]._max.x - AB[col->B]._min.x) / 2;
		float extentX = extentXA + extentXB - abs(v.x);
			
		if (extentX > 0) {
			float extentYA = (AB[col->A]._max.y - AB[col->A]._min.y) / 2;
			float extentYB = (AB[col->B]._max.y - AB[col->B]._min.y) / 2;
			float extentY = extentYA + extentYB - abs(v.y);
			if (extentY > 0) {
				if (extentX < extentY) {
					col->normal = Vec2((v.x < 0 ? -1 : 1), 0);
					col->penetration = extentX;
				} else {
					col->normal = Vec2(0, (v.y < 0 ? -1 : 1));
					col->penetration = extentY;
				}
				return true;
			} else {
				return false;
			}
		}
		return false;
	}

	bool Hitbox::CircleToCircle(manifold *col) {
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &circ = ecs::Ecs::get().getComponentMap<component::Circle>();
		auto v = pos[col->B]._pos - pos[col->A]._pos;
		auto r = circ[col->A]._radius + circ[col->B]._radius;

		if (v.lengthSquared() > r * r)
			return false;
		auto d = v.length();

		if (d != 0) {
			col->penetration = r - d;
			col->normal = v / d;
			return true;
		} else {
			col->penetration = circ[col->A]._radius;
			col->normal = Vec2(1, 0);
			return true;
		}
	}

	bool Hitbox::AABBToCircle(manifold *col) {
		auto &pos = ecs::Ecs::get().getComponentMap<component::Pos>();
		auto &AB = ecs::Ecs::get().getComponentMap<component::AABB>();
		auto &circ = ecs::Ecs::get().getComponentMap<component::Circle>();
		Vec2 v = pos[col->B]._pos - pos[col->A]._pos;
		float extentX = (AB[col->A]._max.x - AB[col->A]._min.x) / 2;
		float extentY = (AB[col->A]._max.y - AB[col->A]._min.y) / 2;
		float r = circ[col->B]._radius;
		Vec2 clos = v;

		clos.x = std::clamp(clos.x, -extentX, extentX);
		clos.y = std::clamp(clos.y, -extentY, extentY);
		if (clos == v) {
			if (abs(v.x) > abs(v.y))
				clos.x = (clos.x > 0 ? extentX : -extentX);
			else
				clos.y = (clos.y > 0 ? extentY : -extentY);
			Vec2 normal = v - clos;
			col->normal = Normalize(-normal);
			col->penetration = r - normal.length();
			return true;
		} 
		else {
			Vec2 normal = v - clos;
			if (normal.lengthSquared()  > r * r) {
				return false;
			} else
				col->penetration = r - normal.length();
				col->normal = Normalize(normal);
				return true;
		}
	}

	float Hitbox::findAxisLeastPen(int *faceIndex, ID A, ID B) {
		float bestDist = -__FLT_MAX__;
		int bestIndex;
		auto &poly = ecs::Ecs::get().getComponentMap<component::Poly>();

		for (int i = 0; i < poly[A]._vertices.size(); ++i) {
			Vec2 norm = poly[A]._normales[i];
			Vec2 s = poly[B].getSupport(-norm);
			float d = norm.dot(s - poly[A]._vertices[i]);
			if (d > bestDist) {
				bestIndex = i;
				bestDist = d;
			}
		}
		*faceIndex = bestIndex;
		return bestDist;
	}

	// bool Hitbox::PolyToPoly(manifold *col) {
	// 	auto &poly = ecs::Ecs::get().getComponentMap<component::Poly>();
	// 	int IndexA;
	// 	int IndexB;
	// 	float DistA = findAxisLeastPen(&IndexA, col->A, col->B);
	// 	float DistB = findAxisLeastPen(&IndexA, col->B, col->A);

	// 	col->normal = poly[col->A]._normales[IndexA];
	// 	col->penetration = DistA;
	// 	if (DistA >= 0) {
	// 		return false;
	// 	} else if (DistB >= 0) {
	// 		return false;
	// 	}

	// 	ID Inc;
	// 	ID Ref;
	// 	int index;
	// 	bool flip;

	// 	if (DistA > DistB * 0.95 + DistA * 0.01) {
	// 		Ref = col->A;
	// 		Inc = col->B;
	// 		index = IndexA;
	// 		flip = false;
	// 	} else {
	// 		Ref = col->B;
	// 		Inc = col->A;
	// 		index = IndexB;
	// 		flip = true;
	// 	}
	// }
}}
