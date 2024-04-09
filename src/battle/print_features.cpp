#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include"print_features.h"
#include"../character/character.h"
#include"../character/monster.h"
#include"../character/boss.h"
using namespace std;
//postion of the Character
vector<pair<int, int>> position_mc = {{5, 1}, {5, 27}, {15, 1}, {15, 27}};
vector<pair<int, int>> position_ms = {{5, 39}, {5, 65}, {15, 39}, {15, 65}};

//postion of numeric features
vector<pair<int, int>> state_mc = {{1, 8}};
vector<pair<int, int>> state_ms = {{1, 59}};
//postion of texts
vector<pair<int, int>> name_mc_p = {{3, 22},{3,32}};
vector<pair<int, int>> name_ms_p = {{3, 35},{3,45}};
vector<pair<int, int>> boardcast_p1 = {{15, 2},{15,32}};
vector<pair<int, int>> boardcast_p2 = {{15, 34},{15,65}};

vector<pair<int, int>> skill1_1 = {{17, 1},{17, 12}};
vector<pair<int, int>> skill1_2 = {{18, 1},{18, 12}};
vector<pair<int, int>> skill2_1 = {{17, 14},{17, 25}};
vector<pair<int, int>> skill2_2 = {{18, 14},{18, 25}};
vector<pair<int, int>> skill3_1 = {{17, 27},{17, 38}};
vector<pair<int, int>> skill3_2 = {{18, 27},{18, 38}};
vector<pair<int, int>> skill4_1 = {{17, 40},{17, 51}};
vector<pair<int, int>> skill4_2 = {{18, 40},{18, 51}};

//a test for features
int Round =1,HP1=2,HP2=500,MP1=232,MP2=32,ATK1=321,ATK2=52;
int roundNumber = 0;
//a test
string filepath_ms="./1340Group2/data/animations/monsters_ASCii.txt";
string filepath_mc="./1340Group2/data/animations/main_character_ASCii.txt";
int line_number = 23;
int col_number = 77;

//basic background for battle
vector<string> fight_map = {
    //map resolution :22*67
"-------------------------------Round    ---------------------------",
"| HP:  [   ]                     |                   HP:  [   ]   |", 
"| MP:  [   ]                     |                   MP:  [   ]   |",             
"| ATK: [   ]          Name:[    ]|Name:[    ]        ATK: [   ]   |", 
"|--------------------------------|--------------------------------|",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|                                |                                |",
"|[                              ][                               ]|",
"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
"*            *            *            *             * Strike(S)  *",
"*            *            *            *             * Info(I)    *",
"*******************************************************************"
};

//read in names
string readName() {
    string name;
    cout << "The name of character(test) ";
    cin >> name;
    return name;
}

//Store the ASCii art of the character
vector<string> ReadCharacters(const string& filePath, string name) {
    ifstream file(filePath);
    if (!file) {
        cerr << "Unable to open file " << filePath << endl;
        exit(1);
    }

    vector<string> lines;
    string line;
    bool startReading = false;
    int count = 0;
    while (getline(file, line)) {
        if (line == name) {
            startReading = true;
            continue;
        }
        if (startReading && count < 10) {
            if (line.size() < 26) {
                line.append(26 - line.size(), ' ');
            } else {
                line = line.substr(0, 26);
            }
            lines.push_back(line);
            count++;
        }
    }

    file.close();
    return lines;
}

//testing how lone the string is
void printLineLengths(const vector<string>& lines) {
    for (const auto& line : lines) {
        cout << line << " " << line.length() << endl;
    }
}
//measure postion of x,y to find the place to insert string
void printPositions(const vector<string>& fight_map) {
    for (int i = 0; i < fight_map.size(); ++i) {
        for (int j = 0; j < fight_map[i].length(); ++j) {
            if (fight_map[i][j] == 'x' || fight_map[i][j] == 'y') {
                cout << "Character '" << fight_map[i][j] << "' found at position (" << i << ", " << j << ")" << endl;
            }
        }
    }
}
//printing everything by lines
void printMap(const vector<string>& lines) {
    for (const auto& line : lines) {
        cout << line << endl;
    }
}
//inserting the character in
void CharacterInsert(vector<string>& fight_map, const vector<string>& lines,vector<pair<int, int>> positions) {

    int startRow = positions[0].first;
    int endRow = positions[2].first;
    int startCol = positions[0].second;
    int endCol = positions[1].second;

    for (int i = startRow, lineIndex = 0; i <= endRow && lineIndex < lines.size(); ++i, ++lineIndex) {
        fight_map[i].replace(startCol, endCol - startCol, lines[lineIndex]);
    }
}
//converting the numbers

string convertNumber(int HP, int MP, int ATK) {
    ostringstream strs;
    strs << fixed << setprecision(0) << setw(3) << setfill('0') << HP 
         << setw(3) << setfill('0') << MP 
         << setw(3) << setfill('0') << ATK;
    return strs.str();
}
//insert HP/MP/ATK
void StateInsert(vector<string>& fight_map, string number,vector<pair<int, int>> positions) {

    int start_row = positions[0].first;
    int start_col = positions[0].second;
    for(int i = 0; i < 3; i++) {
            string part = number.substr(i*3, 3);
            fight_map[start_row + i].replace(start_col, 3, part);
        }
    }
void WordInsert(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions) {
    int start_row = positions[0].first;
    int start_col = positions[0].second;
    int end_col   = positions[1].second;

    string ExpendWord = word;
    int wordLength = word.length();
    int spaceLength = end_col - start_col;
    if (wordLength < spaceLength) {
        ExpendWord.append(spaceLength - wordLength, ' ');
    }

    fight_map[start_row].replace(start_col, spaceLength, ExpendWord);
}
void WordInsert_front(vector<string>& fight_map, const string& word, vector<pair<int, int>> positions) {
    int start_row = positions[0].first;
    int start_col = positions[0].second;
    int end_col   = positions[1].second;

    string ExpendWord = word;
    int wordLength = word.length();
    int spaceLength = end_col - start_col;
    if (wordLength < spaceLength) {
        ExpendWord.insert(0, spaceLength - wordLength, ' ');
    }

    fight_map[start_row].replace(start_col, spaceLength, ExpendWord);
}
void Includeword() {
    WordInsert_front(fight_map, heroname, name_mc_p);
    WordInsert(fight_map, monstername, name_ms_p);
    WordInsert(fight_map, boardcast_word1, boardcast_p1);
    WordInsert(fight_map, boardcast_word2, boardcast_p2);
    WordInsert(fight_map, skillname1, skill1_1);
    WordInsert(fight_map, skillmp1, skill1_2);
    WordInsert(fight_map, skillname2, skill2_1);
    WordInsert(fight_map, skillmp2, skill2_2);
    WordInsert(fight_map, skillname3, skill3_1);
    WordInsert(fight_map, skillmp3, skill3_2);
    WordInsert(fight_map, skillname4, skill4_1);
    WordInsert(fight_map, skillmp4, skill4_2);
}

void NewRound(vector<string>& fight_map,int& roundNumber) {//need implement
    Includeword();
    string& roundLine = fight_map[0]; 
    roundNumber++; 
    ostringstream newRoundNumberStr;
    newRoundNumberStr << setw(3) << setfill('0') << roundNumber; 
    roundLine.replace(37, 3, newRoundNumberStr.str()); 
}
void clearScreen() {
        system("clear");
}
void WaitSecond(int SleepTime) {
    sleep(SleepTime);
}
