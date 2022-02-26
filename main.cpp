#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"
#include "utility.h"

using namespace std;
/**
 * @brief 
 * åå
 * @param argv 
 * @param argc 
 * @return int 
 * 
 * MAKE STUFF FOR <, >, == operators specific to Card
 * use that instead to compare
 * u all good jeff :)
 */

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  char suit;
  int value;
  CardBST alice, bob;
  bool loop = true;


  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  while (getline (cardFile1, line) && (line.length() > 0)){
    suit = line[0];
    value = convertValInt(line.substr(2));
    alice.insert(suit, value);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line[0];
    value = convertValInt(line.substr(2));
    bob.insert(suit, value);
  }
  cardFile2.close();


  Card* amin = alice.min();
  Card* bmax = bob.max();
  bool amatch, bmatch;
  while(true) {
    amatch = false;
    bmatch = false;
    while(alice.getSuccessor(amin->suit, amin->value) && !amatch) {
      Card* temp = alice.getSuccessor(amin->suit, amin->value);
      if(bob.contains(amin->suit, amin->value)) {
        cout << "Alice picked matching card " << amin->toString() << endl;
        alice.remove(amin->suit, amin->value);
        bob.remove(amin->suit, amin->value);
        amatch = true;
      }
      amin = temp;
      if(amatch) break;
    }
    while(bob.getPredecessor(bmax->suit, bmax->value) && !bmatch) {
      Card* temp = bob.getPredecessor(bmax->suit, bmax->value);
      if(alice.contains(bmax->suit, bmax->value)) {
        cout << "Bob picked matching card " << bmax->toString() << endl;
        bob.remove(bmax->suit, bmax->value);
        alice.remove(bmax->suit, bmax->value);
        bmatch = true;
      }
      bmax = temp;
      if(bmax) break;
    }
    if(!amatch && !bmatch) {break;}
  }

  cout << "alice: " << endl;
  alice.printInOrder();
  cout << endl;
  cout << "bob: " << endl;
  bob.printInOrder();
  cout << endl;

  cout << "alice: " << endl;
  alice.printInOrder();
  cout << endl;
  cout << "bob: " << endl;
  bob.printInOrder();
  cout << endl;
  return 0;
}
