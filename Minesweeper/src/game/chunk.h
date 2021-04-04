#include <SFML/Graphics.hpp>

#include <functional>
//#include <memory>

class Chunk
{
public:
	Chunk();
	std::reference_wrapper<sf::Sprite> getSprite(); //ref
	void setRect(sf::IntRect);
	int logic;
	int draws;
	~Chunk();
private:
	sf::Sprite chunk;
	sf::Texture* texture;
};

