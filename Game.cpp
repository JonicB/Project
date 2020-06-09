#include "Game.hpp"

std::pair<float,float> Shift(std::pair<float,float> x, sf::Time time, float speed) {
/* Возвращает x координаты элементов игры, изображающих землю.
   x - начальные координаты.
   time - время игры.
   speed - скорость движения.
*/
	float z = time.asMicroseconds() * speed;
	x.first -= (int) z % 1600;
	x.second -= (int) z % 1600;
	if (x.first <= -800) x.first += 1600;
	if (x.second <= -800) x.second += 1600;
	return x;
}

std::pair<float, float> Jump(std::pair<float, float> y, sf::Time time, bool &jump) {
/* Возвращает y координату игрока при прыжке.
   y - начальные координаты элементов игрока.
   time - время прыжка.
   jump - переменная, показывающая, продолжается ли прыжок.
   При завершении прыжка возвращает начальные координаты и показывает, что прыжок завершился.
*/
	float speed = 0.95;
	float s = 0;
	s = speed * time.asMilliseconds() - time.asMilliseconds() * time.asMilliseconds() * 0.0009;
 	if (s < 0) {
		jump = false;
		return y;
	}
	y.first -= (int)s;
	y.second -= (int)s;
	return y;
}

float Blocks(float &b, sf::Time time, float speed, bool &block) {
/* Возвращает x координату блоков.
   b - координата блока при его появлении.
   time - время движения блока.
   speed - скорость движения.
   block - переменная, показывающая надо или нет перезапускать таймер блока.
   Когда блок выходит за пределы окна с левой стороны, задает координату появления блока с другой стороны и показывает необходимость перезапуска таймера.
*/
	float z = time.asMicroseconds() * speed;
	float x = b - (int)z % 1625;
	if (x < -25) {
		x = rand() % 800 + 800;
		b = x;
		block = true;
	}
	return x;
}

std::string Score(sf::Time time) {
/* Возвращает строку, показывающую счет в игре.
   time - время игры.
*/
	int s = time.asMilliseconds() / 100;
	return "Your score: " + std::to_string(s);
}

void GameJump(sf::RenderWindow& window, sf::Font& font) {
/* Основная часть игры.
   window - окно программы.
   font - шрифт, используемый в программе.
   Описывает игрока, элементы игры (фон, земля, блоки, счет, текст-подсказка) и их перемещения.
   При закрытиии окна прекращает работу.
   При нажатии на пробел описывает прыжок игрока.
   При врезании игрока в блок запускает конец игры.
*/
	window.setKeyRepeatEnabled(true);
	sf::RectangleShape Background(sf::Vector2f(800.f, 600.f)), Ground1(sf::Vector2f(802.f, 200.f)), Ground2(sf::Vector2f(802.f, 200.f));
	Background.setFillColor(sf::Color(8, 125, 231));
	Ground1.setFillColor(sf::Color(7, 19, 213));     Ground2.setFillColor(sf::Color(11, 20, 152));
	Ground1.setPosition(sf::Vector2f(0.f, 400.f));   Ground2.setPosition(sf::Vector2f(799.f, 400.f));

	sf::Text HelpText, ScoreText;
	HelpText.setFont(font);                              ScoreText.setFont(font);
	HelpText.setString("Press space to jump");           ScoreText.setString("Your score: 0");
	HelpText.setFillColor(sf::Color(7, 19, 213));        ScoreText.setFillColor(sf::Color(7, 19, 213));
	HelpText.setCharacterSize(50);                       ScoreText.setCharacterSize(30);
	HelpText.setPosition(sf::Vector2f(200.f, 200.f));    ScoreText.setPosition(sf::Vector2f(500.f, 75.f));

	sf::RectangleShape Player1(sf::Vector2f(50.f, 50.f));
	sf::CircleShape Player2(20.f);
	Player1.setFillColor(sf::Color(11, 20, 152));    Player2.setFillColor(sf::Color(172,10,245));
	Player1.setPosition(sf::Vector2f(50.f, 350.f));  Player2.setPosition(sf::Vector2f(55.f, 355.f));

	sf::RectangleShape Block1(sf::Vector2f(25.f, 150.f)),Block2(sf::Vector2f(25.f,150.f));
	Block1.setFillColor(sf::Color(7, 19, 213));       Block2.setFillColor(sf::Color(7, 19, 213));
	Block1.setPosition(sf::Vector2f(1100.f, 250.f));  Block2.setPosition(sf::Vector2f(1600.f, 250.f));

	std::pair<float, float> x0(0, 800);
	std::pair<float, float> y0(350, 355);
	std::pair<float, float> b0(1100, 1600);
	float speed = 0.0004;
	bool jump = false, help = true, block1 = false, block2 = false;
	sf::Clock clock, clockJump, clockBlock1, clockBlock2;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if ((event.key.code == sf::Keyboard::Space) and (!jump)){ 
						jump = true; 
						clockJump.restart(); 
					}
					break;
				default:
					break;
			}
		}

		sf::FloatRect PlayerBox = Player1.getGlobalBounds();
		sf::FloatRect BlockBox1 = Block1.getGlobalBounds(), BlockBox2 = Block2.getGlobalBounds();

		if (PlayerBox.intersects(BlockBox1) or PlayerBox.intersects(BlockBox2)) {
			GameOver(window, font, ScoreText);
			return;
		}

		if (clock.getElapsedTime() > sf::milliseconds(3000)) help = false;
		ScoreText.setString(Score(clock.getElapsedTime()));

		if (jump) {
			std::pair<float, float> y = Jump(y0, clockJump.getElapsedTime(),jump);
			Player1.setPosition(sf::Vector2f(50.f, y.first));
			Player2.setPosition(sf::Vector2f(55.f, y.second));
		}

		std::pair<float, float> b;
		b.first = Blocks(b0.first, clockBlock1.getElapsedTime(), speed, block1);
		b.second = Blocks(b0.second, clockBlock2.getElapsedTime(), speed, block2);
		Block1.setPosition(sf::Vector2f(b.first, 250.f));
		Block2.setPosition(sf::Vector2f(b.second, 250.f));
		if (block1) {
			clockBlock1.restart();
			block1 = false;
		}
		if (block2) {
			clockBlock1.restart();
			block2 = false;
		}

		std::pair<float,float> x = Shift(x0,clock.getElapsedTime(),speed);
		Ground1.setPosition(sf::Vector2f(x.first, 400.f));
		Ground2.setPosition(sf::Vector2f(x.second, 400.f));

		window.clear();
		window.draw(Background);
		window.draw(Ground1); 
		window.draw(Ground2);
		window.draw(Block1);
		window.draw(Block2);
		window.draw(Player1);
		window.draw(Player2);
		if (help) window.draw(HelpText);
		window.draw(ScoreText);
		window.display();
	}

}

