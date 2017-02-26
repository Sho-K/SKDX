
#include "Application.h"
#include "Framework.h"
#include "Graphics.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include "Transform.h"


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

	vertexShader	= SKDX::VertexShader::LoadFromFile( graphics, L"res/shaders/shader.fx" );
	pixelShader		= SKDX::PixelShader::LoadFromFile( graphics, L"res/shaders/shader.fx" );
	cube			= SKDX::Graphics::Geometries::Cube::Create( graphics, SKDX::Math::Vector3(5, 5, 5) );
}

Application::~Application( )
{
	vertexShader	= nullptr;
	pixelShader		= nullptr;
	cube			= nullptr;
	window			= nullptr;
	graphics		= nullptr;
}

int Application::Run( ){
	return SKDX::Framework::MessageLoop::Run( *window.get( ), std::bind(&Application::Draw, this) );
}

void Application::Draw( )
{
	graphics->Clear( 0.5f, 0.5f, 1.0f, 1.0f );

	SKDX::Math::Matrix4x4 view = SKDX::Math::Matrix4x4::Identity;
	SKDX::Math::Matrix4x4 proj = SKDX::Math::Matrix4x4::Identity;
	{
		auto eye	= SKDX::Math::Vector3::Backward * 10;
		auto look	= SKDX::Math::Vector3::Zero;
		view		= SKDX::Math::Matrix4x4::CreateLookAt( eye, look, SKDX::Math::Vector3::Up );
		proj		= SKDX::Math::Matrix4x4::CreatePersectiveFov( 70.0f*SKDX::Math::Deg2Rad, 1.33333f, 1.0f, 1000.0f );
	}

	auto transform = cube->GetTransform( );
	transform->Rotate( SKDX::Math::Vector3::Up, 0.0001f * SKDX::Math::Pi );
	transform->Update( );
	SKDX::VertexShader::Matrices matrices = { transform->GetMatrix(), view, proj };
	vertexShader->SetMatrices( matrices );
	
	vertexShader->Bind( );
	pixelShader->Bind( );

	cube->Draw( );

	graphics->Present( );
}