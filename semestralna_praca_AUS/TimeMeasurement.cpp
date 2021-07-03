#include "TimeMeasurement.h"

TimeMeasurement::TimeMeasurement()
{
	reset();
}

void TimeMeasurement::start()
{
	if (!started_)
	{
		timeStart_ = clock_.now();
		started_ = true;
	}
}

void TimeMeasurement::stop()
{
	if (started_)
	{
		timeSum_ += std::chrono::duration_cast<TimeMeasurement::TimerUnits>(clock_.now() - timeStart_);
		started_ = false;
	}
}

void TimeMeasurement::reset()
{
	timeSum_ = TimeMeasurement::TimerUnits::zero();
	started_ = false;
}

TimeMeasurement::TimerUnits TimeMeasurement::elapsed()
{
	return timeSum_;
}