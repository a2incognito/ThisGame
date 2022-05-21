#include "Warrior.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include "Engine.h"
#include "CollisionHandling.h"
#include "MapCode.h"
#include "Amthanh.h"
//throws something to screen

#include "SDL.h"

Warrior::Warrior(Properties* prop) : Character(prop) {
	JumpTime = JUMP_TIME;
	JumpForce = JUMP_FORCE;
	FloatingTime = FLOATING_TIME;

	HitBox = new Checker();
	Hit = new Checker();

	Position = new Transform();
	Position -> X = 45.0;
	Position -> Y = 300.0;
	SavePoint = Vector(Position ->X, Position ->Y);
	rigidBody = new RigidBody(); // mass = 1, gravity = 9.8
	rigidBody ->SetGravity(GRAVITY); // set gravity equal 3 to smooth motion

	animation = new Animation();
	animation -> SetProp(TextureID, 0, 6, 80);
	stage = 0;
	lastStage = -1;
	Grounded = 2;
	Jumping = 0;
	HP = 10;
	MapCode::Running() ->completed[0] = 1;
	maxHP = 10;
	AttackLeft = false;
	GetHitDelay = GET_HIT_DELAY_W;
	ChangeStageDelay = CHANGE_STAGE_DELAY;
//	SDL_Log("%f", GetHitDelay);

//	ShootKey = 0;
}

void Warrior::Draw() {
	if (!AttackLeft) animation -> DrawSprite(Position -> X, Position -> Y, width, height);
	else animation -> DrawSprite(Position -> X - 45, Position -> Y, width, height);

//	if (ShootKey) shoot -> DrawSprite(Position -> X, Position -> Y, 41, 32);
	// draw animation at (x, y), sz (w, h), textureID, SpriteRow, SpriteFrame by DrawFrame of TextureManager
	SDL_Rect hit_box = HitBox ->Get();
	SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit_box);
	SDL_Rect hit = Hit ->Get();
	SDL_RenderDrawRect (Engine::Running() ->GetRenderer(), &hit);
}

