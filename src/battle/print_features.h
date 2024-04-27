#ifndef PRINT_FEATURES_H
#define PRINT_FEATURES_H

#include <vector>
#include <string>
#include <utility>

using namespace std;
//the insert loaction for texts
extern vector<pair<int, int>> position_mc, position_ms, state_mc, state_ms;
extern vector<pair<int, int>> name_mc_p, name_ms_p, boardcast_p1,boardcast_p2;
extern vector<pair<int, int>> skill1_1, skill1_2, skill2_1, skill2_2;
extern vector<pair<int, int>> skill3_1, skill3_2, skill4_1, skill4_2;
extern vector<pair<int, int>> chabar, monbar;
extern vector<vector<pair<int, int>>> bc_rounds_p,bc_whos_p,bc_hows_p,bc_effects_p;
extern vector<vector<vector<pair<int, int>>>> bc_p;
extern vector<string> bc_rounds,bc_whos,bc_hows,bc_effects;
//tests

//used in main or files to faciliate the printing progress
extern int roundNumber;
extern string filepath_ms, filepath_mc;
extern vector<string> fight_map;

extern string chat;
extern string mont;
//extern string hpbar;
//test function
// string readName();//insert name
// void printLineLengths(const vector<string>& lines);//print length
// void printPositions(const vector<string>& fight_map);// locate x,y

//reads in ASCii of characters
vector<string> ReadCharacters(const string& filePath,string name);
//inserts the characters
void CharacterInsert(vector<string>& fight_map, const vector<string>& lines, vector<pair<int, int>> positions);

//printout the fight_map
void printMap(const vector<string>& lines);
void printMap(const vector<string>& lines, vector<vector<pair<int,int>>> positionpairs);

// formate the int to string i.e. 1 --> "001"
string convertNumber(int HP, int MP, int ATK);
//insert all the numeric states in
void StateInsert(vector<string>& fight_map, string number, vector<pair<int, int>> positions);
//insert word and fill spaces

void WordInsert(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions);
//insert word after spaces in front to be symmetric
void WordInsert_front(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions);

//call NewRound to change roundnumber
void NewRound(vector<string>& fight_map, int& roundNumber);

//clean the screen
void clearScreen();
//wait for SleepTime seconds 
void WaitSecond(int SleepTime);
// add the information of who attack
void TurnInsert(vector<string> & map, string word);

void stringratio(string & line, int hpmax, int hp,string name);

void wordsinsert (vector<string>& fight_map, const vector<vector<string>> & words, vector<vector<vector<pair<int, int>>>> positionpairs);

void appendword(vector<string> & words, string word,int limit);
void clear(vector<string> & words);

#endif // PRINT_FEATURES_H
