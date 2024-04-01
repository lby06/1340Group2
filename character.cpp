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
       def=2;
       hp=10;
       hp_max=10;
       mp=10;
       exp=0;
       critical_rate=0.15;
       critical_damage=1.5;
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
       cout<<"HP: "<<hp<<"("<<hp_max<<")"<<"\n"<<"attack: "<<atk<<"\n"<<"defence: "<<def<<"\n"<<"MP: "<<mp<<"\n"<<"EXP: "<<exp<<"\n";
       cout<<"Critical Rate: "<<critical_rate*100<<"%"<<"\n"<<"Critical damage: "<<critical_damage*100<<"%"<<"\n";
       cout<<"Evasion Rate: "<<evasion_rate*100<<"%"<<"\n";
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
      def+=level/3;
      hp_max=15*level+10;
      hp=hp_max;
      mp=2*level+3;
      critical_rate+=level*0.006;
      critical_damage+=0.1;
      evasion_rate+=0.02;
      if (critical_rate>1)
      {
        critical_rate=1;
      }
    }
    void hp_recover(int x)
    {
        if ((hp_max-hp)>=x)
        {
          hp+=x;
        }
        else 
        {
          hp=hp_max;
        }
    }
    void mp_recover(int x)
    {
      mp+=x;
    }
    void hurt(int x)
    {
      random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        if (dis(gen)<=evasion_rate) 
        {
           cout<<"Evasion successful.";
        }
        else
        {
           int y=x-def;
           if ((hp-y)<=0)
           {
             hp=0;
           }
           else 
           {
             hp-=y;
           }
        }
    }
    void activate_recoverhit()
    {
      skill_status[0]=1;
    }
    int act_recoverhit()
    {
      if (skill_status[0]==1)
      {
        if (mp>=4)
        {
          mp-=4;
          hp_recover(atk*1.5);
          return atk*1.5;
        }
        else
        {
          cout<<"Magic power is deficient.";
          return 0;
        }      
      }
      else
      {
        cout<<"<recover hit> is not activated yet.";
        return 0;
      }
    }
    

  private:
     int locate_x,locate_y;
     int hp,mp,exp,atk,level,hp_max,def;
     double critical_rate,critical_damage,evasion_rate;
     int skill_status[4],equipment_status[4];
};
int main()
{
  main_character cha1;
  cha1.reset();
  cha1.display();
  for (int i=0;i<=9;i++)
  {
      cha1.upgrade();
      cout<<endl;
      cha1.display();
  }
  cha1.hurt(20);
  cha1.display();
  cout<<endl;
  cha1.activate_recoverhit();
  cout<<cha1.act_recoverhit();
  cout<<endl;
  cha1.display();
  cout<<endl;

}
   
