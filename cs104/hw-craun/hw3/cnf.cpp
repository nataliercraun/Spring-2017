#include "cnf.h"
using namespace std;

/**
 * Helper function to take the absolute value of an integer
 */
int intabs(int a)
{
    if(a < 0) return -a;
    return a;
}


Clause::Clause() : isTrue_(false)
{
}

Clause::Clause(const vector<int>& vars)
    : vars_(vars), isTrue_(false)
{

}
int Clause::eval(std::map<int,int>& varValues)
{
    /* You complete */

   //varValues map with key=variable ID and
   //value = {UNK, VAL0, or VAL1}

   // ONLY ONE OF THE CLAUSES VARS NEEDS TO BE TRUE TO EVAL TO TRUE 

   vector<int>::iterator var_it; // iterator for the clause 
   bool sat = false; 

   for (var_it = vars_.begin(); var_it != vars_.end(); ++var_it) { // iterates through vector of ints repping the vars in each clause 

      int temp = intabs(*var_it); 

      if ( (varValues.find(temp)->second == VAL0 && *var_it < 0) || 
           (varValues.find(temp)->second == VAL1 && *var_it > 0) ) {
         sat = true; 
      }   
   } 

   if (isTrue_ && sat) {
      return 0; // clause satisfaction does not change 
   }

   else if (!isTrue_ && !sat) {
      return 0; // clause satisfaction does not change 
   }

   else if (!isTrue_ && sat) {
      isTrue_ = true; // update clause satisfaction to true
      return 1; 
   }

   else {
      isTrue_ = false; // update clause satisfaction to false 
      return -1; 
   }

}


CNFFormula::CNFFormula(int nVars, const vector<Clause*>& clauses)
    : clauses_(clauses), numSatisfied_(0)
{
   /* You complete */
   // build the ADDITIONAL MAP HERE

   for (int k = 1; k <= nVars; k++) {

      set<Clause*> temp; // temporary set to be added to the map

      for (unsigned int i = 0; i < clauses.size(); i++) { 

         vector<int> tempvars = clauses[i]->vars(); 

         for (unsigned int j = 0; j < tempvars.size(); j++) { 

            if (intabs(tempvars[j]) == k) {
               temp.insert(clauses[i]); 
            }    

         }
      }

      varToClauses_.insert( make_pair(k, temp) ); 
   }

   // set all values in varValues_ map to UNK 

   for (int j = 1; j <= nVars; j++) { // loops through given # of vars beginning at 1; 0 is not a variable option 
      varValues_.insert( make_pair(j, UNK) ); // places vars in map and sets all var values to unknown 
   }
}

CNFFormula::~CNFFormula()
{
    for (unsigned int i = 0; i < clauses_.size(); i++) {
      delete clauses_[i]; 
    }
}

bool CNFFormula::isSatisfied() const
{
    return numSatisfied_ == clauses_.size();
}

void CNFFormula::printVarValues() const
{
    /* You complete */

   map<int, int>::const_iterator it; 

   for (it = varValues_.begin(); it != varValues_.end(); ++it) {
      cout << "Var " << it->first << " : "; 
      if (it->second == UNK) {
         cout << "Unassigned" << endl;  
      }
      else {
         cout << it->second << endl;
      }
   }
}

void CNFFormula::assignVar(int var, int val)
{
    /* You complete */
   map<int, set<Clause*> >::iterator it; 
   varValues_[var] = val; // changes value in master map based on user input 
   it = varToClauses_.find(var); // iterator pointing at the set of clauses that contain the given variable 

   set<Clause*> temp = it->second; // temporary set that has the clauses that contain the given variable 
   set<Clause*>::iterator set_it; // iterator to move through this set of clauses 

   for (set_it = temp.begin(); set_it != temp.end(); ++set_it) { // loops through the set of clauses 

      Clause* temp_clause = *set_it; // temporary pointer to a clause in the set 
      int check = temp_clause->eval(varValues_); // evaluate the clause with the updated master map 

      if (check == -1) {
         numSatisfied_--; 
      }
      if (check == 1) {
         numSatisfied_++; 
      }
   }
}

