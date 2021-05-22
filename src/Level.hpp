#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include "Wall.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Rifle.hpp"
#include "TexturePack.hpp"
#include "Shotgun.hpp"
#include <cmath>
#include <vector>

class Level
{
public:

	Level();
	virtual ~Level();

	void tick();
	void paintOn(sf::RenderWindow & arg);
	void passEvent(sf::Event const& arg);

	void empty();
	void generate(int dimension,int proportion);

	std::vector<sf::Packet> getPacketVector();

private:
	
	bool isInCam(Object* const& arg) const;

	std::vector<Object*> world;
	sf::View camera;
	
};

#endif