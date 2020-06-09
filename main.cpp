#include "Game.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "CubeJump", sf::Style::Close);
	sf::Font font;
	window.setKeyRepeatEnabled(false);
	font.loadFromFile("RMSSans.otf");
	srand(time(0));
	StartGame(window, font);
	return 0;
}