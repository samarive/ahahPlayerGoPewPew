#ifndef MOB_HPP_INCLUDED
#define MOB_HPP_INCLUDED

#include "Player.hpp"

class Mob:public Player
{
public:
	Mob(std::string const& arg0,sf::Vector2f const& arg1);
	virtual ~Mob();
	virtual Mob * clone() const;


	//Override
	virtual void update();
	virtual bool collide(Object & arg);
	virtual std::string toString() const;

private:

	bool hand;//Preferred hand (I am personnaly right handed)
	std::string seen;

};


#endif