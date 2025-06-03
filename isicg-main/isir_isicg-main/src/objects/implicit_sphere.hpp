#ifndef __RT_ISICG_IMPLICIT_SPHERE__
#define __RT_ISICG_IMPLICIT_SPHERE__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere()		  = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & p_name, const Vec3f & p_centre, const float & p_rayon ): ImplicitSurface( p_name ), centre( p_centre ), rayon( p_rayon ){}

		virtual float _sdf( const Vec3f & p_point ) const override { return glm::length( p_point - centre ) - rayon; }

	  private:
		const Vec3f centre;
		const float rayon;
		int count;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SPHERE__
