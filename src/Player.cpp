#include "Player.hpp"
#include "Item.hpp"
#include <exception>
#include <cmath>

using namespace std;
using namespace sf;

Player::Player(string const& arg,Vector2f const& arg0):Object::Object(arg,arg0),velocity(10.f),rotSpeed(0.f),gun(nullptr)
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
Player::~Player()
{
	if(gun!=nullptr)delete gun;
}
Player* Player::clone() const {return new Player(*this);}

	

void Player::treatEvent(Event const& arg)
{
	detailedEvent dE;
	dE.first = arg.type;
	dE.second = arg.key.code;

	try
	{
		Action toDo (bindings.at(dE));

		switch(toDo)
		{
			case Action::None:
				setSpeed(Vector2f(0,0));
			break;
			case Action::MoveRight:
				setSpeed(Vector2f(velocity,getSpeed().y));
			break;
			case Action::MoveUp:
				setSpeed(Vector2f(getSpeed().x,-velocity));
			break;
			case Action::MoveLeft:
				setSpeed(Vector2f(-velocity,getSpeed().y));
			break;
			case Action::MoveDown:
				setSpeed(Vector2f(getSpeed().x,velocity));
			break;
			case Action::StopHorizontal:
				setSpeed(Vector2f(0.f,getSpeed().y));
			break;
			case Action::StopVertical:
				setSpeed(Vector2f(getSpeed().x,0.f));
			break;
			case Action::RotatePos:
				rotSpeed = velocity;
			break;
			case Action::RotateNeg:
				rotSpeed = -velocity;
			break;
			case Action::StopRot:
				rotSpeed = 0.f;
			break;
			case Action::Shoot:
				if(gun!=nullptr)
				{
					gun->setBulletModel(ammo);
					gun->fire(getPosition());
				}
			break;
		}

	}catch(exception const& e)
	{
		return;
	}
}


void Player::bind(detailedEvent const& arg0,Action const& arg1)
{
	bindings.insert(pair<detailedEvent,Action>(arg0,arg1));
}

void Player::setVelocity(float arg) {velocity = arg;}
void Player::setGun(Weapon const& arg)
{
	if(gun!=nullptr)delete gun;
	gun = arg.clone();//gun is deleted in ~Player()
}
void Player::setAmmo(Bullet const& arg)
{ammo = arg;}

void Player::update()
{
	Object::update();
	rotate(rotSpeed);

	if(gun!=nullptr)gun->poke();
}

string Player::toString() const {return Object::toString()+" player";}

bool Player::collide(Object & arg)
{	
	float rot (getRotation());
	setRotation(0);

	bool toReturn (Object::collide(arg));

	setRotation(rot);

	if(toReturn && arg.toString().find("item")!=string::npos)
	{
		Item * it ((Item*) &arg);
		it->affect(*this);
	}

	return toReturn;
}