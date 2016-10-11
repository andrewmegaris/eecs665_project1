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
  int x[] = {2,3,4,5,88,44,321,6,7,8};
  nfaToDfa.markHelper(2,x);
  std::cout << std::endl <<nfaToDfa.epsilon[1][0];
}
