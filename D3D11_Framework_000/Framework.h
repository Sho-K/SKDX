
#pragma once

#include <Windows.h>
#include <functional>
#include <memory>

namespace SKDX{
namespace Framework {

	class Window sealed {
	public:
		Window( const char* windowName, int width, int height );
		~Window( );

		HWND GetHandle( ) const { return handle; }
		HINSTANCE GetInstanceHandle( ) const { return instanceHandle; }
		const RECT& GetClientRect( ) const { return clientRect; } 
		int GetClientWidth( ) const { return clientRect.right - clientRect.left; }
		int GetClientHeight( ) const { return clientRect.bottom - clientRect.top; }
	private:
		Window( Window& ) = delete;
		Window& operator =( Window& ) = delete;

		
		static LRESULT CALLBACK WndProcLauncher( HWND, UINT, WPARAM, LPARAM );
		LRESULT CALLBACK WndProc(  HWND, UINT, WPARAM, LPARAM );

		void SetUserData( HWND hwnd );

		RECT clientRect;
		RECT windowRect;

		HWND		handle;
		HINSTANCE	instanceHandle;
		const char* name;
	};

	class MessageLoop sealed {
	public:
		static void SetFrameRate( unsigned int frameRate ) { FrameRate = frameRate; }
		static int Run( const Window& window, std::function<void(void)> function );
	private:
		MessageLoop( ) = delete;

		static unsigned int FrameRate;
		};
};
};
