#include "Mob.hpp"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Mob::Mob(string const& arg0,Vector2f const& arg1):Player::Player(arg0,arg1),seen("none")
{
	hand = (rand()%2==1);

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
Mob::~Mob() {}
Mob * Mob::clone() const {return new Mob(*this);}

void Mob::update()
{
	Player::update();

	seen = "none";
}

bool Mob::collide(Object & arg)
{

	FloatRect oth (arg.getGlobalBounds());

	Vector2f direction (0.f,0.f);
	float distance (0.f);

	bool collided (false);

	//Eyes
	{

		direction = arg.getPosition()-getPosition();

		distance = (float) sqrt(pow(direction.x,2)+pow(direction.y,2));
		
		if(distance==0)return false;

		direction/=distance;

		if(distance<1000.f)
		{
			collided = true;
		}
	}
	//AI
	
	if(collided)
	{

		map<string,int> priority;
		priority.insert(pair<string,int>("object item healing",0));
		priority.insert(pair<string,int>("object item weapon_giver",1));
		priority.insert(pair<string,int>("object bullet",2));
		priority.insert(pair<string,int>("object player",3));
		priority.insert(pair<string,int>("object wall",4));

		string found (arg.toString());
		try
		{
			if(seen=="none" || priority.at(seen)>=priority.at(found))
			{
				if(found.find("item")!=string::npos)
				{
					setSpeed(direction*getVelocity());
				}
				if(found.find("bullet")!=string::npos)
				{
					if(distance<200.f)
					{
						setSpeed(Vector2f(-direction.y,direction.x));
						
						setSpeed(getSpeed()*getVelocity());
						if(hand)setSpeed(-getSpeed());
					}
				}
				if (found.find("player")!=string::npos && found.find("mob")==string::npos)
				{
					float rayAngle (acos(direction.x));
					if(direction.y<0)rayAngle = -rayAngle;

					rayAngle*=(180.f/3.141592654f);

					if(getRotation()<rayAngle)
						setAction(Player::RotatePos);
					else
						setAction(Player::RotateNeg);
					if(abs(getRotation()-rayAngle)<15.f)
					{
						setAction(Player::StopRot);
						setAction(Player::Shoot);
					}

					if(distance<400.f)
					{
						setSpeed(Vector2f(-direction.y,direction.x)*getVelocity());//Turn around player
						if(hand)setSpeed(-getSpeed());
					}
					else
					{
						setSpeed(direction*getVelocity());
					}
				}
				if (found.find("wall")!=string::npos)
				{
					if(distance<50.f)
					{
						int sign (rand()%2-1);
						if(sign==0)sign=1;

						setSpeed(Vector2f(-direction.y,direction.x)*getVelocity()* (float) sign);
					}
				}

				seen = arg.toString();
			}
			
			
		}catch(exception const& e)
		{}

	}

	return Player::collide(arg);
}
string Mob::toString() const {return Player::toString()+" mob";}