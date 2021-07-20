#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "Map/map.h"
#include "Loader/DataLoader.h"

class Game
{
public:
	Game();
	void run();
	~Game() = default;
private:
	void update();
	void HandleEvent();
	void drawEntity();
	void collision(int key);
	void updateCeil(int key, Chunk& chunk);
private:
	sf::RenderWindow window;
	Field field;
	sf::Font font;
	sf::Text message, seconds;
	std::pair<int, int> textPos = { 145,400 };
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
	int bombs;
	int flags = 0;
	int scores = 0;
};
