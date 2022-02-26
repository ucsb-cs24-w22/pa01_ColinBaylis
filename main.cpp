#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"
#include "utility.h"

using namespace std;

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
  bool amatch, bmatch;
  bool invalid = false;

  while(true) {
    Card* amin = alice.min();
    Card* bmax = bob.max();
    amatch = false;
    bmatch = false;

    while(!amatch && amin && alice.getSuccessor(amin->suit, amin->value)) {
      Card* temp = alice.getSuccessor(amin->suit, amin->value);
      if(bob.contains(amin->suit, amin->value)) {
        cout << "Alice picked matching card " << amin->toString() << endl;
        char temp1 = amin->suit;
        int temp2 = amin->value;
        alice.remove(temp1, temp2);
        bob.remove(temp1, temp2);
        amatch = true;
      }
      amin = temp;
    }
    while(!bmatch && bmax && bob.getPredecessor(bmax->suit, bmax->value)) {
      Card* temp = bob.getPredecessor(bmax->suit, bmax->value);
      if(alice.contains(bmax->suit, bmax->value)) {
        cout << "Bob picked matching card " << bmax->toString() << endl;
        char temp1 = bmax->suit;
        int temp2 = bmax->value;
        bob.remove(temp1, temp2);
        alice.remove(temp1, temp2);
        bmatch = true;
      }
      bmax = temp;
    }
    if(!amatch || !bmatch || invalid) {
      break;
    }
  }

  cout << "\nAlice's cards:" << endl;
  alice.printInOrder();
  cout << "\nBob's cards:" << endl;
  bob.printInOrder();
  return 0;
}
