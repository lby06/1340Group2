#include "monster.h"

using namespace std;

bool Clone::is_alive() {
    if (hp <= 0) {
        return false;
    } else {
        return true;
    }
}

void Clone::reset(int level, int number) {
    double rate = level + number * 0.2;
    hp_max = 20 * rate + 8;
    hp = hp_max;
    mp = 0;
    def = 0 + level * 1.5 + number / 4;
    atk = 3 + level * 1.5 + number / 4;
    evasion_rate = 0.10 + level * 0.04 + number * 0.008;
    critical_rate = 0.2 + level * 0.05 + number * 0.01;
    critical_damage = 1.6;
}

int Clone::damage() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= critical_rate) {
        cout << "Critical Strike!";
        return atk * critical_damage;
    } else {
        return atk;
    }
}

int Clone::normalattack() {
    hp_recover((hp_max - hp) * 0.1);
    return damage();
}

void Clone::hp_recover(int x) {
    if ((hp_max - hp) >= x) {
        hp += x;
    } else {
        hp = hp_max;
    }
}

void Clone::mp_recover(int x) {
    mp += x;
}

void Clone::hurt(int x) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= evasion_rate) {
        cout << "Evasion successful.";
    } else {
        int y = x - def;
        if ((hp - y) <= 0) {
            hp = 0;
        } else {
            hp -= y;
            cout << "hurt: HP-" << y;
            mp_recover(1);
        }
    }
}

bool Robot::is_alive() {
    if (hp <= 0) {
        return false;
    } else {
        return true;
    }
}

void Robot::reset(int level, int number) {
    double rate = level + number * 0.2;
    hp_max = 30 * rate + 10;
    hp = hp_max;
    mp = 0;
    def = 2 + level * 1.8 + number / 4;
    atk = 2 + level * 1.2 + number / 4;
    evasion_rate = 0.10 + level * 0.04 + number * 0.008;
    critical_rate = 0.2 + level * 0.05 + number * 0.01;
    critical_damage = 1.6;
}

int Robot::damage() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= critical_rate) {
        cout << "Critical Strike!";
        return atk * critical_damage;
    } else {
        return atk;
    }
}

int Robot::normalattack() {
    hp_recover((hp_max - hp) * 0.1);
    return damage();
}

void Robot::hp_recover(int x) {
    if ((hp_max - hp) >= x) {
        hp += x;
    } else {
        hp = hp_max;
    }
}

void Robot::mp_recover(int x) {
    mp += x;
}

void Robot::hurt(int x) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= evasion_rate) {
        cout << "Evasion successful.";
    } else {
        int y = x - def;
        if ((hp - y) <= 0) {
            hp = 0;
        } else {
            hp -= y;
            cout << "hurt: HP-" << y;
            mp_recover(1);
        }
    }
}

int Robot::lasers() {
    if (mp >= 2) {
        mp -= 2;
        return damage() * 2;
    } else {
        return 0;
    }
}

bool Cith::is_alive() {
    if (hp <= 0) {
        return false;
    } else {
        return true;
    }
}

void Cith::reset(int level, int number) {
    double rate = level + number * 0.2;
    hp_max = 50 * rate + 20;
    hp = hp_max;
    mp = 0;
    def = 5 + level * 1.8 + number / 4;
    atk = 5 + level * 1.6 + number / 4;
    evasion_rate = 0.10 + level * 0.04 + number * 0.008;
    critical_rate = 0.2 + level * 0.05 + number * 0.01;
    critical_damage = 1.6;
    life = 1;
}

int Cith::damage() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= critical_rate) {
        cout << "Critical Strike!";
        return atk * critical_damage;
    } else {
        return atk;
    }
}

int Cith::normalattack() {
    hp_recover((hp_max - hp) * 0.1);
    return damage();
}

void Cith::hp_recover(int x) {
    if ((hp_max - hp) >= x) {
        hp += x;
    } else {
        hp = hp_max;
    }
}

void Cith::mp_recover(int x) {
    mp += x;
}

void Cith::returntodark() {
    if (mp >= 3) {
        mp -= 3;
        life++;
        cout << "Return to Dark. Life+" << 1;
    }
}

void Cith::hurt(int x) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= evasion_rate) {
        cout << "Evasion successful.";
    } else {
        int y = x - def;
        if ((hp - y) <= 0) {
            hp = 0;
            life--;
        } else {
            hp -= y;
            cout << "hurt: HP-" << y;
            mp_recover(1);
        }
    }
}

int Cith::lasers() {
    if (mp >= 2) {
        mp -= 2;
        return damage() * 2;
    } else {
        return 0;
    }
}

bool Mandalorians::is_alive() {
    if (hp <= 0) {
        return false;
    } else {
        return true;
    }
}

void Mandalorians::reset(int level, int number) {
    double rate=level+number*0.2;
       hp_max=20*rate+8;
       hp=hp_max;
       mp=0;
       def=0+level*1.5+number/4;
       atk=3+level*1.5+number/4;
       evasion_rate=0.10+level*0.04+number*0.008;
       critical_rate=0.2+level*0.05+number*0.01;
       critical_damage=1.6;
}

int Mandalorians::damage() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= critical_rate) {
        cout << "Critical Strike!";
        return atk * critical_damage;
    } else {
        return atk;
    }
}

int Mandalorians::normalattack() {
    hp_recover((hp_max - hp) * 0.1);
    return damage();
}

void Mandalorians::hp_recover(int x) {
    if ((hp_max - hp) >= x) {
        hp += x;
    } else {
        hp = hp_max;
    }
}

void Mandalorians::mp_recover(int x) {
    mp += x;
}

void Mandalorians::rage() {
    if (mp >= 4) {
        mp -= 4;
        beatback++;
        damreturn += 2;
        cout << "Rage. Beatback+" << beatback << " Damreturn+" << damreturn;
    }
}

void Mandalorians::hurt(int x) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) <= evasion_rate) {
        cout << "Evasion successful.";
    } else {
        int y = x - def;
        if ((hp - y) <= 0) {
            hp = 0;
        } else {
            hp -= y;
            cout << "hurt: HP-" << y;
            mp_recover(1);
        }
    }
}
