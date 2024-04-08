#include "monster.h"
#include <iostream>
#include <random>
#include <sched.h>
using namespace std;

/*

	Defines common behaviours of monsters.

 */
double Monster::HP() { return hp_; }
double Monster::MP() { return mp_; }
double Monster::ATK() { return atk_; }
bool Monster::isAlive() {
	if (hp_ <= 0) {
		return false;
	} else {
		return true;
	}
}
void Monster::recoverHP(double x) {
	if ((hp_max_ - hp_) >= x) {
		hp_ += x;
	} else {
		hp_ = hp_max_;
	}
}
void Monster::recoverMP(double x) { mp_ += x; }
double Monster::damage() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= critical_rate_) {
		cout << "Critical Strike!";
		return atk_ * critical_damage_;
	} else {
		return atk_;
	}
}

void Clone::reset(double level, double number) {
	double rate = level + number * 0.2;
	hp_max_ = 20 * rate + 8;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 0 + level * 1.5 + number * 1.0 / 4;
	atk_ = 3 + level * 1.5 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
}
double Clone::normalAttack() {
	recoverHP((hp_max_ - hp_) * 0.1);
	return (damage());
}

void Robot::reset(double level, double number) {
	double rate = level + number * 0.2;
	hp_max_ = 30 * rate + 10;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 2 + level * 1.8 + number * 1.0 / 4;
	atk_ = 2 + level * 1.2 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
}

double Robot::lasers() {
	mp_ -= 3;
	return (damage() * 2);
}
void Cith::reset(double level, double number) {
	double rate = level + number * 0.2;
	hp_max_ = 25 * rate + 9;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 1 + level + number / 4;
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
void Cith::hurt(double x) {
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
		cout << "Evasion successful.";
	} else {
		double y = x - def_;
		if ((hp_ - y) <= 0) {
			hp_ = 0;
		} else {
			hp_ -= y;
			cout << "hurt: hp_-" << y;
			recoverMP(1);
		}
	}
}
double Cith::lasers() {
	mp_ -= 3;
	return (damage() * 1.5);
}

void Mandalorians::reset(double level, double number) {
	double rate = level + number * 0.2;
	hp_max_ = 20 * rate + 8;
	hp_ = hp_max_;
	mp_ = 0;
	def_ = 0 + level * 1.5 + number * 1.0 / 4;
	atk_ = 3 + level * 1.5 + number * 1.0 / 4;
	evasion_rate_ = 0.10 + level * 0.04 + number * 0.008;
	critical_rate_ = 0.2 + level * 0.05 + number * 0.01;
	critical_damage_ = 1.6;
	beatback = level;
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
double Mandalorians::damage() {
	if (beatback >= 1) {
		return (damreturn);
		damreturn = 0;
		beatback -= 1;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= critical_rate_) {
		cout << "Critical Strike!";
		return atk_ * critical_damage_;
	} else {
		return atk_;
	}
}
double Mandalorians::normalAttack() {
	recoverHP((hp_max_ - hp_) * 0.1);
	return (damage());
}
void Mandalorians::hurt(double x) {
	if (beatback >= 1) {
		damreturn = x;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) <= evasion_rate_) {
		cout << "Evasion successful.";
	} else {
		double y = x - def_;
		if ((hp_ - y) <= 0) {
			hp_ = 0;
		} else {
			hp_ -= y;
			cout << "hurt: hp_-" << y;
			recoverMP(1);
		}
	}
}
Clone clo1;