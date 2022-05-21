#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Checker.h"
#include <string>
#include "Vector.h"

#define JUMP_TIME 25.0f
// time for 1 jump
#define JUMP_FORCE 12.0f
// force of 1 jump
#define FLOATING_TIME 7.0f

#define GET_HIT_DELAY_W 30.0f

#define CHANGE_STAGE_DELAY 100.0f

class Warrior : public Character
{
	public:
		Warrior(Properties* prop);
		// just create not init. init in Warrior.cpp
		virtual void Draw();
		virtual void Update(float dt);
		virtual void Clean();
		void ChangeStage(int id);
		void SetSize(int w, int h);
		void GetHit(float dt);
		bool Alive();
		int stage;
		int lastStage;
		Checker* Hit;
		Checker* HitBox;
		float ChangeStageDelay;
	private:
		bool Jumping; // to know player is jumping and set animation jumping for player
		bool Grounded; // make sure player can jump (2 and 1 is can jump)
										//reset when go back to base

		float JumpTime, JumpForce, FloatingTime, GetHitDelay;

		Animation *animation;
		Animation *shoot;
		RigidBody* rigidBody;
		Vector SavePoint;
		int bullet;
		bool ShootKey;
		bool AttackLeft;
};

#endif // WARRIOR_H
