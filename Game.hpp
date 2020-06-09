#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


extern void StartGame(sf::RenderWindow& window, sf::Font& font);

extern void GameJump(sf::RenderWindow& window, sf::Font& font);

extern void GameOver(sf::RenderWindow& window, sf::Font& font, sf::Text ScoreText);

extern std::pair<float,float> Shift(std::pair<float,float> x, sf::Time time, float speed);

extern std::pair<float, float> Jump(std::pair<float, float> y, sf::Time time, bool &jump);

extern float Blocks(float &b, sf::Time time, float speed, bool &block);

extern std::string Score(sf::Time time);