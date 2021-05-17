#include "TexturePack.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

TexturePack::TexturePack()
{}
TexturePack::~TexturePack()
{
	for(map<string,Texture*>::iterator i (data.begin());i!=data.end();i++)delete i->second;
}

void TexturePack::load(std::string const& path)
{
	ifstream in (path);

	if(in)
	{
		vector<string> road;
		string temp;

		while(getline(in,temp))
		{
			road.push_back(temp);
		}

		for(int i (0);i<road.size();i++)
		{
			string key (getField(road.at(i),0));
			Texture * value = new Texture();
			value->loadFromFile(getField(road.at(i),1));

			data.insert(pair<string,Texture*>(key,value));
		}
	}
	in.close();
}

Texture* TexturePack::getTextureFor(string const& key) const
{
	try
	{
		return data.at(key);
	}catch(exception const& e)
	{
		return nullptr;
	}
}

string TexturePack::getField(string const& arg0,unsigned int arg1) const
{
	unsigned int count (0);

	string temp ("");

	for(int i (0);i<arg0.size();i++)
	{
		if(arg0.at(i)==':')
		{
			count++;
			if(count>arg1)
			{
				return temp;
			}
			temp = "";
			i++;
		}
		temp+=arg0.at(i);
	}

	return temp;
}