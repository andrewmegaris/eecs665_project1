/*
AUTHOR: Andrew Megaris
COURSE: EECS-665 Compiler Construction
ASSIGNMENT: Project 1 NFA - DFA Converter
FILE: CONVERTER.H
*/

#ifndef CONVERTER_H
#define CONVERTER_H
#include <vector>
#define TABLE_SIZE 1004
#define ALPHABET_SIZE 100
#define NUMBER_OF_STATES 1000

class Converter{
  public:
  int initialState;
  int dfaFinalStates;
  int statesNum;
  std::vector< int > dfaFinalVector;
  std::vector< std::string > finalStates;
  std::vector< std::string > nextSteps;
  std::vector< int > intFinalStates;
  std::vector< int > intNextSteps;
  std::vector< std::vector< int > > dfaStates;
  std::vector< int > dfaSteps;
  std::vector< std::vector < int > > intEpsilonSteps;
  int alphabetSize;
  std::vector< std::string >  inputVector;
  std::vector< char > alphabetVector;

  Converter();
  ~Converter();
  void findTransitions();
  void load();
  void findInitState();
  void findFinalStates();
  void findNumberOfStates();
  void findAlphabet();
  void assignEverything();
  void readyGo();
  void mark(std::vector<int>,int);
  void pV(std::vector<int>);
  std::vector<int> eClose(std::vector<int> &,int);
  void wrapItUp();
  void findDfaStartFinal();
};

#include "converter.cpp"

#endif
