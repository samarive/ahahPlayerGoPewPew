#include "Rifle.hpp"

using namespace sf;

Rifle::Rifle():Weapon::Weapon(20)
{}
Rifle::~Rifle()
{}
Rifle* Rifle::clone() const{return new Rifle(*this);}//I hate this

void Rifle::generateBullet(Vector2f const& arg) const
{
	Bullet * bull = getBulletModel().clone();//whoever owns world HAVE to delete it anyway...
	bull->setPosition(arg);
	bull->setSize(Vector2f(64.f,36.f));//16:9

	Weapon::world->push_back(bull);
}

std::string Rifle::toString() const {return Weapon::toString()+" rifle";}