/*
AUTHOR: Andrew Megaris
COURSE: EECS-665 Compiler Construction
ASSIGNMENT: Project 1 NFA - DFA Converter
FILE: CONVERTER.CPP
*/

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
//Default Constructor
Converter::Converter() :initialState(0),alphabetSize(1),dfaStateCount(0),markCount(0){}

Converter::~Converter(){}

//Loads a string array line by line for parsing.
void Converter::load(){
  std::string line;
  std::ifstream inputFile("input.txt");

  if(!inputFile){
    std::cout << "Error Opening File" << std::endl;
    return;
  }

  while(std::getline(inputFile,line)){
    inputVector.push_back(line);
  }
  totalStates = inputVector.size() - 4;
}

//finds the intitial state from first line
void Converter::findInitState(){
  bool found = false;
  int x;
  std::vector<char> vector;
  for(int z = 0; z < inputVector[0].size(); z++){
    vector.push_back(inputVector[0][z]);
  } 
  //strip up to initial state value
  while(found == false){
    if(vector[0] != '{')
      vector.erase(vector.begin(),vector.begin()+1);
    else{
      vector.erase(vector.begin(),vector.begin()+1);
      found = true;
    }
  }
  found = false;
  while(found == false){
    for(x = 0; x < vector.size(); x++){
      if(vector[x] == '}')
        found = true;
    }
  }
  //so the start state is stored as chars in a vector currently.
  vector.erase(vector.begin()+x+1,vector.end());
  std::string startState ="";
  for(int q = 0; q <= vector.size() -1; q++){
    startState += vector[q];
  }
}

//finds all of the final states from second line
void Converter::findFinalStates(){
  bool found = false;
  int x;
  std::vector<char> vector;
  for(int z = 0; z < inputVector[1].size(); z++){
    vector.push_back(inputVector[1][z]);
  } 
  //strip up to final states values
  while(found == false){
    if(vector[0] != '{')
      vector.erase(vector.begin(),vector.begin()+1);
    else{
      vector.erase(vector.begin(),vector.begin()+1);
      found = true;
    }
  }
  found = false;
  while(found == false){
    for(x = 0; x < vector.size(); x++){
      if(vector[x] == '}')
        found = true;
    }
  }
  //so the final states is stored as chars in a vector currently.
  vector.erase(vector.begin()+x+1,vector.end());
  std::string finalStates = "";
  for(int q = 0; q < vector.size() -2; q++){
    finalStates += vector[q];
  }
}

//finds the number of states from third line
void Converter::findNumberOfStates(){
  bool found = false;
  std::vector<char> vector;
  for(int z = 0; z < inputVector[2].size(); z++){
    vector.push_back(inputVector[2][z]);
  } 
  while(found == false){
    if(vector[0] != ':')
      vector.erase(vector.begin(),vector.begin()+1);
    else{
      vector.erase(vector.begin(),vector.begin()+2);
      found = true;
    }
  }
  std::string numberOfStates ="";
  for(int q = 0; q <= vector.size() -1; q++){
    numberOfStates += vector[q];
  }
  //use stringstream to convert to integer value.
  std::stringstream stream;
  stream.str(numberOfStates);
  stream >> statesNum;
  
}


//figures the alphabet from the fourth line
void Converter::findAlphabet(){
  //strip front 'State'
  inputVector[3].erase(0,5);
  //strip whitespace from string
  inputVector[3].erase(std::remove_if(inputVector[3].begin(), inputVector[3].end(), isspace),inputVector[3].end());
 
  //find size of alphabet
  alphabetSize = inputVector[3].size();
  for(int z = 0; z < alphabetSize ; z++){
    alphabetVector.push_back(inputVector[3][z]);
  }
}


void Converter::findTransitions(){
  int count = 0;
  bool found = false;
  std::vector<char> vector;
  std::string pushString = "";
  //strip whitespace and proceeding state number
  for(int x = 0; x < statesNum ; x++){
    inputVector[x+4].erase(std::remove_if(inputVector[x+4].begin(),inputVector[x+4].end(),isspace),inputVector[x+4].end());
    while(inputVector[x+4][0] != '{'){
      inputVector[x+4].erase(inputVector[x+4].begin(),inputVector[x+4].begin()+1);
    }
    inputVector[x+4].erase(std::remove(inputVector[x+4].begin(),inputVector[x+4].end(),'{'), inputVector[x+4].end());
    //string is #}}#,#}
    for(int y = 0; y <= alphabetSize - 1; y++){
      found = false;
      count = 0;
      pushString.clear();

      while(found == false){
        if(inputVector[x+4][0] != '}'){
          pushString += inputVector[x+4][0];
          inputVector[x+4].erase(inputVector[x+4].begin(),inputVector[x+4].begin()+1);
          count++;  
        }
        else{
          pushString += inputVector[x+4][0];
          inputVector[x+4].erase(inputVector[x+4].begin(),inputVector[x+4].begin()+1);
          found = true;
          pushString.erase(pushString.end()-1,pushString.end());
          nextSteps.push_back(pushString);
          std::cout << "inserted: " << pushString << " @ " << x<<","<<y<<std::endl;
        }
      }
    }
  }
}

void Converter::assignEverything(){
  for(int x = 0; x < statesNum; x++){
    for(int y = 0; y < alphabetSize; y++){
      if(y == alphabetSize -1){
      //assigne epsilon closure removing commas
      }
      else{
      
      }
    }
  }
}






