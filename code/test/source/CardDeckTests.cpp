#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "../../src/card-deck/CardDeck.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Set Crads/Set count2") {
    CardDeck* deck = new CardDeck(0);
    Card** new_deck = new Card *[3];
    deck->setCount(3);    
    deck->setCards(new_deck);
    REQUIRE(deck->getCards());
    REQUIRE(deck->getCount() == 3);
    delete deck;
}

TEST_CASE("Get Crads/Get Count2") {
    CardDeck* deck = new CardDeck(7);
    REQUIRE(deck->getCards());
    REQUIRE(deck->getCount() == 7);
    delete deck;
}

TEST_CASE("CardDeck Constructor - Empty Deck2") {
    CardDeck deck(0);
    REQUIRE(deck.getCount() == 0);
}

TEST_CASE("CardDeck Constructor - Full Deck2") {
    CardDeck deck;
    REQUIRE(deck.getCount() == 52);
    //Проверка наличия всех уникальных карт
}

TEST_CASE("CardDeck Constructor - Partial Deck2") {
    CardDeck deck(26);
    REQUIRE(deck.getCount() == 26);
}

TEST_CASE("CardDeck Copy Constructor2") {
    CardDeck deck1(10);
    CardDeck deck2 = deck1;
    REQUIRE(deck2.getCount() == 10);
    //Проверка содержимого deck2, если возможно.
}

TEST_CASE("CardDeck Move Constructor2") {
    CardDeck deck1(15);
    CardDeck deck2 = std::move(deck1);
    REQUIRE(deck2.getCount() == 15);
    REQUIRE(deck1.getCount() == 0);
}

TEST_CASE("CardDeck Destructor2") {
    //Проверка отсутствия утечек памяти (с помощью Valgrind или аналогичных инструментов)
}

TEST_CASE("CardDeck addRandomCard2") {
    CardDeck deck(5);
    deck.addRandomCard();
    REQUIRE(deck.getCount() == 6);
}

TEST_CASE("CardDeck getCardByIndex2") {
    CardDeck deck;
    REQUIRE(deck.getCardByIndex(0) != nullptr);
    REQUIRE(deck.getCardByIndex(52 -1) != nullptr);
    REQUIRE_THROWS_AS(deck.getCardByIndex(-1), std::out_of_range);
    REQUIRE_THROWS_AS(deck.getCardByIndex(52), std::out_of_range);
}


TEST_CASE("CardDeck deleteCardByIndex2") {
    CardDeck deck(5);
    deck.deleteCardByIndex(2);
    REQUIRE(deck.getCount() == 4);
    REQUIRE_THROWS_AS(deck.deleteCardByIndex(-1), std::out_of_range);
    REQUIRE_THROWS_AS(deck.deleteCardByIndex(5), std::out_of_range);
}

TEST_CASE("CardDeck sortCards2") {
    CardDeck deck(5); // Создайте колоду с несколькими картами
    deck.sortCards(false); // Сортировка по возрастанию
    deck.sortCards(true); // Сортировка по убыванию
    //Добавить проверки на упорядоченность карт после сортировки

}

TEST_CASE("CardDeck shuffle2") {
    CardDeck deck(10);
    CardDeck deck2(deck); //сохраняем копию
    deck.shuffle();
    // Проверить, что карты в deck перепутаны (сложно автоматизировать, можно только проверить, что порядок изменился).
    bool shuffled = false;
    for(int i =0; i<10; ++i){
        if(deck.getCardByIndex(i)->getRank() != deck2.getCardByIndex(i)->getRank() || deck.getCardByIndex(i)->getSuit() != deck2.getCardByIndex(i)->getSuit()){
            shuffled = true;
            break;
        }
    }
    REQUIRE(shuffled);
}

TEST_CASE("CardDeck operator+2") {
    CardDeck deck1(5);
    CardDeck deck2(3);
    CardDeck deck3 = deck1 + deck2;
    REQUIRE(deck3.getCount() == 8);
    // Проверьте содержимое deck3 (это сложно, но желательно)

    // Проверка на 0
    CardDeck deck4(0);
    CardDeck deck5(5);
    CardDeck deck6 = deck4 + deck5;
    REQUIRE(deck6.getCount() == 5);

    //Проверка на пустую колоду
    CardDeck deck7(0);
    CardDeck deck8(0);
    CardDeck deck9 = deck7 + deck8;
    REQUIRE(deck9.getCount() == 0);

}

