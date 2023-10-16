#include "Lerper.h"
#include <math.h> 
#include <algorithm>

namespace core
{
	float Lerper::GetValue(int step)
	{
		float value = 0.0f;
		float endValue= _endValue;
		float startValue=_startValue;

		if (_lerpLoop==LerpLoop::PingPong)
		{
			if (static_cast<int>(ceil(step / _numberOfSteps)) % 2 == 1)
			{
				endValue = _startValue;
				startValue = _endValue;
				step = step % _numberOfSteps;
			}
		}
		else if (_lerpLoop==LerpLoop::Loop)
		{
			step = step % _numberOfSteps;
		}
		else if (_lerpLoop==LerpLoop::Clamp)
		{
			step = std::min(step, _numberOfSteps);
		}

		switch (_lerpCurve)
		{
		case Lerper::Linear:
			value = startValue + (endValue - startValue) * step / _numberOfSteps;
			break;
		case Lerper::Smooth:
			value = startValue + (endValue - startValue) * (1 - cos(step * 3.14 / _numberOfSteps)) / 2;
			break;
		}

		return value;
	}
}