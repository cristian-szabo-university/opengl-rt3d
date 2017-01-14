#include "Zeno/Interface/Window.h"

#include "Zeno/OpenGL.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	WindowMessage::WindowMessage()
	{
		m_pWindow = nullptr;

		m_nMessage = -1;

		m_lParam = 0;

		m_wParam = 0;
	}

	//-------------------------------------------------------------------------------------------------
	WindowParams::WindowParams( std::string Title )
	{
		m_Title = Title;

		m_nWidth = 640;

		m_nHeight = 480;

		m_nPosX = 0;

		m_nPosY = 0;

		m_bFullScreen = false;
	}

	//-------------------------------------------------------------------------------------------------
	Window::Window()
	{
		m_hWnd = nullptr;
	}

	//-------------------------------------------------------------------------------------------------
	Window::~Window()
	{

	}

	//-------------------------------------------------------------------------------------------------
	bool Window::Create( WindowParams* pWndParam, HINSTANCE hInst, std::string ClassName )
	{
		if ( m_hWnd != NULL ) 
		{
			return false;
		}
	
		DWORD dwStyle, dwStyleEx;

		if ( pWndParam->m_bFullScreen ) 
		{ 
			// Set style for full screen window
			dwStyle	= WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX;
			dwStyleEx = WS_EX_APPWINDOW; 
		}
		else 
		{	
			// Set style for windowed game
			dwStyle	= WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
			dwStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		}

		RECT rcWnd;

		// Correct window size so that active area is width x height
		rcWnd.left = 0;
		rcWnd.right	= pWndParam->m_nWidth;
		rcWnd.top = 0;
		rcWnd.bottom = pWndParam->m_nHeight;
	
		AdjustWindowRectEx( &rcWnd, dwStyle, FALSE, dwStyleEx );

		m_hWnd = CreateWindowEx(dwStyleEx,
			ClassName.c_str(), pWndParam->m_Title.c_str(),
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			0, 0,
			rcWnd.right  - rcWnd.left, // Window width	
			rcWnd.bottom - rcWnd.top,  // Window height
			NULL, NULL, hInst, NULL);

		if ( m_hWnd == NULL ) 
		{
			Destroy();

			return false;
		}

		m_hDC = GetDC( m_hWnd );

		if (m_hDC == NULL) 
		{
			Destroy();

			return false;
		}

		int m_nScreenWidth = GetSystemMetrics( SM_CXSCREEN );
		int m_nScreenHeight = GetSystemMetrics( SM_CYSCREEN );	

		// Center window on the screen if it is a window
		if ( !pWndParam->m_bFullScreen ) 
		{
			int nPosX = 0;
			int nPosY = 0;

			if ( m_nScreenWidth > pWndParam->m_nWidth ) 
			{
				nPosX = ( int )( ( m_nScreenWidth - pWndParam->m_nWidth ) / 2 );
			}
		
			if ( m_nScreenHeight > pWndParam->m_nHeight ) 
			{
				nPosY = ( int )( ( m_nScreenHeight - pWndParam->m_nHeight ) / 2 );
			}

			MoveWindow(m_hWnd, nPosX, nPosY, pWndParam->m_nWidth, pWndParam->m_nHeight, FALSE);

			SetCursorPos( m_nScreenWidth / 2, m_nScreenHeight / 2 );
		}

		// Define pixel format
		PIXELFORMATDESCRIPTOR pfd;

		ZeroMemory( &pfd, sizeof(pfd) );  

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.iLayerType = PFD_MAIN_PLANE;
	
		int iPixelFormat = ChoosePixelFormat( m_hDC, &pfd );

		if (!iPixelFormat) 
		{
			Destroy();

			return false;
		}

		if ( !SetPixelFormat( m_hDC, iPixelFormat, &pfd ) ) 
		{
			Destroy();

			return false;
		}

		m_hGLRC = wglCreateContext ( m_hDC );

		if ( m_hGLRC == NULL ) 
		{
			Destroy();

			return false;
		}

		if ( !wglMakeCurrent(m_hDC, m_hGLRC)) 
		{
			Destroy();

			return false;
		}

		// Create appropriate window
		if ( pWndParam->m_bFullScreen ) 
		{
			DEVMODE	dmScreenSettings;

			ZeroMemory( &dmScreenSettings, sizeof(dmScreenSettings) );

			dmScreenSettings.dmSize	= sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = pWndParam->m_nWidth;
			dmScreenSettings.dmPelsHeight = pWndParam->m_nHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				Destroy();

				return false;	
			}				
		}

		ShowWindow( m_hWnd, SW_SHOW );

		SetForegroundWindow( m_hWnd );

		SetFocus( m_hWnd );

		UpdateWindow( m_hWnd );

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	bool Window::SetupGL( int nVersionMajor, int nVersionMinor )
	{
		if ( !m_hWnd || nVersionMajor <= 2 )
		{
			return false;
		}

		const GLenum Error = glewInit();

		if ( GLEW_OK != Error ) 
		{
			return false;
		}

		if ( !wglewIsSupported("WGL_ARB_create_context") ) 
		{
			return false;
		}

		int nPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		int nContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, nVersionMajor,
			WGL_CONTEXT_MINOR_VERSION_ARB, nVersionMinor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		int nPixelFormat, nNumFormats;

		wglChoosePixelFormatARB( m_hDC, nPixelFormatAttribList, NULL, 1, &nPixelFormat, (UINT*)&nNumFormats);

		if ( wglewIsSupported("WGL_ARB_create_context") == 1 ) 
		{
			m_hGLRC = wglCreateContextAttribsARB( m_hDC, 0, nContextAttribs );

			wglMakeCurrent( m_hDC, m_hGLRC );
		} 

		if ( !m_hGLRC ) 
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	void Window::Present()
	{
		SwapBuffers( m_hDC );
	}

	//-------------------------------------------------------------------------------------------------
	void Window::Destroy()
	{
		// Deselect OpenGL rendering context
		if ( m_hDC ) 
		{
			wglMakeCurrent(m_hDC, NULL);
		}

		// Delete the OpenGL context
		if ( m_hGLRC ) 
		{
			wglDeleteContext(m_hGLRC);
		
			m_hGLRC = NULL;
		}

		// Dree memory for DC
		if ( m_hWnd && m_hDC ) 
		{
			ReleaseDC(m_hWnd, m_hDC);
		
			m_hDC = NULL;
		}

		if ( m_hWnd ) 
		{
			DestroyWindow( m_hWnd );
		
			m_hWnd = NULL;
		}
	}

	//-------------------------------------------------------------------------------------------------
	int Window::GetWidth()
	{
		RECT WndRect;

		GetClientRect( m_hWnd, &WndRect );

		return ( WndRect.left - WndRect.right );
	}

	//-------------------------------------------------------------------------------------------------
	int Window::GetHeight()
	{
		RECT WndRect;

		GetClientRect( m_hWnd, &WndRect );

		return ( WndRect.bottom - WndRect.top );
	}

	//-------------------------------------------------------------------------------------------------
	HWND Window::GetHandle()
	{
		return m_hWnd;
	}
}
