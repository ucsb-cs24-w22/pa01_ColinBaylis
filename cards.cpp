// intbst.cpp
// Colin Baylis 6061543 2/22/22
#include <iostream>
#include "cards.h"
#include "utility.h"

using namespace std;

CardBST::CardBST() : root(nullptr) { }

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

void CardBST::clear(Card *n) {
    if (n) {
	    clear(n->left);
	    clear(n->right);
	    delete n;
    }
}

// for use in tree
bool CardBST::insert(char suit, int value) {
    if (!root) {
        root = new Card(suit, value);
        return true;
    }
    return insert(new Card(suit, value), root);
}

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
void CardBST::printPreOrder() const {
    printPreOrder(root);
}

void CardBST::printPreOrder(Card *root) const {
    if (root) {
	    cout << root->suit << root->value << " ";
	    printPreOrder(root->left);
	    printPreOrder(root->right);
    }
}

void CardBST::printInOrder() const {
    printInOrder(root);
}


void CardBST::printInOrder(Card *n) const {
    if (n!=NULL) {
        printInOrder(n->left);
        cout << n->suit << n->value << " ";
        printInOrder(n->right);
    }
}

void CardBST::printPostOrder() const {
    printPostOrder(root);
}


void CardBST::printPostOrder(Card *n) const {
    if(n!=NULL) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->suit << n->value << " ";
    }
}

int CardBST::countCards() const {
    return countCards(root);
}

int CardBST::countCards(Card *n) const {
    int total = 0;
    if(n == NULL) {
        return 0;
    } else {
        total += CardBST::countCards(n->left);
        total += CardBST::countCards(n->right);
        return total + 1;
    }
    return total;
}

Card* CardBST::minim() const {
    Card *min = root;
    while(min && min->left) {
        min = min->left;
    }
    if(!min) {return 0;}
    return mi;
}

Card* CardBST::maxim() const {
    Card *max = root;
    while(max && max->right) {
        max = max->right;
    }
    if(!max) { return 0; }
    return max;
}

Card* CardBST::returnCard(Card* c, Card* n) const{
    Card *fin = nullptr;
    if(n != NULL) {
        if(*c == *n) {
            fin = n;
        }
        if(fin == nullptr){
            fin = CardBST::returnCard(c, n->left);
        }
        if(fin == nullptr) {
            fin = CardBST::returnCard(c, n->right);
        }
    }
    return fin;
}

bool CardBST::contains(char suit, int value) const {
    Card *n = root;
    return CardBST::returnCard(new Card(suit, value), n) != nullptr;
}

Card* CardBST::getNextCard(Card *c) const{
    Card *n = returnCard(c, this->root);
    if(*n == *minim()) {
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
    return n; 
}

Card* CardBST::getNext(char suit, int value) const{
    return getNextCard(new Card(suit, value)) ? getNextCard(new Card(suit, value)) : 0; 
}

Card* CardBST::getPrevCard(Card *c) const{
    Card *n = returnCard(c, this->root);
    if(*n == *maxim()) {
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


Card* CardBST::getPrev(char suit, int value) const{
    return getPrevCard(new Card(suit, value)) ? getPrevCard(new Card(suit, value)): 0;
}

bool CardBST::remove(char suit, int value){
    Card *c = new Card(suit, value);
    bool ans = false;
    Card *n = returnCard(c, this->root);
    if(n && !n->left! && n->parent  && !n->right) {
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
        //
        Card *r;
        if(n == root) {
            if(n->right) {
                Card *s = getPrevCard(n);
                char curr1 = s->suit;
                int curr2 = s->value;
                ans = remove(curr1, curr2);
                n->suit = curr1;
                n->value = curr2;
            }
            if(n->left) {
                root = n->left;
                n->right->parent = root;
                delete(n);
            }
        }
        if(n->parent && (*n > *n->parent)) {
            if(n->left) {
                n->parent->right = n->left;
                n->left->parent = n->parent;
                delete(n);
            } else {
                if(n->right->left) {
                    Card *s = getPrevCard(n);
                    char curr1 = s->suit;
                    int curr2 = s->value;
                    ans = remove(curr1, curr2);
                    n->suit = curr1;
                    n->value = curr2;
                } else {
                    n->parent->right = n->right;
                    n->right->parent = n->parent;
                    delete(n);
                }
            }
        } else if(n->parent) {
            if(n->left) {
                n->parent->left = n->left;
                n->left->parent = n->parent;
                delete(n);
            } else {
                if(n->right->left) {
                    Card *s = getPrevCard(n);
                    char curr1 = s->suit;
                    int curr2 = s->value;
                    ans = remove(curr1, curr2);
                    n->suit = curr1;
                    n->value = curr2;
                } else {
                    n->parent->left = n->right;
                    n->right->parent = n->parent;
                    delete(n);
                }
            }
        }
    } else if (n && n->left && n->right) {
        bool newRoot = false;
        if(n == root) { 
            newRoot = true;
        }
        Card *s = new Card();
        s = getPrevCard(n);
        char curr1 = s->suit;
        int curr2 = s->value;
        ans = remove(curr1, curr2);
        n->suit = curr1;
        n->value = curr2;
        if(newRoot) {
            root = n;
        }
    }
    return ans;
}
  
string Card::toString() {
    string str = "";
    str.insert(0, 1, this->suit);
    return str + " " + valToString(this->value);
}

bool Card::operator ==(Card const& c1) {
    // if val and suit equal
    return (this->suit == c1.suit) && (this->value == c1.value);
}

bool Card::operator !=(Card const& c1) {
    // if val suit not equal
    return !(this->suit == c1.suit) || !(this->value == c1.value);
}

bool Card::operator <(const Card& c1) {
    char curr1, curr2;
    if(c1.suit == 'h') {
      curr2 = 'z';
    }
    else {
      curr2 = c1.suit;
    }
    if(this->suit == 'h') {
      curr1 = 'z';
    } else {
      curr1 = this->suit;
    }
    if(curr1 == curr2) {
      return this->value < c1.value;
    }
    return curr1 < curr2;
  }

bool Card::operator >(const Card& c1) {
    char curr1, curr2;
    if(c1.suit == 'h') {
      curr2 = 'z';
    }
    else {
      curr2 = c1.suit;
    }
    if(this->suit == 'h') {
      curr1 = 'z';
    } else {
      curr1 = this->suit;
    }
    if(curr1 == curr2) {
      return this->value > c1.value;
    }
    return curr1 > curr2;
  }
