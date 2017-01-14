#include "Zeno/Interface/EventManager.h"
#include "Zeno/Interface/Window.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	EventManager::EventManager()
	{
		m_pWindow = nullptr;

		ZeroMemory( &m_Class, sizeof( m_Class ) );

		m_hInst = nullptr;

		m_Name = "ZenoWndClassName";
	}

	//-------------------------------------------------------------------------------------------------
	EventManager::~EventManager()
	{
		if ( m_pWindow )
		{
			delete m_pWindow;

			m_pWindow = nullptr;
		}
	}

	//-------------------------------------------------------------------------------------------------
	Window* EventManager::Initialise( WindowParams* pWndParams )
	{
		if ( m_pWindow )
		{
			return nullptr;
		}

		m_hInst = GetModuleHandle( 0 );

		m_Class.cbClsExtra = NULL;
		m_Class.cbSize = sizeof( WNDCLASSEX );
		m_Class.cbWndExtra = NULL;
		m_Class.hbrBackground = NULL;
		m_Class.hCursor = LoadCursor( NULL, IDC_ARROW );
		m_Class.hIcon = LoadIcon( NULL, IDI_WINLOGO );
		m_Class.hIconSm = LoadIcon( NULL, IDI_WINLOGO );
		m_Class.hInstance = m_hInst;
		m_Class.lpfnWndProc = WndProc;
		m_Class.lpszClassName = m_Name.c_str();
		m_Class.lpszMenuName = NULL;
		m_Class.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS; 

		if ( !RegisterClassEx( &m_Class ) ) 
		{
			m_hInst = nullptr;

			return false;
		}

		m_pWindow = new Window;

		if ( !m_pWindow->Create( pWndParams, m_hInst, m_Name ) )
		{
			return nullptr;
		}

		return m_pWindow;
	}

	//-------------------------------------------------------------------------------------------------
	WindowMessage EventManager::ProcessEvents( bool bEnablePolling )
	{
		MSG Msg;
		WindowMessage WndMsg;

		WndMsg.m_pWindow = m_pWindow;

		if ( !bEnablePolling )
		{
			GetMessage( &Msg, m_pWindow->GetHandle(), 0, 0 );
		}
		else
		{
			PeekMessage( &Msg, m_pWindow->GetHandle(), 0, 0, PM_REMOVE );
		}
	
		WndMsg.m_lParam = Msg.lParam;
		WndMsg.m_wParam = Msg.wParam;
		WndMsg.m_nMessage = Msg.message;

		TranslateMessage( &Msg );
		DispatchMessage( &Msg );

		return WndMsg;
	}

	//-------------------------------------------------------------------------------------------------
	void EventManager::Terminate()
	{
		m_pWindow->Destroy();

		if ( m_hInst ) 
		{
			UnregisterClass( m_Name.c_str(), m_hInst );

			m_hInst = nullptr;
		}
	}

	//-------------------------------------------------------------------------------------------------
	LRESULT CALLBACK EventManager::WndProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
	{
		switch ( nMsg )
		{
		case WM_CLOSE :
		case WM_DESTROY :
			{
				PostQuitMessage( 0 );
			}
			break;

		default:
			{
				return DefWindowProc( hWnd, nMsg, wParam, lParam );
			}
		}

		return 0;
	}
}
