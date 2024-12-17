#include <vector>
#include "../card/Card.h"

class CardDeck {
public:
    CardDeck();

    explicit CardDeck(int count);

    CardDeck(const CardDeck &cardDeck);

    CardDeck(CardDeck &&cardDeck);

    ~CardDeck();

    void operator>>(CardDeck &cardDeck);

    Card **getCards() const;

    void setCards(Card **cards);

    int getCount() const;

    void setCount(int count);

    void addRandomCard();

    Card *getCardByIndex(int index) const;

    void deleteCardByIndex(int index);

    void sortCards(bool reversed = false);

    void shuffle();

    CardDeck &operator+(const CardDeck &cardDeck) const;

    CardDeck& operator=(CardDeck &&cardDeck);

    CardDeck& operator=(const CardDeck& cardDeck);

    friend std::ostream &operator<<(std::ostream &os, const CardDeck &carddeck);

    friend std::istream &operator>>(std::istream &is, CardDeck &carddeck);

    CardDeck suitFinder(int suit) const;

    bool is_twink();

    void cardsDestroy();

private:
    Card **cards;
    int count;

    bool contains(Card *card) const;

    const int MAX_UNIQUE_CARDS_SIZE = 52;
};

