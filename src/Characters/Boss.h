#ifndef BOSS_H
#define BOSS_H

#include "Character.h"
#include "Animation.h"
#include "Checker.h"
#include <string>
#include "Vector.h"
#include "Transform.h"

#define GET_HIT_DELAY_B 30.0f
#define DELAY 15.0f

class Boss : public Character
{
  public:
    Boss(Properties* prop, Transform p);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();
    void DrawSpawn();
    void DrawIdle();
    void DrawAttack();
    void DrawFire();
    void DrawDeath();
    void GetHit(float dt);

    bool Alive() {return (HP != -1);}

  public:
    bool spawn;
    Animation* animation;

  public:
    int LastFrame, AnimationSpeed, FrameCount, CurrentFrame;
    int Frame = 1;
    float Delay;
    float GetHitDelay;
    bool hit, endHit, startHit;
    bool fire, endFire, startFire;
    bool startDeath;
    string id;
    Checker* HitBox;
    Checker* HitBoxAttack;
    Checker* HitBoxFire;
    Transform position;
    int width, height;
    bool start;
    bool gethit;
    bool dame;
};

#endif // BOSS_H
