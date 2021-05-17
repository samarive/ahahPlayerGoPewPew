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

using namespace std;
using namespace sf;

/*
	TODO
	
	-[If bored] Add some collectibles (Items on ground)
	-Bad guys (essentially hurting walls)
	-Natural spawn in level generation
*/


int main()
{
	srand(time(NULL));

	TexturePack basic;
	basic.load("texturepacks/basic.txt");
	Object::texturePack = &basic;
	Level lvl;
	lvl.generate(100,3);

	RenderWindow win (VideoMode(800,450),"fenetre",Style::Fullscreen);
	win.setFramerateLimit(60);

	
	while(win.isOpen())
	{
		Event event;
		while(win.pollEvent(event))
		{
			lvl.passEvent(event);
			if(event.type==Event::Closed)win.close();
		}

		lvl.tick();

		win.clear();

		lvl.paintOn(win);

		win.display();
	}

	lvl.empty();

	return 0;
}