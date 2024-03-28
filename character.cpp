#include<iostream>
#include<random>
using namespace std;
class main_character
{
  public:
     bool is_alive=(hp>0);
     void reset()
     {
       level=0;
       locate_x=0;
       locate_y=0;
       atk=3;
       hp=10;
       hp_max=10;
       mp=10;
       exp=0;
       critical_rate=0.15;
       critical_damage=1.5;
       mp_recover_rate=1;
       evasion_rate=0.1;
       for (int i = 0; i < 5; ++i) 
       {
        skill_status[i] = 0;
       }
       for (int i = 0; i < 5; ++i) 
       {
        equipment_status[i] = 0;
       }

     }
     void display()
     {
       cout<<"LEVEL : "<<level<<endl;
       cout<<"HP: "<<hp<<"\n"<<"attack: "<<atk<<"\n"<<"MP: "<<mp<<"\n"<<"EXP: "<<exp<<"\n";
       cout<<"Critical Rate: "<<critical_rate*100<<"%"<<"\n"<<"Critical damage: "<<critical_damage*100<<"%"<<"\n";
       cout<<"Evasion Rate: "<<evasion_rate*100<<"%"<<"\n"<<"MP Recover Rate: "<<mp_recover_rate*100<<"%"<<"\n";
     }
     double damage()
     {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        if (dis(gen)<=critical_rate) 
        {
           return atk*critical_damage;
        }
        else
        {
           return atk;
        }
     }
     void upgrade()
    {
      level++;
      exp=0;
      atk+=level/2;
      hp_max=15*level+10;
      hp=hp_max;
      mp=2*level;
      critical_rate+=level*0.006;
      critical_damage+=0.1;
      evasion_rate+=0.02;
      if (critical_rate>1)
      {
        critical_rate=1;
      }
    }

  private:
     int locate_x,locate_y;
     int hp,mp,exp,atk,level,hp_max;
     double critical_rate,critical_damage,evasion_rate,mp_recover_rate;
     int skill_status[6],equipment_status[6];
};
int main()
{
  main_character cha1;
  cha1.reset();
  cha1.display();
  for (int i=0;i<=10;i++)
  {
      cha1.upgrade();
      cout<<endl;
      cha1.display();
      }
  }
