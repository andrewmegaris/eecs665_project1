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
  std::vector< int > finalStates;
  std::vector< std::vector< std::string > > nextStates;
  std::vector< std::vector< int > > nextSteps;
  std::vector< std::vector< int > > epsilon;
  int totalStates;
  int tableSize;
  int alphabetSize;
  int dfaStateCount;
  std::string  inputArr;
  int  markCount;
  std::string alphabet;

  Converter();
  ~Converter();
  void findTransitions();
  void loadArray();
  void findInitState();
  void findFinalStates();
  void findNumberOfStates();
  void findAlphabet();
  void assignEverything();
  void mark(int,std::vector<int>);
  void markHelper(int,std::vector<int>);
  void printSet(std::vector<int>);
};

#include "converter.cpp"

#endif
