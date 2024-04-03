#include<iostream>
#include<random>
#include<cmath>
#include <sched.h>
using namespace std;

class bossskill{
    public:
    double *a(int atk){
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
    double *b(int atk){
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
    double *c(int atk){
    cout<<"c";
    double*x=new double [20];
    //加固
    x[0]=0;
    x[1]=0;
    x[2]=0.8;
    x[3]=1.3*difficulty;
    x[4]=1;
    x[5]=1;
    x[6]=0;
    return x;
    }
    double *d(int atk){
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
    double *e(int atk){
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
    double *f(int atk){
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
    void set(double x)
    {
      difficulty=x;
    };
    private:
    int difficulty=1;
    int shutdown;
};
class Vadar
{
  public:
  Vadar(bossskill* j) : ptrB(j) { };
  double* skill1(){
      double* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 5);  
            int randomIndex = dis(gen); 
            seed1=randomIndex;
            return (ptrB->*set[randomIndex])(atk);  
   }
   double* skill2(){
      double* (bossskill::*set[])(int atk) = {&bossskill::a, &bossskill::b, &bossskill::c, &bossskill::d, &bossskill::e,&bossskill::f};

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, 4);  
            int randomIndex = dis(gen); 
            seed2=(seed1+randomIndex)%6;
            return (ptrB->*set[seed2])(atk);  

   }
   int read(double *a)
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
   int damage()
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
    void set(){
      atk=10;
      critical_rate=0.2;
      critical_damage=1.6;
      def=6;
      hp_max=100;
      hp=hp_max;
      shield=0;
      evasion_rate=0.1;
    }
    void display()
    {

       cout<<"HP: "<<hp<<"("<<hp_max<<")"<<"\n"<<"attack: "<<atk<<"\n"<<"defence: "<<def<<"\n"<<"MP: "<<mp<<"\n";
       cout<<"Critical Rate: "<<critical_rate*100<<"%"<<"\n"<<"Critical damage: "<<critical_damage*100<<"%"<<"\n";
       cout<<"Evasion Rate: "<<evasion_rate*100<<"%"<<"\n";
    }
    //技能1
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
  private:
  int hp,hp_max,atk,def,mp;
  double critical_rate,critical_damage;
  double evasion_rate;
  int seed1,seed2;
  bossskill* ptrB;
  int shield;

};


int main(){
  bossskill skilla;
  Vadar *vada=new Vadar(&skilla);
  vada->set();
  vada->hurt(20);
  cout<<endl;
  vada->display();
  
  for (int i=0;i<=10;i++){
 //以下为技能释放过程，若有伤害则会返回伤害值
  double* skill1Result = vada->skill1();
  cout<<endl;
  cout << vada->read(skill1Result) << endl;
//技能释放结束
  vada->display();
  cout<<endl;
  cout<<endl;
  }
  }
