#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <random>
//改动
#include <string>
//改动
class Monster {
  public:
	// Returns monsters' basic properties
	int HP();
	int MP();
	int ATK();
	// Returns monsters' position.
	std::pair<int, int> getPosition();
	void setPosition(int, int);
	bool isAlive();
	// Common behaviours of monsters.
	void recoverHP(int);
	void recoverMP(int);
	void reset(int, int);
	int normalAttack();
	void hurt(int);
	int damage();

  protected:
	int locate_x, locate_y;
	int hp_, hp_max_;
	int atk_;
	int def_;
	int mp_;
	double critical_rate_, critical_damage_;
	double evasion_rate_;
};

class Clone : public Monster {
  public:
	Clone(){};
	void reset(int, int);
	int normalAttack();
};

class Robot : Monster {
  public:
	int lasers();
	void reset(int, int);
};

class Cith : Monster {
  public:
	void returntodark();
	int lasers();
	void hurt(int);
	void reset(int, int);

  private:
	int life;
};

class Mandalorians : Monster {
  public:
	void rage();
	int normalAttack();
	void hurt(int);
	int damage();
	void reset(int, int);

  private:
	int beatback;
	int damreturn;
};

//改动
void mon_show_reset();
extern Clone clo1;
extern Robot rob1;
extern Cith cit1;
extern Mandalorians man1;
extern std::string mon_show_crit;
extern std::string mon_show_evasion;
extern std::string mon_show;
//改动
#endif
