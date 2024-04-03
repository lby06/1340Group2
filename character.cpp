#include<iostream>
#include<random>
#include<cmath>
using namespace std;
class main_character
{
  public:
     HP=hp;
     MP=mp;
     ATK=atk;
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
       cout<<"Rage Attack: "<<rageattack<<"\n";

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
            return atk*critical_damage*critical_damage;
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
      critical_rate+=level*0.006+0.008;
      critical_damage+=0.1;
      evasion_rate+=0.01;
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
             cout<<"hurt: HP-"<<y;
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
    //普通攻击
    int normal_attack()
    {
      if (rageattack>=1)
      {
        cout<<"Attack with raaaage"<<endl;
        rageattack-=1;
        return damage()*1.6;
      }
      return damage();
    }
    //主动技能1.1：原力攻击 Hit with the Force
    //造成伤害，一定比例回血，不可暴击
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
          cout<<"recover: "<<atk*1.5;
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
        cout<<"<Hit with the Force> is not activated yet.";
        return 0;
      }
    }
   //主动技能1.2：光剑风暴 Storm of lightsaber
   // 对指定敌方造成3-5段伤害
   //可暴击，且释放技能期间暴击伤害提升（40%）
    void activate_bladestorm()
    {
      skill_status[0]=1;
    }
     int act_bladestorm()
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
        cout<<"<Storm of lightsaber> is not activated yet.";
        return 0;
      }
    }
    //被动技能1.1：血族 Vengeance
    //普攻，技能最终伤害一定比例回复生命值
    void activate_vengeance()
    {
      skill_status[1]=1;
    }
    //被动技能1.2 原力汇聚 Force convergence
    // 使用技能后按一定比例返还技能消耗的原力
    void activate_magicdraw()
    {
      skill_status[1]=2;
    }
    //主动技能2.1 黑暗烈焰 Dark Force Flame
    // 耗尽魔法值进行攻击，消耗魔法值越多增伤越高（1.5次方）
    // 可暴击 
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
          int dam=use*sqrt(use)*sqrt(damage())/4+5;
          if (skill_status[1]==2)
          {
            cout<<"magicdraw: "<<0.2*use+1;
            mp_recover(0.2*use+1);
          }
          if (skill_status[1]==1)
          {
            cout<<"Vampiric effect: "<<0.2*dam+1;
            hp_recover(0.2*1.5*dam+1);
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
        cout<<"<Dark Force Flame> is not activated yet.";
        return 0;
      }
    }
    //主动技能2.2 绝地之怒 Rage of Jedi
    //一定比例减少生命值，生命值上限，防御
    //一定比例增加伤害，暴击率，暴击伤害
    //强化接下来两次普攻，强化为Rage attack（最终伤害值*1.6）
    void activate_rage()
    {
      skill_status[2]=2;
    }
    void act_rage()
    {
      if (skill_status[2]==2)
      {
        if (mp>=7)
        {
          mp-=7;
         
          hp_max*=0.8;
          hp*=0.6;
          def*=0.7;
          atk*=1.1;
          critical_rate*=1.25;
          critical_damage*=1.3;
          rageattack+=2;

        }
        else
        {
          cout<<"Magic power is deficient.";
          return ;
        }      
      }
      else
      {
        cout<<"<Rage of Jedi> is not activated yet.";
        return ;
      }
    }
    //被动2.1 索罗之力 Gift of Solo
    // 改良暴击机制，触发暴击时有一定概率（根据自身暴击率）触发二次暴击
    void activate_doublecrit()
    {
      skill_status[3]=2;
    }
    //被动2.2 最终防御 Ultimate shield
    // 血量越低，减伤越高，且血量低于40%时，受击回能额外加1
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
  for (int i=0;i<=3;i++)
  {
      cha1.upgrade();
      cout<<endl;
      cha1.display();
  }
  cout<<endl;
  cha1.hurt(20);
  cha1.display();
  cout<<endl;
  cha1.activate_recoverhit();
  cout<<cha1.act_recoverhit();
  cout<<endl;
  cha1.display();
  cout<<endl;
  cha1.mp_recover(0);
  cha1.activate_rage();
  cha1.act_rage();
  cha1.display();
  cout<<endl;
  cha1.activate_doublecrit();
  for(int i=0;i<=20;i++)
  {
    cout<<cha1.normal_attack()<<endl;
  }

}
   

   

