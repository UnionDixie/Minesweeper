#include <SFML/Graphics.hpp>

#include <iostream>

#include <random>

#include <string>

#include <cassert>
//static_assert

#include <optional>
#include <vector>

class Game
{
public:
	Game();
	void run();
	~Game();

private:
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
	std::random_device rand;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;

	const int sizeMap = 10;//square 10*10 easy
	const int bombs = 10;

	int flags = 0;

	sf::RenderWindow window;

	sf::Texture TileMapTexture;
	sf::Sprite TileMap;

	sf::Font font;
	sf::Text text,sec;
	std::pair<int, int> textPos = { 150,2 };
	const int sizeText = 24;

	const int size = 32;//size of tileMap
	const std::string Dir = "Data/";
	const std::string nameTileMap = "1.png";
	const std::string nameFont = "arial.ttf";

	int state = 0;

	int MapValue[12][12];//val - bomb or num
	int MapDraw[12][12];//drawMap

	sf::Clock clock;
	sf::Time timer;

	std::vector<std::vector
		<std::tuple<sf::Sprite, sf::Texture*, int>>> tiles;
};
