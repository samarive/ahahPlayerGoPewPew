#include "Object.hpp"
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

sf::Texture * Object::base = nullptr;
unsigned int Object::objectCount = 0;
TexturePack* Object::texturePack = nullptr;

Object::Object(string const& arg0,Vector2f const& arg1,int arg2):Sprite::Sprite(),name(arg0),health (arg2),maxHealth (arg2)
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
Object::Object(Object const& arg):Sprite(arg),speed(arg.speed),name(arg.name+"-Copy"),health(arg.health),maxHealth(arg.maxHealth)
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
int Object::getMaxHealth() const {return maxHealth;}
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

string Object::getName() const {return name;}

bool Object::collide(Object & arg)
{

	if(arg.getRotation()==0.f)
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
	else
	{
	  	Vector2f origin (Vector2f(arg.getGlobalBounds().left,arg.getGlobalBounds().top)+Vector2f(arg.getGlobalBounds().width,arg.getGlobalBounds().height)/2.f);


	  	Object * copy (arg.clone());
	  	copy->setRotation(0.f);
	  	Vector2f dimensions (copy->getGlobalBounds().width,copy->getGlobalBounds().height);
	  	delete copy;
	  	copy = nullptr;

	  	Object * disCopy ((Object*) clone());
	  	disCopy->setRotation(0.f);
	  	Vector2f disDim (disCopy->getGlobalBounds().width,disCopy->getGlobalBounds().height);
	  	delete disCopy;
	  	disCopy = nullptr;


	  	Vector2f abscisse (cos(getRotation()*(3.141592654f/180.f)),sin(getRotation()*(3.141592654f/180.f)));
	  	Vector2f ordonee (-abscisse.y,abscisse.x);
	  	


	  	Vector2f vertex[] = 
	  	{
	  		Vector2f(getGlobalBounds().left+getGlobalBounds().width/2.f,getGlobalBounds().top+getGlobalBounds().height/2.f) - abscisse*disDim.x/2.f - ordonee*disDim.y/2.f,
	  		Vector2f(getGlobalBounds().left+getGlobalBounds().width/2.f,getGlobalBounds().top+getGlobalBounds().height/2.f) + abscisse*disDim.x/2.f - ordonee*disDim.y/2.f,
	  		Vector2f(getGlobalBounds().left+getGlobalBounds().width/2.f,getGlobalBounds().top+getGlobalBounds().height/2.f) + abscisse*disDim.x/2.f + ordonee*disDim.y/2.f,
	  		Vector2f(getGlobalBounds().left+getGlobalBounds().width/2.f,getGlobalBounds().top+getGlobalBounds().height/2.f) - abscisse*disDim.x/2.f + ordonee*disDim.y/2.f
	  	};

	  	for(int i (0);i<4;i++)
	  	{
	  		Vector2f inRef (vertex[i]+speed);
	  		inRef-=origin;

	  		float angle (acos(inRef.x/sqrt(pow(inRef.x,2)+pow(inRef.y,2))));
	  		if(inRef.y<0)angle = -angle;
	  		angle-=arg.getRotation()*(3.141592654f/180.f);

	  		float norm (sqrt(pow(inRef.x,2)+pow(inRef.y,2)));
	  		inRef = Vector2f(cos(angle),sin(angle));
	  		inRef*=norm;

	  		if(inRef.x<dimensions.x/2.f
	  		&& inRef.x>-dimensions.x/2.f
	  		&& inRef.y<dimensions.y/2.f
	  		&& inRef.y>-dimensions.y/2.f)
	  		{

	  			if(toString().find("bullet")==string::npos && arg.toString().find("bullet")==string::npos)setSpeed(Vector2f(0.f,0.f));

	  			return true;
	  		}
	  	}

	  	return false;
	  }
}


void Object::setHealth(int arg) {health = arg;}