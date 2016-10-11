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
  
  nfaToDfa.load();
  nfaToDfa.findInitState();
  nfaToDfa.findFinalStates();
  nfaToDfa.findNumberOfStates();
  nfaToDfa.findAlphabet();
  nfaToDfa.findTransitions();
  nfaToDfa.assignEverything();
  nfaToDfa.readyGo();
}
