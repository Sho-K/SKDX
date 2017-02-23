
#include "Application.h"
#include "Framework.h"
#include "Graphics.h"

using namespace SKDX::Framework;

std::shared_ptr< Application > Application::Create( const char* appName )
{
	std::shared_ptr< Application > app( new Application(appName) );
	return app;
}

Application::Application( const char* appName )
{
	window.reset( new SKDX::Framework::Window( appName, 800, 600) );
	graphics = std::make_shared< SKDX::Graphics::Graphics >( std::weak_ptr<SKDX::Framework::Window>(window) );
}

Application::~Application( )
{
	window = nullptr;
	graphics = nullptr;
}

int Application::Run( ){
	return SKDX::Framework::MessageLoop::Run( *window.get( ), std::bind(&Application::Draw, this) );
}

void Application::Draw( )
{
	graphics->Clear( 0.5f, 0.5f, 1.0f, 1.0f );
	graphics->Present( );
}