#pragma once

#include<map>
#include<string>
#include<string_view>
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<memory>

class DataLoader
{
public:
	// "local + DataPath/"
	DataLoader(std::string_view path);
	std::unique_ptr<sf::Texture> getTexture(std::string_view name) const;
	std::unique_ptr<sf::Font> getFont(std::string_view name) const;
	~DataLoader() = default;
private:

private:
	std::map<std::string, sf::Texture> textureStorage;
	std::map<std::string, sf::Font> fontStorage;
	//std::map<std::string, sf::> soundStorage;
	//also can use any :)
};

