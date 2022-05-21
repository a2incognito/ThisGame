#ifndef BAT_H
#define BAT_H

#include "Character.h"
#include "Animation.h"
#include "Checker.h"
#include <string>
#include "Vector.h"
#include "Transform.h"

class Bat : public Character
{
  public:
    Bat(Properties* prop, Transform p);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();

    void SetSize(int w, int h);
    bool Death();

    void PositionPlayer(Transform p);

  private:
  	float IdleTime;
    Checker* HitBox;
    Animation* animation;
    Transform position;
    Transform player;
    bool left;
    bool idle;
};
//
//class Bat : public Character
//{
//  public:
//    Bat(Properties* prop, Transform p);
//
//    virtual void Draw();
//    virtual void Update(float dt, Transform player);
//    virtual void Clean();
//    bool Death();
//
//    void SetSize(int w, int h);
//
//  private:
//    Checker* HitBox;
//    Animation* animation;
//    Transform position;
//    bool idle;
//    bool left;
//};

#endif // BAT_H
