#include <SFML/Graphics.hpp>
#include "ParticleSystem.cpp"
#include <iostream>

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Particles");
	
	// create a clock to track the elapsed time
	sf::Clock clock;


	// create the particle system
	float anlge_factor = 0.3;
	float speed_factor = 0.3;
	int NumOfParticles = 100;
	ParticleSystem *particles = new ParticleSystem(NumOfParticles, anlge_factor, speed_factor, "redTexture.png");

	int NumOfParticles2 = 70;
	ParticleSystem *particles2 = new ParticleSystem(NumOfParticles2, anlge_factor * 1.5, speed_factor * 2, "blueTexture.png");


	
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
			NumOfParticles += 50;
			particles = new ParticleSystem(NumOfParticles, anlge_factor, speed_factor, "redTexture.png");
			
			delete particles2;
			NumOfParticles2 += 50;
			particles2 = new ParticleSystem(NumOfParticles2, anlge_factor * 1.5, speed_factor * 2, "blueTexture.png");

			std::cout << "increase" << NumOfParticles << std::endl;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && NumOfParticles - 500 > 0 ) {
			delete particles;
			NumOfParticles -= 50;
			particles = new ParticleSystem(NumOfParticles, anlge_factor, speed_factor, "redTexture.png");

			delete particles2;
			NumOfParticles2 -= 50;
			particles2 = new ParticleSystem(NumOfParticles2, anlge_factor * 1.5, speed_factor * 2, "blueTexture.png");

			std::cout << "decrease" << NumOfParticles << std::endl;
		}
		
		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles->setEmitter(window.mapPixelToCoords(mouse));
		particles2->setEmitter(window.mapPixelToCoords(mouse) + sf::Vector2f(100, 200));
		
		
		// update it
		sf::Time elapsed = clock.restart();
		particles->update(elapsed);

		sf::Time elapsed2 = clock.restart();
		particles2->update(elapsed2);


		// draw it
		window.clear();
		window.draw(*particles);
		window.draw(*particles2);
		window.display();
	}

	return 0;
}