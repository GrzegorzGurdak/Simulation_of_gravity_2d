#include "Planet.h"

std::vector<Planet*> Planet::objects;// = std::vector<Physicable*>();
sf::Font Planet::font;
float Planet::drawScale;

Planet::Planet(float r, sf::Vector2f p, sf::Vector2f v, bool is_move) :
	Physicable(r* r* r, p, v, is_move), radius{ r }, cs{ r, 6 }
{
	objects.push_back(this);
	pStat.setCharacterSize(12);
	pStat.setFillColor(sf::Color::Green);
	if (font.getInfo().family != "") pStat.setFont(font);
}

void Planet::setFont(sf::Font& f)
{
	font = f;
	for (auto&& i : objects) {
		i->pStat.setFont(font);
	}
}

void Planet::drawAll(sf::RenderTarget& target, sf::Vector2f massOffset, float dscale)
{
	drawScale = dscale;
	sf::Vector2f off = massOffset - sf::Vector2f(target.getSize()) * 0.5f;

	for (auto&& i : objects) {
		i->offset = off;
		target.draw(*i);
	}
}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vector2f v = getVel() * Physicable::scale;
	pStat.setString(
		std::string("mass: ") + std::to_string(getMass()) + "\n" +
		"velocity: {" + std::to_string(v.x) + ", " + std::to_string(v.y) + "}"
	);

	float drawRad = radius * drawScale;


	sf::Vector2f drawPos = (getPos() - offset) * drawScale + (sf::Vector2f)target.getSize() * (1 - drawScale) * 0.5f;
	clamp(drawPos, sf::Vector2f(0, 0), (sf::Vector2f)target.getSize());

	cs.setPosition(drawPos - sf::Vector2f(drawRad, drawRad));
	clamp(drawPos, sf::Vector2f(0, 0), (sf::Vector2f)target.getSize() - sf::Vector2f(200, 100));
	pStat.setPosition(drawPos + sf::Vector2f(drawRad + 2, -drawRad - 5));
	target.draw(cs);
	target.draw(pStat);
}

