#include "Shotgun.hpp"
#include <iostream>

using namespace sf;

Shotgun::Shotgun():Weapon::Weapon(60)
{}
Shotgun::~Shotgun()
{}
Shotgun* Shotgun::clone() const{return new Shotgun(*this);}//I hate this

void Shotgun::generateBullet(Vector2f const& arg) const
{
	Bullet * bull0 = getBulletModel().clone();//whoever owns world HAVE to delete it anyway...
	bull0->setPosition(arg);
	bull0->setSize(Vector2f(64.f,36.f));//16:9
	bull0->setAngleDerivation(3.141592654f/8.f);

	Bullet * bull1 = getBulletModel().clone();//whoever owns world HAVE to delete it anyway...
	bull1->setPosition(arg);
	bull1->setSize(Vector2f(64.f,36.f));//16:9

	Bullet * bull2 = getBulletModel().clone();//whoever owns world HAVE to delete it anyway...
	bull2->setPosition(arg);
	bull2->setSize(Vector2f(64.f,36.f));//16:9
	bull2->setAngleDerivation(-3.141592654f/8.f);

	Weapon::world->push_back(bull0);
	Weapon::world->push_back(bull1);
	Weapon::world->push_back(bull2);
}

std::string Shotgun::toString() const {return Weapon::toString()+" shotgun";}