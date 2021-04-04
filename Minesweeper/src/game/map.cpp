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
			auto&& sprite = it.getSprite().get();
			sprite.setTexture(TileMapTexture);
			it.setRect(sf::IntRect(Type::close * size, 0, size, size));
			sprite.setPosition(i * size + size, j * size + size);
			it.logic = Type::empty;
			it.draws = Type::close;
		}
	}

	for (size_t i = 0; i <= bombs; i++)
	{
		int x = dist(gen), y = dist(gen);
		auto&& it = chunks[x][y];
		it.logic = Type::bomb;
	}

	for (size_t i = 1; i <= sizeMap; i++)
	{
		for (size_t j = 1; j <= sizeMap; j++)
		{
			auto&& it = chunks[i][j];
			int cnt = 0;
			if (it.logic == Type::bomb) {
				continue;
			}
			if (auto&& val = chunks[i - 1][j].logic; val == Type::bomb)
				++cnt;//up
			if (auto&& val = chunks[i + 1][j].logic; val == Type::bomb)
				++cnt;//down
			if (auto&& val = chunks[i][j + 1].logic; val == Type::bomb)
				++cnt;//right
			if (auto&& val = chunks[i][j - 1].logic; val == Type::bomb)
				++cnt;//left
			if (auto&& val = chunks[i + 1][j + 1].logic; val == Type::bomb)
				++cnt;//diagn
			if (auto&& val = chunks[i - 1][j + 1].logic; val == Type::bomb)
				++cnt;
			if (auto&& val = chunks[i + 1][j - 1].logic; val == Type::bomb)
				++cnt;
			if (auto&& val = chunks[i - 1][j - 1].logic; val == Type::bomb)
				++cnt;
			it.logic = cnt;//0..8
		}
	}
}

std::pair<bool,Chunk*> Field::contains(const sf::Vector2f& pos)
{
	for (size_t i = 1; i <= sizeMap; i++) {
		for (size_t j = 1; j <= sizeMap; j++) {
			if (chunks[i][j].getSprite().get().getGlobalBounds().contains(pos)) {
				return std::make_pair(true, &chunks[i][j]);
			}
		}
	}
	return std::make_pair(0, new Chunk());
}

void Field::switchRect(Chunk& chunk,const int start)
{
	chunk.setRect(sf::IntRect(start * size, 0, size, size));
}

std::vector<std::vector<Chunk>>& Field::getField()
{
	return chunks;
}

Field::~Field()
{
}
