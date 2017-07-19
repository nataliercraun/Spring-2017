#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
    bool placed; 
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
  return os << r.ID;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
  return os << p.first << "," << p.second;
}

void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}

bool allPlaced(InputMapType& input) {

    InputMapType::iterator it; 
    for (it = input.begin(); it != input.end(); ++it) {
        if (it->second.placed == false) {
            return false; 
        }
    }
    return true; 
}

bool isValid(vector<vector<bool> >& grid, int row, int col, InputMapType::iterator& it) {

    for (int i = row; i < it->second.length; i++) {
        for (int j = col; j < it->second.height; j++) {
            if (grid[i][j] == true) {
                return false; 
            } 
        }
    }
    return true; 
}

bool solve(vector<vector<bool> >& grid, InputMapType::iterator& it, InputMapType& input, OutputMapType& output, int row, int col) {
    
    if (it == input.end()) { 
        return true;  
    }

    else if ((unsigned)col == grid[0].size()) {

        if ((unsigned)row == grid.size()) {
            return false; 
        }
        return solve(grid, it, input, output, row + 1, 0); 
    }

    else {
        if (isValid(grid, row, col, it)) {
            flip(row, col, it->second, grid); 
            output.insert(make_pair(it->first, pair<int, int>(row, col))); 
            if (solve(grid, ++it, input, output, row, col+1)) {
                output.insert(make_pair(it->first, pair<int, int>(row, col))); 
                return true; 
            } 
            else {
                output.erase(it->first); 
            }
        }
        else {
            if (isValid(grid, col, row, it)) {
                flip(col, row, it->second, grid); 
                output.insert(make_pair(it->first, pair<int, int>(col, row))); 
                if (solve(grid, ++it, input, output, row, col+1)) {
                    output.insert(make_pair(it->first, pair<int, int>(col, row))); 
                    return true; 
                }
            }
            else {
                output.erase(it->first); 
            }
        }  
    }
    return false; 
} 

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
	    r.placed = false;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;
    
    for (int i = 0; i < n; i++)
    {
      grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here
    solution_exists = solve(grid, it, input, output, 0, 0); 

    if (!solution_exists) {
      ofile << "No solution found.";
    }
    else {
      printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}



