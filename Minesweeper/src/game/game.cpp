#include "Game.h"

Game::Game() : gen(rand()),
			   sizeMap(10), dist(1,10),
			   window(sf::VideoMode(400, 500), L"Сапер xD!")
{
	//window.setVerticalSyncEnabled(true);//vSync
	if (!TileMapTexture.loadFromFile(Dir + nameTileMap))
	{
		std::cerr << "Failt load file\n";
		sf::Image redBox;
		redBox.create(200, 200, sf::Color::Red);
		TileMapTexture.loadFromImage(redBox);
	}
	TileMap.setTexture(TileMapTexture);
	font.loadFromFile(Dir + nameFont);

	text.setFont(font);
	//text.setString("");
	text.setPosition(textPos.first, textPos.second);
	text.setCharacterSize(sizeText);
	text.setFillColor(sf::Color::Red);

	for (size_t i = 0; i < bomb; i++)
	{
		MapValue[dist(gen)][dist(gen)] = 9;
	}

	for (size_t i = 1; i <= sizeMap; i++) {
		for (size_t j = 1; j <= sizeMap; j++)
		{
			MapDraw[i][j] = 10;//all square are close
			if (!MapValue[i][j]) {
				MapValue[i][j] = 0;//empty
			}
		}
	}
	//create nums around bomb
	for (size_t i = 1; i <= sizeMap; i++) {
		for (size_t j = 1; j <= sizeMap; j++)
		{
			int cnt = 0;//Счётчик бомб в округе
			if (MapValue[i][j] == 9) {//if bomb
				continue;
			}
			if (MapValue[i - 1][j] == 9)
				++cnt;//up
			if (MapValue[i + 1][j] == 9)
				++cnt;//down
			if (MapValue[i][j + 1] == 9)
				++cnt;//right
			if (MapValue[i][j - 1] == 9)
				++cnt;//left
			if (MapValue[i + 1][j + 1] == 9)
				++cnt;//diagn
			if (MapValue[i - 1][j + 1] == 9)
				++cnt;
			if (MapValue[i + 1][j - 1] == 9)
				++cnt;
			if (MapValue[i - 1][j - 1] == 9)
				++cnt;
			MapValue[i][j] = cnt;//0..8
		}
	}

	//log mapValue in console
	{
		std::cout << bomb << '\n';
		for (size_t j = 1; j <= sizeMap; j++) {
			for (size_t i = 1; i <= sizeMap; i++)
			{
				std::cout << MapValue[i][j];
			}
			std::cout << '\n';
		}
	}

}

void Game::run()
{
	auto contains = [&](sf::Vector2f pos) -> std::optional<std::pair<int, int>> {
		for (size_t i = 1; i <= sizeMap; i++) {
			for (size_t j = 1; j <= sizeMap; j++)
			{
				sf::FloatRect sq(i*size, j * size, size, size);
				if (sq.contains(pos)) {
					return std::make_pair(i, j);
				}
			}
		}
		return std::nullopt;
	};



	while (window.isOpen())
	{
		auto mousePos = static_cast<sf::Vector2f> (sf::Mouse::getPosition(window));

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {


				if (event.key.code == sf::Mouse::Left) {
					if (auto xy = contains(mousePos); xy != std::nullopt) {
						auto [x, y] = *xy;
						MapDraw[x][y] = MapValue[x][y];//open tile
						if (MapValue[x][y] == 9) { //if bomb - lose
							text.setString("You Lose");
							state = 1;
						}
					}
				}
				else if (event.key.code == sf::Mouse::Right) {// Если была нажата правая кнопка мыши, то
					if (auto xy = contains(mousePos); xy != std::nullopt) {
						auto [x, y] = *xy;

						if (MapDraw[x][y] == 11)
							MapDraw[x][y] = 10;// off flag
						else
							MapDraw[x][y] = 11;//on flag	

						if (MapValue[x][y] == 9)
							flags++;// if flag on bomb score++
						if (flags == bomb)
							state = 2;//win
					}
				}
			}
		}
		window.clear(sf::Color::White);

		for (size_t i = 1; i <= 10; i++) {
			for (size_t j = 1; j <= 10; j++) {  //11*32
				TileMap.setTextureRect(sf::IntRect(MapDraw[i][j] * size, 0, size, size));//10*32 x, y =0 
				TileMap.setPosition(i * size, j * size);//
				window.draw(TileMap);
			}
		}
		if (state > 0)
			window.draw(text);//win or lose
		window.display();
	}
}

Game::~Game()
{
}