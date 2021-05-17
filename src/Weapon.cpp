#include "Weapon.hpp"

using namespace sf;
using namespace std;

vector<Object*> * Weapon::world = nullptr;

Weapon::Weapon(int arg0):cooldown(arg0),countdown(0)
{}
Weapon::~Weapon() {}

void Weapon::fire(sf::Vector2f const& arg)
{
	if(countdown<0 && world!=nullptr)
	{
		generateBullet(arg);
		countdown = cooldown;
	}

}

void Weapon::poke()
{
	countdown--;
}

void Weapon::setBulletModel(Bullet const& arg)
{
	model = arg;
}

void Weapon::setWorld(std::vector<Object*> & arg)
{
	world = &arg;
}

Bullet Weapon::getBulletModel() const
{
	return model;
}

string Weapon::toString() const {return "weapon";}

string Weapon::toShortString() const
{
	string toReturn ("");

	for(int i (toString().size()-1);i>-1;i--)
	{
		if(toString().at(i)==' ')return toReturn;
	
		toReturn = toString().at(i) + toReturn;
	}

	return toReturn;
}
