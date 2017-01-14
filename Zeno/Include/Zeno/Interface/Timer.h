#pragma once

#include "Zeno/Config.h"

namespace Zeno
{
	class ZENO_DLL Timer
	{
	public:
		Timer();

		~Timer();

		// Records current time in start variable
		void Start();

		// Records current time in stop variable
		void Stop();

		// Time since last Start call
		float Elapsed();

		// Time between last Start and Stop calls
		float Difference();

		// Get the current clock count
		LONGLONG Current();

	private:
		LARGE_INTEGER m_Freq;

		LARGE_INTEGER m_Start, m_Stop, m_Current;

		void Query( LARGE_INTEGER& Query );

	};
}
