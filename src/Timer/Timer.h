#ifndef TIMER_H
#define TIMER_H

const int FPS = 60;
const float DELTATIME = 2.0f;

class Timer
{
	public:
		inline static Timer* Running() {
			// make sure only 1 Timer run during programme
			return s_Running = (s_Running != nullptr) ? s_Running : new Timer();
		}
		void Tick();
		inline float GetDeltaTime() {return m_DeltaTime;}

	private:
		Timer() {}
		static Timer* s_Running;
		float m_DeltaTime;
		// use around code, DeltaTime is the time that occurs between two event
		// calc DeltaTime need LastTime
		float m_LastTime;
		// m_DeltaTime is the time that occurs between two event
		// call m_DeltaTime is delT
		// with delT, we can update position from velocity from accelertion from sumf
		// and sumf equal value x of frc Warrior : Update() -> ApplyForceX(x)
		// time unit: frame
		// length unit: pixel
};

#endif // TIMER_H
