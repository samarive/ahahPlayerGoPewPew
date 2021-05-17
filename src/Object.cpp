#include "Object.hpp"
#include <iostream>

using namespace sf;
using namespace std;

sf::Texture * Object::base = nullptr;
unsigned int Object::objectCount = 0;
TexturePack* Object::texturePack = nullptr;

Object::Object(string const& arg0,Vector2f const& arg1,int arg2):Sprite::Sprite(),name(arg0),health (arg2)
{
	Object::objectCount++;
	
	if(Object::base==nullptr)
	{
		base = new Texture();
		base->loadFromFile("img/default.png");
	}

	setTexture(*base);

	if(Object::texturePack!=nullptr)
	{
		Texture * pack (Object::texturePack->getTextureFor(toShortString()));
		if(pack!=nullptr)
		{
			setTextureRect({0,0,(int) pack->getSize().x,(int) pack->getSize().y});
			setTexture(*pack);
		}
	}

	setPosition(arg1);
}
Object::Object(Object const& arg):Sprite(arg),speed(arg.speed),name(arg.name+"-Copy"),health(arg.health)
{
	Object::objectCount++;
	setTexture(*base);
}
Object::~Object()
{
	Object::objectCount--;

	if(Object::objectCount==0u)
	{
		delete base;
		base = nullptr;
	}
}

Object* Object::clone() const {return new Object(*this);}

int Object::getHealth() const {return health;}
void Object::suffer(int arg)
{
	health-=arg;
}

sf::Vector2f Object::getSpeed() const
{
	return speed;
}
void Object::setSpeed(sf::Vector2f const& arg)
{
	speed = arg;
}

void Object::update()
{
	setPosition(getPosition()+speed);
}

void Object::setSize(sf::Vector2f const& arg)
{
	if(getTexture()->isRepeated())setTextureRect({0,0,(int) arg.x,(int) arg.y});

	if(getLocalBounds().width!=0 && getLocalBounds().height!=0)setScale(arg.x/getLocalBounds().width,arg.y/getLocalBounds().height);
	
	setOrigin(Vector2f(getLocalBounds().width,getLocalBounds().height)/2.f);
}

Packet Object::toPacket () const
{
	Packet toReturn;
	toReturn << name;
	toReturn << toString();
	toReturn << getPosition().x;
	toReturn << getPosition().y;
	toReturn << getLocalBounds().width;
	toReturn << getLocalBounds().height;
	toReturn << health;

	return toReturn;
}

std::string Object::toString () const
{
	return "object";
}
string Object::toShortString() const
{
	string toReturn ("");

	for(int i (toString().size()-1);i>-1;i--)
	{
		if(toString().at(i)==' ')return toReturn;
	
		toReturn = toString().at(i) + toReturn;
	}

	return toReturn;
}

bool Object::collide(Object & arg)
{
	FloatRect dis (getGlobalBounds());
	FloatRect oth (arg.getGlobalBounds());

	dis.left+=speed.x;
	dis.top+=speed.y;
  
  	if(dis.left>oth.left+oth.width 
	|| dis.left+dis.width<oth.left      
	|| dis.top>oth.top+oth.height         
	|| dis.top+dis.height<oth.top)
  	{


  		return false;
  	}
  	else if(arg.toString().find("bullet")==string::npos && toString().find("bullet")==string::npos)
  	{

  		speed = Vector2f(0.f,0.f);

  		return true;
  	}
  	else
  	{
  		return true;
  	}

}

void Object::setHealth(int arg) {health = arg;}