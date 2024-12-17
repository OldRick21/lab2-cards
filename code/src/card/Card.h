#include <iostream>

enum Suit{
    HEARTS,
    DIAMOND,
    CLUBS,
    SPIDES
};


class Card {
public:
    Card();
    Card(int rank, Suit suit);
    Card(const Card &card);
    // Card(Card &&card);

    int getRank() const;
    Suit getSuit() const;

    void setRank(int rank);
    void setSuit(Suit suit);

    bool operator==(const Card& card) const;
    bool operator<(const Card& card) const;
    bool operator<=(const Card& card) const;
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend std::istream& operator>>(std::istream& is, Card& card);

    // bool operator<=>(Card& card) const;


    void inputCard(int new_rank, int new_suit);
    std::string outputCard() const;

    int getSizeForSort() const;
private:
    
    std::string parseRank() const;
    std::string parseSuit() const;
    int rank;
    Suit suit;


};

