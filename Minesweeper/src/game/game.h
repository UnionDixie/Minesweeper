#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "Map/map.h"

class Game
{
public:
	Game();
	void run();
	~Game() = default;
private:
	sf::RenderWindow window;
	void update();
	void HandleEvent();
	void drawEntity();

	void collision(int key);
	void updateCeil(int key, Chunk*& chunk);
private:
	Field field;
	sf::Font font;
	sf::Text message, seconds;
	std::pair<int, int> textPos = { 145,425 };
	const int sizeText = 24;
	const int sizeMap = 10;
	const int size = 32;//size of tileMap
	sf::Clock clock;
	sf::Time timer;
	enum States
	{
		running,
		lose,
		win
	};
	int state = States::running;
	const int bombs = 10;
	int flags = 0;
	int scores = 0;
};
