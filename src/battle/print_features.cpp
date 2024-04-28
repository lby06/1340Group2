#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include"print_features.h"

using namespace std;
//postion of the Character
vector<pair<int, int>> position_mc = {{5, 1}, {5, 27}, {15, 1}, {15, 27}};
vector<pair<int, int>> position_ms = {{5, 39}, {5, 65}, {15, 39}, {15, 65}};

//postion of numeric features
vector<pair<int, int>> state_mc = {{1, 8}};
vector<pair<int, int>> state_ms = {{1, 59}};
//postion of texts
vector<pair<int, int>> name_mc_p = {{3, 22},{3,32}};
vector<pair<int, int>> name_ms_p = {{3, 34},{3,50}};
vector<pair<int, int>> skill1_1 = {{18, 1},{18, 12}};
vector<pair<int, int>> skill1_2 = {{19, 1},{19, 12}};
vector<pair<int, int>> skill2_1 = {{18, 14},{18, 25}};
vector<pair<int, int>> skill2_2 = {{19, 14},{19, 25}};
vector<pair<int, int>> skill3_1 = {{18, 27},{18, 38}};
vector<pair<int, int>> skill3_2 = {{19, 27},{19, 38}};
vector<pair<int, int>> skill4_1 = {{18, 40},{18, 51}};
vector<pair<int, int>> skill4_2 = {{19, 40},{19, 51}};
vector<pair<int, int>> chabar = {{1, 13},{1, 30}};
vector<pair<int, int>> monbar = {{1, 35},{1, 52}};
string chat = ">-----------your turn------------<                                                                                  ";
string mont = "                                 >-------------charging-----------<                                                 ";
string hpbar= "=================";
vector<vector<pair<int, int>>> bc_rounds_p = {{{1, 67},{1, 70}},{{2, 67},{2, 70}},{{3, 67},{3, 70}},{{4, 67},{4, 70}},{{5, 67},{5, 70}}};
vector<vector<pair<int, int>>> bc_whos_p =   {{{1, 71},{1, 75}},{{2, 71},{2, 75}},{{3, 71},{3, 75}},{{4, 71},{4, 75}},{{5, 71},{5, 75}}};
vector<vector<pair<int, int>>> bc_hows_p =   {{{1, 76},{1, 84}},{{2, 76},{2, 84}},{{3, 76},{3, 84}},{{4, 76},{4, 84}},{{5, 76},{5, 84}}};
vector<vector<pair<int, int>>> bc_effects_p ={{{1, 87},{1, 115}},{{2, 87},{2, 115}},{{3, 87},{3, 115}},{{4, 87},{4, 115}},{{5, 87},{5, 115}}};
// vector<pair<int, int>> bc2 = ;
// vector<pair<int, int>> bc3 = ;
// vector<pair<int, int>> bc4 = ;
// vector<pair<int, int>> bc5 = ;
vector<vector<vector<pair<int, int>>>> bc_p = {bc_rounds_p,bc_whos_p,bc_hows_p,bc_effects_p};
vector<string> bc_rounds = {};
vector<string> bc_whos = {};
vector<string> bc_hows = {};
vector<string> bc_effects = {};
//a test for features
int roundNumber = 0;
//a test
string filepath_ms="data/animations/monsters_ASCii.txt";
string filepath_mc="data/animations/main_character_ASCii.txt";


//basic background for battle
vector<string> fight_map = {
    //map resolution :22*67
"-------------------------------Round    -------------------------------------boardcast------------------------------",
"| HP:  [   ][                 ]  |[                 ]HP:  [   ]   |   |    |          |                            |", 
"| MP:  [   ]                     |                   MP:  [   ]   |   |    |          |                            |",             
"| ATK: [   ]          Name:      |Name:              ATK: [   ]   |   |    |          |                            |", 
"|--------------------------------|--------------------------------|   |    |          |                            |",
"|                                |                                |   |    |          |                            |",
"|                                |                                |------------------------------------------------|",
"|                                |                                |ro-|atta|attack    |additional effects          |",
"|                                |                                |und|cker|method    |                            |",
"|                                |                                |num|    |          |                            |",
"|                                |                                |-------------------------------------------------",
"|                                |                                |                                                 ",
"|                                |                                |                                                 ",
"|                                |                                |                                                 ",
"|                                |                                |                                                 ",
"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                                                 ",
"|     01     *            *      02     *            *            |                                                 ",
"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                                                 ",
"*            *            *            *             * strike:[s] *                                                 ",
"*            *            *            *             * skill:[1/2]*                                                 ",
"*******************************************************************                                                 ",
"                                                                                                                    ", //line21
// "Press 1 or 2 to use the skills",
// "Press s for normal strike(in each round only one input allowed)"
};

