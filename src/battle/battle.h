#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "monster.h"
#include "print_features.h"
#include <string>

//call battle_monster when encountering monster.
//name_mc for ASCii of different level, name_ms for type of monster to fight with
int readKeyboard();
void battle_monster(int level,std::string name_ms);

#endif // BATTLE_H
