#include "Wall.hpp"
#include <cmath>

using namespace std;
using namespace sf;

Wall::Wall(string const& arg,Vector2f const& arg2,int arg3):Object::Object(arg,arg2,arg3),mDuration(0),count(0)
{
	movement = path.begin();

	if(Object::texturePack!=nullptr)
	{
		Texture * pack (Object::texturePack->getTextureFor(toShortString()));
		
		if(pack!=nullptr)
		{
			pack->setRepeated(true);
			setTextureRect({0,0,(int) pack->getSize().x,(int) pack->getSize().y});
			setTexture(*pack);
		}
	}
}
Wall::~Wall() {};
Wall* Wall::clone() const {return new Wall(*this);}


void Wall::setMovementDuration(unsigned int arg) {mDuration = arg;}
void Wall::setPath(pattern const& arg)
{
	path = arg;
	movement = path.begin();
	count = 0u;
}

void Wall::update()
{
	Object::update();

	if(mDuration>0 && path.size()>0)
	{	
		if(count==mDuration)
		{
			movement++;
			count=0;
		}
		if(movement==path.end())movement=path.begin();
		setSpeed(*movement);
		setRotation(asin((*movement).y/sqrt(pow((*movement).x,2)+pow((*movement).y,2))));
		count++;
	}
}
string Wall::toString() const
{
	return Object::toString()+" wall";
}