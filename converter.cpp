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
Converter::Converter(){}

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
  std::stringstream ss;
  ss.str(startState);
  ss >> initialState;
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
 // int count = 0;
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
     // count = 0;
      pushString.clear();

      while(found == false){
        if(inputVector[x+4][0] != '}'){
          pushString += inputVector[x+4][0];
          inputVector[x+4].erase(inputVector[x+4].begin(),inputVector[x+4].begin()+1);
        //  count++;  
        }
        else{
          pushString += inputVector[x+4][0];
          inputVector[x+4].erase(inputVector[x+4].begin(),inputVector[x+4].begin()+1);
          found = true;
          pushString.erase(pushString.end()-1,pushString.end());
          nextSteps.push_back(pushString);
        }
      }
    }
  }
}

void Converter::assignEverything(){
  int pullLocation = 0;
  for(int x = 0; x < statesNum; x++){
    for(int y = 0; y < alphabetSize; y++){
      if(y != alphabetSize -1){
        int temp;
        std::string str;
        std::stringstream stream;
        if (nextSteps[pullLocation] == "")
          str = "0";
        else
         str = nextSteps[pullLocation];
        stream.str(str);
        stream >> temp;
        intNextSteps.push_back(temp);
      }
      else{
        nextSteps[pullLocation].push_back(',');
        std::vector<int> vector;
        while(nextSteps[pullLocation].size() != 0){
          bool found = false;
          std::string tempString = "";
          int tempInt = 0;
            while(!found){
              if(nextSteps[pullLocation][0] != ','){
                tempString += nextSteps[pullLocation][0];
                nextSteps[pullLocation].erase(nextSteps[pullLocation].begin(),nextSteps[pullLocation].begin()+1);
              }
              else{
                nextSteps[pullLocation].erase(nextSteps[pullLocation].begin(),nextSteps[pullLocation].begin()+1);
                found = true;
                std::stringstream stream;
                stream.str(tempString);
                stream >> tempInt;
                vector.push_back(tempInt);
              }
              if(nextSteps[pullLocation].size() == 0)
                found = true;
            }
          }
          intEpsilonSteps.push_back(vector);
        }
      pullLocation++;
    }
  }
}


void Converter::readyGo(){
  std::vector<int> startState;
  std::vector<int> testState;

  startState.push_back(initialState);
  startState = eClose(startState,0);
  dfaStates.push_back(startState);
  std::cout << "E-closure(IO) = ";

  pV(dfaStates[0]);

  std::cout << " = 1" << std::endl;  
  mark(dfaStates[0],1);
}


std::vector<int> Converter::eClose(std::vector<int> &inputVector,int marker){
  int startPoint = inputVector[marker] -1;
  for(int x = marker ;x < inputVector.size();x++){
    if(intEpsilonSteps[startPoint][x] != 0){
      for(int y = 0; y < intEpsilonSteps[startPoint].size(); y++){
        if(intEpsilonSteps[startPoint][y] != 0){
        bool insert = true;
        for(int i = 0; i < inputVector.size(); i++){
          if(intEpsilonSteps[startPoint][y] == inputVector[i])
            insert = false;
        }
        if(insert){
          inputVector.push_back(intEpsilonSteps[startPoint][y]);
          eClose(inputVector,++x);
        }
        }
      }
    }
  }
  return inputVector;
}

