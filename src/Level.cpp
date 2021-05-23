#include "Level.hpp"
#include "WeaponGiver.hpp"
#include "Mob.hpp"
#include "Healing.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Level::Level():camera (Vector2f(0.f,0.f),Vector2f(1920.f,1080.f))
{
	Weapon::setWorld(world);
}
Level::~Level()
{
	empty();
}

void Level::tick()
{

	if(world.size()>0)camera.move(Vector2f(world.at(0)->getPosition()-camera.getCenter())/10.f);

	for(vector<Object*>::iterator i (world.begin());i!=world.end();i++)
	{
		if(!isInCam(*i))continue;

		for(vector<Object*>::iterator i_ (i+1);i_!=world.end();i_++)
		{
			if(!isInCam(*i_))continue;
			(*i_)->collide(*(*i));
			(*i)->collide(*(*i_));
		}

		(*i)->update();

		if((*i)->getHealth()<=0)
		{
			delete *i;
			world.erase(i);
			i--;
		}

		if(Keyboard::isKeyPressed(Keyboard::LShift) && (*i)->toShortString()=="mob")cout << "coucou" << endl;
	}
}
void Level::paintOn(RenderWindow & arg)
{
	View minimap (world.at(0)->getPosition(),Vector2f(5000.f,5000.f));
	minimap.setViewport({0.7f,0.f,0.3f,0.53333f});
	for(vector<Object*>::iterator i (world.begin());i!=world.end();i++)
	{
		arg.setView(minimap);
		arg.draw(*(*i));
		if(!isInCam(*i))continue;
		arg.setView(camera);
		if((*i)->getHealth()<(*i)->getMaxHealth())
		{
			RectangleShape bar (Vector2f(100.f,16.f));
			bar.setOrigin(Vector2f(50.f,8.f));
			bar.setPosition((*i)->getPosition()-Vector2f(0.f,(*i)->getGlobalBounds().height/2.f+32.f));
			bar.setFillColor(Color::White);
			
			RectangleShape lifeBar (Vector2f(98.f*((float) ((*i)->getHealth())/ (float) ((*i)->getMaxHealth())),14.f));
			lifeBar.setPosition(bar.getPosition()-Vector2f(bar.getGlobalBounds().width,bar.getGlobalBounds().height)/2.f+Vector2f(1.f,1.f));
			lifeBar.setFillColor(Color::Green);
			
			if((float) ((*i)->getHealth())/ (float) ((*i)->getMaxHealth())<0.5f)
				lifeBar.setFillColor(Color(255,255,0));
			if((float) ((*i)->getHealth())/ (float) ((*i)->getMaxHealth())<0.25f)
				lifeBar.setFillColor(Color::Red);

			arg.draw(bar);
			arg.draw(lifeBar);

		}
		arg.draw(*(*i));

	}

	arg.setView(camera);
	if(world.size()>0)
	{
		Vector2f v (cos((world.at(0)->getRotation()+45)*(3.141592654f/180.f)),sin((world.at(0)->getRotation()+45)*(3.141592654f/180.f)));
		Vector2f w (cos((world.at(0)->getRotation()-45)*(3.141592654f/180.f)),sin((world.at(0)->getRotation()-45)*(3.141592654f/180.f)));

		VertexArray light (Triangles,3);
		light[0].position = world.at(0)->getPosition();
		light[1].position = world.at(0)->getPosition()+v*1500.f;
		light[2].position = world.at(0)->getPosition()+w*1500.f;

		light[0].color = Color(255,255,255,100);
		light[1].color = Color(255,255,255,100);
		light[2].color = Color(255,255,255,100);

		RectangleShape darkness (Vector2f(1920.f,1080.f));
		darkness.setPosition(camera.getCenter()-camera.getSize()/2.f);
		darkness.setFillColor(Color(0,0,0,150));

		arg.draw(darkness);
		arg.draw(light);
	}

}
void Level::passEvent(Event const& arg)
{

	for(vector<Object*>::iterator i (world.begin());i!=world.end();i++)
	{
		if((*i)->toString().find("player")!=string::npos)
		{
			Player * playerPtr ((Player*) (*i));
			playerPtr->treatEvent(arg);
		}
	}
}

