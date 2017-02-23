
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Windows.h>

#include "Application.h"


int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	auto app = Application::Create( "SKDX_exp_000" );
	return app->Run( );
}
