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
    this->st = c1.st;
    this->ve = c1.ve;
    this->lt = c1.lt;
    this->rt = c1.rt;
    this->pt = c1.pt;
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
    // handle special case of empty tree first
    if (!root) {
        root = new Card(suit, number);
        return true;
    }
    // otherwise use recursive helper
    return insert(new Card(suit, number), root);
}

bool CardBST::insert(Card *c, Card *n) {
    if (*c == *n) {
	    return false;
    }
    if (*c < *n) {
        if (n->left)
            return insert(c, n->left);
        else {
            n->left = new Card(c->suit, c->number);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->rt)
            return insert(c, n->rt);
        else {
            n->rt = new Card(c->suit, c->number);
            n->rt->parent = n;
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
	printPreOrder(n->left);
	printPreOrder(n->rt);
    }
}

void CardBST::printInOrder() const {
    printInOrder(root);
}


void CardBST::printInOrder(Card *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->suit << n->number << " ";
        printInOrder(n->rt);
    }
}

void CardBST::printPostOrder() const {
    printPostOrder(root);
}


void CardBST::printPostOrder(Card *n) const {
    if(n) {
        printPostOrder(n->left);
        printPostOrder(n->rt);
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
        count += CardBST::count(n->left);
        count += CardBST::count(n->rt);
        return count + 1;
    }
    return count;
}

Card* CardBST::min() const {
    Card *n = root;
    while(n && n->left) {
        n = n->left;
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
            ans = CardBST::getCardFor(c, n->left);
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
    if(n && n->left) {
        n = n->left;
        while(n && n->rt) {
            n = n->rt;
        }
    } else if(n && n->parent) {
        Card *p = n->parent;
        while(p && (*n < *p)) {
            p = p->parent;
        }
        n = p;
    }
    return n; // REPLACE THIS NON-SOLUTION
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
        while(n && n->left) {
            n = n->left;
        }
    } else if(n && n->parent) {
        Card *p = n->parent;
        while(p && (*n > *p)) {
            p = p->parent;
        }
        n = p;
    }
    return n; 
}
Card* CardBST::getSuccessor(char suit, int number) const{
    return getSuccessorCard(new Card(suit, number)) ? getSuccessorCard(new Card(suit, number)): 0;
}

// deletes the Card containing the given number from the tree
// returns true if the node exist and was deleted or false if the node does not exist

bool CardBST::remove(char suit, int number){
    Card *c = new Card(suit, number);
    bool ans = false;
    Card *n = getCardFor(c, this->root);
    if(n && !n->parent && !n->left && !n->rt) {
        delete(n);
        this->root = nullptr;
        return true;
    }
    if(n && !n->left && !n->rt) {
        if(n->parent && (*n > *n->parent)) {
            n->parent->rt = 0;
        } else if (n->parent) {
            n->parent->left = 0;
        }
        if(*n == *c) {
            n = 0;
        }
        delete(n);
        ans = true;
    } else if(n && (!n->left || !n->rt)) {
        if(n->parent && (*n > *n->parent)) {
            n->parent->rt = n->left ? n->left : n->rt;
        } else if(n->parent) {
            n->parent->left = n->left ? n->left : n->rt;
        }
        delete(n);
        ans = true;
    } else if (n && n->left && n->rt) {
        Card *s = new Card();
        s = getSuccessorCard(n);
        Card *temp = s;
        ans = remove(s->suit, s->number);
        n->suit = temp->suit;
        n->number = temp->number;
    }
    return ans; // REPLACE THIS NON-SOLUTION
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
