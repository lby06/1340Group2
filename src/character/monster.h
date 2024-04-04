#ifndef MONSTER_H
#define MONSTER_H
#include <random>
#include <iostream>

class Clone {
public:
    int HP();
    int MP();
    int ATK();
    bool is_alive();
    void reset(int level, int number);
    int normalattack();
    void hp_recover(int x);
    void mp_recover(int x);
    void hurt(int x);

private:
    int hp, hp_max, atk, def, mp;
    double critical_rate, critical_damage;
    double evasion_rate;
    int damage();
};

class Robot {
public:
    int HP();
    int MP();
    int ATK();
    bool is_alive();
    void reset(int level, int number);
    int normalattack();
    void hp_recover(int x);
    void mp_recover(int x);
    void hurt(int x);
    int lasers();

private:
    int hp, hp_max, atk, def, mp;
    double critical_rate, critical_damage;
    double evasion_rate;
    int damage();
};

class Cith {
public:
    int HP();
    int MP();
    int ATK();
    bool is_alive();
    void reset(int level, int number);
    int normalattack();
    void hp_recover(int x);
    void mp_recover(int x);
    void returntodark();
    void hurt(int x);
    int lasers();

private:
    int hp, hp_max, atk, def, mp;
    double critical_rate, critical_damage;
    double evasion_rate;
    int life;
    int damage();
};

class Mandalorians {
public:
    int HP();
    int MP();
    int ATK();
    bool is_alive();
    void reset(int level, int number);
    int normalattack();
    void hp_recover(int x);
    void mp_recover(int x);
    void rage();
    void hurt(int x);

private:
    int hp, hp_max, atk, def, mp;
    double critical_rate, critical_damage;
    double evasion_rate;
    int beatback;
    int damreturn;
    int damage();
};
extern Clone clo1;
#endif
