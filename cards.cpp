// intbst.cpp
// Implements class CardBST
// Jeffrey Mun 5970595 2/03/2022
#include <iostream>
#include "cards.h"
#include "utility.h"

using namespace std;

CardBST::CardBST() : root(nullptr) { }

// destructor deletes all nodes
CardBST::~CardBST() {
    clear(root);
}

Card* Card::operator=(const Card& c1){
    this->suit = c1.suit;
    this->value = c1.value;
    this->left = c1.left;
    this->right = c1.right;
    this->parent = c1.parent;
    return this;
}

// recursive helper for destructor
void CardBST::clear(Card *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(char suit, int value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Card(suit, value);
        return true;
    }
    // otherwise use recursive helper
    return insert(new Card(suit, value), root);
}

// recursive helper for insert (assumes n is never 0)
/**
 * @brief 
 * CHANGE STUFF IN INSERT; ADOPT IT TO CARD STUFF
 */

bool CardBST::insert(Card *c, Card *n) {
    if (*c == *n) {
	    return false;
    }
    if (*c < *n) {
        if (n->left)
            return insert(c, n->left);
        else {
            n->left = new Card(c->suit, c->value);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right)
            return insert(c, n->right);
        else {
            n->right = new Card(c->suit, c->value);
            n->right->parent = n;
            return true;
        }
    }
}

// print tree data pre-order

void CardBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()

void CardBST::printPreOrder(Card *n) const {
    if (n) {
	cout << n->suit << n->value << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper

void CardBST::printInOrder() const {
    printInOrder(root);
}


void CardBST::printInOrder(Card *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->suit << n->value << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper

void CardBST::printPostOrder() const {
    printPostOrder(root);
}


void CardBST::printPostOrder(Card *n) const {
    if(n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->suit << n->value << " ";
    }
}

// return count of values

int CardBST::count() const {
    return count(root);
}

// recursive helper for count

int CardBST::count(Card *n) const {
    int count = 0;
    if(n) {
        count += CardBST::count(n->left);
        count += CardBST::count(n->right);
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
    while(n && n->right) {
        n = n->right;
    }
    if(!n) { return 0; }
    return n;
}

/**
 * @brief 
 * CHANGE STUFF FOR INFOS ON THIS TOO
 * 
 * 
 * 
 * 
 * 
 * 
 */

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// T value: the value to be found
// Card* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"


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
            ans = CardBST::getCardFor(c, n->right);
        }
    }
    return ans;
}


bool CardBST::contains(char suit, int value) const {
    Card *n = root;
    return CardBST::getCardFor(new Card(suit, value), n) != nullptr;
}
// returns the Card containing the predecessor of the given value

Card* CardBST::getPredecessorCard(Card *c) const{
    Card *n = getCardFor(c, this->root);
    if(*n == *min()) {
        return 0;
    }
    if(n && n->left) {
        n = n->left;
        while(n && n->right) {
            n = n->right;
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

// returns the predecessor value of the given value or 0 if there is none

Card* CardBST::getPredecessor(char suit, int value) const{
    return getPredecessorCard(new Card(suit, value)) ? getPredecessorCard(new Card(suit, value)) : 0; 
}

// returns the Card containing the successor of the given value

Card* CardBST::getSuccessorCard(Card *c) const{
    Card *n = getCardFor(c, this->root);
    if(*n == *max()) {
        return 0;
    }
    if(n && n->right) {
        n = n->right;
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

// returns the successor value of the given value or 0 if there is none

Card* CardBST::getSuccessor(char suit, int value) const{
    return getSuccessorCard(new Card(suit, value)) ? getSuccessorCard(new Card(suit, value)): 0;
}

// deletes the Card containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist

bool CardBST::remove(char suit, int value){
    Card *c = new Card(suit, value);
    bool ans = false;
    Card *n = getCardFor(c, this->root);
    if(n && !n->parent && !n->left && !n->right) {
        delete(n);
        this->root = nullptr;
        return true;
    }
    if(n && !n->left && !n->right) {
        if(n->parent && (*n > *n->parent)) {
            n->parent->right = 0;
        } else if (n->parent) {
            n->parent->left = 0;
        }
        if(*n == *c) {
            n = 0;
        }
        delete(n);
        ans = true;
    } else if(n && (!n->left || !n->right)) {
        if(n->parent && (*n > *n->parent)) {
            n->parent->right = n->left ? n->left : n->right;
        } else if(n->parent) {
            n->parent->left = n->left ? n->left : n->right;
        }
        delete(n);
        ans = true;
    } else if (n && n->left && n->right) {
        Card *s = new Card();
        s = getSuccessorCard(n);
        Card *temp = s;
        ans = remove(s->suit, s->value);
        n->suit = temp->suit;
        n->value = temp->value;
    }
    return ans; // REPLACE THIS NON-SOLUTION
}
  
string Card::toString() {
    string x = "";
    x.insert(0, 1, this->suit);
    return x + " " + convertValString(this->value);
}

bool Card::operator ==(Card const& c1) {
    return (this->suit == c1.suit) && (this->value == c1.value);
}

bool Card::operator !=(Card const& c1) {
    return !(this->suit == c1.suit) || !(this->value == c1.value);
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
      return this->value < c1.value;
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
      return this->value > c1.value;
    }
    return temp1 > temp2;
  }