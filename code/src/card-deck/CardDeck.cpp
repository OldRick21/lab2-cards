
#include "CardDeck.h"
#include <algorithm>
#include <random>
#include <iostream>

CardDeck::CardDeck(int count) {
    if (count < 1) {
        this->count = 0;
        cards = nullptr;
        return;
    }
    if (count > 52) {
        this->count = 52;
    } else {
        this->count = count;
    }
    cards = new Card *[this->count];
    int flag = this->count;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            if (flag > 0) {
                Card *newCard = new Card(j, static_cast<Suit>(i));
                this->cards[flag - 1] = newCard;
                flag--;
            }
        }
    }
    this->shuffle();
}


CardDeck::CardDeck(const CardDeck &cardDeck) {
    count = cardDeck.getCount();
    cards = new Card *[count];
    for (int i = 0; i < count; ++i) {
        cards[i] = new Card(*cardDeck.cards[i]); 
    }
}

CardDeck::CardDeck(CardDeck &&cardDeck) {
    std::swap(count, cardDeck.count);
    std::swap(cards, cardDeck.cards);
    cardDeck.count = 0;
    cardDeck.cards = nullptr;
}

CardDeck::CardDeck() {
    count = MAX_UNIQUE_CARDS_SIZE;
    cards = new Card *[MAX_UNIQUE_CARDS_SIZE];
    int flag = MAX_UNIQUE_CARDS_SIZE;
    for (int i = 0; i < 4; i++) {
        if (flag > 0) {
            for (int j = 0; j < 13; j++) {
                if (flag > 0) {
                    Card *newCard = new Card(j, static_cast<Suit>(i));
                    this->cards[flag - 1] = newCard;
                    flag--;
                }
            }
        }
    }
    this->shuffle();
}

CardDeck::~CardDeck() {
    cardsDestroy();
}

bool CardDeck::contains(Card *card) const {
    for (int i = 0; i < count; i++) {
        if (card->getSuit() == cards[i]->getSuit()) {
            if (*card == *this->cards[i]) {
                return true;
            }
        }
    }
    return false;
}

void CardDeck::operator>>(CardDeck &cardDeck) {
    if (count == 0) return;

    Card *card = this->cards[this->count - 1];

    Card **newCards1 = new Card *[count - 1];
    std::copy(&cards[0], &cards[count - 1], &newCards1[0]);

    delete[] cards;
    cards = newCards1;

    Card **newCards2 = new Card *[cardDeck.getCount() + 1];
    std::copy(&cardDeck.getCards()[0], &cardDeck.getCards()[cardDeck.getCount()], &newCards2[0]);

    newCards2[cardDeck.getCount()] = card;

    cardDeck.setCards(newCards2, false); 

    count--;
    cardDeck.setCount(cardDeck.getCount() + 1);
}

Card **CardDeck::getCards() const {
    return cards;
}

void CardDeck::setCards(Card **cards, bool destroyExisting) {
    if (destroyExisting) {
        cardsDestroy();
    }
    this->cards = cards;
}

int CardDeck::getCount() const {
    return count;
}

void CardDeck::setCount(int newCount) {
    if (newCount > 0) {
        if (newCount < count) {
            
            for (int i = newCount; i < count; ++i) {
                delete cards[i];
            }
        }
        this->count = newCount;
    } else {
        this->count = 0;
        cardsDestroy(); 
    }
}

void CardDeck::addRandomCard() {
    Card **newCards = new Card *[count + 1];
    std::copy(cards, cards + count, newCards);
    newCards[count] = new Card(); 
    count++;
    delete[] cards;
    cards = newCards;
}

Card *CardDeck::getCardByIndex(int index) const {
    if (index > count - 1 || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return cards[index];
}

void CardDeck::deleteCardByIndex(int index) {
    if (index > count - 1 || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    Card **newCards = new Card *[count - 1];
    int j = 0;
    for (int i = 0; i < count; i++) {
        if (i != index) {
            newCards[j] = cards[i];
            j++;
        } else {
            delete cards[i];
        }
    }
    delete[] cards;
    count--;
    cards = newCards;
}

void CardDeck::sortCards(bool reversed) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = count - 1; j > i; j--) {
            if ((cards[i]->getSizeForSort() > cards[j]->getSizeForSort() && !reversed) ||
                (cards[i]->getSizeForSort() < cards[j]->getSizeForSort() && reversed)) {
                Card *t = cards[i];
                cards[i] = cards[j];
                cards[j] = t;
            }
        }
    }
}

void CardDeck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(cards, cards + count, g);
}

CardDeck CardDeck::operator+(const CardDeck &cardDeck) const {
    CardDeck newDeck(0);

    newDeck.count = count + cardDeck.getCount();

    newDeck.cards = new Card* [newDeck.count];

    for (int i = 0; i < count; ++i) {
        newDeck.cards[i] = new Card(*cards[i]); 
    }
    for (int i = 0; i < cardDeck.getCount(); ++i) {
        newDeck.cards[count + i] = new Card(*cardDeck.cards[i]); 
    }
    return newDeck;
}

CardDeck& CardDeck::operator=(CardDeck &&cardDeck) {
    if (this == &cardDeck) {
        return *this;
    }
    cardsDestroy();
    std::swap(count, cardDeck.count);
    std::swap(cards, cardDeck.cards);
    cardDeck.count = 0;
    cardDeck.cards = nullptr;
    return *this;
}

CardDeck& CardDeck::operator=(const CardDeck &cardDeck) {
    if (this == &cardDeck) {
        return *this;
    }
    cardsDestroy();
    count = cardDeck.getCount();
    cards = new Card *[count];
    for (int i = 0; i < count; ++i) {
        cards[i] = new Card(*cardDeck.cards[i]); 
    }
    return *this;
}

CardDeck CardDeck::suitFinder(int suit) const {
    int c_count = 0;
    std::for_each(cards, cards + count, [&suit, &c_count](Card *&card) {
        if (card->getSuit() == suit) {
            c_count++;
        }
    });

    CardDeck newDeck(0);
    newDeck.count = c_count;
    newDeck.cards = new Card* [c_count];

    int flag = 0;
    std::for_each(cards, cards + count, [&flag, &suit, &newDeck](Card *&card) {
        if (card->getSuit() == suit) {
            newDeck.cards[flag] = new Card(*card); 
            flag++;
        }
    });

    return newDeck;
}

bool CardDeck::is_twink() {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (cards[i]->getSuit() == cards[j]->getSuit() && *cards[i] == *cards[j]) {
                return true;
            }
        }
    }
    return false;
}

void CardDeck::cardsDestroy() {
    if (cards != nullptr) {
        for (int i = 0; i < count; ++i) {
            delete cards[i];
        }
        delete[] cards;
        cards = nullptr;
        count = 0;
    }
}

std::ostream &operator<<(std::ostream &os, const CardDeck &carddeck) {
    os << carddeck.getCount();
    return os;
}

std::istream &operator>>(std::istream &is, CardDeck &carddeck) {
    int tmp;
    is >> tmp;
    carddeck.setCount(tmp);
    return is;
}
