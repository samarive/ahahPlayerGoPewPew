#ifndef RIFLE_HPP_INCLUDED
#define RIFLE_HPP_INCLUDED

#include "Weapon.hpp"

class Rifle:public Weapon
{
public:
	Rifle();
	virtual ~Rifle();
	virtual Rifle* clone() const;

	//Override

	virtual std::string toString() const;

protected:
	
	void generateBullet(sf::Vector2f const& arg) const;

};

#endif