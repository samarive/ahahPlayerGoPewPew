/*

	Program by Sama Rive
	SPECIAL THANKS TO MARCUS PHAM FOR EMOTIONAL SUPPORT
	Visit : https://www.youtube.com/channel/UCeGx3tHBFJ2CxMifChp6uiQ

*/

#include <iostream>
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Rifle.hpp"
#include "TexturePack.hpp"
#include "Level.hpp"
#include <cmath>
#include <ctime>
#include <cstring>


using namespace std;
using namespace sf;

/*
	TODO
	
	-Add some collectibles (Items on ground)
	-MORE BAD GUYS
	-More ammo
	-More weapons
	-Eventually implement multiplayer

*/


int main(int argc,char ** argv)
{
	srand(time(NULL));

	TexturePack basic;
	basic.load("texturepacks/basic.txt");
	Object::texturePack = &basic;
	Level lvl;
	lvl.generate(rand()%10+5,rand()%5+2);

	RenderWindow win (VideoMode(800,450),"Player go PEW ! PEW !",Style::Fullscreen);
	win.setFramerateLimit(60);

	
	while(win.isOpen())
	{
		Event event;
		while(win.pollEvent(event))
		{
			lvl.passEvent(event);
			if(event.type==Event::Closed)win.close();
			if(event.type==Event::KeyPressed && event.key.code==Keyboard::R)
			{
				lvl.empty();
				lvl.generate(rand()%10+5,rand()%5+2);
			}
		}

		lvl.tick();

		win.clear();

		lvl.paintOn(win);

		win.display();
	}

	lvl.empty();
	

	return 0;
}