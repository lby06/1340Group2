#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <random>
//change
#include <string>
//change
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

	std::string genre_;

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
	Clone() { genre_ = "Clone"; };
	void reset(int, int);
	int normalAttack();
};

class Robot : public Monster {
  public:
	Robot() { genre_ = "Robot"; };
	int lasers();
	void reset(int, int);
};

class Sith : public Monster {
  public:
	Sith() { genre_ = "Sith"; };
	void returntodark();
	int lasers();
	void hurt(int);
	void reset(int, int);

  private:
	int life;
};

class Mandalorians : public Monster {
  public:
	Mandalorians() { genre_ = "Mandalorians"; };
	void rage();
	int normalAttack();
	void hurt(int);
	int damage();
	void reset(int, int);

  private:
	int beatback;
	int damreturn;
};

// Function call to create a list of new monsters.
std::vector<Monster> createMonsters(int);

//change
void mon_show_reset();
extern Clone clo1;
extern Robot rob1;
extern Sith sit1;
extern Mandalorians man1;
extern std::string mon_show_crit;
extern std::string mon_show_evasion;
extern std::string mon_show;
//change
#endif