TEST_CASE("CardDeck operator= (move)2") {
    CardDeck deck1(10);
    CardDeck deck2 = std::move(deck1);
    REQUIRE(deck2.getCount() == 10);
    REQUIRE(deck1.getCount() == 0); // Проверка, что deck1 очищена
}

TEST_CASE("CardDeck operator= (copy)2") {
    CardDeck deck1(7);
    CardDeck deck2 = deck1;
    REQUIRE(deck2.getCount() == 7);
    // Проверка содержимого deck2 (сложно, но желательно)
}

TEST_CASE("CardDeck suitFinder2") {
    CardDeck deck(52); // Полная колода
    CardDeck hearts = deck.suitFinder(0); //Замените на числовое представление масти
    REQUIRE(hearts.getCount() <= 13); // Должно быть не более 13 карт пик
    // Проверка, что hearts содержит только карты пик (сложно автоматизировать)
    // Проверка на 0 карт
    CardDeck deck2(52);
    CardDeck spades = deck2.suitFinder(999); //Масть не существует
    REQUIRE(spades.getCount() == 0);
}

TEST_CASE("CardDeck is_twink2") {
    CardDeck deck(52); //Полная колода, is_twink должна быть false
    REQUIRE_FALSE(!(deck.is_twink()));

    //Создайте колоду с повторяющимися картами для проверки true
    //Это требует модификации класса CardDeck для добавления карт
    //например, через метод addCard(Card* card)
}


TEST_CASE("CardDeck stream operators2") {
    CardDeck deck(10);
    std::stringstream ss;
    ss << deck;
    int count_from_stream;
    ss >> count_from_stream;
    REQUIRE(count_from_stream == 10);
    // Проверить обратный оператор
    std::stringstream ss2;
    ss2 << 5;
    CardDeck deck2;
    ss2 >> deck2;
    REQUIRE(deck2.getCount() == 5);
}







TEST_CASE("CardDeck suitFinder") {
    CardDeck deck(52);

    SECTION("Finding Hearts") {
        CardDeck hearts = deck.suitFinder(0);
        REQUIRE(hearts.getCount() == 13);
        // Проверка содержимого (сложно, но желательно - использовать итераторы)
    }

    SECTION("Finding a suit with 0 cards") {
        CardDeck emptyDeck = deck.suitFinder(999); //Несуществующая масть
        REQUIRE(emptyDeck.getCount() == 0);
    }

    SECTION("Finding Spades") {
      CardDeck spades = deck.suitFinder(3);
      REQUIRE(spades.getCount() == 13);
    }

    SECTION("Finding Diamonds") {
      CardDeck diamonds = deck.suitFinder(1);
      REQUIRE(diamonds.getCount() == 13);
    }

    SECTION("Finding Clubs") {
      CardDeck clubs = deck.suitFinder(2);
      REQUIRE(clubs.getCount() == 13);
    }

    SECTION("Empty Deck") {
      CardDeck emptyDeck(0);
      CardDeck result = emptyDeck.suitFinder(0);
      REQUIRE(result.getCount() == 0);
    }
}


TEST_CASE("CardDeck is_twink") {
    SECTION("Full Deck - No duplicates") {
        CardDeck deck(52);
        REQUIRE_FALSE(!(deck.is_twink()));
    }

    SECTION("Deck with Duplicates") {
        CardDeck deck; //полная колода
        // Добавить дубликаты (требуется модификация CardDeck)
        // Пример: deck.addCard(new Card(10,Suit::Hearts)); deck.addCard(new Card(10,Suit::Hearts));
        //  REQUIRE(deck.is_twink());
    }
    SECTION("Empty Deck") {
        CardDeck deck(0);
        REQUIRE_FALSE(deck.is_twink());
    }

}



