#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>
#include <iostream>

#include "Slider.h"
#include "font.h"
#include "Physical_Obj.h"
#include "Planet.h"
#include "Grid.h"

#define M_PI 3.14159265358979323846

constexpr float speed = 3e-6f;

using namespace std;

int main()
{
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0, frame_counter = 0;
	sf::Text fps_text;

	sf::Font font;
	font.loadFromMemory(font_data, font_data_size);
	fps_text.setFont(font);
	fps_text.setCharacterSize(12);
	fps_text.setFillColor(sf::Color::White);

	fps_text.setPosition(20, 70);
	fps_text.setString("fps: " + std::to_string(FPS));

	//sf::RenderWindow window(sf::VideoMode(770, 730), "Orbiting", sf::Style::Titlebar | sf::Style::Close);//sf::Style::Fullscreen
	sf::RenderWindow window(sf::VideoMode(770, 730), "Orbiting", sf::Style::Fullscreen);
	sf::Event event;

	window.setFramerateLimit(120);
	
	Planet::setFont(font);

	//Planet pl1(4, sf::Vector2f(360, 100), sf::Vector2f(5, 0));
	//Planet pl3(64, sf::Vector2f(360, 450), sf::Vector2f(-5, 0));
	//Planet pl3(25 * 25 * 25, sf::Vector2f(360, 420), sf::Vector2f(-9, 0));
	//Planet pl2(25, sf::Vector2f(360, 300), sf::Vector2f(0, 0));
	float sunRad = 50;
	Planet sun(50, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	Planet earth(10, sf::Vector2f(0, 600), sf::Vector2f(sqrt(G_const * sunRad * sunRad * sunRad / 600.) * Physicable::scale, 0));
	Planet moon(3, sf::Vector2f(0, 630), sf::Vector2f(sqrt(G_const * 1000 / 30.) * Physicable::scale + sqrt(G_const * sunRad * sunRad * sunRad / 600.) * Physicable::scale, 0));
	sf::Texture tgrid;
	tgrid.loadFromFile("grid_128.png");
	Grid grid(window, tgrid);

	sf::err().rdbuf(NULL);
	clock.restart().asMilliseconds();

	//sf::Vector2f cameraPos(0,0);
	float zoom = 1;

	//Slider slid(40, 680, 700, 30, sf::Color::Black, sf::Color::White);
	Slider slid(30, 20, 700, 30, sf::Color::Black, sf::Color::White);
	slid.setLineThick(10);
	slid.setRectWidth(15);
	slid.setValue(0);

	float massBallScale = 3;
	sf::Texture massBallT;
	massBallT.loadFromFile("massBall.png");
	sf::Sprite massBallS;
	massBallS.setTexture(massBallT);
	massBallS.setPosition(((sf::Vector2f)window.getSize() - (sf::Vector2f)massBallT.getSize() * massBallScale) / 2.f);
	massBallS.scale(sf::Vector2f(1, 1) * massBallScale);
	//massBallS.setPosition(100,100);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) window.close();
			//if (event.key.code == sf::Keyboard::W) cameraPos.y += clock.getElapsedTime().asMicroseconds() * speed;
			//if (event.key.code == sf::Keyboard::S) cameraPos.y -= clock.getElapsedTime().asMicroseconds() * speed;
			//if (event.key.code == sf::Keyboard::A) cameraPos.x += clock.getElapsedTime().asMicroseconds() * speed;
			//if (event.key.code == sf::Keyboard::D) cameraPos.x -= clock.getElapsedTime().asMicroseconds() * speed;
			if (event.type == sf::Event::MouseWheelMoved)
				zoom += event.mouseWheel.delta / 10.;
			slid.set(event);

			if (slid.flag)
			{

			}
		}

		fps_text.setString("fps: " + std::to_string(FPS));

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		Physicable::sim_step(((slid.value) + 1) / 60);

		sf::Vector2f sm = Physicable::systemMomentum();
		//cout << "momentum  of system: {" << sm.x << ", " << sm.y << "}\n";

		grid.gridMove(-Physicable::centerOfMass());
		window.draw(grid);

		//window.draw(pl2);
		Planet::drawAll(window, Physicable::centerOfMass(), zoom);

		//sf::CircleShape hm(8, 8);
		//sf::Vector2f off = - Physicable::centerOfMass() + sf::Vector2f(window.getSize()) * 0.5f;
		//std::cout << off.x << " -- " << off.y << "\n";
		//hm.setPosition(Physicable::centerOfMass() - sf::Vector2f(8,8) + off);
		//hm.setFillColor(sf::Color::Red);
		//window.draw(hm);//122376
		//window.draw(massBallS);

		window.draw(fps_text);
		window.draw(slid);

		window.display();
	}
	return 0;
}


/*TODO:
	-circleshape in planet do not create every single time.

	-maybe add to sim_step bool argument rearrange that will call function rearranging them graphicaly
*/