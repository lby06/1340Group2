// upgrade.h
// call function: upgrade() in main.cpp to show the animation of upgrading

#ifndef BATTLE_UPGRADE_H  
#define BATTLE_UPGRADE_H
#include <iostream>
#include "string"
#include <vector>

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
using namespace std;
void upgrade();

void clearScreen();
string appendspace(string line,int length);
vector<string> getpaint(string filename,string target,int line_number,int length);
vector<string> merge(vector<vector<string>> vectors,int line_number,int length);
vector<string> selectframe(vector<string> input, int line,int col);
vector<vector<string>>makematrix(vector<string> before, vector<string> upgrading, vector<string> upgraded, vector<string> after,int length,int line);
void printvector(vector<string> vector);
void printvectorwithcolor(vector<string> vector, string color, string reset);
void printmatrix(vector<vector<string>> matrix, string color);
vector<vector<string>> fromtoto (vector<vector<string>> generater, vector<string> toframe );
vector<vector<string>> make (vector<vector<vector<string>>> generaters, vector<string> Upgraded, vector<string> Upgrading, vector<string> toframe, int level, int line_num, int col_num,int line__);






#endif  
