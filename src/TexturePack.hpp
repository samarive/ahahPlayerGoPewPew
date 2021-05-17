#ifndef TEXTUREPACK_HPP_INCLUDED
#define TEXTUREPACK_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <exception>

class TexturePack
{
public:
	TexturePack();
	virtual ~TexturePack();

	void load(std::string const& path);

	sf::Texture * getTextureFor(std::string const& key) const;

private:

	std::string getField(std::string const& arg0,unsigned int arg1) const;

	std::map<std::string,sf::Texture*> data;

};

#endif