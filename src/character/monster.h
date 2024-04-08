#ifndef MONSTER_H
#define MONSTER_H
#include <random>
#include <iostream>
#include <string>
class Monster {
  public:
	// Returns monsters' HP (Health point)
	int HP();
	int MP();
	int ATK();
	bool isAlive();
	virtual void reset(int, int);
	virtual int normalAttack();
	void recoverHP(int);
	void recoverMP(int);
	virtual void hurt(int);
	virtual int damage();

  protected:
	int hp_, hp_max_;
	int atk_;
	int def_;
	int mp_;
	double critical_rate_, critical_damage_;
	double evasion_rate_;
};

class Clone : public Monster {
  public:
	virtual void reset(int, int);
	virtual int normalAttack();
};

class Robot : Monster {
  public:
	int lasers();
	virtual void reset(int, int);
};

class Cith : Monster {
  public:
	void returntodark();
	int lasers();
	virtual void hurt(int);
	virtual void reset(int, int);

  private:
	int life;
};

class Mandalorians : Monster {
  public:
	virtual int normalAttack();
	virtual void hurt(int);
	void rage();
	virtual int damage();
	virtual void reset(int, int);

  private:
	int beatback;
	int damreturn;
};
void mon_show_reset();

extern Clone clo1;
extern Robot robo1;
extern Cith cit1;
extern Mandalorians man1;
extern std::string mon_show_crit;
extern std::string mon_show_evasion;
#endif
