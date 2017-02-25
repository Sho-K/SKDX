
#pragma once

#include <memory>

namespace SKDX {
	class Transform;

	namespace Graphics {
		class RenderObject abstract {
		public:
			virtual void Draw( ) = 0;

			const std::shared_ptr< Transform >& GetTransform( ) const { return transform; }
		protected:
			std::shared_ptr< Transform > transform;
		};
	};
};
