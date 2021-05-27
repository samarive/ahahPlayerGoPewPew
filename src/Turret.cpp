#include "Turret.hpp"

using namespace sf;
using namespace std;

Turret::Turret(string const& arg0,Vector2f const& arg1,int arg2):Mob::Mob(arg0,arg1,arg2)
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
Turret::~Turret()
{}
Turret * Turret::clone() const {return new Turret(*this);}

string Turret::toString() const {return Mob::toString()+" turret";}

void Turret::think(Object & arg)
{
	Mob::think(arg);
	setSpeed(Vector2f(0.f,0.f));
}