#include "map.h"

Field::Field() : gen(rand()),dist(1,10),chunks(12, std::vector<Chunk>())
{
	if (!TileMapTexture.loadFromFile(Dir + nameTileMap))
	{
		std::cerr << "Failt load file\n";
		sf::Image redBox;
		redBox.create(800, 600, sf::Color::Red);
		TileMapTexture.loadFromImage(redBox);
	}
	chunks[0].resize(sizeMap + 2);
	chunks[sizeMap+1].resize(sizeMap + 2);
	for (size_t i = 1; i <= sizeMap; i++)
	{
		chunks[i].resize(sizeMap + 2);
		for (size_t j = 1; j <= sizeMap; j++)
		{
			auto&& it = chunks[i][j];
			sf::Sprite tmp(TileMapTexture, sf::IntRect(Type::close * size, 0, size, size));
			tmp.setPosition(i * size, j * size);
			it.setSprite(tmp);			
			it.logic = Type::empty;
			it.draws = Type::close;
		}
	}

	for (size_t i = 0; i <= bombs; i++)
	{
		int x = dist(gen), y = dist(gen);
		auto&& it = chunks[x][y];
		it.logic = Type::bomb;

		for (int dx = -1; dx < 2; dx++)
		{
			for (int dy = -1; dy < 2; dy++)
			{
				auto w = x + dx, z = y + dy;
				if (dx != 0 || dy != 0)
					if (chunks[w][z].logic != 9)
						chunks[w][z].logic += 1;
			}
		}
	}
	
	{
		for (size_t i = 1; i <= sizeMap; i++) {
			for (size_t j = 1; j <= sizeMap; j++) {
				std::cout << chunks[j][i].logic << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

}

Chunk* Field::contains(const sf::Vector2f& pos)
{
	for (size_t i = 1; i <= sizeMap; i++) {
		for (size_t j = 1; j <= sizeMap; j++) {
			if (chunks[i][j].getSprite().getGlobalBounds().contains(pos)) {
				return &chunks[i][j];
			}
		}
	}
	return nullptr;
}

void Field::switchRect(Chunk& chunk,int start)
{
	chunk.setRect(sf::IntRect(start * size, 0, size, size));
}

std::vector<std::vector<Chunk>>& Field::getField()
{
	return chunks;
}


