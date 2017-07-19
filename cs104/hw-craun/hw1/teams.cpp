#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
       const string* team2,
       int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

void teams(string* names, string* t1, string* t2, int size, int t1curr, int t2curr, 
           int index) {

  if (t2curr == size/2 && t1curr == size/2) {
    printSolution(t1, t2, size/2); 
  }

  else { 

    if (t1curr < size/2) {
      t1[t1curr] = names[index]; 
      teams(names, t1, t2, size, t1curr+1, t2curr, index+1);  
    }

    if (t2curr < size/2) {
      t2[t2curr] = names[index]; 
      teams(names, t1, t2, size, t1curr, t2curr+1, index+1); 
    }   
  }
}


int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  
  ifstream ifile(argv[1]);

  if(ifile.fail()){
    cerr << "Error" << endl;
    return 1;
  }

  int size;  
  ifile >> size;  
  string* names = new string[size];

  string check; 
  int count = 0; 

  while (ifile >> check) {

    if (count < size) {
      names[count] = check; 
    }

    count++; 
  }

  if (count != size) {
    cout << "Error" << endl; 
    return 1; 
  } 

  int t1curr = 0; 
  int t2curr = 0; 
  int index = 0; 

  string* t1 = new string[size/2]; 
  string* t2 = new string[size/2]; 

  teams(names, t1, t2, size, t1curr, t2curr, index); 

  delete[] names; 
  delete[] t1; 
  delete[] t2; 

  return 0;
}