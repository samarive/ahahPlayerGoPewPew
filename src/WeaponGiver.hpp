#ifndef WEAPON_GIVER_HPP_INCLUDED
#define WEAPON_GIVER_HPP_INCLUDED

#include "Item.hpp"
#include "Weapon.hpp"
#include "Rifle.hpp"

class WeaponGiver:public Item
{
public:
	WeaponGiver(std::string const& arg0="WGivy",sf::Vector2f const& arg1=sf::Vector2f(0.f,0.f),Weapon const& arg2=Rifle());
	virtual ~WeaponGiver();
	virtual WeaponGiver * clone() const;

	//Override
	virtual void affect(Player & arg);
	virtual std::string toString() const;

private:

	Weapon * toGive;
};


#endif