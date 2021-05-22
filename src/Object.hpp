#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "TexturePack.hpp"

class Object:public sf::Sprite
{
public:
	Object(std::string const& arg="Thingy",sf::Vector2f const& arg0=sf::Vector2f(0.f,0.f)/*Position*/,int arg2 = 100);//calls setSize
	Object(Object const& arg);
	virtual ~Object();
	virtual Object* clone() const;

	int getHealth() const;
	int getMaxHealth() const;
	void suffer(int arg);

	sf::Vector2f getSpeed() const;
	void setSpeed(sf::Vector2f const& arg);

	virtual void update();//༼ つ ◕_◕ ༽つ
	void setSize(sf::Vector2f const& arg);//scale and set origin to center

	virtual sf::Packet toPacket() const;//packet contains name;toString;position (x and y);size (x and y);health

	virtual bool collide(Object & arg);

	virtual std::string toString() const;//Returns lower case class name + lower case parent toString (convention)
	std::string toShortString() const;
	std::string getName() const;

	static TexturePack * texturePack;

protected:

	void setHealth(int arg);

private:

	sf::Vector2f speed;
	std::string name;

	int health;
	int maxHealth;

	static sf::Texture * base;
	static unsigned int objectCount;
};

#endif