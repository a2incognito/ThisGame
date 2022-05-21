#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector.h"

#define GRAVITY 6.0f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1
// because gravity directed down

class RigidBody
{
	public:
		RigidBody() {
			m_Gravity = 6.0f;
			m_Force = Vector();
			m_Position = Vector();
			m_Velocity = Vector();
			m_Acceleration = Vector();
		}

		//Set mass & gravity
		void SetGravity(float gravity) {m_Gravity = gravity;}

		//Set Force
		inline void ApplyForce (Vector vt) {m_Force = vt;}
		inline void ApplyForceX (float x) {m_Force.X = x;}
		inline void ApplyForceY (float y) {m_Force.Y = y;}
		inline void UnsetForce() {m_Force = Vector(0, 0);}

		//Set Acceleration
		inline void ApplyAccelerationY (float y) {m_Acceleration.Y = y;}

		//Get private member
		inline float GetGravity() {return m_Gravity;}
		inline Vector GetForce() {return m_Force;}
		inline Vector GetPosition() {return m_Position;}
		inline Vector GetVelocity() {return m_Velocity;}
		inline Vector GetAcceleration() {return m_Acceleration;}


		//Update
		void Update (float dt) {//deltaTime
			m_Acceleration.X = m_Force.X;
			m_Acceleration.Y = m_Gravity + m_Force.Y;
//			m_Acceleration.Y = m_Gravity + m_Force.Y;
			// update a by Newton's 2 Law
			m_Velocity.X = m_Acceleration.X * dt;
			m_Velocity.Y = m_Acceleration.Y * dt;
			// v = a * t
			m_Position = m_Velocity * dt;
//			SDL_Log("rigidbody.cpp %f %f", m_Position.X, m_Position.Y);
			// p = v * t
		}

	private:
		float m_Gravity; // g

		Vector m_Force; //f
		// running -> x-axis transform
		// jumping -> y-axis transform
		// f = m * a
		Vector m_Position;
		Vector m_Velocity; // v
		Vector m_Acceleration; // a
};

#endif // RIGIDBODY_H
