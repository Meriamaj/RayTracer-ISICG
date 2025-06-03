#ifndef __RT_ISICG_IMPLICIT_BOX__
#define __RT_ISICG_IMPLICIT_BOX__

#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitBox : public ImplicitSurface
	{
	  public:
		ImplicitBox()		   = delete;
		virtual ~ImplicitBox() = default;

		ImplicitBox( const std::string & p_name, const Vec3f & p_center, const Vec3f & p_size )
			: ImplicitSurface( p_name ), _center( p_center ), _size( p_size )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec3f d = glm::abs( p_point - _center ) - _size;
			return glm::length( glm::max( d, Vec3f( 0.0f ) ) )
				   + glm::min( glm::max( d.x, glm::max( d.y, d.z ) ), 0.0f );
		}

	  private:
		const Vec3f _center;
		const Vec3f _size;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_BOX__
