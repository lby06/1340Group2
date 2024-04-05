#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
class main_character
{
  public:
     int HP();
     int MP();
     int ATK();
     bool is_alive();
     void reset();
     void set(double a[]);
     double* save(int num);
     void display();
     int damage();
     void upgrade();
     void hp_recover(int x);
     void mp_recover(int x);
     void hurt(int x);

     void activate_attackup();
     void activate_defenceup();
     void activate_crup();
     void clear_status();

     int normal_attack();
     void activate_recoverhit();
     int act_recoverhit();
     void activate_bladestorm();
     int act_bladestorm();
     void activate_vengeance();
     void activate_magicdraw();
     void activate_hellfire();
     int act_hellfire();
     void activate_rage();
     void act_rage();
     void activate_doublecrit();
     void activate_ultimatedef();
  private:
     int locate_x,locate_y;
     int hp,mp,exp,atk,level,hp_max,def;
     double critical_rate,critical_damage,evasion_rate;
     int skill_status[4],equipment_status[4];
     int rageattack;
     int status[3];
};
extern main_character cha1;
extern std::string heroname;
extern std::string monstername;
extern std::string boardcast_word;
extern std::string skillname1;
extern std::string skillmp1;
extern std::string skillname2;
extern std::string skillmp2; 
extern std::string skillname3;
extern std::string skillmp3;
extern std::string skillname4;
extern std::string skillmp4;

#endif // CHARACTER_H