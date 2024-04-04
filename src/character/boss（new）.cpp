#include<iostream>
#include<random>
#include<cmath>
#include <sched.h>
#include "boss.h"
using namespace std;


    double* bossskill::a(int atk){
    cout<<"a";
    double*x=new double [20];
    //回复
    x[0]=5*difficulty;
    x[1]=0;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=0;
    return x;
    }
    double* bossskill::b(int atk){
    cout<<"b";
    double*x=new double [20];
    //攻击
    x[0]=0;
    x[1]=1+difficulty;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=0;
    return x;
    }
    double* bossskill::c(int atk){
    cout<<"c";
    double*x=new double [20];
    //加固
    x[0]=0;
    x[1]=0;
    x[2]=0.8;
    x[3]=1.3*difficulty;
    x[4]=1;
    x[5]=1;
    x[6]=1;
    return x;
    }
    double* bossskill::d(int atk){
    cout<<"d";
    double*x=new double [20];
    //狂暴
    x[0]=-5;
    x[1]=0;
    x[2]=1.2;
    x[3]=0.7;
    x[4]=1.2*difficulty;
    x[5]=1.2*difficulty;
    x[6]=0;
    return x;
    }
    double* bossskill::e(int atk){
    cout<<"e";
    double*x=new double [20];
    //重击
    x[0]=-5;
    x[1]=2+difficulty;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=0;
    return x;
    }
    double* bossskill::f(int atk){
    cout<<"f";
    double*x=new double [20];
    //上盾
    x[0]=-5;
    x[1]=0;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=2;
    return x;
    }
    double* bossskill::g(int atk){
    cout<<"g";
    double*x=new double [20];
    //自毁
    x[0]=-8*difficulty;
    x[1]=0;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=1;
    return x;
    }
     double* bossskill::h(int atk){
    cout<<"h";
    double*x=new double [20];
    //吸血攻击
    x[0]=atk*0.8*difficulty;
    x[1]=1;
    x[2]=1;
    x[3]=1;
    x[4]=1;
    x[5]=1;
    x[6]=0;
    return x;
    }
    void bossskill::set(double x)
    {
      difficulty=x;
    }

  Vadar::Vadar(bossskill* j) : ptrB(j) { };
  double* Vadar::skill1(){
      double* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f,&bossskill::g,&bossskill::h};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 7);  
            int randomIndex = dis(gen); 
            seed1=randomIndex;
            return (ptrB->*set[randomIndex])(atk);  
   }
   double* Vadar::skill2(){
      double* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f,&bossskill::g,&bossskill::h};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, 6);  
            int randomIndex = dis(gen); 
            seed2=(seed1+randomIndex)%8;
            return (ptrB->*set[seed2])(atk);  

   }
   int Vadar::read(double *a)
   {
     hp_max+=a[0];
     hp_recover(a[0]);
     atk*=a[2];
     def*=a[3];
     critical_rate*=a[4];
     critical_damage*=a[5];
     shield+=a[6];
     if (a[1!=0]){
      return a[1]*damage();
     }
     return 0;
   }
   int Vadar::damage()
     {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        if (dis(gen)<=critical_rate) 
        {
          cout<<"Critical Strike!";
          return atk*critical_damage;
        }
        else
        {
           return atk;
        }
     }
     void Vadar::hp_recover(int x)
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
    void Vadar::mp_recover(int x)
    {
      mp+=x;
    }
    void Vadar::set(){
      atk=7;
      critical_rate=0.2;
      critical_damage=1.6;
      def=6;
      hp_max=100;
      hp=hp_max;
      shield=0;
      evasion_rate=0.1;
    }
    void Vadar::display()
    {

       cout<<"HP: "<<hp<<"("<<hp_max<<")"<<"\n"<<"attack: "<<atk<<"\n"<<"defence: "<<def<<"\n"<<"MP: "<<mp<<"\n";
       cout<<"Critical Rate: "<<critical_rate*100<<"%"<<"\n"<<"Critical damage: "<<critical_damage*100<<"%"<<"\n";
       cout<<"Evasion Rate: "<<evasion_rate*100<<"%"<<"\n";
    }
    //技能1
    void Vadar::hurt(int x)
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
          if (shield>=1)
          {
            y*=0.5;
            shield-=1;
          }
           if ((hp-y)<=0)
           {
             hp=0;
           }
           else 
           {
             hp-=y;
             cout<<"hurt: HP-"<<y;
             mp_recover(1);
           }
        }
    }
bossskill skilla;
Vadar *vada=new Vadar(&skilla);

