#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <string>
//#include <cassert>
//#include <optional>
#include <vector>

#include "map.h"

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

	sf::RenderWindow window;
	void update();
	void HandleEvent();
	void drawEntity();

	Field field;

	const int bombs = 10;
	int flags = 0;

	sf::Font font;
	sf::Text text,sec;
	std::pair<int, int> textPos = { 150,2 };
	const int sizeText = 24;
	const int sizeMap = 10;
	const int size = 32;//size of tileMap
	const std::string Dir = "Data/";
	const std::string nameFont = "arial.ttf";
	int state = 0;

	sf::Clock clock;
	sf::Time timer;
};
