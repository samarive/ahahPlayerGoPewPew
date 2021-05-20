#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Object.hpp"

class Bullet:public Object//Health decrease each update call, so it doesn't fly to infinity and beyond
{
public:

	Bullet(std::string const& arg="Bully",sf::Vector2f const& arg0=sf::Vector2f(0.f,0.f)/*Position*/,int arg2=100);
	Bullet(Bullet const& arg);
	virtual ~Bullet();
	virtual Bullet* clone() const;

	virtual bool collide(Object & arg);

	void setDamages(int arg);
	void setAngleDerivation(float arg);
	Object const* getOwner() const;

	//Override
	virtual void update();
	virtual std::string toString() const;

protected:
	void setVelocity(float arg);
private:

	Object* owner;//Owner is the first object being collided
	int damages;//can be negative
	float velocity;
	float angleDerivation;//Adds up to the calculated trajectory angle

};

#endif