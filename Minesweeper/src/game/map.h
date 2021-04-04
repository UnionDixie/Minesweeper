#include <SFML/Graphics.hpp>

#include <list>
#include <random>
#include <iostream>

#include "chunk.h"

class Field
{
public:
	enum Type
	{
		empty,
		one,
		two,
		three,
		four,
		five,
		six,
		seven,
		eigth,
		bomb,
		close,
		flag
	};
	Field();
	std::pair<bool, Chunk*> contains(const sf::Vector2f&);
	void switchRect(Chunk&,const int);
	std::vector<std::vector<Chunk>>& getField();
	~Field();
private:
	std::vector<std::vector<Chunk>> chunks;

	std::random_device rand;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;

	sf::Texture TileMapTexture;

	const int bombs = 10;
	const int sizeMap = 10;
	const int size = 32;//size of tileMap
	const std::string Dir = "Data/";
	const std::string nameTileMap = "1.png";
};

