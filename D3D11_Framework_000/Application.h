
#pragma once

#include <memory>

namespace SKDX{
	namespace Framework {
		class Window;
	};
	namespace Graphics{
		class Graphics;
	};
};


class Application {
public:
	static std::shared_ptr< Application > Create( const char* applicationName );
	~Application( );
	int Run( );
private:
	Application( const char* appName );
	Application( Application& ) = delete;
	Application& operator =( Application& ) = delete;

	void Draw( );

	std::shared_ptr< SKDX::Framework::Window >		window;
	std::shared_ptr< SKDX::Graphics::Graphics >		graphics;
};

