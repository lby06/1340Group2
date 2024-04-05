#ifndef BOSS_H
#define BOSS_H

class bossskill {
public:
    double* a(int atk);
    double* b(int atk);
    double* c(int atk);
    double* d(int atk);
    double* e(int atk);
    double* f(int atk);
    double* g(int atk);
    double* h(int atk);
    void set(double x);
    
private:
    double difficulty;
    int shutdown;
};

class Vadar {
public:
    Vadar(bossskill* j);
    double* skill1();
    double* skill2();
    int read(double* a);
    int damage();
    void hp_recover(int x);
    void mp_recover(int x);
    void set();
    void display();
    void hurt(int x);
    
private:
    int hp, hp_max, atk, def, mp;
    double critical_rate, critical_damage;
    double evasion_rate;
    int seed1, seed2;
    bossskill* ptrB;
    int shield;
};
extern bossskill skilla;
extern Vadar *vada;
#endif