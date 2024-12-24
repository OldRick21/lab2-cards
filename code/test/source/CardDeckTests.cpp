#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../src/card-deck/CardDeck.h"

TEST_CASE("CardDeck Constructor with count") {
    CardDeck deck(10);
    REQUIRE(deck.getCount() == 10);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck Constructor with count greater than 52") {
    CardDeck deck(60);
    REQUIRE(deck.getCount() == 52);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 52; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck Constructor with count less than 1") {
    CardDeck deck(0);
    REQUIRE(deck.getCount() == 0);
    REQUIRE(deck.getCards() == nullptr);
}

TEST_CASE("CardDeck Default Constructor") {
    CardDeck deck;
    REQUIRE(deck.getCount() == 52);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 52; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck Copy Constructor") {
    CardDeck deck1(10);
    CardDeck deck2(deck1);
    REQUIRE(deck2.getCount() == 10);
    REQUIRE(deck2.getCards() != nullptr);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(*deck1.getCardByIndex(i) == *deck2.getCardByIndex(i));
    }
}

TEST_CASE("CardDeck Move Constructor") {
    CardDeck deck1(10);
    CardDeck deck2(std::move(deck1));
    REQUIRE(deck2.getCount() == 10);
    REQUIRE(deck2.getCards() != nullptr);
    REQUIRE(deck1.getCount() == 0);
    REQUIRE(deck1.getCards() == nullptr);
}

TEST_CASE("CardDeck Destructor") {
    CardDeck* deck = new CardDeck(10);
    delete deck;
    REQUIRE(true); 
}

TEST_CASE("CardDeck getCards and setCards methods") {
    CardDeck deck(10);
    Card** cards = deck.getCards();
    REQUIRE(cards != nullptr);
    deck.setCards(cards, false); 
    REQUIRE(deck.getCards() == cards);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck getCount and setCount methods") {
    CardDeck deck(10);
    REQUIRE(deck.getCount() == 10);
    deck.setCount(5);
    REQUIRE(deck.getCount() == 5);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 5; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck addRandomCard method") {
    CardDeck deck(10);
    deck.addRandomCard();
    REQUIRE(deck.getCount() == 11);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 11; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck getCardByIndex method") {
    CardDeck deck(10);
    REQUIRE_THROWS_AS(deck.getCardByIndex(10), std::out_of_range);
    REQUIRE_NOTHROW(deck.getCardByIndex(0));
    REQUIRE(deck.getCardByIndex(0) != nullptr);
}

TEST_CASE("CardDeck deleteCardByIndex method") {
    CardDeck deck(10);
    REQUIRE_THROWS_AS(deck.deleteCardByIndex(10), std::out_of_range);
    deck.deleteCardByIndex(0);
    REQUIRE(deck.getCount() == 9);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 9; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck sortCards method") {
    CardDeck deck(10);
    deck.sortCards(false);
    for (int i = 0; i < 9; ++i) {
        REQUIRE(deck.getCardByIndex(i)->getSizeForSort() <= deck.getCardByIndex(i + 1)->getSizeForSort());
    }
    deck.sortCards(true);
    for (int i = 0; i < 9; ++i) {
        REQUIRE(deck.getCardByIndex(i)->getSizeForSort() >= deck.getCardByIndex(i + 1)->getSizeForSort());
    }
}

TEST_CASE("CardDeck shuffle method") {
    CardDeck deck(10);
    CardDeck originalDeck(deck);
    deck.shuffle();
    bool shuffled = false;
    for (int i = 0; i < 10; ++i) {
        if (*deck.getCardByIndex(i) != *originalDeck.getCardByIndex(i)) {
            shuffled = true;
            break;
        }
    }
    REQUIRE(shuffled == true);
}

TEST_CASE("CardDeck operator+") {
    CardDeck deck1(10);
    CardDeck deck2(5);
    CardDeck newDeck = deck1 + deck2;
    REQUIRE(newDeck.getCount() == 15);
    REQUIRE(newDeck.getCards() != nullptr);
    for (int i = 0; i < 15; ++i) {
        REQUIRE(newDeck.getCardByIndex(i) != nullptr);
    }
}

TEST_CASE("CardDeck operator= (move assignment)") {
    CardDeck deck1(10);
    CardDeck deck2(5);
    deck2 = std::move(deck1);
    REQUIRE(deck2.getCount() == 10);
    REQUIRE(deck2.getCards() != nullptr);
    REQUIRE(deck1.getCount() == 0);
    REQUIRE(deck1.getCards() == nullptr);
}

TEST_CASE("CardDeck operator= (copy assignment)") {
    CardDeck deck1(10);
    CardDeck deck2(5);
    deck2 = deck1;
    REQUIRE(deck2.getCount() == 10);
    REQUIRE(deck2.getCards() != nullptr);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(*deck1.getCardByIndex(i) == *deck2.getCardByIndex(i));
    }
}

TEST_CASE("CardDeck suitFinder method") {
    CardDeck deck(52);
    CardDeck heartsDeck = deck.suitFinder(static_cast<int>(Suit::HEARTS));
    REQUIRE(heartsDeck.getCount() == 13);
    REQUIRE(heartsDeck.getCards() != nullptr);
    for (int i = 0; i < 13; ++i) {
        REQUIRE(heartsDeck.getCardByIndex(i)->getSuit() == Suit::HEARTS);
    }
}

TEST_CASE("CardDeck is_twink method") {
    CardDeck deck(52);
    REQUIRE(deck.is_twink() == false);
}

TEST_CASE("CardDeck cardsDestroy method") {
    CardDeck deck(10);
    deck.cardsDestroy();
    REQUIRE(deck.getCount() == 0);
    REQUIRE(deck.getCards() == nullptr);
}

TEST_CASE("CardDeck operator<<2") {
    CardDeck deck(10);
    std::ostringstream oss;
    oss << deck;
    REQUIRE(oss.str() == "10");
}

TEST_CASE("CardDeck operator>>2") {
    CardDeck deck;
    std::istringstream iss("5");
    iss >> deck;
    REQUIRE(deck.getCount() == 5);
    REQUIRE(deck.getCards() != nullptr);
    for (int i = 0; i < 5; ++i) {
        REQUIRE(deck.getCardByIndex(i) != nullptr);
    }
}