void Warrior::Update(float deltaTime) {
//	SDL_Log("%d", HP);
//	SDL_Log ("%d %d",stage, lastStage);
//	SDL_Log ("%f %f",Position ->X, Position ->Y);
	if (stage != lastStage) {
		if (ChangeStageDelay < 0) {
			if (stage > lastStage) for (int i = 0; i < 15; ++i) {
				if (MapCode::Running() ->base[i][0] == 3) {
					Position ->X = 0;
					Position ->Y = 32 * i;
				}
//				SDL_Log("%d %d %d", stage, lastStage, MapCode::Running() ->base[i][0]);
			}
			else {
				for (int i = 0; i < 15; ++i) {
					if (MapCode::Running() ->base[i][20] == 3) {
						SDL_Log ("%d", MapCode::Running() ->base[i][20]);
						Position ->X = 20 * 32;
						Position ->Y = 32 * i;
					}
				}
			}
			lastStage = stage;
		}
		return ;
	}
	rigidBody ->SetGravity(GRAVITY);
	bool attack = 0;
  AttackLeft = false;
  Hit = new Checker();
	SDL_RendererFlip tmp = animation  -> GetFlip();
	// save memory of flip for SetProp
	animation -> SetProp("idle", 0, 4, 300, tmp);
	HitBox ->SetChange(8, 0, 0, 0);
	width = 44, height = 32;

	// reset player idle
	rigidBody -> UnsetForce();
	// reset f
	//----------------------------LEFT------------------------------------
		if (EventHandler::Event() -> GetKey(SDL_SCANCODE_LEFT)) {
			Amthanh::Running() ->play("content/Sound/run.mp3", 0);
			rigidBody -> ApplyForceX(4 * BACKWARD);
			// left buttom to -3 f.x
			animation -> SetProp("run", 0, 3, 100, SDL_FLIP_HORIZONTAL);
			tmp = SDL_FLIP_HORIZONTAL;
			HitBox ->SetChange(0, 0, 0, 0);
			width = 48, height = 32;
			// set animation from player_idle tp player_run (left)
		}

	//----------------------------RIGHT------------------------------------
		if (EventHandler::Event() -> GetKey(SDL_SCANCODE_RIGHT)) {
			Amthanh::Running() ->play("content/Sound/run.mp3", 0);
			rigidBody -> ApplyForceX(4 * FORWARD);
			// left buttom to +3 f.x
			tmp = SDL_FLIP_NONE;
			animation -> SetProp("run", 0, 3, 100);
			width = 48, height = 32;
	//		animation -> SetProp("player_jump", 0, 6, 80);
			// set animation from player_idle tp player_run (right)
		}

	//----------------------------JUMP-----------------------

	//	SDL_Log("info: %d %f %d %d", Grounded, JumpTime, Jumping, (EventHandler::Event() -> GetKey(SDL_SCANCODE_K)));

		if (EventHandler::Event() -> GetKey(SDL_SCANCODE_K) && Grounded && !Jumping) {
			Amthanh::Running() ->play("content/Sound/jump.mp3", 0);
			rigidBody -> ApplyForceY(JUMP_FORCE * UPWARD);
	//		SDL_Log("here 1");
			Jumping = true;
			Grounded = false;
			animation -> SetProp("jump_1", 0, 1, 1, tmp);
			width = 42, height = 61;
		}

		else if (EventHandler::Event() -> GetKey(SDL_SCANCODE_K) && Jumping && JumpTime > 0) {
			rigidBody -> ApplyForceY((JUMP_FORCE) * UPWARD);
	//		rigidBody -> ApplyForceY((JUMP_FORCE - (rigidBody ->GetGravity() * (JUMP_TIME - JumpTime))) * UPWARD);
			JumpTime -= deltaTime;
	//		SDL_Log("here 1");
			width = 38, height = 55;
			animation -> SetProp("jump_1", 0, 1, 1, tmp);
	//		if (JumpTime < 0) SDL_Log("limit: %f", JumpTime);
		}

		else if (EventHandler::Event() ->GetKey(SDL_SCANCODE_K) && Jumping && JumpTime <= 0 && FloatingTime > 0) {
			rigidBody -> ApplyForceY ((GRAVITY - 1) * UPWARD);
			FloatingTime -= deltaTime;
			animation -> SetProp("jump_2", 0, 1, 1, tmp);
			width = 53, height = 34;
		}

		else if (!(EventHandler::Event() ->GetKey(SDL_SCANCODE_K)) && Jumping && JumpTime) {
			JumpTime = 0;
		}

		else if (Grounded == false) {
			animation -> SetProp("jump_3", 0, 1, 1, tmp);
			width = 42, height = 57;
		}
		if (Grounded) {
			Jumping = false;
			JumpTime = JUMP_TIME;
			FloatingTime = FLOATING_TIME;
		}

	//-------------------------------ATTACK----------------------------------
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_J)) {
			Amthanh::Running() ->play("content/Sound/hit.mp3", 0);
			if (tmp == SDL_FLIP_NONE) {
				animation -> SetProp("attack", 0, 8, 50, tmp);
				width = 91, height = 36;
				attack = 1;
	//			if (!JumpTime) rigidBody ->SetGravity(GRAVITY - 3.0f);
			}
			else {
				animation -> SetProp("attack", 0, 8, 50, tmp);
				width = 91, height = 36;
				AttackLeft = 1;
				attack = 1;
	//			if (!JumpTime) rigidBody ->SetGravity(GRAVITY - 3.0f);
			}
		}
	//-------------------------------SHOOT----------------------------------

	//	if (EventHandler::Event() ->GetKey(SDL_SCANCODE_K) && ShootDelay <= 0) {
	//		shoot -> SetProp("shoot", 0, 2, 200, tmp);
	//		ShootDelay = SHOOT_DELAY;
	//		ShootKey = 1;
	//	}
	//-------------------------------ROLL_RIGHT----------------------------------
		if (EventHandler::Event() -> GetKey(SDL_SCANCODE_L) && tmp == SDL_FLIP_NONE && !EventHandler::Event() ->GetKey(SDL_SCANCODE_J)) {
			rigidBody -> ApplyForceX(7 * FORWARD);
			// left buttom to +3 f.x
			animation -> SetProp("roll", 0, 5, 100, tmp);
			width = 56, height = 36;
	//		animation -> SetProp("player_jump", 0, 6, 80);
			// set animation from player_idle tp player_run (right)
		}
	//-------------------------------ROLL_LEFT----------------------------------
		if (EventHandler::Event() -> GetKey(SDL_SCANCODE_L) && tmp != SDL_FLIP_NONE && !EventHandler::Event() ->GetKey(SDL_SCANCODE_J)) {
			rigidBody -> ApplyForceX(7 * BACKWARD);
			// left buttom to +3 f.x
			animation -> SetProp("roll", 0, 5, 100, tmp);
			width = 56, height = 36;
		}
	//----------------------------RESET------------------------------------
		rigidBody -> Update(deltaTime);
		// update f_all, v, a, p with delta_t
		SavePoint.X = Position ->X;
		Position ->X = Position ->X + rigidBody -> GetPosition().X;
		// update Transform by Position of rigidBody
		HitBox ->SetRect(Position->X, Position->Y, 32, 32);

		if (CollisionHandling::Running() ->MapCollision(HitBox ->Get())) {
			Position ->X = SavePoint.X;
		}

		rigidBody -> Update(deltaTime);
		SavePoint.Y = Position ->Y;
	//	float a = Position ->Y, b = rigidBody -> GetPosition().Y;
	//	a = 2.6, b = 0;
	//	float c = a + b;
	//	SDL_Log("info: %f %f %f", a, b, c);
		Position ->Y = 0.0f + Position ->Y + rigidBody -> GetPosition().Y;
		HitBox ->SetRect(Position->X, Position->Y, 32, 32);
	//
		if (attack) {
			if (!AttackLeft) {
				SDL_Rect tmp = HitBox ->Get();
				Hit ->SetChange(0, 0, 0, 0);
				Hit ->SetRect(tmp.x + 32, tmp.y, 40, 32);
			}
			else {
				SDL_Rect tmp = HitBox ->Get();
				Hit ->SetChange(0, 0, 0, 0);
				Hit ->SetRect(tmp.x - 40, tmp.y, 40, 32);
			}
		}

		if (CollisionHandling::Running() ->MapCollision(HitBox ->Get())) {
			Position ->Y = SavePoint.Y;
			Grounded = true;
			if (Jumping && JumpTime) {
				JumpTime = 0;
			}
		}
		else {
			Grounded = false;
		}

