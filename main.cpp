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
    value = valToInt(line.substr(2));
    alice.insert(suit, value);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line[0];
    value = valToInt(line.substr(2));
    bob.insert(suit, value);
  }
  cardFile2.close();
  bool firstMatch, secMatch;
  bool invalid = false;

  while(true) {
    Card* primMin = alice.minim();
    Card* pimMax = bob.maxim();
    firstMatch = false;
    secMatch = false;

    while(!firstMatch && primMin && alice.getNext(primMin->suit, primMin->value)) {
      Card* temp = alice.getNext(primMin->suit, primMin->value);
      if(bob.contains(primMin->suit, primMin->value)) {
        cout << "Alice picked matching card " << primMin->toString() << endl;
        char temp1 = primMin->suit;
        int temp2 = primMin->value;
        alice.remove(temp1, temp2);
        bob.remove(temp1, temp2);
        firstMatch = true;
      }
      primMin = temp;
    }
    while(!secMatch && pimMax && bob.getPrev(pimMax->suit, pimMax->value)) {
      Card* temp = bob.getPrev(pimMax->suit, pimMax->value);
      if(alice.contains(pimMax->suit, pimMax->value)) {
        cout << "Bob picked matching card " << pimMax->toString() << endl;
        char temp1 = pimMax->suit;
        int temp2 = pimMax->value;
        bob.remove(temp1, temp2);
        alice.remove(temp1, temp2);
        secMatch = true;
      }
      pimMax = temp;
    }
    if(!firstMatch || !secMatch || invalid) {
      break;
    }
  }

  cout << "\nAlice's cards:" << endl;
  alice.inOrderPrint();
  cout << "\nBob's cards:" << endl;
  bob.inOrderPrint();
  return 0;
}
