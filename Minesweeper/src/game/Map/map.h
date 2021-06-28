#include <SFML/Graphics.hpp>

#include <vector>
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
	//10 10 32
	Field(int bombs,int sizeMap,int size);
	Chunk* contains(const sf::Vector2f&);
	void switchRect(Chunk&,int);
	std::vector<std::vector<Chunk>>& getField();
	void generate();
	void setTexture(sf::Texture* texture);
	void Open(Chunk* chunk);
	~Field() = default;
private:
	std::vector<std::vector<Chunk>> chunks;
	sf::Texture TileMapTexture;
	int bombs, sizeMap, size;
	std::random_device rand;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
};