//	SDL_Log("%f", Position ->X);
	if (Position ->X > 670.0 || Position ->X < 0.0) {
		if (!MapCode::Running() ->completed[stage]) {
			Position ->X = SavePoint.X;
			Position ->Y = SavePoint.Y;
		}
		else {
			if (Position ->X > 670.0) ++stage;
			else --stage;
			ChangeStageDelay = CHANGE_STAGE_DELAY;
		}
	}

	if ((stage == 8 || stage == 9) && MapCode::Running() ->completed[stage]) {
		if (EventHandler::Event() ->GetKey(SDL_SCANCODE_SPACE)) {
			++stage;
			ChangeStageDelay = CHANGE_STAGE_DELAY;
			Position -> X = 360.0;
			Position -> Y = 120.0;
		}
	}


	animation -> Update();

	// (milliseconds / speed of player ) % frame count -> frame to draw sprite
}

void Warrior::Clean() {
	TextureManager::Running() -> Clean();
}

void Warrior::ChangeStage(int id) {
	stage = id;
}

void Warrior::SetSize(int w, int h)
{
	width = w, height = h;
}

void Warrior::GetHit(float dt) {
	if (GetHitDelay == GET_HIT_DELAY_W) {
		HP -= 1;
	}
	GetHitDelay -= dt;
	if (GetHitDelay < 0) GetHitDelay = GET_HIT_DELAY_W;
}

bool Warrior::Alive() {
	if (HP) return true;
	return false;
}
