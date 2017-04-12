#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_vertices2(sf::Points, count * 2),
		m_lifetime(sf::seconds(3)),
		m_gravity(0, 100),
		m_emitter(0, 0),
		m_emitter2(50, 50)
	{
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}

	void setEmitter2(sf::Vector2f position) 
	{
		m_emitter2 = position;
	}

	void setTexture(sf::Texture texture)
	{
		m_texture = texture;
	}

	sf::Vector2f generateRandomPos() 
	{
		float x = float(std::rand() % 512);
		float y = float(std::rand() % 256);
		return sf::Vector2f(x, y);
	}

	
	void update(sf::Time elapsed)
	{
		//setEmitter2(generateRandomPos());
		//setEmitter2(sf::Vector2f(1,1))
		m_texture.loadFromFile("redTexture.png");
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			
			// update the particle lifetime
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			// update the position of the corresponding vertex
			p.velocity += m_gravity * elapsed.asSeconds();


			// update the position of the corresponding vertex
			m_vertices[i].position += p.velocity * elapsed.asSeconds();

			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);

			// update the position of the corresponding vertex
			m_vertices2[i].position += p.velocity * elapsed.asSeconds();

			// update the alpha (transparency) of the particle according to its lifetime
			ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices2[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = NULL;
		//states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_vertices, states);
		target.draw(m_vertices2, states);
	}

	/*
	virtual void draw2(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = NULL;
		//states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_vertices2, states);
	}
	*/

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index)
	{
		// for emitter 1
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
		
		// for emitter 2
		// give a random velocity and lifetime to the particle
		float angle2 = (std::rand() % 360) * 3.14f / 180.f;
		float speed2 = (std::rand() % 50) + 50.f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle2) * speed2, std::sin(angle2) * speed2);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		// reset the position of the corresponding vertex
		m_vertices2[index].position = m_emitter2;
	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::VertexArray m_vertices2;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Vector2f m_emitter2;
	sf::Vector2f m_gravity;
	sf::Texture m_texture;
};