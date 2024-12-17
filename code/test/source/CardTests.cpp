#define CATCH_CONFIG_MAIN
#include "Card.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Card Construction") {
    // Test default constructor
    // Card card1;
    // REQUIRE(card1.getRank() >= 1 && card1.getRank() < 14);
    // REQUIRE(card1.getSuit() >= 0 && card1.getSuit() < 4);

    // Test constructor with parameters
    Card card2(10, HEARTS);
    REQUIRE(card2.getRank() == 10);
    REQUIRE(card2.getSuit() == HEARTS);

    // Test copy constructor
    Card card3(card2);
    REQUIRE(card3.getRank() == 10);
    REQUIRE(card3.getSuit() == HEARTS);
}

TEST_CASE("Card Comparison") {
    Card card1(10, HEARTS);
    Card card2(10, HEARTS);
    Card card3(11, HEARTS);
    Card card4(10, CLUBS);

    REQUIRE(card1 == card2);
    REQUIRE(card1 <= card2);
    REQUIRE(card1 < card3);
    REQUIRE(card1 <= card3);

    REQUIRE_THROWS_AS(card1 < card4, std::invalid_argument);
    REQUIRE_THROWS_AS(card1 == card4, std::invalid_argument);
}

TEST_CASE("Card Output") {
    Card card1(10, HEARTS);
    std::stringstream ss;
    ss << card1;
    REQUIRE(ss.str() == "J♥");

    Card card2(13, SPIDES);
    ss.str(""); //clear stream
    ss << card2;
    REQUIRE(ss.str() == "A♠");

    Card card3(12, CLUBS);
    ss.str(""); //clear stream
    ss << card3;
    REQUIRE(ss.str() == "K♣");

    Card card4(11, DIAMOND);
    ss.str(""); //clear stream
    ss << card4;
    REQUIRE(ss.str() == "Q♦");
}

TEST_CASE("Card Input") {
    Card card;
    std::stringstream ss("10 2"); // 10 of Hearts
    ss >> card;
    REQUIRE(card.getRank() == 10);
    REQUIRE(card.getSuit() == HEARTS);

    std::stringstream ss2("1 1"); // Ace of Diamonds
    ss2 >> card;
    REQUIRE(card.getRank() == 1);
    REQUIRE(card.getSuit() == DIAMOND);

    std::stringstream ss3("14 1"); //invalid rank
    REQUIRE_THROWS_AS(ss3 >> card, std::invalid_argument);

    std::stringstream ss4("1 5"); //invalid suit
    REQUIRE_THROWS_AS(ss4 >> card, std::invalid_argument);
}

TEST_CASE("Card Setters and Getters") {
    Card card;
    card.setRank(5);
    card.setSuit(CLUBS);
    REQUIRE(card.getRank() == 5);
    REQUIRE(card.getSuit() == CLUBS);
}

TEST_CASE("Card getSizeForSort"){
    Card card1(10, HEARTS);
    REQUIRE(card1.getSizeForSort() == 10);
    Card card2(1, DIAMOND);
    REQUIRE(card2.getSizeForSort() == 14);
    Card card3(13, CLUBS);
    REQUIRE(card3.getSizeForSort() == 39);
}