#include "battle.h"


void battle_monster(std::string name_mc,std::string name_ms){
    /*
    use start_battle when encountering monster/boss
    1.read in which character is going to battle with each other
    2.battle by round  under is_alive situation //needs to implement output function 
    3.
    */
    //if clone    need to implement ohter
//step1.1 encounter monster
    if (name_ms =="clone"){
        CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);
    //step1.2 fill in character state
        CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
        roundNumber = 0;
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
    //2.keep battling by rounds
        while (true){
            //a round start
            printMap(fight_map);

            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();

                if (in == 's' ) {
                    clo1.hurt(cha1.normal_attack());
                    break;
                }
                //implement here
                /*
                1.skills need implement
                2.info function
                */
            }
            cha1.hurt(clo1.normalattack());
            clearScreen();
            WaitSecond(1);
            //one round finish

            //implement win or lose
            if (clo1.is_alive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }

            //refresh status and round number
            NewRound(fight_map, roundNumber);
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
        }
    }
    

 if (name_ms =="Robot"){
        CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);
    //step1.2 fill in character state
        CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
        roundNumber = 0;
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
    //2.keep battling by rounds
        while (true){
            printMap(fight_map);
            char in;
            while (true) {
                in = readKeyboard();

                if (in == 's' ) {
                    rob1.hurt(cha1.normal_attack());
                    break;
                }
                //implement here
            }

            cha1.hurt(rob1.normalattack());
            clearScreen();
            WaitSecond(1);
            if (rob1.is_alive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            NewRound(fight_map, roundNumber);
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
        }
    }
    
 if (name_ms =="Cith"){
        CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);
    //step1.2 fill in character state
        CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
        roundNumber = 0;
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(cit1.HP(), cit1.MP(), cit1.ATK()), state_ms);
    //2.keep battling by rounds
        while (true){
            printMap(fight_map);            
            char in;
            while (true) {
                in = readKeyboard();

                if (in == 's' ) {
                    cit1.hurt(cha1.normal_attack());
                    break;
                }
                //implement here
            }

            cha1.hurt(cit1.normalattack());
            clearScreen();
            WaitSecond(1);
            if (cit1.is_alive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            NewRound(fight_map, roundNumber);
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(cit1.HP(), cit1.MP(), cit1.ATK()), state_ms);
        }
    }
     if (name_ms =="Mandalorains"){
        CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);
    //step1.2 fill in character state
        CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
        roundNumber = 0;
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
    //2.keep battling by rounds
        while (true){
            printMap(fight_map);
            char in;
            while (true) {
                in = readKeyboard();

                if (in == 's' ) {
                    man1.hurt(cha1.normal_attack());
                    break;
                }
                //implement here
            }
            cha1.hurt(man1.normalattack());
            clearScreen();
            //WaitSecond(1);
            if (man1.is_alive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            NewRound(fight_map, roundNumber);
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
        }
    }
}    

// void refresh_state(){
//     /*
//     when battle ends,if exp is enough, upgrade and maybe choose skills
//     lose output defeat

//     */
//     return 0;
// }

//test
// int main() {
//     string name_mc = readName();
//     string name_ms =readName();
//     cha1.reset();
//     cha1.upgrade();
//     cha1.upgrade();
//     cha1.upgrade();
//     clo1.reset(1,1);
//     battle_monster(name_ms);
//     return 0;
// }
