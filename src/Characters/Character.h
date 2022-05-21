#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>
// inherit GameObject.h

class Character : public GameObject
{
	public:
		Character(Properties* prop) : GameObject (prop) {}

//		virtual void Draw() = 0;
//		virtual void Update(float dt) = 0;
//		virtual void Clean() = 0;
	public:
		string m_Name;
		int HP, maxHP;


};

#endif // CHARACTER_H
