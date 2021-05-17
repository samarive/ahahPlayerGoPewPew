#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include "Object.hpp"
#include "Player.hpp"

class Item:public Object
{
public:
	Item(std::string const& arg0="Itemy",sf::Vector2f const& arg1=sf::Vector2f(0,0));
	virtual ~Item();

	virtual void affect(Player & arg)=0;

	//Override
	virtual std::string toString() const;

};

#endif