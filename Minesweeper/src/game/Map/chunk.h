#include <SFML/Graphics.hpp>

class Chunk
{
public:
	Chunk() = default;
	void setSprite(sf::Sprite sprite); 
	sf::Sprite& getSprite(); 
	void setRect(sf::IntRect);
	~Chunk() = default;
private:
	const int closeChunk = 10;
	const int emptyCeil = 0;
public:
	int whatIs = emptyCeil;
	int whatDraw = closeChunk;
	std::pair<int, int> position = {-1,-1};
private:
	sf::Sprite chunk;
};

