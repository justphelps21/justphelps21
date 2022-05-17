#ifndef __TIMER__
#define __TIMER__
#include <chrono>

class Timer
{
public:

	void Start();
	void End();

	unsigned DurationInNanoSeconds();
	unsigned DurationInMicroSeconds();
	unsigned DurationInMilliSeconds();

private:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
};

#endif