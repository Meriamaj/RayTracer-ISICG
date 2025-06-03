#ifndef __RT_ISICG_IMPLICIT_BLOB__
#define __RT_ISICG_IMPLICIT_BLOB__

#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitBlob : public ImplicitSurface
	{
	  public:
		ImplicitBlob()			= delete;
		virtual ~ImplicitBlob() = default;

		ImplicitBlob( const std::string & p_name, const Vec3f & p_center, const float p_radius )
			: ImplicitSurface( p_name ), _center( p_center ), _radius( p_radius )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override
		{
			// Variation d'une sphère avec effet "soft"
			float d = glm::length( p_point - _center );
			return d - _radius + 0.2f * sin( 4.0f * d );
		}

	  private:
		const Vec3f _center;
		const float _radius;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_BLOB__