// //read in names
// string readName() {
//     string name;
//     cout << "The name of character(test) ";
//     cin >> name;
//     return name;
// }
//testing how long the string is
// void printLineLengths(const vector<string>& lines) {
//     for (const auto& line : lines) {
//         cout << line << " " << line.length() << endl;
//     }
// }
// //measure postion of x,y to find the place to insert string
// void printPositions(const vector<string>& fight_map) {
//     for (int i = 0; i < fight_map.size(); ++i) {
//         for (int j = 0; j < fight_map[i].length(); ++j) {
//             if (fight_map[i][j] == 'x' || fight_map[i][j] == 'y') {
//                 cout << "Character '" << fight_map[i][j] << "' found at position (" << i << ", " << j << ")" << endl;
//             }
//         }
//     }
// }

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

//printing everything out
void printMap(const vector<string>& lines) {
    for (const string& line : lines) {
        for(int i = 0;i<line.length();i++)
        {
            cout << line[i] ;
        }
        cout << endl;
    }
}
//change some color when printing
int positionin(vector<vector<pair<int,int>>> positionpairs, pair<int,int> pos)
{
    for(int i = 0; i< positionpairs.size(); i++)
    {
        if(positionpairs[i][0] == pos){return 1;}
        else if(positionpairs[i][1] == pos){return -1;}
    }
    return 0;
}

void printMap(const vector<string>& lines, vector<vector<pair<int,int>>> positionpairs) {
    for (int i = 0; i<lines.size();i++) {
        for(int j = 0;j<lines[i].length();j++)
        {
            if(positionin(positionpairs, make_pair(i,j)) == 1){cout << "\033[91;1m";}
            if(positionin(positionpairs, make_pair(i,j)) == -1){cout << "\033[0m";}
            cout << lines[i][j] ;
        }
        cout << endl;
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
//insert word and fill the empty space with " "
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
//To make formate symmetric, fill " " and insert word afterward
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

//add roundnumer
void NewRound(vector<string>& fight_map,int& roundNumber) {//need implement
    string& roundLine = fight_map[0]; 
    roundNumber++; 
    ostringstream newRoundNumberStr;
    newRoundNumberStr << setw(3) << setfill('0') << roundNumber; 
    roundLine.replace(37, 3, newRoundNumberStr.str()); 
}
//clean the whole screen
void clearScreen() {
        system("clear");
}
//stop for SleepTime seconds
void WaitSecond(int SleepTime) {
    sleep(SleepTime);
}

void TurnInsert(vector<string> & map, string word)
{
    map[21] = word;
    return;
}

void stringratio(string & line, int hpmax, int hp,string name)
{
    //if(hp > hpmax){cout << "caonima" <<endl;return;}
    int remain;
    if(hp >hpmax){remain = hpmax;}
    else{remain = (line.length()*hp/hpmax);}
    for(int i = 0; i < remain;i++)
    {
        line[i] = '=';
    }
    for(int i = remain;i < line.length();i++)
    {
        line[i] = ' ';
    }
    if(name != "cha")
    {
        string temp = line;
        for(int i = 0; i < line.length();i++)
        {
            line[i] = temp[line.length()-i-1];
        }
    }
    return;
}


void appendword(vector<string> & words, string word,int limit)
{
    vector <string> temp = words;
    if(words.size() < limit){words.push_back(word);}
    else
    {
        for(int i = 0;i<words.size()-1;i++)
        {
            words[i] = temp[i+1];
        }
        words[words.size()-1] = word;
    }
    return;
}

void clear(vector<string> & words)
{
    words = {};
    return;
}

void wordsinsert (vector<string>& fight_map, const vector<vector<string>> & words, vector<vector<vector<pair<int, int>>>> positionpairs)
{
    if(words[0].size() > positionpairs[0].size()){cout << "there may be some error"<<endl;}
    else
    {
        for(int i = 0 ; i< words.size();i++)
        {
            for(int j = 0; j<words[0].size();j++)
            {
            WordInsert(fight_map,words[i][j],positionpairs[i][j]);
            }
        }
    }
    return;
}

string some(vector <string> strings)
{
    for(int i =0; i < strings.size();i++)
    {
        if(strings[i] != "")
        {
            return strings[i];
        }
    }
    return "None";
}


// int main()
// {
//     stringratio(hpbar,3,1);
//     cout  << hpba
// }






