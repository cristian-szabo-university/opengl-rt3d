#pragma once

#include "Zeno/Config.h"

namespace Zeno
{
	class Window;

	// A structure that excapsulated the window message
	class ZENO_DLL WindowMessage
	{
	public:
		Window* m_pWindow;

		int m_nMessage;

		LPARAM m_lParam;

		WPARAM m_wParam;

		WindowMessage();

	};

	// A structure used by the user to define the window settings
	class ZENO_DLL WindowParams
	{
	public:
		std::string m_Title;

		int m_nWidth;

		int m_nHeight;

		int m_nPosX;

		int m_nPosY;

		bool m_bFullScreen;

		WindowParams( std::string Title );

	};

	class ZENO_DLL Window
	{
	public:
		Window();

		~Window();

		// Create the window
		bool Create( WindowParams* pWndParams, HINSTANCE hInst, std::string WndClassName );

		// Setup the OpenGL environment with a core profile
		bool SetupGL( int nVerMajor, int nVerMinor );

		// Show the framebuffer to window
		void Present();

		// Destroy the window
		void Destroy();

		int GetWidth();

		int GetHeight();

		HWND GetHandle();

	private:
		HWND m_hWnd;

		HDC	m_hDC;

		HGLRC m_hGLRC;

	};
}
