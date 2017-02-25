
#pragma once

#include <memory>
#include "Transform.h"

namespace SKDX {
	namespace Graphics {

		class Graphics;

		class RenderObject abstract {
		public:
			virtual ~RenderObject( );
			virtual void Draw( ) = 0;

			virtual void Dispose( ) {}

			std::shared_ptr< Transform > GetTransform( ) const { return transform; }
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
