#include "chunk.h"

Chunk::Chunk()  
{
}

std::reference_wrapper<sf::Sprite> Chunk::getSprite()
{
	return std::reference_wrapper<sf::Sprite>(chunk);
}

void Chunk::setRect(sf::IntRect rect)
{
	chunk.setTextureRect(rect);
}

Chunk::~Chunk()
{
}
