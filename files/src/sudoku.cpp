/**
 * @brief Sudoku class implementation
 */

#include <string>
#include <fstream>
#include "sudoku.hpp"
#include <sstream>

Sudoku::Sudoku(string infile){
    
    string line;
    ifstream file;
    string holder;
    stringstream ss;
    
    for (int i=0;i<6;i++)
        cell.push_back(vector<grid>(6)); //intialize 2dvector
    
    
    file.open(infile);
    
    
    if (file.is_open()){
        
        for (int i = 0; i < 6; i++){
            getline(file, line);
            ss << line;
            for (int j = 0; j < 6; j++)
            {
                ss >> holder;
                //cout << line << endl;
                
                if (holder.size()==1) {
                    
                    cell[i][j].one = true;
                    if (holder=="-")
                        cell[i][j].top=0;
                    
                    else
                        cell[i][j].top=holder[0] - 48;
                    // cout << holder;
                    
                }
                
                
                
                else if (holder.size()==3){
                    cell[i][j].three = true;
                    if (holder[0] == '-')
                        cell[i][j].top=0;
                    
                    else
                        cell[i][j].top=holder[0] - 48;
                    
                    
                    if (holder[2] == '-')
                        cell[i][j].bottom=0;
                    
                    else
                        cell[i][j].bottom=holder[2] - 48;
                    
                }
            }
            
            ss.str("");
            ss.clear();
            holder="";
            holder.clear();
        }
        
    }
}


void Sudoku::Save(string filename){
    
    std::ofstream f(filename);
    
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++)
        {
            if (cell[i][j].one==true) {
                f << cell[i][j].top<<" ";
            }
            else if (cell[i][j].three==true){
                f << cell[i][j].top << "/" << cell[i][j].bottom << " ";
            }
        }
        cout << '\n';
    }
}

// Put documentation here
bool Sudoku::Solve(){
    int c,r;
    
    int x = 0;
    int y = 0;
    
    
    if (!locate_unsolved(r, c))
        return true; //done
    
    
    
    
    for (int i = 1; i<=9; i++)
    {
        // cout << cell[0][0].bottom;
        if (valid_entry(r,c,i))
        {
            //cout << "Issss";
            if(cell[r][c].top==0 && cell[r][c].bottom==0)
            {
                cell[r][c].top=i;
                x++;
            }
            
            
            if(cell[r][c].top>0 && cell[r][c].bottom==0 && x == 0)
            {
                if (i>cell[r][c].top) {
                    cell[r][c].bottom=i;
                    y++;
                }
                else
                    continue;
            }
            
            
            if(cell[r][c].top==0 && cell[r][c].bottom>0)
            {
                
                if (i<cell[r][c].bottom)
                {
                    cell[r][c].top=i;
                    x++;
                }
                else
                    continue;
            }
            
            if(cell[r][c].one==true)
            {
                cell[r][c].top=i;
                x++;
            }
            
            
            if (Solve())
                return true;
            
            
            if (x>0)
                cell[r][c].top=0;
            
            if (y>0)
                cell[r][c].bottom=0;
        }
        
        x=0;
        y=0;
        
        
    }
    return false;
    
}


// Put documentation here
bool Sudoku::locate_unsolved(int & r, int & c){
    for (r = 0; r<6; r++)
        for (c = 0; c<6; c++)
            if(cell[r][c].top==0 || cell[r][c].bottom == 0){
                return true;
            }
    return false;
}

// Put documentation here
bool Sudoku::valid_row(int r, int val)
{
    
    for (int i = 0; i < 6; i++)
        if (cell[r][i].top==val || cell[r][i].bottom==val)
            return true;
    return false;
    
}

// Put documentation here
bool Sudoku::valid_col(int c, int val)
{
    
    for (int i = 0; i < 6; i++)
        if (cell[i][c].top==val || cell[i][c].bottom==val)
            return true;
    return false;
    
    
}

// Put documentation here
bool Sudoku::valid_box(int r, int c, int val){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            if (cell[i+r][j+c].top==val || cell[i+r][j+c].bottom==val)
                return true;
    return false;
}

// Put documentation here
bool Sudoku::valid_entry(int r, int c, int val){
    
    return !valid_row(r, val) && !valid_col(c, val) && !valid_box(r - (r % 2), c - (c % 3), val);
    
}

// Put documentation here
std::ostream & operator<<(std::ostream & out, Sudoku & sdku){
    
    
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++)
        {
            if (sdku.cell[i][j].one==true) {
                out << sdku.cell[i][j].top<<" ";
            }
            else if (sdku.cell[i][j].three==true){
                out << sdku.cell[i][j].top << "/" << sdku.cell[i][j].bottom << " ";
            }
        }
        out << '\n';
    }
    return out;
}
