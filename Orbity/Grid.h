#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid(sf::Window& window, sf::Texture &tgrid) : grid_tex{ tgrid }
	{
		tsize = grid_tex.getSize().x;
		unsigned int vwidth = window.getSize().x / tsize + 1, vheight = window.getSize().y / tsize + 2;
		
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(vwidth * vheight * 4);

		for (unsigned int i = 0; i < vwidth; ++i)
			for (unsigned int j = 0; j < vheight; ++j)
			{
				sf::Vertex* quad = &m_vertices[(i + j * vwidth) * 4];

				quad[0].position = sf::Vector2f(i * tsize, j * tsize);
				quad[1].position = sf::Vector2f((i + 1) * tsize, j * tsize);
				quad[2].position = sf::Vector2f((i + 1) * tsize, (j + 1) * tsize);
				quad[3].position = sf::Vector2f(i * tsize, (j + 1) * tsize);

				quad[0].texCoords = sf::Vector2f(0, 0);
				quad[1].texCoords = sf::Vector2f(tsize, 0);
				quad[2].texCoords = sf::Vector2f(tsize, tsize);
				quad[3].texCoords = sf::Vector2f(0, tsize);
			}
	}

	void gridMove(sf::Vector2f cameraPos)
	{
		setPosition(sf::Vector2f(((int)cameraPos.x % tsize), (int)cameraPos.y % tsize) - sf::Vector2f(tsize,tsize));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &grid_tex;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:
	sf::Texture &grid_tex;
	sf::VertexArray m_vertices;
	unsigned int tsize;
};

