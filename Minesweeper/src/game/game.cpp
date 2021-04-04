#include "Game.h"

Game::Game() :window(sf::VideoMode(400, 500), L"Сапер xD!" ,
				     sf::Style::Close | sf::Style::Titlebar), field()
{
	
	font.loadFromFile(Dir + nameFont);
	text.setFont(font);
	text.setPosition(textPos.first, textPos.second);
	text.setCharacterSize(sizeText);
	text.setFillColor(sf::Color::Red);
	sf::Text tmp("",font,18);
	sec = tmp;
	sec.setPosition(size * (sizeMap + 2) / 2, (sizeMap + 2) * size + 25);
	sec.setFillColor(sf::Color::Red);
}

void Game::HandleEvent()
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
				if (auto&& [collision, chunk] = field.contains(mousePos); collision) {
					field.switchRect(*chunk, chunk->logic);
					if (chunk->logic == Field::bomb) {
						text.setString("You Lose");
						state = 1;
					}
				}
			}
			else if (event.key.code == sf::Mouse::Right) {// Если была нажата правая кнопка мыши, то
				if (auto&& [collision, chunk] = field.contains(mousePos); collision) {
					if (chunk->draws == Field::flag) {
						chunk->draws = Field::close;
						chunk->setRect(sf::IntRect(Field::close * 32, 0, 32, 32));
					}
					else {
						chunk->draws = Field::flag;
						chunk->setRect(sf::IntRect(Field::flag * 32, 0, 32, 32));
					}
					if (chunk->logic == Field::bomb) {
						flags++;// if flag on bomb score++
					}
					if (flags == bombs) {
						state = 2;//win
					}
				}
			}
		}
	}
}

void Game::update()
{
	timer = clock.getElapsedTime();
	sec.setString(std::to_string(static_cast<int>(timer.asSeconds())));
}

void Game::drawEntity()
{
	auto&& map = field.getField();
	for (auto&& vec : map) {
		for (auto&& it : vec) {
			window.draw(it.getSprite().get());
		}
	}
	if (state)
		window.draw(text);//win or lose
	window.draw(sec);
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		HandleEvent();
		window.clear(sf::Color::White);
		drawEntity();
		window.display();
	}
}

Game::~Game()
{
}