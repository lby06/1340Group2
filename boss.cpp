//想做一个技能库（类似宝可梦）但问题在于不知道怎么让一个函数调用一个类别里的变量
#include<iostream>
#include<random>
#include<cmath>
#include <sched.h>
using namespace std;

class bossskill{
    public:
    int *a(int atk){
    int*x=new int [20];
    return x;
    }
    int *b(int atk){
    int*x=new int [20];
    }
    int *c(int atk){
    int*x=new int [20];
    }
    int *d(int atk){
    int*x=new int [20];
    }
    int *e(int atk){
    int*x=new int [20];
    }
    int *f(int atk){
    int*x=new int [20];
    }
};
class Vadar
{
  public:
  Vadar(bossskill* j) : ptrB(j) { };
  void skill1(){
      int* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 5);  
            int randomIndex = dis(gen); 
            seed1=randomIndex;
            (ptrB->*set[randomIndex])(atk);  
   }
   void skill2(){
      int* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, 4);  
            int randomIndex = dis(gen); 
            seed2=(seed1+randomIndex)%6;
            (ptrB->*set[seed2])(atk);  
   }
  private:
  int hp,hp_max,atk,def,mp;
  double critical_rate,critical_damage;
  double evasion_rate;
  int seed1,seed2;
  bossskill* ptrB;

};


int main(){

}
