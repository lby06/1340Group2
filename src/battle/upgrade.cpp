#include <iostream>
#include "battle_upgrade.h"
#include "./../character/character.h"

vector<pair<string,string>> names = 
{
    make_pair("recoverhit (Active Skill)","bladestorm (Active Skill)"),
    make_pair("vengeance (Passive Skill)","magicdraw (Passive Skill)"),
    make_pair("hellfire (Active Skill)","rage (Active Skill)"),
    make_pair("doublecrit (Passive Skill)","ultimatedef (Passive Skill)")
  
};
vector<pair<string,string>> description = 
{
    make_pair("restore HP after attacking","more damage to a certain enemy"),
    make_pair("restore HP after being attacked","restore MP after using skills"),
    make_pair("Cost more MP to get more attack","Strengthen the next two basic attacks"),
    make_pair("chance for double ctritical hit","restore attributes after getting hurt")
};

// vector<pair<void (*)(),void(*)()>> activate_funs =
// {
//     make_pair(main_character::activate_recoverhit,main_character::activate_bladestorm),
//     make_pair(main_character::activate_vengeance,main_character::activate_magicdraw),
//     make_pair(main_character::activate_hellfire,main_character::activate_rage),
//     make_pair(main_character::activate_doublecrit,main_character::activate_ultimatedef)
// }





// int main()
// {
//     cout << "which level you are now?" <<endl;
//     string name1,name2;
//     int level;
//     cin >> level;
//     name1 = names[level].first;
//     name2 = names[level].second;
//     int choice = UPGRADE(level);
//     cout << "your choice is: " << choice << endl;
// }

int main() {
	int level;
	cin >> level;
	activate(level);
}

