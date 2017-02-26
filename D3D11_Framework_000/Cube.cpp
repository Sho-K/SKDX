
#include "Cube.h"
#include "Graphics.h"
#include "VertexShader.h"


using namespace SKDX::Graphics::Geometries;
using namespace SKDX::Math;

std::shared_ptr< Cube > Cube::Create( const std::shared_ptr< SKDX::Graphics::Graphics >& graphics, const Vector3& size ) 
{
	std::shared_ptr< Cube > cube( new Cube(graphics) );
	cube->Initialize( size );
	return cube;
}

Cube::Cube( const std::shared_ptr< SKDX::Graphics::Graphics >& graphics ) : SKDX::Graphics::RenderObject( graphics )
{
}

Cube::~Cube( )
{
	Dispose( );
}

bool Cube::Initialize( const Vector3& size )
{
	Dispose( );

	this->size = size;
	InitPositions( );
	InitNormals( );
	InitTexCoords( );

	SKDX::VertexShader::Vertex vertices[28];
	for( int i=0; i<(int)ARRAYSIZE(vertices); ++i ) {
		vertices[i].position	= positions[i];
		vertices[i].normal		= normals[i];
		vertices[i].texCoords	= texCoords[i];
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage		= D3D11_USAGE_DEFAULT;
	bd.ByteWidth	= sizeof( SKDX::VertexShader::Vertex ) * 28;
	bd.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory( &initData, sizeof(initData) );
	initData.pSysMem = vertices;

	auto device = graphics.lock( )->GetDevice( );
	auto hr = device->CreateBuffer( &bd, &initData, &vertexBuffer );

	return SUCCEEDED( hr );
}

void Cube::Dispose( )
{
	vertexBuffer	= nullptr;

	positions.reset( nullptr );
	normals.reset( nullptr );
	texCoords.reset( nullptr );
}

void Cube::Draw( )
{
	auto immediateContext = graphics.lock( )->GetContext( );
	UINT offset = 0, stride = sizeof( SKDX::VertexShader::Vertex );
	immediateContext->IASetVertexBuffers( 0, 1, vertexBuffer.GetAddressOf(), &stride, &offset );
	immediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	immediateContext->Draw( 28, 0 );
}

void Cube::InitPositions( )
{
	int vertexCount = 28;
//	positions = std::shared_ptr< Vector3 >( new Vector3[vertexCount], std::default_delete<Vector3[]>() );
	positions = std::unique_ptr< Vector3[] >( new Vector3[vertexCount] );

	auto SetVec3ValArray = []( std::unique_ptr< Vector3[] >& p, Vector3* valueArr, int size ){
		for( int i=0; i<size; ++i ){
			p.get( )[i] = *(valueArr+i);
		}
	};

	auto x = size.x * 0.5f;
	auto y = size.y * 0.5f;
	auto z = size.z * 0.5f;
	Vector3 posData[] = {
		//	front
		{ -x, -y, -z }, { -x, +y, -z }, { +x, -y, -z }, { +x, +y, -z },
		//	right
		{ +x, -y, -z }, { +x, +y, -z }, { +x, -y, +z }, { +x, +y, +z },
		//	back
		{ +x, -y, +z }, { +x, +y, +z }, { -x, -y, +z }, { -x, +y, +z },
		//	left
		{ -x, -y, +z }, { -x, +y, +z }, { -x, -y, -z }, { -x, +y, -z },
		
		{ -x, +y, -z }, { -x, +y, -z },

		//	up
		{ -x, +y, -z }, { -x, +y, +z }, { +x, +y, -z }, { +x, +y, +z },

		{ -x, -y, -z }, { -x, -y, -z },

		//	down
		{ -x, -y, +z }, { -x, -y, -z }, { +x, -y, +z }, { +x, -y, -z },
	};
	SetVec3ValArray( positions, posData, ARRAYSIZE(posData) );

}

void Cube::InitNormals( )
{
	int vertexCount = 28;
	//normals = std::shared_ptr< Vector3 >( new Vector3[28], std::default_delete< Vector3[] >() );
	normals = std::unique_ptr< Vector3[] >( new Vector3[vertexCount] );

	auto SetNormal = []( Vector3* p, const Vector3& nrm ) -> Vector3*  {
		for( int i=0; i<4; ++i ){
			*p = nrm;
			++p;
		}
		return p;
	};
	auto p = normals.get( );
	p = SetNormal( p, Vector3::Backward );
	p = SetNormal( p, Vector3::Right );
	p = SetNormal( p, Vector3::Forward );
	p = SetNormal( p, Vector3::Left );
	p += 2;
	p = SetNormal( p, Vector3::Up );
	p += 2;
	p = SetNormal( p, Vector3::Down );
}

void Cube::InitTexCoords( )
{
	int vertexCount = 28;
//	texCoords = std::shared_ptr< Vector2 >( new Vector2[28], std::default_delete< Vector2[] >() );
	texCoords = std::unique_ptr< Vector2[] >( new Vector2[vertexCount] );

	auto SetTexCoord = []( Vector2* p ) -> Vector2* {
		*(p++) = Vector2( 0, 1 );
		*(p++) = Vector2( 0, 0 );
		*(p++) = Vector2( 1, 1 );
		*(p++) = Vector2( 1, 0 );
		return p;
	};
	auto p = texCoords.get( );
	for( int i=0; i<4; ++i ){
		p = SetTexCoord( p );
	}
	for( int i=0; i<2; ++i ){
		p += 2;
		p = SetTexCoord( p );
	}
}