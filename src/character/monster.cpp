#include "monster.h"
#include "../utils/utils.hpp"
#include <iostream>
#include <random>
#include <sched.h>
using namespace std;

/*

	Defines common behaviours of monsters.

 */
//改动---------------
string mon_show_crit = "";
string mon_show_evasion = "";
string mon_show = "";
void mon_show_reset() {
	mon_show_crit = "";
	mon_show_evasion = "";
	mon_show = "";
}
//改动----------------

// NOTE -  Modify the percentage distribution here.
const int kNormalMonsterPercentage = 20; // 20
const int kClonePercentage = 40;		 // 20+20
const int kCithPercentage = 60;			 // 20+20+20
const int kMandaloriansPercentage = 80;	 // 20+20+20+20
const int kRobotPercentage = 100;		 // 20+20+20+20+20
// Function call to create a new monster.
Monster createMonster() {
	uniform_int_distribution<int> dis(0, 100);
	int tmp = dis(rng);
	auto pos = randomPosition();
	// Create a monster based on the percentage distribution.
	if (tmp < kClonePercentage) {
		auto f = Clone();
		f.setPosition(pos.first, pos.second);
		return f;
	} else if (tmp < kCithPercentage) {
		auto f = Cith();
		f.setPosition(pos.first, pos.second);
		return f;
	} else if (tmp < kMandaloriansPercentage) {
		auto f = Mandalorians();
		f.setPosition(pos.first, pos.second);
		return f;
	} else {
		auto f = Robot();
		f.setPosition(pos.first, pos.second);
		return f;
	}
}

// Create a list of monsters.
std::vector<Monster> createMonsters(int n) {
	std::vector<Monster> monsters;
	for (int i = 0; i < n; i++) {
		monsters.push_back(createMonster());
	}
	return monsters;
}

int Monster::HP() { return hp_; }
int Monster::MP() { return mp_; }
int Monster::ATK() { return atk_; }
std::pair<int, int> Monster::getPosition() {
	return std::make_pair(locate_x, locate_y);
}
void Monster::setPosition(int x, int y) {
	locate_x = x;
	locate_y = y;
}
bool Monster::isAlive() {
	if (hp_ <= 0) {
		return false;
	} else {
		return true;
	}
}
void Monster::recoverHP(int x) {
	if ((hp_max_ - hp_) >= x) {
		hp_ += x;
	} else {
		hp_ = hp_max_;
	}
}
void Monster::recoverMP(int x) { mp_ += x; }
int Monster::damage() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= critical_rate_) {
		mon_show_crit = "Critical Strike!"; //改动----------------
		return atk_ * critical_damage_;
	} else {
		return atk_;
	}
}

int Monster::normalAttack() {
	return (damage());
}

void Monster::hurt(int x) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= evasion_rate_) {
		cout << "Evasion successful.";
	} else {
		int y = x - def_;
		if ((hp_ - y) <= 0) {
			hp_ = 0;
		} else {
			hp_ -= y;
			//cout << "hurt: HP-" << y;
			recoverMP(1);
		}
	}
}

void Clone::reset(int level, int number) {
	int rate = level + number * 0.2;
	hp_max_ = 25 * rate + 8;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 0 + level * 1 + number * 1.0 / 4;
	atk_ = 3 + level * 1.5 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
}
int Clone::normalAttack() {
	int x=damage();
	recoverHP(x*0.3);
	return (x);
}

void Robot::reset(int level, int number) {
	int rate = level + number * 0.2;
	hp_max_ = 30 * rate + 10;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 1 + level * 1.2 + number * 1.0 / 4;
	atk_ = 2 + level * 1.2 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
}

int Robot::lasers() {
	mp_ -= 3;
	return (damage() * 2);
}
void Cith::reset(int level, int number) {
	int rate = level + number * 0.2;
	hp_max_ = 25 * rate + 9;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 0 + level*0.5 + number / 4;
	atk_ = 3 + level * 2 + number * 1.0 / 4;
	evasion_rate_ = 0.12 + level * 0.06 + number * 0.012;
	critical_rate_ = 0.25 + level * 0.07 + number * 0.014;
	critical_damage_ = 1.6;
	life = 0;
}
//技能1
void Cith::returntodark() {
	mp_ -= 5;
	life = 4;
	critical_rate_ *= 1.2;
	critical_damage_ = 1.8;
}
void Cith::hurt(int x) {
	if (life >= 2) {
		life -= 1;
		return;
	}
	if (life == 1) {
		hp_ = 0;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= evasion_rate_) {
		mon_show_evasion = "Evasion successful."; //改动--------------
	} else {
		int y = x - def_;
		if ((hp_ - y) <= 0) {
			hp_ = 0;
		} else {
			hp_ -= y;
			cout << "hurt: hp_-" << y;
			recoverMP(1);
		}
	}
}
int Cith::lasers() {
	mp_ -= 3;
	return (damage() * 1.5);
}

void Mandalorians::reset(int level, int number) {
	int rate = level + number * 0.2;
	hp_max_ = 20 * rate + 8;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 0 + level * 1 + number * 1.0 / 4;
	atk_ = 3 + level * 1.5 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
	beatback = level/2;
	damreturn = 0;
}
void Mandalorians::rage() {
	mp_ -= 3;
	hp_max_ *= 1.1;
	hp_ *= 1.1;
	critical_rate_ *= 1.1;
	atk_ *= 1.1;
	beatback += 2;
}
int Mandalorians::damage() {
	if (beatback >= 1) {
		int x=damreturn;
		damreturn = 0;
		beatback -= 1;
		return x;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= critical_rate_) {
		mon_show_crit = "Critical Strike!"; //改动----------------
		return atk_ * critical_damage_;
	} else {
		return atk_;
	}
}
int Mandalorians::normalAttack() {
	recoverHP((hp_max_ - hp_) * 0.1);
	return (damage());
}
void Mandalorians::hurt(int x) {
	if (beatback >= 1) {
		damreturn = x;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= evasion_rate_) {
		mon_show_evasion = "Evasion successful."; //改动--------------
	} else {
		int y = x - def_;
		if ((hp_ - y) <= 0) {
			hp_ = 0;
		} else {
			hp_ -= y;
			cout << "hurt: hp_-" << y;
			recoverMP(1);
		}
	}
}
//改动----------------
Clone clo1;
Robot rob1;
Cith cit1;
Mandalorians man1;
//改动----------------
