// print_features.h
#ifndef PRINT_FEATURES_H
#define PRINT_FEATURES_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

extern vector<pair<int, int>> position_mc, position_ms, state_mc, state_ms;
extern vector<pair<int, int>> name_mc_p, name_ms_p, boardcast_p1,boardcast_p2;
extern vector<pair<int, int>> skill1_1, skill1_2, skill2_1, skill2_2;
extern vector<pair<int, int>> skill3_1, skill3_2, skill4_1, skill4_2;

extern int Round, HP1, HP2, MP1, MP2, ATK1, ATK2;
extern int roundNumber;
extern string filepath_ms, filepath_mc;
extern int line_number, col_number;
extern vector<string> fight_map;

string readName();
vector<string> ReadCharacters(const string& filePath,string name);
void printLineLengths(const vector<string>& lines);
void printPositions(const vector<string>& fight_map);
void printMap(const vector<string>& lines);
void CharacterInsert(vector<string>& fight_map, const vector<string>& lines, vector<pair<int, int>> positions);
string convertNumber(int HP, int MP, int ATK);
void StateInsert(vector<string>& fight_map, string number, vector<pair<int, int>> positions);
void WordInsert(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions);
void WordInsert_front(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions);
void Includeword();
void NewRound(vector<string>& fight_map, int& roundNumber);
void clearScreen();
void WaitSecond(int SleepTime);

#endif // PRINT_FEATURES_H
