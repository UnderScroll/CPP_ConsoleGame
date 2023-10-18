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

		Lerper(double startValue, double endValue, int numberOfSteps,LerpCurve lerpCurve, LerpLoop lerpLoop):_startValue(startValue),_endValue(endValue),_numberOfSteps(numberOfSteps),_lerpCurve(lerpCurve),_lerpLoop(lerpLoop) {};
		double GetValue(int step);
	private:

		double _startValue;
		double _endValue;
		int _numberOfSteps;
		LerpCurve _lerpCurve;
		LerpLoop _lerpLoop;
	};
}


