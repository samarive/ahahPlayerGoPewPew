#ifndef HEALING_HPP_INCLUDED
#define HEALING_HPP_INCLUDED

#include "Item.hpp"

class Healing:public Item
{
public:
	Healing(std::string const& arg0="Healy",sf::Vector2f const& arg1=sf::Vector2f(0.f,0.f));
	virtual ~Healing();
	virtual Healing * clone() const;

	//Override
	virtual void affect(Player & arg);
	virtual std::string toString() const;
private:
	int strenght;
};


#endif