#include<iostream>
#include<random>
#include<cmath>
using namespace std;
class main_character
{
  public:
     bool is_alive()
     {
       if (hp<=0)
       {
         return false;
       }
       else 
       {
         return true;
       }
     }
     void reset()
     {
       level=0;
       locate_x=0;
       locate_y=0;
       atk=3;
       def=2;
       hp=10;
       hp_max=10;
       mp=5;
       exp=0;
       critical_rate=0.15;
       critical_damage=1.5;
       evasion_rate=0.1;
       rageattack=0;
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
          if (skill_status[3]==2 && dis(gen)<=critical_rate/2.2+0.05)
          {
            cout<<"Utimate Critical Strike!!!";
            return atk*critical_damage*critical_damage*1.15;
          } 
          cout<<"Critical Strike!";
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
      mp=1.4*level+4;
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
             mp_recover(1);//受击回蓝
             if (skill_status[3]==1)
             { 
               double rate=hp/hp_max;
               hp+=y*(1-rate)/1.5;               
               if(rate<=0.4)
               {
                 mp_recover(1);
               }
             }
           }
        }
    }
    double normal_attack()
    {
      if (rageattack>=1)
      {
        rageattack-=1;
        return damage()*1.6;
      }
      return damage();
    }
    void activate_recoverhit()
    {
      skill_status[0]=1;
    }
    int act_recoverhit()
    {
      if (skill_status[0]==1)
      {
        if (mp>=3)
        {
          mp-=3;
          hp_recover(atk*1.5);
          if (skill_status[1]==2)
          {
            cout<<"magicdraw: "<<"1";
            mp_recover(1);
          }
          if (skill_status[1]==1)
          {
            cout<<"Vampiric effect: "<<0.2*1.5*atk+1;
            hp_recover(0.2*1.5*atk+1);
          }
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
    void activate_bladestorm()
    {
      skill_status[0]=1;
    }
     double act_bladestorm()
    {
      if (skill_status[0]==2)
      {
        if (mp>=4)
        {
          mp-=4;
          random_device rd;
          mt19937 gen(rd());
          uniform_real_distribution<> dis(0.3, 0.6);
          int dam=0;
          int da[6];
          int times=10*dis(gen);
          cout<<"Number of segments in this attack: "<<times;
          for (int i=0;i<times;i++)
          {
            dam+=damage()*0.3;
          }
          critical_damage-=0.4;
          if (skill_status[1]==2)
          {
            cout<<"magicdraw: "<<"1";
            mp_recover(1);
          }
          if (skill_status[1]==1)
          {
            cout<<"Vampiric effect: "<<0.2*dam+1;
            hp_recover(0.2*dam+1);
          }
          return dam;
          
    
        }
        else
        {
          cout<<"Magic power is deficient.";
          return 0;
        }      
      }
      else
      {
        cout<<"<blade storm> is not activated yet.";
        return 0;
      }
    }
    void activate_vengeance()
    {
      skill_status[1]=1;
    }
    void activate_magicdraw()
    {
      skill_status[1]=2;
    }
    void activate_hellfire()
    {
      skill_status[2]=1;
    }
    int act_hellfire()
    {
      if (skill_status[2]==1)
      {
        if (mp>=1)
        {
          cout<<"Magic power used"<<mp;
          double use=mp;
          mp=0;
          int dam=use*sqrt(use)+1;
          if (skill_status[1]==2)
          {
            cout<<"magicdraw: "<<0.2*use+1;
            mp_recover(0.2*use+1);
          }
          if (skill_status[1]==1)
          {
            cout<<"Vampiric effect: "<<0.2*dam+1;
            hp_recover(0.2*1.5*atk+1);
          }
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
        cout<<"<hellfire> is not activated yet.";
        return 0;
      }
    }
    void activate_rage()
    {
      skill_status[2]=2;
    }
    int act_rage()
    {
      if (skill_status[2]==2)
      {
        if (mp>=7)
        {
          mp-=7;
         
          hp_max*=0.8;
          hp*=0.8;
          def*=0.8;
          atk*=1.1;
          critical_rate*=1.1;
          critical_damage*=1.1;
          rageattack+=2;

        }
        else
        {
          cout<<"Magic power is deficient.";
          return 0;
        }      
      }
      else
      {
        cout<<"<hellfire> is not activated yet.";
        return 0;
      }
    }
    void activate_doublecrit()
    {
      skill_status[3]=2;
    }
     void activate_ultimatedef()
    {
      skill_status[3]=1;
    }

    

  private:
     int locate_x,locate_y;
     int hp,mp,exp,atk,level,hp_max,def;
     double critical_rate,critical_damage,evasion_rate;
     int skill_status[4],equipment_status[4];
     int rageattack;
};
int main()
{//试验
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
   
