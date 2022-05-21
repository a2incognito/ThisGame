#ifndef WORM_H
#define WORM_H

#include "Character.h"
#include "Animation.h"
#include "Checker.h"
#include <string>
#include "Vector.h"
#include "Transform.h"

#define IDLE_TIME 30.0f

#define GET_HIT_DELAY 20.0f

class Worm : public Character
{
  public:
    Worm(Properties* prop, Transform *p);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();

    void SetSize(int w, int h);
    void GetHit(float dt);
    bool Death();
    Checker* GetHitBox();

  private:
  	float IdleTime, GetHitDelay, IdleDelay;
    Checker* HitBox;
    Animation* animation;
    Transform position;
    bool left;
    bool idle;
    bool gethit;
};
#endif // WORM_H
