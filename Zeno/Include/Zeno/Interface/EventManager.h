#pragma once

#include "Zeno/Config.h"

namespace Zeno
{
	class Window;
	class WindowMessage;
	class WindowParams;

	class ZENO_DLL EventManager
	{
	public:
		EventManager();

		~EventManager();

		// Create a window based on user defines parameters
		Window* Initialise( WindowParams* pWndParams );

		// Get window message
		WindowMessage ProcessEvents( bool bEnablePolling );

		// Shutdown the system and window
		void Terminate();

	private:
		HINSTANCE m_hInst;

		WNDCLASSEX m_Class;

		std::string m_Name;

		Window* m_pWindow;

		static LRESULT CALLBACK WndProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam );

	};
}
