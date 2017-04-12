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
	int NumOfParticles = 200;
	ParticleSystem *particles = new ParticleSystem(NumOfParticles);
	if (!redTexture.loadFromFile("blueTexture.png"))
		return -1;
	sprite.setTexture(redTexture);
	sprite.setPosition(sf::Vector2f(0, 0));

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
			particles = new ParticleSystem(NumOfParticles);
			std::cout << "increase" << NumOfParticles << std::endl;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && NumOfParticles - 200 > 0 ) {
			delete particles;
			NumOfParticles -= 200;
			particles = new ParticleSystem(NumOfParticles);
			std::cout << "decrease" << NumOfParticles << std::endl;
		}
		
		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles->setEmitter(window.mapPixelToCoords(mouse));
		
		// update it
		sf::Time elapsed = clock.restart();
		particles->update(elapsed);

		// draw it
		window.clear();
		window.draw(*particles);
		//window.draw(sprite);
		window.display();
	}

	return 0;
}