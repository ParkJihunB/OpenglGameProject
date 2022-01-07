#pragma once
#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer() : timeStamp(clock_t::now()) {}

	void ResetTimeStamp() { timeStamp = clock_t::now(); }

	float GetElapsedSeconds() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - timeStamp).count();
	}

	void CalFps()
	{
		const auto delta_time_seconds = GetElapsedSeconds();
		ResetTimeStamp();
		fpsEllapsedTime += delta_time_seconds;
		++fpsFrames;
		if (fpsEllapsedTime >= 1.0f)
		{
			std::cout << int(fpsFrames / fpsEllapsedTime) << std::endl;
			fpsEllapsedTime = 0;
			fpsFrames = 0;
		}
	}

private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<float, std::ratio<1>>;

	std::chrono::time_point<clock_t> timeStamp;

	float fpsEllapsedTime = 0;
	int fpsFrames = 0;
};