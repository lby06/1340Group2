#include "battle.h"
#include "../utils/utils.hpp"
#include <termio.h>
#include <utility>
#include <string>



void battle_monster(int level,std::string name_ms){
    // cout << cha_show_crit << " 1 " << cha_show_evasion << " 2 " << cha_show1 <<endl;
    // WaitSecond(1);
    vector <string> temp = fight_map;
    clear(bc_rounds);
    clear(bc_whos);
    clear(bc_hows);
    clear(bc_effects);
    clearScreen();
    string name_mc;
    string effect;
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
        skillmp1 = "MP: 4";
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
    string hpbar = "=================";
    WordInsert(fight_map, hpbar, chabar);
    WordInsert(fight_map, hpbar, monbar);
    string bc_round;
    string bc_who;
    string bc_how;
    string bc_effect;
    // WordInsert(fight_map, "placeforbd1", boardcast_p1);
    // WordInsert(fight_map, "bd2", boardcast_p2);

    
    roundNumber = 0;
    NewRound(fight_map, roundNumber);
    StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
    TurnInsert(fight_map,chat);
    //monster added later

    int chamax = cha1.HP();
    
    if (name_ms =="Clone"){
        StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
        int monmax = clo1.HP();
        while (true){
            printMap(fight_map,{chabar});
            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    clo1.hurt(cha1.normal_attack());
                    appendword(bc_hows,"strike",5);
                    
                    break;
                }
                if (in =='2'){

                if (cha1.skill_status[2]==1){
                    clo1.hurt(cha1.act_hellfire());
                    appendword(bc_hows,"hellfire",5);

                    }
                else if (cha1.skill_status[2]==2){
                    cha1.act_rage();
                    appendword(bc_hows,"rage",5);
                }
                else{
                    appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                }
                    //skill 2
                    break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        clo1.hurt(cha1.act_recoverhit());
                        appendword(bc_hows,"recover",5);
                        }
                    else if (cha1.skill_status[0]==2){
                        clo1.hurt(cha1.act_bladestorm());
                        appendword(bc_hows,"blade",5);
                    }
                    else{
                    appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }

                        //skill 1
                    break;
                }
            }
            if (clo1.isAlive() == false){
                break;
            }
            //string mon_effect = 
            clearScreen();
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
            stringratio(hpbar, monmax,clo1.HP()," ");
            WordInsert(fight_map,hpbar,monbar);
            TurnInsert(fight_map,mont);
            appendword(bc_rounds,std::to_string(roundNumber),5);
            appendword(bc_whos,"you",5);

            //when cha attack mon
            effect = some({cha_show_crit,mon_show_evasion,cha_show1,cha_show2});
            appendword(bc_effects,effect,5);
            cha_show_reset();
            mon_show_reset();

            wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
            printMap(fight_map, {monbar});
            WaitSecond(1);
            cha1.hurt(clo1.normalAttack());

            // when mon attack cha
            effect = some({mon_show_crit,cha_show_evasion});
            appendword(bc_effects,effect,5);
            cha_show_reset();
            mon_show_reset();

            clearScreen();
            //WaitSecond(1);
            //one round finish
            //implement win or lose
            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        appendword(bc_rounds,std::to_string(roundNumber),5);
        appendword(bc_hows,"attack",5);
        appendword(bc_whos,"mon",5);
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(clo1.HP(), clo1.MP(), clo1.ATK()), state_ms);
        TurnInsert(fight_map,chat);
        stringratio(hpbar, chamax, cha1.HP(),"cha");
        WordInsert(fight_map,hpbar,chabar);

        wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
        }
    }
    if (name_ms =="Robot"){
        StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
        int monmax = rob1.HP();
        while (true){

            printMap(fight_map,{chabar});

            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    rob1.hurt(cha1.normal_attack());
                    appendword(bc_hows,"strike",5);
                    break;
                }
                if (in =='2'){

                    if (cha1.skill_status[2]==1){
                        rob1.hurt(cha1.act_hellfire());
                        appendword(bc_hows,"hellfire",5);
                        }
                    else if (cha1.skill_status[2]==2){
                        cha1.act_rage();
                        appendword(bc_hows,"rage",5);
                    }
                    else{
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 1
                        break;
                }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        rob1.hurt(cha1.act_recoverhit());
                        appendword(bc_hows,"recover",5);
                        }
                    else if (cha1.skill_status[0]==2){
                        rob1.hurt(cha1.act_bladestorm());
                        appendword(bc_hows,"blade",5);
                    }
                    else
                    {
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 2
                    break;
                }
            }
            if (rob1.isAlive() == false){
                break;
            }
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
            stringratio(hpbar, monmax,rob1.HP()," ");
            WordInsert(fight_map,hpbar,monbar);
            TurnInsert(fight_map,mont);
            appendword(bc_rounds,std::to_string(roundNumber),5);
            appendword(bc_whos,"you",5);

            effect = some({cha_show_crit,mon_show_evasion,cha_show1,cha_show2});
            appendword(bc_effects,effect,5);
            cha_show_reset();
            mon_show_reset();

            wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
            clearScreen();
            printMap(fight_map,{monbar});
            WaitSecond(1);
            if (roundNumber % 3 == 0 && rob1.MP() >=3) {
                cha1.hurt(rob1.lasers());
                appendword(bc_hows,"lasers",5);
                } else {
                cha1.hurt(rob1.normalAttack());
                appendword(bc_hows,"attack",5);
                }
            
            clearScreen();
            // WaitSecond(1);
            //one round finish
            //implement win or lose

            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        appendword(bc_rounds,std::to_string(roundNumber),5);
        appendword(bc_whos,"mon",5);
        // when mon attack cha
        effect = some({mon_show_crit,cha_show_evasion});
        appendword(bc_effects,effect,5);
        cha_show_reset();
        mon_show_reset();

        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(rob1.HP(), rob1.MP(), rob1.ATK()), state_ms);
        TurnInsert(fight_map,chat);
        stringratio(hpbar, chamax, cha1.HP(),"cha");
        WordInsert(fight_map,hpbar,chabar);
        wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);

        }
    }
    if (name_ms =="Sith"){
        StateInsert(fight_map, convertNumber(sit1.HP(), sit1.MP(), sit1.ATK()), state_ms);
        int monmax = sit1.HP();
        while (true){
            printMap(fight_map,{chabar});

            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    sit1.hurt(cha1.normal_attack());
                    appendword(bc_hows,"strike",5);
                    break;
                }
                if (in =='2'){

                    if (cha1.skill_status[2]==1){
                        sit1.hurt(cha1.act_hellfire());
                        appendword(bc_hows,"hellfire",5);
                        }
                    else if (cha1.skill_status[2]==2){
                        cha1.act_rage();
                        appendword(bc_hows,"rage",5);
                    }
                    else{
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 1
                        break;
                    }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        sit1.hurt(cha1.act_recoverhit());
                        appendword(bc_hows,"recover",5);
                        }
                    else if (cha1.skill_status[0]==2){
                        sit1.hurt(cha1.act_bladestorm());
                        appendword(bc_hows,"blade",5);
                    }
                    else{
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 2
                    break;
                }
            }
            if (sit1.isAlive() == false){
                break;
            }
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(sit1.HP(), sit1.MP(), sit1.ATK()), state_ms);
            stringratio(hpbar, monmax,sit1.HP()," ");
            WordInsert(fight_map,hpbar,monbar);
            TurnInsert(fight_map,mont);
            appendword(bc_rounds,std::to_string(roundNumber),5);
            appendword(bc_whos,"you",5);

            effect = some({cha_show_crit,mon_show_evasion,cha_show1,cha_show2});
            appendword(bc_effects,effect,5);
            cha_show_reset();
            mon_show_reset();            

            wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
            clearScreen();
            printMap(fight_map,{monbar});
            WaitSecond(1);
            if (roundNumber % 3 == 0 && sit1.MP() >=3) {
                cha1.hurt(sit1.lasers());
                appendword(bc_hows,"lasers",5);
                } else {
                cha1.hurt(sit1.normalAttack());
                appendword(bc_hows,"attack",5);
                }
            
            clearScreen();
            // WaitSecond(1);
            //one round finish
            //implement win or lose

            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        appendword(bc_rounds,std::to_string(roundNumber),5);
        appendword(bc_whos,"mon",5);
        // when mon attack cha
        effect = some({mon_show_crit,cha_show_evasion});
        appendword(bc_effects,effect,5);
        cha_show_reset();
        mon_show_reset();
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(sit1.HP(), sit1.MP(), sit1.ATK()), state_ms);
        TurnInsert(fight_map,chat);
        stringratio(hpbar, chamax, cha1.HP(),"cha");
        WordInsert(fight_map,hpbar,chabar);
        wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
        }
    }
    if (name_ms =="Mandalorians"){
        StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
        int monmax = man1.HP();
        while (true){
            printMap(fight_map,{chabar});

            //for player to choose skill
            char in;
            while (true) {
                in = readKeyboard();
                if (in == 's' ) {
                    man1.hurt(cha1.normal_attack());
                    appendword(bc_hows,"strike",5);
                    break;
                }
                if (in =='2'){

                    if (cha1.skill_status[2]==1){
                        man1.hurt(cha1.act_hellfire());
                        appendword(bc_hows,"hellfire",5);
                        }
                    else if (cha1.skill_status[2]==2){
                        cha1.act_rage();
                        appendword(bc_hows,"rage",5);
                    }
                    else
                    {
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 2
                        break;
                    }
                if (in =='1'){
                    if (cha1.skill_status[0]==1){
                        man1.hurt(cha1.act_recoverhit());
                        appendword(bc_hows,"recover",5);
                        }
                    else if (cha1.skill_status[0]==2){
                        man1.hurt(cha1.act_bladestorm());
                        appendword(bc_hows,"blade",5);
                    }
                    else
                    {
                        appendword(bc_hows,"skill",5); cha_show2 = "inactivated";
                    }
                        //skill 1
                    break;
                }
            }
            if (man1.isAlive() == false){
                break;
            }           
            StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
            StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
            stringratio(hpbar, monmax,man1.HP()," ");
            WordInsert(fight_map,hpbar,monbar);
            TurnInsert(fight_map,mont);
            appendword(bc_rounds,std::to_string(roundNumber),5);
            appendword(bc_whos,"you",5);

            effect = some({cha_show_crit,mon_show_evasion,cha_show1,cha_show2});
            appendword(bc_effects,effect,5);
            cha_show_reset();
            mon_show_reset();

            wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
            clearScreen();
            printMap(fight_map,{monbar});
            WaitSecond(1);

            if (roundNumber % 3 == 0 && man1.MP() >=3) {
                cha1.hurt(man1.damage());
                appendword(bc_hows,"damage",5);
                } else {
                cha1.hurt(man1.normalAttack());
                appendword(bc_hows,"attack",5);
                }
            
            
            clearScreen();
            // WaitSecond(1);
            //one round finish
            //implement win or lose
            if (cha1.is_alive() == false){
                break;
            }
            //refresh status and round number
        appendword(bc_rounds,std::to_string(roundNumber),5);
        appendword(bc_whos,"mon",5);
        // when mon attack cha
        effect = some({mon_show_crit,cha_show_evasion});
        appendword(bc_effects,effect,5);
        cha_show_reset();
        mon_show_reset();
        NewRound(fight_map, roundNumber);
        StateInsert(fight_map, convertNumber(cha1.HP(), cha1.MP(), cha1.ATK()), state_mc);
        StateInsert(fight_map, convertNumber(man1.HP(), man1.MP(), man1.ATK()), state_ms);
        TurnInsert(fight_map,chat);
        stringratio(hpbar, chamax, cha1.HP(),"cha");
        WordInsert(fight_map,hpbar,chabar);
        wordsinsert(fight_map,{bc_rounds,bc_whos,bc_hows,bc_effects},bc_p);
        }
    }
    fight_map = temp;
}
// //test
