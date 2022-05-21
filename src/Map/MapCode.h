#ifndef MAPCODE_H
#define MAPCODE_H

#include <iostream>
#include <string>
#include <vector>
#include "Worm.h"
#include "Bat.h"
#include "Boss.h"
#include "Warrior.h"

class MapCode
{
	public:
	  static MapCode* Running() {
      return run = (run != nullptr) ? run : new MapCode();
	  }
		void GetBase(int stage);
		void Update(float dt, int stage);
		void SpawnWorm();
		void SpawnBoss();
		void DrawMod();
		void Completed(int stage);
		void Reset();
  public:
		int base[30][30];
		int stage;
		int amountMod;
		bool spawn = 0;
	  vector <Worm*> worm;
	  vector <bool> wormDeath;
	  Boss* boss;
	  bool completed[13];
	private:
	  MapCode() {}
	  static MapCode* run;
};

#endif // MAPCODE_H
