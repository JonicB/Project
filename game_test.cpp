#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Game.hpp"


TEST_CASE("Shift_int_distance"){
    std::pair <float,float> x0(0,100);
    std::pair <float,float> result = Shift(x0,sf::microseconds(2000),0.1);
    REQUIRE(result.first == -200);
    REQUIRE(result.second == -100);
}

TEST_CASE("Shift_float_distance"){
    std::pair <float,float> x0(0,-100);
    std::pair <float,float> result = Shift(x0,sf::microseconds(255),0.03);
    REQUIRE(result.first == -7);
    REQUIRE(result.second == -107);
}

TEST_CASE("Shift_transition"){
    std::pair <float,float> x0(0,100);
    std::pair <float,float> result = Shift(x0,sf::microseconds(1000),1);
    REQUIRE(result.first == 600);
    REQUIRE(result.second == 700);
}

TEST_CASE("Shift_big_distance"){
    std::pair <float,float> x0(0,100);
    std::pair <float,float> result = Shift(x0,sf::microseconds(100000),1);
    REQUIRE(result.first == 800);
    REQUIRE(result.second == -700);
}

TEST_CASE("Jump_height"){
    std::pair <float,float> y0(0,0);
    bool test = true;
    std::pair <float,float> result = Jump(y0,sf::milliseconds(100),test);
    REQUIRE(result.first == -86);
    REQUIRE(result.second == -86);
    REQUIRE(test == true);
}

TEST_CASE("Jump_landing"){
    std::pair <float,float> y0(0,0);
    bool test = true;
    std::pair<float,float> result = Jump(y0,sf::milliseconds(10000),test);
    REQUIRE(result.first == 0);
    REQUIRE(result.second == 0);
    REQUIRE(test == false);
}

TEST_CASE("Blocks_little_distance"){
    float b = 1000;
    bool test = false;
    float result = Blocks(b,sf::microseconds(100),10,test);
    REQUIRE(result == 0);
    REQUIRE(b == 1000);
    REQUIRE(test == false);
}

TEST_CASE("Blocks_transition"){
    float b = 0;
    bool test = false;
    float result = Blocks(b,sf::microseconds(100),1,test);
    REQUIRE(result >= 800);
    REQUIRE(result <= 1600);
    REQUIRE(b == result);
    REQUIRE(test == true);
}

TEST_CASE("Score_some_numbers"){
    std::string result1 = Score(sf::milliseconds(1000));
    std::string result2 = Score(sf::milliseconds(1255));
    REQUIRE(result1 == "Your score: 10");
    REQUIRE(result2 == "Your score: 12");
}