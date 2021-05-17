#ifndef WALL_HPP_INCLUDED
#define WALL_HPP_INCLUDED

#include "Object.hpp"
#include <vector>

typedef std::vector<sf::Vector2f> pattern;

class Wall:public Object
{
public:
	Wall(std::string const& arg="Wally",sf::Vector2f const& arg0=sf::Vector2f(0.f,0.f)/*Position*/,int arg1=100/*health*/);
	virtual ~Wall();
	virtual Wall* clone() const;

	void setMovementDuration(unsigned int arg);
	void setPath(pattern const& arg);

	//Override
	virtual void update();//Calls Object::update()
	virtual std::string toString() const;
private:

	unsigned int mDuration;//How long does it move beafore changing direction
	unsigned int count;//from 0 to mDuration in loops
	pattern path;//All movement vectors :)
	pattern::iterator movement;//iterates over pattern

};

#endif