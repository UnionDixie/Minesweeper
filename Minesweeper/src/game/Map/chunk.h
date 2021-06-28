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
	int logic;
	int draws;
private:
	sf::Sprite chunk;
};

