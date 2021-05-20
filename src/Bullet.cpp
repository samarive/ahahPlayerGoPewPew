#include "Bullet.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

Bullet::Bullet(string const& arg0,Vector2f const& arg1,int arg2):Object::Object(arg0,arg1,arg2),damages(10),owner(nullptr),velocity(10.f),angleDerivation(0.f)
{
	if(Object::texturePack!=nullptr)
	{
		Texture * pack (Object::texturePack->getTextureFor(toShortString()));
		if(pack!=nullptr)
		{
			setTextureRect({0,0,(int) pack->getSize().x,(int) pack->getSize().y});
			setTexture(*pack);
		}
	}
}
Bullet::Bullet(Bullet const& arg):Object::Object(arg),damages(arg.damages),owner(nullptr),velocity(arg.velocity),angleDerivation(arg.angleDerivation)
{
	if(Object::texturePack!=nullptr)
	{
		Texture * pack (Object::texturePack->getTextureFor(toShortString()));
		if(pack!=nullptr)
		{
			setTextureRect({0,0,(int) pack->getSize().x,(int) pack->getSize().y});
			setTexture(*pack);
		}
	}
}
Bullet::~Bullet()
{}
Bullet* Bullet::clone() const {return new Bullet(*this);}


bool Bullet::collide(Object & arg)
{	
	if(arg.toString().find("bullet")!=string::npos)return false;
	if(Object::collide(arg) && owner!=&arg && owner!=nullptr)
	{
		setHealth(0);
		arg.suffer(damages);

		if(arg.toString().find("wall")!=string::npos)
		{
			Vector2f diff (getPosition()-arg.getPosition());
		
			if(arg.getLocalBounds().width>arg.getLocalBounds().height)
			{
				if(diff.y>0)arg.rotate(-diff.x/25.f);
				if(diff.y<0)arg.rotate(diff.x/25.f);
			}
			if(arg.getLocalBounds().width<arg.getLocalBounds().height)
			{
				if(diff.x>0)arg.rotate(diff.y/25.f);
				if(diff.x<0)arg.rotate(-diff.y/25.f);
			}
		}

		return true;
	}
	else if(Object::collide (arg) && owner==nullptr)
	{
		owner = &arg;
		
		setSpeed(Vector2f(cos(angleDerivation+arg.getRotation()*(3.141592654f/180.f))*velocity,sin(angleDerivation+arg.getRotation()*(3.141592654f/180.f))*velocity));
		setRotation(arg.getRotation()+angleDerivation*(180.f/3.141592654f));
	}

	return false;
}

void Bullet::setDamages(int arg) {damages = arg;}
void Bullet::setAngleDerivation(float arg) {angleDerivation = arg;}
Object const* Bullet::getOwner() const {return owner;}


void Bullet::setVelocity(float arg) {velocity = arg;}

void Bullet::update()
{
	Object::update();
	setHealth(getHealth()-1);
}
string Bullet::toString() const
{
	return Object::toString()+" bullet";
}
