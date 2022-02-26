//cards.h
//Authors: Your name and your partner's name
//All class declarations go here

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
        void printPreOrder() const;
        void printInOrder() const;
        void printPosOrder() const;
        bool contains (char suit, int value) const;
        Card* getPredecessor(char suit, int value) const;
        Card* getSuccessor(char suit, int value) const;
        bool remove(char suit, int value);
        int count() const;
        Card* min() const;
        Card* max() const;
        
    private:
        Card *root;
        Card* getCardFor(Card *c, Card* n) const;
        void clear(Card *c);
        bool insert(Card *c, Card *n);
        void printPreOrder(Card *c) const;
        void printInOrder(Card *c) const;
        void printPosOrder(Card *c) const;
        int count(Card *c) const;
        Card* getSuccessorCard(Card *c) const;
        Card* getPredecessorCard(Card *c) const;
};

#endif
