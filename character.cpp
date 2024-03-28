#include<iostream>
#include<random>
using namespace std;
class main_character
{
  public:
     is_alive=(hp>0);
     void reset()
     {
       hp=10;
       mp=10;
       exp=0;
       critical_rate=0.15
       critical_damage=1.5
       mp_recover_rate=1;
       evasion_rate=0.1;
       memset(skill_status,0,skill_status.length)
       memset(equipment_status,0,equipment_status.length)
     }
     void display()
     {
       if (is_alive==0)
       { 
         return 0
       }
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
           return atk;
        }
        else
        {
           return atk*critical_damage;
        }
     }
     

  

  private:
     int hp,mp,exp,attack;
     double critical_rate,critical_damage,evasion_rate,mp_recover_rate.
     int skill_status[6],equipment_status[6];
};
int main()
{
  return 0;
}
