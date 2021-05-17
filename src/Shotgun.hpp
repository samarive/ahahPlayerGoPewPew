#ifndef SHOTGUN_HPP_INCLUDED
#define SHOTGUN_HPP_INCLUDED

#include "Weapon.hpp"

class Shotgun:public Weapon
{
public:
	Shotgun();
	virtual ~Shotgun();
	virtual Shotgun* clone() const;

	//Override
	virtual std::string toString() const;

protected:
	
	void generateBullet(sf::Vector2f const& arg) const;
	
};


#endif