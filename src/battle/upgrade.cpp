#include <iostream>
#include "battle_upgrade.h"
#include "./../character/character.h"

vector<pair<string,string>> names = 
{
    make_pair("ac1.1","ac1.2"),
    make_pair("ac2.1","ac2.2"),
    make_pair("pa3.1","pa3.2"),
    make_pair("pa4.1","pa4.2")
  
};
vector<pair<string,string>> description = 
{
    make_pair("des1.1","des1.2"),
    make_pair("des2.1","des2.2"),
    make_pair("des3.1","des3.2"),
    make_pair("des4.1","des4.2")
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

