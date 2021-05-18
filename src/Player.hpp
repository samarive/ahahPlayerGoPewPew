#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Object.hpp"
#include "Weapon.hpp"
#include "Bullet.hpp"
#include <map>
#include <utility>

typedef std::pair<sf::Event::EventType,sf::Keyboard::Key> detailedEvent;

class Player:public Object
{
public:
	
	enum Action
	{
		None=0,
		MoveRight,
		MoveLeft,
		MoveUp,
		MoveDown,
		Shoot,//Asks weapon to fire
		StopHorizontal,//Sets horizontal speed to 0
		StopVertical,//Same but with vertical
		RotatePos,//Rotate with a postitif angle
		RotateNeg,//Rotate with a negative angle
		StopRot
	};

	Player(std::string const& arg="Player",sf::Vector2f const& arg0=sf::Vector2f(0.f,0.f)/*Position*/);
	virtual ~Player();
	virtual Player* clone() const;

	void treatEvent(sf::Event const& arg);//Only works with keypressed and key released event
	void bind(detailedEvent const& arg0,Action const& arg1);

	void setVelocity(float arg);
	void setGun(Weapon const& arg);
	void setAmmo(Bullet const& arg);

	//Override
	virtual void update();
	virtual std::string toString() const;
	virtual bool collide(Object & arg);
protected:

	float getVelocity() const;
	void setAction(Action arg);

private:

	std::map<detailedEvent,Action> bindings;
	float velocity;

	float rotSpeed;

	Weapon * gun;
	Bullet ammo;

};

#endif