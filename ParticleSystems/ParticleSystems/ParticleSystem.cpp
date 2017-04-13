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

	ParticleSystem(unsigned int count, float i_anlge_factor, float i_speed_factor, std::string textureFile) :
		m_particles(count),
		m_particles2(count + 100),
		m_lifetime(sf::seconds(20)),
		m_gravity(0, 50),
		m_emitter(0, 0),
		m_emitter2(0, 0),
		m_angle_factor(i_anlge_factor),
		m_speed_factor(i_speed_factor)
	{
		m_texture.loadFromFile(textureFile);
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
		m_emitter2 = position + sf::Vector2f(400, 100);
	}

	void update(sf::Time elapsed)
	{
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
			p.quad[0].position += p.velocity * elapsed.asSeconds();
			p.quad[1].position += p.velocity * elapsed.asSeconds();
			p.quad[2].position += p.velocity * elapsed.asSeconds();
			p.quad[3].position += p.velocity * elapsed.asSeconds();

		}


		for (std::size_t i = 0; i < m_particles2.size(); ++i)
		{

			// update the particle lifetime
			Particle& p = m_particles2[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle2(i);

			// update the position of the corresponding vertex
			p.velocity += m_gravity * elapsed.asSeconds();

			// update the position of the corresponding vertex
			p.quad[0].position += p.velocity * elapsed.asSeconds();
			p.quad[1].position += p.velocity * elapsed.asSeconds();
			p.quad[2].position += p.velocity * elapsed.asSeconds();
			p.quad[3].position += p.velocity * elapsed.asSeconds();

		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = &m_texture;
		//states.texture = NULL;

		// draw the vertex array
		for (int i = 0; i < m_particles.size(); ++i) {
			target.draw(m_particles[i].quad, states);
		}

		for (int i = 0; i < m_particles2.size(); ++i) {
			target.draw(m_particles2[i].quad, states);
		}
		
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::VertexArray quad;
	};

	void resetParticle(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f * m_angle_factor;
		float speed = (std::rand() % 50) + 50.f * m_speed_factor;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		// reset the position of the corresponding vertex
		m_particles[index].quad = sf::VertexArray(sf::Quads, 4);
		m_particles[index].quad[0] = m_emitter + sf::Vector2f(0, 0);
		m_particles[index].quad[1] = m_emitter + sf::Vector2f(0, 20);
		m_particles[index].quad[2] = m_emitter + sf::Vector2f(20, 20);
		m_particles[index].quad[3] = m_emitter + sf::Vector2f(20, 0);

		m_particles[index].quad[0].texCoords = sf::Vector2f(0, 0);
		m_particles[index].quad[1].texCoords = sf::Vector2f(0, 100);
		m_particles[index].quad[2].texCoords = sf::Vector2f(100, 100);
		m_particles[index].quad[3].texCoords = sf::Vector2f(100, 0);

	}

	void resetParticle2(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f * m_angle_factor;
		float speed = (std::rand() % 50) + 50.f * m_speed_factor;
		m_particles2[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles2[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		// reset the position of the corresponding vertex
		m_particles2[index].quad = sf::VertexArray(sf::Quads, 4);
		m_particles2[index].quad[0] = m_emitter2 + sf::Vector2f(0, 0);
		m_particles2[index].quad[1] = m_emitter2 + sf::Vector2f(0, 50);
		m_particles2[index].quad[2] = m_emitter2 + sf::Vector2f(50, 50);
		m_particles2[index].quad[3] = m_emitter2 + sf::Vector2f(50, 0);

		m_particles2[index].quad[0].texCoords = sf::Vector2f(0, 0);
		m_particles2[index].quad[1].texCoords = sf::Vector2f(0, 100);
		m_particles2[index].quad[2].texCoords = sf::Vector2f(100, 100);
		m_particles2[index].quad[3].texCoords = sf::Vector2f(100, 0);

	}

	std::vector<Particle> m_particles;
	std::vector<Particle> m_particles2;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Vector2f m_emitter2;
	sf::Vector2f m_gravity;
	sf::Texture m_texture;

	//for multiple particle system
	float m_angle_factor;
	float m_speed_factor;
};