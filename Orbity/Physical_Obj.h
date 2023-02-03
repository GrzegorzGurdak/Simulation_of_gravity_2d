#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define G_const 6.6743e-11f

inline bool clamp(float &v, float min, float max)
{
	bool t = v < min ? true : (v > max ? true : false);
	v = v < min ? min : (v > max ? max : v);
	return t;
}

inline bool clamp(sf::Vector2f& v, sf::Vector2f min, sf::Vector2f max)
{
	bool t = clamp(v.y, min.y, max.y);
	return clamp(v.x, min.x, max.x) || t;
}

class Planet;

class Physicable {
public:
	Physicable(float m, sf::Vector2f p, sf::Vector2f v, bool is_mv);
	static void sim_step(float dtime);
	static sf::Vector2f centerOfMass();
	static sf::Vector2f systemMomentum();

	sf::Vector2f getPos() const { return position; }
	sf::Vector2f getVel() const { return velocity; }
	void set_movability(bool m) { is_movable = m; }
	float getMass() const { return mass; }
	static float scale;
private:
	float mass;
	sf::Vector2f velocity;
	sf::Vector2f position;
	static std::vector<Physicable*> pObjects;
	bool is_movable;
};