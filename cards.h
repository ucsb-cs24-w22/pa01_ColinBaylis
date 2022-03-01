//cards.h
//Colin Baylis 6061543 2/22/22

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
using namespace std;

struct Card {
    char suit;
    int value;
    Card *left, *right, *parent;
    Card(char s=0, int v=0) : suit(s), value(v), left(0), right(0), parent(0) { }
    string toString();
    bool operator ==(const Card& c1);
    bool operator !=(const Card& c1);
    bool operator <(const Card& c1);
    bool operator >(const Card& c1);
    Card* operator =(const Card& c1);
};


class CardBST {
    public: 
        CardBST();
        ~CardBST();
        bool insert(char suit, int value);
        void preOrderPrint() const;
        void inOrderPrint() const;
        void printPostOrder() const;
        bool contains (char suit, int value) const;
        Card* getNext(char suit, int value) const;
        Card* getPrev(char suit, int value) const;
        bool remove(char suit, int value);
        int countCards() const;
        Card* minim() const;
        Card* maxim() const;
        
    private:
        Card *root;
        Card* returnCard(Card *c, Card* n) const;
        void clear(Card *c);
        bool insert(Card *c, Card *n);
        void preOrderPrint(Card *c) const;
        void inOrderPrint(Card *c) const;
        void printPostOrder(Card *c) const;
        int countCards(Card *c) const;
        Card* getPrevCard(Card *c) const;
        Card* getNextCard(Card *c) const;
};

#endif
