/*
AUTHOR: Andrew Megaris
COURSE: EECS-665 Compiler Construction
ASSIGNMENT: Project 1 NFA - DFA Converter
FILE: MAIN.CPP
*/

#include <iostream>
#include <cstdio>
#include "converter.h"

int main(int argc, char** argv){

  Converter nfaToDfa;
  
  nfaToDfa.loadArray();
  nfaToDfa.findInitState();
  nfaToDfa.findFinalStates();
  nfaToDfa.findNumberOfStates();
  nfaToDfa.findAlphabet();
  nfaToDfa.findTransitions();
  nfaToDfa.assignEverything();
  std::vector<int> x;
  x.pushBack(10);
  x.pushBack(11);
  x.pushback(100);
  nfaToDfa.markHelper(2,x);
  std::cout << std::endl <<nfaToDfa.epsilon[1][0];
}
