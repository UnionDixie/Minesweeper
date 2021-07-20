#include "map.h"

Field::Field(int bombs, int sizeMap, int size) : 
	bombs(bombs),sizeMap(sizeMap),size(size),
	gen(rand()),dist(1, sizeMap),chunks(sizeMap + 2, std::vector<Chunk>())
{

}


void Field::generate()
{
	chunks.clear();
	chunks.resize(sizeMap + 2);
	chunks[0].resize(sizeMap + 2);
	chunks[sizeMap + 1].resize(sizeMap + 2);
	for (size_t i = 1; i <= sizeMap; i++)
	{
		chunks[i].resize(sizeMap + 2);
		for (size_t j = 1; j <= sizeMap; j++)
		{
			sf::Sprite tmp(TileMapTexture, sf::IntRect(Type::close * size, 0, size, size));
			tmp.setPosition(i * size, j * size);
			chunks[i][j].setSprite(tmp);
			chunks[i][j].position = { i,j };
		}
	}

	for (size_t i = 0; i <= bombs; i++)
	{
		int x = dist(gen), y = dist(gen);
		chunks[x][y].whatIs = Type::bomb;
		for (int dx = -1; dx < 2; dx++)
		{
			for (int dy = -1; dy < 2; dy++)
			{
				auto w = x + dx, z = y + dy;
				if ((dx != 0 || dy != 0) && chunks[w][z].whatIs != Type::bomb)
					chunks[w][z].whatIs += 1;
			}
		}
	}


	for (size_t i = 1; i <= sizeMap; i++)
	{
		for (size_t j = 1; j <= sizeMap; j++)
		{
			std::cout << chunks[j][i].whatIs << " ";
		}
		std::cout << "\n";
	}

}

void Field::setTexture(const sf::Texture* texture)
{
	TileMapTexture = *texture;
}

void Field::Open(Chunk& chunk)
{
	if (chunk.whatDraw == Type::empty)
		return;
	if (chunk.whatIs == Type::empty) {
		chunk.whatDraw = Type::empty;
		for (int dx = -1; dx < 2; dx++)
		{
			for (int dy = -1; dy < 2; dy++)
			{
				auto [x, y] = chunk.position;
				auto w = x + dx, z = y + dy;
				if (w >= 1 && z >= 1 && w <= sizeMap && z <= sizeMap) {
					if (chunk.whatIs == 0) {
						chunks[w][z].setRect(sf::IntRect(chunks[w][z].whatIs * 32, 0, 32, 32));
						Open(chunks[w][z]);
					}
				}
			}
		}
	}
}

Chunk& Field::contains(const sf::Vector2f& pos)
{
	for (size_t i = 1; i <= sizeMap; i++) {
		for (size_t j = 1; j <= sizeMap; j++) {
			if (chunks[i][j].getSprite().getGlobalBounds().contains(pos)) {
				return chunks[i][j];
			}
		}
	}
	return chunks[0][0];
}

void Field::switchRect(Chunk& chunk,int start)
{
	chunk.setRect(sf::IntRect(start * size, 0, size, size));
}

std::vector<std::vector<Chunk>>& Field::getField()
{
	return chunks;
}




