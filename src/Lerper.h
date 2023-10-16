#pragma once
namespace core
{
	class Lerper
	{
		public:
			enum LerpCurve {
				Linear,
				Smooth
			};
			enum LerpLoop {
				Clamp,
				Loop,
				PingPong,
			};

		Lerper(float startValue, float endValue, int numberOfSteps,LerpCurve lerpCurve, LerpLoop lerpLoop):_startValue(startValue),_endValue(endValue),_numberOfSteps(numberOfSteps),_lerpCurve(lerpCurve),_lerpLoop(lerpLoop) {};
		float GetValue(int step);
	private:

		float _startValue;
		float _endValue;
		int _numberOfSteps;
		LerpCurve _lerpCurve;
		LerpLoop _lerpLoop;
	};
}


