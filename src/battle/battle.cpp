#include "battle.h"
#include "../utils/utils.hpp"
#include <termio.h>
#include <utility>
#include <string>



void battle_monster(int level,std::string name_ms){
    clearScreen();
    string name_mc;
//check the status
    //character name_mc or the image
    if (level >= 0 && level <= 3) {
        name_mc="apprentice";
    } else if (level >= 4 && level <= 7) {
        name_mc ="knight";
    } else if (level >= 8 && level <= 10) {
        name_mc ="master" ;
    } else {
        name_mc ="legendary"; // return -1 or throw an exception if level is out of range
    }
    //the monster to fight and skill status
    string monstername = name_ms;
    string skillname1 = "";
    string skillmp1 = "";
    string skillname2 = "";
    string skillmp2 = "";
    string skillname3 = "";
    string skillmp3 = "";
    string skillname4 = "";
    string skillmp4 = "";
    if (cha1.skill_status[0]==1){
        skillname1="recoverhit";
        skillmp1 = "MP: 3";
    }
    if (cha1.skill_status[0]==2){
        skillname1="bladestorm";
        skillmp2 = "MP: 4";
    }
    if (cha1.skill_status[1]==1){
        skillname2="Vengeance";
        //cha1.activate_vengeance;
    }
    if (cha1.skill_status[1]==2){
        skillname2="magicdraw";
        //cha1.activate_magicdraw;
    }
    if (cha1.skill_status[2]==1){
        skillname3="hellfire";
        skillmp3 ="MP: 1";
    }
    if (cha1.skill_status[2]==2){
        skillname3="Rage";
        skillmp3 ="MP: 7";
    }
    if (cha1.skill_status[3]==1){
        skillname4="doublecrit";
        //cha1.activate_doublecrit;
    }
    if (cha1.skill_status[3]==2){
        skillname4="ultimatedef";
        //cha1.activate_ultimatedef;
    }




//insert all status
    CharacterInsert(fight_map, ReadCharacters(filepath_ms, name_ms), position_ms);
    CharacterInsert(fight_map, ReadCharacters(filepath_mc, name_mc), position_mc);
    WordInsert_front(fight_map, name_mc, name_mc_p);//heroname is the players name name_mc is reading
    WordInsert(fight_map, monstername, name_ms_p);
    WordInsert(fight_map, skillname1, skill1_1);
    WordInsert(fight_map, skillmp1, skill1_2);
    WordInsert(fight_map, skillname2, skill2_1);
    WordInsert(fight_map, skillmp2, skill2_2);
    WordInsert(fight_map, skillname3, skill3_1);
    WordInsert(fight_map, skillmp3, skill3_2);
    WordInsert(fight_map, skillname4, skill4_1);
    WordInsert(fight_map, skillmp4, skill4_2);
    roundNumber = 0;
    NewRound(fight_map, roundNumber);
    StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
    //monster added later
    if (name_ms =="clone"){
        StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
        while (true){

            printMap(fight_map);
            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    clo1.hurt(cha1.normal_attack());
                    break;
                }
                if (in =='2'){

                if (cha1.skill_status[0]==1){
                    clo1.hurt(cha1.act_hellfire());
                    }
                if (cha1.skill_status[0]==2){
                    cha1.act_rage();
                }
                    //skill 2
                    break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        clo1.hurt(cha1.act_recoverhit());
                        }
                    if (cha1.skill_status[0]==2){
                        clo1.hurt(cha1.act_bladestorm());
                    }
                        //skill 1
                    break;
                }
            }
            cha1.hurt(clo1.normalAttack());
            clearScreen();
            WaitSecond(1);
            //one round finish
            //implement win or lose
            if (clo1.isAlive() == false){
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
        StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
        while (true){

            printMap(fight_map);
            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    rob1.hurt(cha1.normal_attack());
                    break;
                }
                if (in =='2'){

                    if (cha1.skill_status[0]==1){
                        rob1.hurt(cha1.act_hellfire());
                        }
                    if (cha1.skill_status[0]==2){
                        cha1.act_rage();
                    }
                        //skill 1
                        break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        rob1.hurt(cha1.act_recoverhit());
                        }
                    if (cha1.skill_status[0]==2){
                        rob1.hurt(cha1.act_bladestorm());
                    }
                        //skill 2
                    break;
                }
            }
            cha1.hurt(rob1.normalAttack());
            clearScreen();
            WaitSecond(1);
            //one round finish
            //implement win or lose
            if (rob1.isAlive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
        }
    }
        if (name_ms =="Cith"){
        StateInsert(fight_map, convertNumber(cit1.HP(), cit1.MP(), cit1.ATK()), state_ms);
        while (true){

            printMap(fight_map);
            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    cit1.hurt(cha1.normal_attack());
                    break;
                }
                if (in =='2'){

                if (cha1.skill_status[0]==1){
                    cit1.hurt(cha1.act_hellfire());
                    }
                if (cha1.skill_status[0]==2){
                    cha1.act_rage();
                }
                    //skill 1
                    break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        cit1.hurt(cha1.act_recoverhit());
                        }
                    if (cha1.skill_status[0]==2){
                        cit1.hurt(cha1.act_bladestorm());
                    }
                        //skill 2
                    break;
                }
            }
            cha1.hurt(cit1.normalAttack());
            clearScreen();
            WaitSecond(1);
            //one round finish
            //implement win or lose
            if (cit1.isAlive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(cit1.HP(), cit1.MP(), cit1.ATK()), state_ms);
        }
    }
    if (name_ms =="Mandalorains"){
        StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
        while (true){

            printMap(fight_map);
            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    man1.hurt(cha1.normal_attack());
                    break;
                }
                if (in =='2'){

                if (cha1.skill_status[0]==1){
                    man1.hurt(cha1.act_hellfire());
                    }
                if (cha1.skill_status[0]==2){
                    cha1.act_rage();
                }
                    //skill 2
                    break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        man1.hurt(cha1.act_recoverhit());
                        }
                    if (cha1.skill_status[0]==2){
                        man1.hurt(cha1.act_bladestorm());
                    }
                        //skill 1
                    break;
                }
            }
            cha1.hurt(man1.normalAttack());
            clearScreen();
            WaitSecond(1);
            //one round finish
            //implement win or lose
            if (man1.isAlive() == false){
                break;
            }
            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
        }
    }
}
// //test
