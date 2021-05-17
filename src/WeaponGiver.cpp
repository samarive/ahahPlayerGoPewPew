#include "WeaponGiver.hpp"

using namespace sf;
using namespace std;

WeaponGiver::WeaponGiver(string const& arg0,Vector2f const& arg1,Weapon const& arg2):Item::Item(arg0,arg1),toGive(nullptr)
{

	toGive = arg2.clone();
	if(Object::texturePack!=nullptr)
	{
		Texture * pack (Object::texturePack->getTextureFor(toGive->toShortString()+"_giver"));
		if(pack!=nullptr)
		{
			setTextureRect({0,0,(int) pack->getSize().x,(int) pack->getSize().y});
			setTexture(*pack);
		}
	}
}
WeaponGiver::~WeaponGiver()
{
	if(toGive!=nullptr)delete toGive;
}
WeaponGiver * WeaponGiver::clone() const {return new WeaponGiver(*this);}

void WeaponGiver::affect(Player & arg)
{
	arg.setGun(*toGive);
	setHealth(0);
}

string WeaponGiver::toString() const {return Item::toString()+" weapon_giver";}