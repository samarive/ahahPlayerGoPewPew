#include "Healing.hpp"

using namespace sf;
using namespace std;

Healing::Healing(string const& arg0,Vector2f const& arg1):Item::Item(arg0,arg1)
{
	strenght = rand()%90+10;

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
Healing::~Healing()
{}
Healing* Healing::clone() const {return new Healing(*this);}

void Healing::affect(Player & arg)
{
	arg.suffer(-strenght);
	if(arg.getMaxHealth()<arg.getHealth())
		arg.suffer(arg.getHealth()-arg.getMaxHealth());

	setHealth(0);
}

string Healing::toString() const {return Item::toString()+ " healing";}