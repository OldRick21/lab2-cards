#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "Card.h"
#include "string"
#include <unordered_map>

Card::Card(int rank, Suit suit) {
    this->rank = rank;
    this->suit = suit;
}

Card::Card() {
    srand(time(nullptr));
    this->rank = rand() % 13 + 1;
    this->suit = static_cast<Suit>(rand() % 4);
}

Card::Card(const Card &card) {
    this->rank = card.getRank();
    this->suit = card.getSuit();
}


bool Card::operator<(const Card& card) const {
    if (this->suit != card.suit) {
        throw std::invalid_argument("Cards must have same suit");
    }
    return this->rank < card.rank;
}

bool Card::operator==(const Card& card) const {
    if (this->suit != card.suit) {
        throw std::invalid_argument("Cards must have same suit");
    }
    return this->rank == card.rank;
}

bool Card::operator<=(const Card &card) const {
    return operator==(card) || operator<(card);
}


std::string Card::outputCard() const{
    return this->parseRank() + this->parseSuit();
}

std::string Card::parseRank() const{
    std::unordered_map<int, std::string> a;
    a[13] = "A";
    a[12] = "K";
    a[11] = "Q";
    a[10] = "J";
    if (a.contains(this->rank)) return a[this->rank];
    return std::to_string(this->rank);
}

std::string Card::parseSuit() const{

    switch (suit)
    {
        case DIAMOND : return "♦";
        case HEARTS : return "♥";
        case SPIDES : return "♠";
        case CLUBS : return "♣";
    }

    return std::string();
}

void Card::inputCard(int new_rank, int new_suit)
{

    if (new_rank > 13 || new_rank < 1){
        throw std::invalid_argument("Rank not in range 1-13");
    }

    setRank(new_rank);

    if (new_suit > 4 || new_suit < 1){
        throw std::invalid_argument("Suit number not in range 1-4");
    }

    std::unordered_map<int, Suit> a;
    a[1] = DIAMOND;
    a[2] = HEARTS;
    a[3] = SPIDES;
    a[4] = CLUBS;

    setSuit(a[new_suit]);
}

void Card::setRank(int rank) {
    Card::rank = rank;
}

void Card::setSuit(Suit suit) {
    Card::suit = suit;
}

int Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}

int Card::getSizeForSort() const {
    return suit * 13 + rank;
}

std::ostream &operator<<(std::ostream &os, const Card &card)
{
    os << card.outputCard();
    return os;
}

std::istream &operator>>(std::istream &is, Card &card)
{
    int temp1;
    int temp2;
    is >> temp1 >> temp2;
    card.inputCard(temp1, temp2);
    return is;
    
}
