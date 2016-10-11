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
Converter::Converter() : tableSize(0),totalStates(0),initialState(0),alphabetSize(1),dfaStateCount(0),markCount(0){}

Converter::~Converter(){}

//Loads a string array line by line for parsing. For very large tables
// increase the constant ARRAY_SIZE in header file(default 1000)
void Converter::loadArray(){
  std::string line = "";
  std::ifstream inputFile;
  inputFile.open("input.txt");
  int lineCount = 0;

  //load each line into array and count total lines. 
  while(!inputFile.eof()){
  getline(inputFile,line);
  inputArr[lineCount] = line;
  lineCount++;
  }
  totalStates = lineCount - 4;
}

//finds the intitial state from first line
void Converter::findInitState(){
  //strip front 'Initial State: {'
  inputArr[0].erase(0,16);
  //strip back '}'
  inputArr[0].erase(inputArr[0].end()-1,inputArr[0].end());
  
  //initialState = std::stoi(inputArr[0]);
  std::cout << "Initial State: {" << inputArr[0] << "}" << std::endl;
  std::stringstream ss;
  ss.str(inputArr[0]);
  ss>>initialState;
  std::cout << "ss check: " << initialState << std::endl;
}

//finds all of the final states from second line
void Converter::findFinalStates(){
  //strip front 'Final States: {'
  inputArr[1].erase(0,15);
  //strip back '}'
  inputArr[1].erase(inputArr[1].end()-1,inputArr[1].end());
  std::cout << "Final State(s): {" << inputArr[1] << "}" << std::endl;
}

//finds the number of states from third line
void Converter::findNumberOfStates(){
  //strip front 'Total States : '
  inputArr[2].erase(0,14);
  std::cout << "Total States: " << inputArr[2] << std::endl;
}


//figures the alphabet from the fourth line
void Converter::findAlphabet(){
  //strip front 'State'
  inputArr[3].erase(0,5);
  std::cout << "alphabet: " << inputArr[3] << std::endl;

  //strip whitespace from string
  inputArr[3].erase(std::remove_if(inputArr[3].begin(), inputArr[3].end(), isspace),inputArr[3].end());
  int x = 0;
  std::cout << inputArr[3][0] << std::endl;
  //find size of alphabet
  alphabetSize = inputArr[3].size();
  std::cout << "alphabet size: " << alphabetSize << std::endl;
  //output alphabet for testing purposes.
  std::cout << inputArr[3] << std::endl;
  alphabet = inputArr[3];
}

//Strip down the information from the input NDA into string arrays.
void Converter::findTransitions(){
int alphabetCounter;
  //strip out the front numbers from state transitions (ONLY WORKS FOR UP TO 99 STATES!!)
  for(int x = 0; x < totalStates - 1; x++){
    if(x < 10)
      inputArr[x+4].erase(inputArr[x+4].begin(),inputArr[x+4].begin()+1);
    else
      inputArr[x+4].erase(inputArr[x+4].begin(),inputArr[x+4].begin()+2);
    //Strip out whitespace and all leading {'s
    inputArr[x+4].erase(std::remove_if(inputArr[x+4].begin(),inputArr[x+4].end(),isspace),inputArr[x+4].end());
    inputArr[x+4].erase(std::remove(inputArr[x+4].begin(),inputArr[x+4].end(),'{'), inputArr[x+4].end());
    //reset counter for array insertion
    alphabetCounter = 0;
    //insert into array locations traveled to, including epsilon closure.
    for(int y = 0; y < inputArr[x+4].size(); y++){
      if(inputArr[x+4][y] != '}'){
          nextStates[x+1][alphabetCounter] += (inputArr[x+4][y]);
       //   std::cout << "string insert @ nextStats [" << x+1 << "][" << alphabetCounter << "] value : " << nextStates[x+1][alphabetCounter] <<std::endl;
      }
      else{
        alphabetCounter++;          
      }
    }
  //add one extra ',' to end of epsilon closure step
  nextStates[x+1][alphabetSize -1] += ',';
  }
}
//Take the stripped down information and load it into integer arrays.
void Converter::assignEverything(){
  int x;
  int y;
  std::string epsilonStr ="";
  int epsilonCounter;
  //load the steps for everything except epsilon closure.
  for(x = 1; x <= totalStates -1; x++){
    for(y = 0; y <= alphabetSize - 2; y++){
      std::stringstream ss(nextStates[x][y]);
      ss>>nextSteps[x][y];
    //  std::cout << "int insert @ nextSteps [" << x << "][" << y << "] value: " << nextSteps[x][y] << std::endl;
    }
    //split epsilon steps on ','s and load into epsilon array.
    epsilonCounter = 0;
  //  std::cout << "pre epsilon cell: " << nextStates[x][alphabetSize-1] << std::endl;
    for(int z = 0; z <= nextStates[x][alphabetSize-1].size(); z++){
      if(nextStates[x][alphabetSize-1][z] != ','){
        epsilonStr += nextStates[x][alphabetSize-1][z];
      //  std::cout << "building epsilonStr: " << epsilonStr << std::endl;
      }
      else{
        if(epsilonStr == ","){
          epsilonStr = "";
        }
        else{
          std::cout << "epsilonStr b4 conversion: " << epsilonStr << std::endl;
          std::stringstream ss;
          ss.str(epsilonStr);
          ss>>epsilon[x][epsilonCounter];
          std::cout << "int insert @ epsilon[" << x << "][" << epsilonCounter << "] value: " << epsilon[x][epsilonCounter] << std::endl;
          epsilonCounter++;
          epsilonStr = "";
        }
      }
    }
  }
}

/*void Converter::eClosure(int inputState[]){
int index = 0;
if()
while(epsilon[inputstate][index] != 0)
}*/

void Converter::mark(int markInt,int inputArray[]){
  //first build the set. 
  int index = 0;
  //add epsilon states of input state
  if(epsilon[markInt][index] != 0){
    while(epsilon[markInt][index] != 0){
      inputArray[index] = epsilon[markInt][index];
      index++;
    }
    for(int x = 0;x < index; x++){
      //check if any epsilon states have their own epsilon states
      if(epsilon[inputArray[x]][0] == 0){
        mark(inputArray[x],inputArray);
      }
    }
  }
  else{//set has now been built
    for(int x = 0;x <= alphabetSize; x++){
      markHelper(x,inputArray);
    }
  }
}
void Converter::markHelper(int letter,int inputArray[]){
  printSet(inputArray);
  std::cout << "--" << alphabet[letter] << "-->";
}
void Converter::printSet(int inputArray[]){
  int size;
  size = sizeof(inputArray)/sizeof(inputArray[6]);
  std::cout << "{";
  for (int x = 0; x <= size+1;x++){
    std::cout << inputArray[x] << ",";
  }
  std::cout << "}";
}



