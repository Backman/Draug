#pragma once

#include <Windows.h>

namespace Draug {
class Timer {
public:
	inline Timer() {
		reset();
	}

	inline void reset() {
		QueryPerformanceFrequency(&m_freq);
		QueryPerformanceCounter(&m_first_tick);
		m_last_tick = m_first_tick;
	}

	inline float timeSinceStart() {
		LARGE_INTEGER curr_tick;
		QueryPerformanceCounter(&curr_tick);
		float dt = static_cast<float>((m_first_tick.QuadPart - m_last_tick.QuadPart) / m_freq.QuadPart);
		return dt;
	}

	inline float time() {
		LARGE_INTEGER curr_tick;
		QueryPerformanceCounter(&curr_tick);
		float dt = static_cast<float>((curr_tick.QuadPart - m_last_tick.QuadPart) / m_freq.QuadPart);
		return dt;
	}

	inline float tick() {
		LARGE_INTEGER curr_tick;
		QueryPerformanceCounter(&curr_tick);
		float dt = static_cast<float>((curr_tick.QuadPart - m_last_tick.QuadPart) / m_freq.QuadPart);
		m_last_tick = curr_tick;
		return dt;
	}

private:
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_first_tick;
	LARGE_INTEGER m_last_tick;
};
}
