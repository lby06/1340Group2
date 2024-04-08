#ifndef MONSTER_H
#define MONSTER_H
#include <random>
#include <iostream>

class Monster {
  public:
	// Returns monsters' HP (Health point)
	double HP();
	double MP();
	double ATK();
	bool isAlive();
	virtual void reset(int, int);
	virtual double normalAttack();
	void recoverHP(double);
	void recoverMP(double);
	virtual void hurt(double);
	virtual double damage();

  protected:
	double hp_, hp_max_;
	double atk_;
	int def_;
	double mp_;
	double critical_rate_, critical_damage_;
	double evasion_rate_;
};

class Clone : public Monster {
  public:
	virtual void reset(int, int);
	virtual double normalAttack();
};

class Robot : Monster {
  public:
	double lasers();
	virtual void reset(int, int);
};

class Cith : Monster {
  public:
	void returntodark();
	double lasers();
	virtual void hurt(double);
	virtual void reset(int, int);

  private:
	int life;
};

class Mandalorians : Monster {
  public:
	virtual double normalAttack();
	virtual void hurt(double);
	void rage();
	virtual double damage();
	virtual void reset(int, int);

  private:
	int beatback;
	int damreturn;
};
extern Clone clo1;
#endif
