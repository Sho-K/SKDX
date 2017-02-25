
#pragma once

#include <memory>

namespace SKDX {
	class Transform;

	namespace Graphics {

		class Graphics;

		class RenderObject abstract {
		public:
			virtual ~RenderObject( );
			virtual void Draw( ) = 0;

			virtual void Dispose( ) {}

			const std::shared_ptr< Transform >& GetTransform( ) const { return transform; }
		protected:
			RenderObject( const std::shared_ptr< Graphics >& graphics );
			

			std::weak_ptr< Graphics > graphics;
			std::shared_ptr< Transform > transform;

		private:
			RenderObject( RenderObject& ) = delete;
			RenderObject& operator =( RenderObject& ) = delete;
		};
	};
};
