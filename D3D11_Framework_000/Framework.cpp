
#include "Framework.h"
using namespace SKDX::Framework;

Window::Window( const char* windowName, int width, int height )
{
	this->name = windowName;
	instanceHandle = GetModuleHandle( nullptr );

	const WNDCLASSEX wc = {
		sizeof( WNDCLASSEX ),
		CS_VREDRAW | CS_HREDRAW,
		WndProcLauncher,
		0, 0, 
		instanceHandle,
		LoadIcon( nullptr, IDI_APPLICATION ),
		LoadCursor( nullptr, IDC_ARROW ),
		(HBRUSH)GetStockObject( WHITE_BRUSH ),
		nullptr,
		name,
		LoadIcon( nullptr, IDI_APPLICATION )
	};
	RegisterClassEx( &wc );

	clientRect = { 0, 0, width, height };
	windowRect = clientRect;

	RECT desktopRect;
	GetWindowRect( GetDesktopWindow(), &desktopRect );
	int x = ( desktopRect.right  - width )	/ 2;
	int y = ( desktopRect.bottom - height ) / 2;

	auto windowStyle = WS_OVERLAPPED | WS_SYSMENU;
	AdjustWindowRect( &windowRect, windowStyle, false );
	int w = ( windowRect.right	- windowRect.left );
	int h = ( windowRect.bottom	- windowRect.top );
	handle = CreateWindow( name, name, windowStyle, x, y, w, h, nullptr, nullptr, instanceHandle, (void*)this );
}

Window::~Window( )
{
	UnregisterClass( name, instanceHandle );
}

LRESULT CALLBACK Window::WndProcLauncher( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
{
	auto thisPtr = (Window*)GetWindowLong( hwnd, GWL_USERDATA );
	if( thisPtr == nullptr ){
		if( msg == WM_CREATE ) thisPtr = (Window*)((CREATESTRUCT*)lp)->lpCreateParams;
		if( thisPtr != nullptr ) thisPtr->SetUserData( hwnd );
	}
	if( thisPtr != nullptr ) return thisPtr->WndProc( hwnd, msg, wp, lp );
	return DefWindowProc( hwnd, msg, wp, lp );
}

LRESULT CALLBACK Window::WndProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
{
	switch( msg ){
	case WM_CREATE:		return 1L;
	case WM_DESTROY:	PostQuitMessage( 0 ); break;
	case WM_CLOSE:		DestroyWindow( hwnd ); break;
	case WM_KEYDOWN:
		if( wp == VK_ESCAPE ) SendMessage( hwnd, WM_CLOSE, 0, 0L ); 
		break;

	default:			return DefWindowProc( hwnd, msg, wp, lp );
	}
	return 0L;
}

void Window::SetUserData( HWND hwnd )
{
	SetWindowLong( hwnd, GWL_USERDATA, (LONG)(void*)this );
}


unsigned int MessageLoop::FrameRate = 60;

int MessageLoop::Run( const Window& window, std::function< void(void) > func )
{
	ShowWindow( window.GetHandle(), SW_SHOW );
	UpdateWindow( window.GetHandle() );
	MSG msg = { 0 };
	while( msg.message != WM_QUIT ) {
		if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}else{
			func( );
		}
	}
	return (int)msg.wParam;
}

