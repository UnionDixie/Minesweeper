#include "chunk.h"


void Chunk::setSprite(sf::Sprite sprite)
{
	chunk = sprite;
}

sf::Sprite& Chunk::getSprite()
{
	return chunk;
}

void Chunk::setRect(sf::IntRect rect)
{
	chunk.setTextureRect(rect);
}

