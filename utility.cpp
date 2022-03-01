#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int valToInt(string s1) {
  if(s1 == "a") {
    return 0;
  } 
  if(s1 == "j") {
    return 11;
  }
  if(s1 == "q") {
    return 12;
  }
  if(s1 == "k") { 
    return 13;
  }
  return stoi(s1);
}

string valToString(int x) {
  if(x == 0) {
    return "a";
  } 
  if(x == 11) {
    return "j";
  }
  if(x == 12) {
    return "q";
  }
  if(x == 13) { 
    return "k";
  }
  return to_string(x);
}
