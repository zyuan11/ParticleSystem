#include <SFML/Graphics.hpp>
#include "ParticleSystem.cpp"
#include <iostream>

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");
	sf::Texture redTexture;
	sf::Sprite sprite;
	
	// create a clock to track the elapsed time
	sf::Clock clock;


	// create the particle system
	float anlge_factor = 0.3;
	float speed_factor = 0.3;
	int NumOfParticles = 200;
	ParticleSystem *particles = new ParticleSystem(NumOfParticles, anlge_factor, speed_factor);

	int NumOfParticles2 = 1000;
	ParticleSystem *particles2 = new ParticleSystem(NumOfParticles2, anlge_factor * 2, speed_factor * 2);


	if (!redTexture.loadFromFile("blueTexture.png"))
		return -1;
	//sprite.setTexture(redTexture);
	//sprite.setPosition(sf::Vector2f(0, 0));

	particles->setTexture(redTexture);

	// run the main loop
	while (window.isOpen())
	{
		
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//check growth 100000 for system to slow down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			delete particles;
			NumOfParticles += 200;
			particles = new ParticleSystem(NumOfParticles, 100.f, speed_factor);
			
			delete particles2;
			NumOfParticles2 += 500;
			particles2 = new ParticleSystem(NumOfParticles2, 200.f, speed_factor * 2);

			std::cout << "increase" << NumOfParticles << std::endl;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && NumOfParticles - 500 > 0 ) {
			delete particles;
			NumOfParticles -= 200;
			particles = new ParticleSystem(NumOfParticles, 100.f, speed_factor);

			delete particles2;
			NumOfParticles2 -= 500;
			particles2 = new ParticleSystem(NumOfParticles2, 200.f, speed_factor * 2);

			std::cout << "decrease" << NumOfParticles << std::endl;
		}
		
		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles->setEmitter(window.mapPixelToCoords(mouse));
		particles2->setEmitter(sf::Vector2f(100, 200));
		particles2->setEmitter2(sf::Vector2f(400, 100));

		
		// update it
		sf::Time elapsed = clock.restart();
		particles->update(elapsed);

		sf::Time elapsed2 = clock.restart();
		particles2->update(elapsed2);


		// draw it
		window.clear();
		window.draw(*particles);
		window.draw(*particles2);
		//window.draw(sprite);
		window.display();
	}

	return 0;
}