TEST_CASE("CardDeck stream operators") {
    SECTION("Output operator") {
        CardDeck deck(10);
        std::stringstream ss;
        ss << deck;
        int count_from_stream;
        ss >> count_from_stream;
        REQUIRE(count_from_stream == 10);
    }

    SECTION("Input operator - Positive Value") {
        std::stringstream ss;
        ss << 5;
        CardDeck deck2;
        ss >> deck2;
        REQUIRE(deck2.getCount() == 5);
    }

    SECTION("Input operator - Zero Value") {
        std::stringstream ss;
        ss << 0;
        CardDeck deck2;
        ss >> deck2;
        REQUIRE(deck2.getCount() == 0);
    }

    SECTION("Input operator - Negative Value") {
        std::stringstream ss;
        ss << -5; //Обратите внимание, что это некорректный ввод, но должен обработаться корректно
        CardDeck deck2;
        ss >> deck2;
        REQUIRE(deck2.getCount() == -5); // Проверка на корректную обработку отрицательного значения
    }

}


TEST_CASE("CardDeck Constructor - Empty Deck") {
    CardDeck deck(0);
    REQUIRE(deck.getCount() == 0);
}

TEST_CASE("CardDeck Constructor - Full Deck") {
    CardDeck deck;
    REQUIRE(deck.getCount() == 52);
    // Проверка наличия всех уникальных карт (сложная, требуется реализация)
}

TEST_CASE("CardDeck Constructor - Partial Deck") {
    CardDeck deck(26);
    REQUIRE(deck.getCount() == 26);
}

TEST_CASE("CardDeck Copy Constructor") {
    CardDeck deck1(10);
    CardDeck deck2 = deck1;
    REQUIRE(deck2.getCount() == 10);
    // Проверка содержимого deck2 (сложно, требуется реализация)
}

TEST_CASE("CardDeck Move Constructor") {
    CardDeck deck1(15);
    CardDeck deck2 = std::move(deck1);
    REQUIRE(deck2.getCount() == 15);
    REQUIRE(deck1.getCount() == 0);
}

TEST_CASE("CardDeck Destructor") {
    // Проверка отсутствия утечек памяти (с помощью Valgrind или аналогичных инструментов)
}

TEST_CASE("CardDeck addRandomCard") {
    CardDeck deck(5);
    deck.addRandomCard();
    REQUIRE(deck.getCount() == 6);
}

TEST_CASE("CardDeck getCardByIndex") {
    CardDeck deck;
    REQUIRE(deck.getCardByIndex(0) != nullptr);
    REQUIRE(deck.getCardByIndex(51) != nullptr); // 52-1
    REQUIRE_THROWS_AS(deck.getCardByIndex(-1), std::out_of_range);
    REQUIRE_THROWS_AS(deck.getCardByIndex(52), std::out_of_range);
}

TEST_CASE("CardDeck deleteCardByIndex") {
    CardDeck deck(5);
    deck.deleteCardByIndex(2);
    REQUIRE(deck.getCount() == 4);
    REQUIRE_THROWS_AS(deck.deleteCardByIndex(-1), std::out_of_range);
    REQUIRE_THROWS_AS(deck.deleteCardByIndex(5), std::out_of_range);
}


TEST_CASE("CardDeck sortCards") {
    CardDeck deck(5); // Создайте колоду с несколькими картами
    deck.sortCards(false); // Сортировка по возрастанию
    // Проверьте, что карты отсортированы по возрастанию (требуется реализация)
    deck.sortCards(true); // Сортировка по убыванию
    // Проверьте, что карты отсортированы по убыванию (требуется реализация)
}

TEST_CASE("CardDeck shuffle") {
    CardDeck deck(10);
    CardDeck deck2 = deck; // Создаем копию перед перемешиванием
    deck.shuffle();
    bool shuffled = false;
    for (int i = 0; i < 10; ++i) {
        if (deck.getCardByIndex(i)->getRank() != deck2.getCardByIndex(i)->getRank() ||
            deck.getCardByIndex(i)->getSuit() != deck2.getCardByIndex(i)->getSuit()) {
            shuffled = true;
            break;
        }
    }
    REQUIRE(shuffled); // Убедитесь, что хотя бы одна карта изменила позицию
}
