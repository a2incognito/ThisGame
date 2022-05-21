#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"

class Transform
{
	public:
		float X, Y;
	public:
		Transform(float x = 0, float y = 0) : X(x), Y(y) {}
	public:
		inline void TransX (float x) {X += x;};
		inline void TransY (float y) {Y += y;};
		inline void Trans (Vector v) {
			X += v.X;
			Y += v.Y;
		}
};

#endif // TRANSFORM_H
