#include "Mob.hpp"
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Mob::Mob(string const& arg0,Vector2f const& arg1):Player::Player(arg0,arg1)
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
Mob::~Mob() {}
Mob * Mob::clone() const {return new Mob(*this);}

bool Mob::collide(Object & arg)
{

	Vector2f rays[16];

	FloatRect oth (arg.getGlobalBounds());

	for(int i (0);i<8;i++)
	{
		rays[i] = getPosition();
		Vector2f rayDir (cos((float) (i)*3.141592654f/4.f),sin((float) (i)*3.141592654f/4.f));
	
		float rayVelocity (10.f);
		float traveled (0.f);

		rayDir*=rayVelocity;

		bool collided (false);

		while(traveled<512.f and !collided)
		{
			rays[i]+=rayDir;
			traveled+=rayVelocity;

			collided = (rays[i].x>oth.left
				&& rays[i].x<oth.left+oth.width
				&& rays[i].y>oth.top
				&& rays[i].y<oth.top+oth.height);
		}

		if(collided)
		{
			if(arg.toString().find("wall")!=string::npos)
			{
				if(traveled<100.f)
				{
					setSpeed(-rayDir);//Normal to rayDir
				}
			}
			if(arg.toString().find("player")!=string::npos && arg.toString().find("mob")==string::npos)
			{
				if(traveled<200)setSpeed(Vector2f(-rayDir.y,rayDir.x));
				else setSpeed(Vector2f(rayDir.x,rayDir.y));

				float diff ((180.f/3.141592654f)*(float) (i)*3.141592654f/4.f - getRotation());

				if(diff > 12.5f)
					setAction(Player::RotatePos);
				else if(diff < -12.5f)
					setAction(Player::RotateNeg);
				else
				{
					setAction(Player::StopRot);
					setAction(Player::Shoot);
				}
			}
		}
		if(collided && getSpeed().x == 0.f && getSpeed().y == 0.f)
		{
			setAction(Player::None);
			float dirX ((float) (rand()%200-100)/100.f);
			setSpeed(Vector2f(dirX,sqrt(1.f-dirX))*getVelocity());
		}
	}

	return Player::collide(arg);
}
string Mob::toString() const {return Player::toString()+" mob";}