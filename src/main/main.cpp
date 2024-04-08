#include "../battle/print_features.h"
#include "../character/boss.h"
#include "../character/character.h"
#include "../character/monster.h"
#include <iostream>
//目前仅供测试用
//已实现将主角数据传入战斗界面
int main() {
	string name_mc = readName();
	string name_ms = readName();

	// Insert the characters and their stats into the map
	CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc),
					position_mc);
	CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms),
					position_ms);
	cha1.reset();
	cha1.display();

	for (int i = 0; i <= 3; i++) {
		cha1.upgrade();
		cout << endl;
		cha1.display();
	}
	cout << endl;
	NewRound(fight_map, roundNumber);

	printMap(fight_map);

	cha1.hurt(20);
	NewRound(fight_map, roundNumber);
	printMap(fight_map);

	// cha1.display();
	cout << endl;
	cha1.activate_recoverhit();
	skillname1 = "ultimatedef";
	cout << cha1.act_recoverhit();
	NewRound(fight_map, roundNumber);
	printMap(fight_map);
	cout << endl;
	// cha1.display();
	cout << endl;
	cha1.mp_recover(0);
	NewRound(fight_map, roundNumber);
	printMap(fight_map);
	cha1.activate_rage();
	skillname2 = "vegenance";
	cha1.act_rage();
	cha1.display();
	NewRound(fight_map, roundNumber);
	printMap(fight_map);
	cout << endl;
	cha1.activate_doublecrit();
	skillname3 = "doublecrit";
	NewRound(fight_map, roundNumber);
	printMap(fight_map);

	return 0;
}
//战斗过程
//传入doublecrit
