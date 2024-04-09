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
int upgrade(string name1,string name2,int level);

void clearScreen();
string appendspace(string line,int length);
vector<string> getpaint(string filename,string target,int line_number,int length);
vector<string> merge(vector<vector<string>> vectors,int line_number,int length);
vector<string> selectframe(vector<string> input, int line,int col);
vector<vector<string>>makematrix(vector<string> before, vector<string> upgrading, vector<string> upgraded, vector<string> after,int length,int line);
void printvector(vector<string> vector);
void printvectorwithcolor(vector<string> vector, string color, string reset);
int printmatrix(vector<vector<string>> matrix, string color,bool trigger);
vector<vector<string>> fromtoto (vector<vector<string>> generater, vector<string> toframe );
int make (vector<vector<vector<string>>> generaters, vector<string> Upgraded, vector<string> Upgrading, vector<string> toframe,vector<string> chooseframe, int level, int line_num, int col_num,int line__);
void insert (vector <string> & frame, string name, pair<int,int> position);
void upgrade();
int UPGRADE(int level, string name1,string name2);





#endif  
