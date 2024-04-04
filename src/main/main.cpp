#include "print_features.h"
#include "character.h"
#include <iostream>
//目前仅供测试用
//已实现将主角数据传入战斗界面
int main() {
  cha1.reset();
  cha1.display();
  for (int i=0;i<=3;i++)
  {
      cha1.upgrade();
      cout<<endl;
      cha1.display();
  }
  cout<<endl;
  cha1.hurt(20);
  cha1.display();
  cout<<endl;
  cha1.activate_recoverhit();
  cout<<cha1.act_recoverhit();
  cout<<endl;
  cha1.display();
  cout<<endl;
  cha1.mp_recover(0);
  cha1.activate_rage();
  cha1.act_rage();
  cha1.display();
  cout<<endl;
  cha1.activate_doublecrit();

    // Read the names of the characters
    string name_mc = readName();
    string name_ms = readName();

    // Insert the characters and their stats into the map
    CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
    CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);


    for (int i = 0; i < 11; i++) {
        NewRound(fight_map, roundNumber);
        clearScreen();
        waitOneSecond();
        printMap(fight_map);
     //printPositions(fight_map);
        waitOneSecond();
    }

    return 0;
}
