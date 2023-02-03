#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <cmath>

#include "Physical_Obj.h"

class Planet : public sf::Drawable, public Physicable
{
public:

	Planet(float r, sf::Vector2f p, sf::Vector2f v, bool is_move = true);

	static void setFont(sf::Font& f);

	static void drawAll(sf::RenderTarget& target, sf::Vector2f massOffset, float dscale);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	mutable sf::Text pStat;
	mutable sf::CircleShape cs;
	sf::Vector2f offset;
	static float drawScale;
	float radius;
	static std::vector<Planet*> objects;
	static sf::Font font;

	friend class Physicable;
};