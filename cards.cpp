// intbst.cpp
// Colin Baylis 2/22/22
//Implementation of the classes defined in cards.h
#include <iostream>
#include "cards.h"
#include "utility.h"

using namespace std;

CardBST::CardBST() : root(nullptr) { }
// clear nodes
CardBST::~CardBST() {
    clear(root);
}

Card* Card::operator=(const Card& c1){
    this->start = c1.start;
    this->number = c1.number;
    this->lt = c1.lt;
    this->rt = c1.rt;
    this->head = c1.head;
    return this;
}

void CardBST::clear(Card *n) {
    if (n) {
	clear(n->lt);
	clear(n->rt);
	delete n;
    }
}

bool CardBST::insert(char suit, int number) {
    if (!root) {
        root = new Card(suit, number);
        return true;
    }
    return insert(new Card(suit, number), root);
}

bool CardBST::insert(Card *c, Card *n) {
    if (*c == *n) {
	    return false;
    }
    if (*c < *n) {
        if (n->lt)
            return insert(c, n->lt);
        else {
            n->lt = new Card(c->suit, c->number);
            n->lt->head = n;
            return true;
        }
    }
    else {
        if (n->rt)
            return insert(c, n->rt);
        else {
            n->rt = new Card(c->suit, c->number);
            n->rt->head = n;
            return true;
        }
    }
}
void CardBST::printPreOrder() const {
    printPreOrder(root);
}

void CardBST::printPreOrder(Card *n) const {
    if (n) {
	cout << n->suit << n->number << " ";
	printPreOrder(n->lt);
	printPreOrder(n->rt);
    }
}

void CardBST::printInOrder() const {
    printInOrder(root);
}


void CardBST::printInOrder(Card *n) const {
    if (n) {
        printInOrder(n->lt);
        cout << n->suit << n->number << " ";
        printInOrder(n->rt);
    }
}

void CardBST::printPosOrder() const {
    printPosOrder(root);
}


void CardBST::printPosOrder(Card *n) const {
    if(n) {
        printPosOrder(n->lt);
        printPosOrder(n->rt);
        cout << n->suit << n->number << " ";
    }
}

int CardBST::count() const {
    return count(root);
}

// recursive helper for count

int CardBST::count(Card *n) const {
    int count = 0;
    if(n) {
        count += CardBST::count(n->lt);
        count += CardBST::count(n->rt);
        return count + 1;
    }
    return count;
}

Card* CardBST::min() const {
    Card *n = root;
    while(n && n->lt) {
        n = n->lt;
    }
    if(!n) {return 0;}
    return n;
}

Card* CardBST::max() const {
    Card *n = root;
    while(n && n->rt) {
        n = n->rt;
    }
    if(!n) { return 0; }
    return n;
}

Card* CardBST::getCardFor(Card* c, Card* n) const{
    Card *ans = nullptr;
    if(n) {
        if(*c == *n) {
            ans = n;
        }
        if(!ans){
            ans = CardBST::getCardFor(c, n->lt);
        }
        if(!ans) {
            ans = CardBST::getCardFor(c, n->rt);
        }
    }
    return ans;
}


bool CardBST::contains(char suit, int number) const {
    Card *n = root;
    return CardBST::getCardFor(new Card(suit, number), n) != nullptr;
}

Card* CardBST::getPredecessorCard(Card *c) const{
    Card *n = getCardFor(c, this->root);
    if(*n == *min()) {
        return 0;
    }
    if(n && n->lt) {
        n = n->lt;
        while(n && n->rt) {
            n = n->rt;
        }
    } else if(n && n->head) {
        Card *p = n->head;
        while(p && (*n < *p)) {
            p = p->head;
        }
        n = p;
    }
    return n;
}

Card* CardBST::getPredecessor(char suit, int number) const{
    return getPredecessorCard(new Card(suit, number)) ? getPredecessorCard(new Card(suit, number)) : 0; 
}
Card* CardBST::getSuccessorCard(Card *c) const{
    Card *n = getCardFor(c, this->root);
    if(*n == *max()) {
        return 0;
    }
    if(n && n->rt) {
        n = n->rt;
        while(n && n->lt) {
            n = n->lt;
        }
    } else if(n && n->head) {
        Card *p = n->head;
        while(p && (*n > *p)) {
            p = p->head;
        }
        n = p;
    }
    return n; 
}
Card* CardBST::getSuccessor(char suit, int number) const{
    return getSuccessorCard(new Card(suit, number)) ? getSuccessorCard(new Card(suit, number)): 0;
}

bool CardBST::remove(char suit, int number){
    Card *c = new Card(suit, number);
    bool ans = false;
    Card *n = getCardFor(c, this->root);
    if(n && !n->head && !n->lt && !n->rt) {
        delete(n);
        this->root = nullptr;
        return true;
    }
    if(n && !n->lt && !n->rt) {
        if(n->head && (*n > *n->head)) {
            n->head->rt = 0;
        } else if (n->head) {
            n->head->lt = 0;
        }
        if(*n == *c) {
            n = 0;
        }
        delete(n);
        ans = true;
    } else if(n && (!n->lt || !n->rt)) {
        if(n->head && (*n > *n->head)) {
            n->head->rt = n->lt ? n->lt : n->rt;
        } else if(n->head) {
            n->head->lt = n->lt ? n->lt : n->rt;
        }
        delete(n);
        ans = true;
    } else if (n && n->lt && n->rt) {
        Card *s = new Card();
        s = getSuccessorCard(n);
        Card *temp = s;
        ans = remove(s->suit, s->number);
        n->suit = temp->suit;
        n->number = temp->number;
    }
    return ans; 
}
  
string Card::toString() {
    string x = "";
    x.insert(0, 1, this->suit);
    return x + " " + convertValString(this->number);
}

bool Card::operator ==(Card const& c1) {
    return (this->suit == c1.suit) && (this->number == c1.number);
}

bool Card::operator !=(Card const& c1) {
    return !(this->suit == c1.suit) || !(this->number == c1.number);
}

bool Card::operator <(const Card& c1) {
    char temp1, temp2;
    if(c1.suit == 'h') {
      temp2 = 'z';
    }
    else {
      temp2 = c1.suit;
    }
    if(this->suit == 'h') {
      temp1 = 'z';
    } else {
      temp1 = this->suit;
    }
    if(temp1 == temp2) {
      return this->number < c1.number;
    }
    return temp1 < temp2;
  }

bool Card::operator >(const Card& c1) {
    char temp1, temp2;
    if(c1.suit == 'h') {
      temp2 = 'z';
    }
    else {
      temp2 = c1.suit;
    }
    if(this->suit == 'h') {
      temp1 = 'z';
    } else {
      temp1 = this->suit;
    }
    if(temp1 == temp2) {
      return this->number > c1.number;
    }
    return temp1 > temp2;
  }
