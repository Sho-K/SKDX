
#pragma once

#include <memory>

namespace SKDX{
	namespace Framework {
		class Window;
	};
	class VertexShader;
	class PixelShader;

	namespace Graphics{
		class Graphics;
		namespace Geometries{ class Cube; };
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

	std::shared_ptr< SKDX::Graphics::Geometries::Cube > cube;
	std::shared_ptr< SKDX::VertexShader >	vertexShader;
	std::shared_ptr< SKDX::PixelShader >		pixelShader;

	std::shared_ptr< SKDX::Framework::Window >		window;
	std::shared_ptr< SKDX::Graphics::Graphics >		graphics;
};