void Converter::mark(std::vector<int> inputV,int marker){
  std::vector<int> startState;
  std::vector<int> flagVector;
  bool endState;
  bool insert;
  bool emptyStep;
  int flag;
  for(int x = 0; x < inputV.size(); x++){
    startState.push_back(inputV[x]);
  }
  int pullLocation;
  std::cout << "Mark " << marker << std::endl;
  for(int y = 0; y < alphabetSize - 1; y++){
    emptyStep = true;
    for(int x = 0; x < inputV.size(); x++){
      if(inputV[x] == 1)
        pullLocation = 0;
      else
        pullLocation = (inputV[x] * (alphabetSize -1)) - (alphabetSize -1);

      pullLocation += y;
      if(intNextSteps[pullLocation] != 0){
        flagVector.push_back(intNextSteps[pullLocation]);
        emptyStep = false;
      }
    }
    if(emptyStep)
      flagVector.push_back(0);
  } 

  for(int x = 0; x < alphabetSize -1; x++){
 
    if(flagVector[x] < (statesNum * (alphabetSize -1) )&& flagVector[x] != 0){
      endState = true;
      pV(inputV);
      std::cout << "--" << alphabetVector[x] << "--> {";
      std::cout << flagVector[x] << "}" << std::endl;
      std::cout << "E-Closure {" << flagVector[x] << "} = ";
      std::vector<int> tempVector;
      tempVector.push_back(flagVector[x]);
      tempVector = eClose(tempVector,0);
      pV(tempVector);
      
      // TEST///
/*      insert = false;
      //check every entry in dfa state table
      for(int a = 0; a < dfaStates.size(); a++){
      //compare each individual entry
        if(tempVector.size() == dfaStates[a].size()){
          for(int b = 0; b < dfaStates[a].size();b++){
            if(tempVector[b] != dfaStates[a][b]){
              insert = true;
            }
            else{
              insert = false;              
            }
          }
        }
        else
          insert = true;
        //if(!insert)
        //flag = a;
      }
      if(insert){
      dfaStates.push_back(tempVector);
      std::cout << " = " <<  dfaStates.size() << std::endl;
      dfaSteps.push_back(dfaStates.size());
      }
      else{
        std::cout << " = " << flag << std::endl;
        dfaSteps.push_back(flag);
      }*/
      // END TEST //
      // SORTA WORKS NEED TO IMPROVE//
      dfaStates.push_back(tempVector);
      dfaSteps.push_back(dfaStates.size());
      std::cout << " = " <<  dfaStates.size() << std::endl;
      //END SORTA WORKS //
      if(tempVector.size() == startState.size()){
        for(int z = 0; z < tempVector.size(); z++){
          if(tempVector[z] != startState[z])
            endState = false;
        }
      }
      else 
        endState = false;
    }
    else{
      dfaSteps.push_back(0);
    }

  }
  if(!endState){
    marker++;
    std::cout << std::endl;
    mark(dfaStates[marker-1],marker);
  }
  if(endState)
    dfaFinalStates = marker;
}

void Converter::wrapItUp(){
  int pullLocation;
  findDfaStartFinal();
  std::cout << "State     ";
  for(int z = 0; z < alphabetSize -1;z++){
    std::cout<<alphabetVector[z] << "     ";
  }
  std::cout<<std::endl;
  for(int x = 0; x < dfaStates.size(); x++){
    std::cout << x + 1 << "        {"; 
    for(int y = 0; y < alphabetSize -1; y++){
      pullLocation = (x * (alphabetSize -1)) + y;

      if(dfaSteps[pullLocation] == 0){
       std::cout << " }";

      }
      else{
       std::cout << dfaSteps[pullLocation] << "}";
      }
      if(y != alphabetSize - 2){
        std::cout << "   {"; 
      }
      else{
        std::cout << std::endl;
      }
    }
  }
}

void Converter::findDfaStartFinal(){
bool insert;
  for(int x = 0; x < dfaStates.size(); x++){
    for(int y = 0; y < dfaStates[x].size(); y++){
      if(initialState == dfaStates[x][y])
        initialState = x+1;
      for(int z = 0; z < dfaStates[dfaFinalStates].size(); z++){
        if(dfaStates[x].size() == dfaStates[dfaFinalStates].size())
          if(dfaStates[x][y] == dfaStates[dfaFinalStates][z])
            insert = true;
          for(int q = 0; q < dfaFinalVector.size(); q++){
              if(x - 1 == dfaFinalVector[q])
                insert = false;
              else
                insert = true;
            }
          if(insert)
            dfaFinalVector.push_back(x - 1);
      }
    }
  }
  std::cout << "Start State: {" << initialState <<"}" << std::endl;

  std::cout << "Final States: ";
  pV(dfaFinalVector);
  std::cout << std::endl;
}

//Just a helper function for printing out all the elements in a 1d vector
void Converter::pV(std::vector<int> iV){
  std::cout <<  "{";
  for(int x = 0; x < iV.size(); x++){
    std::cout << iV[x];
    if(x + 1 != iV.size())
      std::cout << ", ";
    else
      std::cout << "}";
  }
}





