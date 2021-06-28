#include <SFML/Graphics.hpp>

class Chunk
{
public:
	Chunk() = default;
	void setSprite(sf::Sprite sprite); 
	sf::Sprite& getSprite(); 
	void setRect(sf::IntRect);
	~Chunk() = default;
public:
	int logic = 0;
	int draws = 10;
	std::pair<int, int> pos = {-1,-1};
private:
	sf::Sprite chunk;
};

