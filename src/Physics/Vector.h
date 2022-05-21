#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector
{
	public:
		float X, Y;
	public:
		Vector(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {}
		// init with default value (0, 0)
	public:
		inline Vector operator + (const Vector &op) const {
			return Vector (X + op.X, Y + op.Y);
		}

		inline Vector operator - (const Vector &op) const {
			return Vector (X - op.X, Y - op.Y);
		}

		inline Vector operator * (const float scalar) const {
			return Vector (X * scalar, Y * scalar);
		}

};

#endif // VECTOR_H
