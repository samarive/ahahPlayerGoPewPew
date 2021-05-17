#include "Item.hpp"

using namespace sf;
using namespace std;

Item::Item(string const& arg0,Vector2f const& arg1):Object::Object(arg0,arg1)
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
};
Item::~Item() {}


string Item::toString() const {return Object::toString()+" item";}