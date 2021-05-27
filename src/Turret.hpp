#ifndef TURRET_HPP_INCLUDED
#define TURRET_HPP_INCLUDED

#include "Mob.hpp"

class Turret:public Mob
{
public:
	
	Turret(std::string const& arg0="Turry",sf::Vector2f const& arg1=sf::Vector2f(0.f,0.f),int arg2=100);
	virtual ~Turret();
	virtual Turret * clone() const;

	//Override
	virtual std::string toString() const;

protected:

	virtual void think(Object & arg);


};


#endif