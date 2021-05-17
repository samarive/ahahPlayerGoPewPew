#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "Bullet.hpp"

class Weapon
{
public:
	
	Weapon(int arg0=30);
	virtual ~Weapon();
	virtual Weapon* clone() const=0;

	void fire(sf::Vector2f const& arg);//Takes owner coords for argument

	void poke();

	void setBulletModel(Bullet const& arg);

	static void setWorld(std::vector<Object*> & arg);

	virtual std::string toString() const;
	std::string toShortString() const;

protected:

	virtual void generateBullet(sf::Vector2f const& arg) const=0;//Owner coords as arg
	Bullet getBulletModel() const;

	static std::vector<Object*> * world;//vector to fill with generateBullet()

private:
	
	Bullet model;//every created bullet is a copy of this
	int countdown;//From cooldown to 0
	const int cooldown;
};

#endif