#include "Zeno/Interface/Timer.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	Timer::Timer( )
	{
		QueryPerformanceFrequency( &m_Freq );

		Start();

		Stop();
	}

	//-------------------------------------------------------------------------------------------------
	Timer::~Timer()
	{

	}

	//-------------------------------------------------------------------------------------------------
	void Timer::Start()
	{
		QueryPerformanceCounter( &m_Start );
	}

	//-------------------------------------------------------------------------------------------------
	void Timer::Stop()
	{
		QueryPerformanceCounter( &m_Stop );
	}

	//-------------------------------------------------------------------------------------------------
	float Timer::Elapsed()
	{
		QueryPerformanceCounter( &m_Current );

		return (m_Current.QuadPart - m_Start.QuadPart) / (float)m_Freq.QuadPart;
	}

	//-------------------------------------------------------------------------------------------------
	float Timer::Difference()
	{
		return (m_Stop.QuadPart - m_Start.QuadPart) / (float)m_Freq.QuadPart;
	}

	//-------------------------------------------------------------------------------------------------
	LONGLONG Timer::Current()
	{
		QueryPerformanceCounter( &m_Current );
  
		return m_Current.QuadPart;
	}
}
