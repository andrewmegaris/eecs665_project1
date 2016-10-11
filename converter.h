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
  int finalStates[NUMBER_OF_STATES];
  std::string nextStates[NUMBER_OF_STATES][ALPHABET_SIZE];
  int nextSteps[NUMBER_OF_STATES][ALPHABET_SIZE];
  int epsilon[NUMBER_OF_STATES][NUMBER_OF_STATES];
  int totalStates;
  int tableSize;
  int alphabetSize;
  int dfaStateCount;
  std::string inputArr[TABLE_SIZE];
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
  void eClosure();
  void mark(int,int[]);
  void markHelper(int,int[]);
  void printSet(int[]);
};

#include "converter.cpp"

#endif
