#include "Game.hpp"

void GameOver(sf::RenderWindow &window, sf::Font &font, sf::Text ScoreText) {
/* Конец игры.
   window - окно программы.
   font - шрифт, использующийся в программе.
   ScoreText - элемент игры, показывающий счет.
   Описывает окно программы и отслеживает события:
   - закрытие окна - прекращает работу программы.
   - нажатие на пробел - запускает основную часть игры.
*/
	window.setKeyRepeatEnabled(false);
	sf::RectangleShape Background(sf::Vector2f(800.f, 600.f));
	Background.setFillColor(sf::Color(8, 125, 231));

	sf::Text GoodText, PressText;
	GoodText.setFont(font);                             PressText.setFont(font);
	GoodText.setString("Amazing!");                     PressText.setString("press space to play");
	GoodText.setFillColor(sf::Color(7, 19, 213));       PressText.setFillColor(sf::Color(7, 19, 213));
	GoodText.setCharacterSize(100);                     PressText.setCharacterSize(50);
	GoodText.setPosition(sf::Vector2f(230.f, 150.f));   PressText.setPosition(sf::Vector2f(210.f, 350.f));
	ScoreText.setCharacterSize(100);
	ScoreText.setPosition(100.f, 250.f);

	int i = 0;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					GameJump(window,font);
					return;
				}
			default:
				break;
			}
		}

		i++;
		if (i > 800) i = 0;

		window.clear();
		window.draw(Background);
		window.draw(GoodText);
		window.draw(ScoreText);
		if (i < 400) window.draw(PressText);
		window.display();
	}
}