void Level::empty()
{
	for(vector<Object*>::iterator i (world.begin());i!=world.end();i++)
	{
		delete *i;
	}
	world.clear();
}
void Level::generate(int dimension,int proportion)
{
	int createdRoom (0);
	
	bool rooms[dimension][dimension];
	for(int y (0);y<dimension;y++)
	{
		for(int x (0);x<dimension;x++)
		{
			rooms[y][x]=false;
		}
	}

	while(pow(dimension,2)/proportion>createdRoom)
	{
		Vector2i coords (rand()%dimension,rand()%dimension);
	
		if(rooms[coords.y][coords.x]!=true)
		{
			createdRoom++;
			rooms[coords.y][coords.x]=true;
		}
	}
	rooms[dimension/2][dimension/2] = true;

	Player * player = new Player("j1",Vector2f((dimension/2)*500+250,(dimension/2)*500+250));
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::Right),Player::MoveRight);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::Left),Player::MoveLeft);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::Up),Player::MoveUp);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::Down),Player::MoveDown);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::A),Player::RotateNeg);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::E),Player::RotatePos);
	player->bind(detailedEvent(Event::KeyPressed,Keyboard::Space),Player::Shoot);


	player->bind(detailedEvent(Event::KeyReleased,Keyboard::Right),Player::StopHorizontal);
	player->bind(detailedEvent(Event::KeyReleased,Keyboard::Left),Player::StopHorizontal);
	player->bind(detailedEvent(Event::KeyReleased,Keyboard::Up),Player::StopVertical);
	player->bind(detailedEvent(Event::KeyReleased,Keyboard::Down),Player::StopVertical);
	player->bind(detailedEvent(Event::KeyReleased,Keyboard::A),Player::StopRot);
	player->bind(detailedEvent(Event::KeyReleased,Keyboard::E),Player::StopRot);

	player->setGun(Rifle());
	player->setSize(Vector2f(100,100));

	world.push_back(player);

	for(int y (0);y<dimension;y++)
	{
		for(int x (0);x<dimension;x++)
		{
			if(rand()%20==0)
			{
				WeaponGiver * wG;
				if(rand()%2==0)
				{
					wG = new WeaponGiver("generated",Vector2f(x*500+250,y*500+250));
				}
				else
				{
					wG = new WeaponGiver("generated",Vector2f(x*500+250,y*500+250),Shotgun());
				}
				wG->setSize(Vector2f(128,64));
				world.push_back(wG);
			}
			else if(rand()%20==0)
			{
				world.push_back(new Healing("generated",Vector2f(x*500+250,y*500+250)));
				world.at(world.size()-1)->setSize(Vector2f(128,128));
			}
			if(rand()%20==0)
			{
				Mob * m = new Mob("generated"+to_string(x*y),Vector2f(x*500+200,y*500+200));
				m->setGun(Rifle());
				m->setSize(Vector2f(100,100));
				
				world.push_back(m);
			}
			
			if(x==0 || (rooms[y][x]==true && x>0 && rooms[y][x-1]==false))
			{
				Wall * wall = new Wall("generated",Vector2f(x*500+32,y*500+250),10000);
				wall->setSize(Vector2f(64,500));
				world.push_back(wall);
			}
			if(x==dimension-1 || (rooms[y][x]==true && x<dimension-1 && rooms[y][x+1]==false))
			{
				Wall * wall = new Wall("generated",Vector2f(x*500+532,y*500+250),10000);
				wall->setSize(Vector2f(64,500));
				world.push_back(wall);
			}
			if(y==0 || (rooms[y][x]==true && y>0 && rooms[y-1][x]==false))
			{
				Wall * wall = new Wall("generated",Vector2f(x*500+250,y*500+32),10000);
				wall->setSize(Vector2f(500,64));
				world.push_back(wall);
			}
			if(y==dimension-1 || (rooms[y][x]==true && y<dimension-1 && rooms[y+1][x]==false))
			{
				Wall * wall = new Wall("generated",Vector2f(x*500+250,y*500+532),10000);
				wall->setSize(Vector2f(500,64));
				world.push_back(wall);
			}

		}
	}


}

vector<Packet> Level::getPacketVector()
{
	vector<Packet> toReturn;

	for(int i (0);i<world.size();i++)
	{
		toReturn.push_back(world.at(i)->toPacket());
	}

	return toReturn;
}

bool Level::isInCam(Object* const& arg) const
{
	FloatRect cam ({camera.getCenter().x-camera.getSize().x/2.f,camera.getCenter().y-camera.getSize().y/2.f,camera.getSize().x,camera.getSize().y});
	FloatRect obj (arg->getGlobalBounds());

	return !(cam.left>obj.left+obj.width
	|| cam.left+cam.width<obj.left
	|| cam.top>obj.top+obj.height
	|| cam.top+cam.height<obj.top);
}