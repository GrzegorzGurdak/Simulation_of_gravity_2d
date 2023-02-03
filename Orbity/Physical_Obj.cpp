#include "Physical_Obj.h"
#include <vector>

std::vector<Physicable*> Physicable::pObjects;// = std::vector<Physicable*>();
float Physicable::scale = 5e4;

Physicable::Physicable(float m, sf::Vector2f p, sf::Vector2f v, bool is_mv) : mass{ m }, velocity{ v / scale }, position{ p }, is_movable{ is_mv } { pObjects.push_back(this); }

void Physicable::sim_step(float dtime) {
	for (auto& i : pObjects) {
		if (i->is_movable)
			for (auto& j : pObjects) {
				if (&j != &i) {
					sf::Vector2f r = j->position - i->position;
					float r_2 = r.x * r.x + r.y * r.y;
					sf::Vector2f tmp = (r / sqrt(r_2)) * (dtime * G_const * j->mass / r_2 * scale);
					i->velocity += (r / sqrt(r_2)) * (dtime * G_const * j->mass / r_2 * scale);
				}
			}
	}
	for (auto& i : pObjects) {
		if (i->is_movable) i->position += i->velocity * dtime * scale;
	}
}

sf::Vector2f Physicable::centerOfMass(){
	float massSum{};
	sf::Vector2f currentCent{};
	for (auto& i : pObjects) {
		currentCent = (currentCent * massSum + i->position * i->mass) / (massSum + i->mass);
		//currentCent = (currentCent * cbrt(massSum) + i->position * cbrt(i->mass)) / (cbrt(massSum) + cbrt(i->mass));
		massSum += i->mass;
	}
	return currentCent;
}

sf::Vector2f Physicable::systemMomentum()
{
	sf::Vector2f M{};
	for (auto&& i : pObjects) M += i->velocity * i->mass;
	return M;
}
