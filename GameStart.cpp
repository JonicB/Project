#include "Game.hpp"

void StartGame(sf::RenderWindow& window, sf::Font& font) {
/* Начальное окно игры.
   window - окно программы.
   font - шрифт, используемый в программе.
   Описывает начальное окно и отслеживает события:
   - закрытие окна - программа прекращает работу
   - нажатие пробела - запускает основную часть игры
*/
	sf::RectangleShape Background(sf::Vector2f(800.f, 600.f));
	Background.setFillColor(sf::Color(8, 125, 231));

	sf::Text PlayText, PressText;
	PlayText.setFont(font);                           PressText.setFont(font);
	PlayText.setString("let's play!");                PressText.setString("press space");
	PlayText.setFillColor(sf::Color(7, 19, 213));     PressText.setFillColor(sf::Color(7, 19, 213));
	PlayText.setCharacterSize(100);                   PressText.setCharacterSize(50);
	PlayText.setPosition(sf::Vector2f(200.f, 200.f)); PressText.setPosition(sf::Vector2f(250.f, 330.f));

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
					GameJump(window, font);
					return;
				}
				break;
			default:
				break;
			}
		}

		i++;
		if (i > 800) i = 0;

		window.clear();
		window.draw(Background);
		window.draw(PlayText);
		if (i < 400) window.draw(PressText);
		window.display();
	}
	return;
}
