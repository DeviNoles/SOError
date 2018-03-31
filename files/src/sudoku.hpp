/**
 * @brief Sudoku class declaration, your implementation is up to you.
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Sudoku{
private:
    
    // Helper functions if you need them, declare/implement more if needed...
    bool valid_col(int, int);
    bool valid_row(int, int);
    bool valid_box(int, int, int);
    bool valid_entry(int, int, int);
    bool locate_unsolved(int &, int &);
    
    
public:
    void print();
    // Required functions
    Sudoku(std::string);
    bool Solve();
    void Save(std::string);
    friend std::ostream & operator<<(std::ostream &, Sudoku &);
    struct grid
    {
        bool three = false;
        bool one = false;
        int bottom = 0;
        int top;
    };
    vector<vector<grid> > cell;
};

#endif
