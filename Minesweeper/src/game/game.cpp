#include "Game.h"

#include "Loader/DataLoader.h"


Game::Game() : window(sf::VideoMode(400, 500), "Minesweeper xD!"), field()
{
	DataLoader loader("Data/");

	if (auto it = loader.getFont("arial"); it != nullptr) {
		font = *loader.getFont("arial");
	}
	
	sf::Text tmp("", font, sizeText);

	message = tmp;
	message.setPosition(textPos.first, textPos.second);
	message.setFillColor(sf::Color::Red);
		
	const int offset = 25;
	seconds = std::move(tmp);
	seconds.setPosition((size * 10 + offset) / 2, size * 10 + offset * 2);
	seconds.setFillColor(sf::Color::Red);

}

void Game::HandleEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {	
			if (event.key.code == sf::Mouse::Left || event.key.code == sf::Mouse::Right) {
				collision(event.key.code);
			}
		}
	}
}

void Game::collision(int key)
{
	auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	if (auto chunk = field.contains(mousePos); chunk != nullptr) {
		updateCeil(key, chunk);
	}
}

void Game::updateCeil(int key,Chunk*& chunk)
{
	if (key == sf::Mouse::Left) {
			field.switchRect(*chunk, chunk->logic);
			if (chunk->logic == Field::bomb) {
				message.setString("You Lose");
				state = States::lose;
			}
			chunk->draws = chunk->logic;
	}
	else if (key == sf::Mouse::Right) {
		if (chunk->draws == Field::flag) {
			flags--;
			if (chunk->logic == Field::bomb) {
				scores--;
			}
			chunk->draws = Field::close;
			chunk->setRect(sf::IntRect(Field::close * 32, 0, 32, 32));
		}
		else if (flags<=bombs && chunk->draws == Field::close) {
			chunk->draws = Field::flag;
			chunk->setRect(sf::IntRect(Field::flag * 32, 0, 32, 32));
			if (chunk->logic == Field::bomb) {
				scores++;
			}
			flags++;
		}
		if (scores == bombs) {
			state = States::win;
		}
	}
}

void Game::update()
{
	if (state == States::running) {
		timer = clock.getElapsedTime();
		seconds.setString(std::to_string(static_cast<int>(timer.asSeconds())));
	}
}

void Game::drawEntity()
{
	auto map = field.getField();
	for (auto&& vec : map) {
		for (auto&& it : vec) {
			window.draw(it.getSprite());
		}
	}
	if (state)
		window.draw(message);//win or lose
	window.draw(seconds);
}

void Game::run()
{
	while (window.isOpen())
	{
		//if (state == States::running) {
			update();
			HandleEvent();
			window.clear(sf::Color::White);
			drawEntity();
			window.display();
		//}
		//else {
		//	//sf::sleep(sf::Time(sf::seconds(5)));
		//	HandleEvent();
		//	window.clear(sf::Color::White);
		//	window.display();
		//}
	}
}

