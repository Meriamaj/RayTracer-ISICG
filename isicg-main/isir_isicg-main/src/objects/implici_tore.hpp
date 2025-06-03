#ifndef __RT_ISICG_IMPLICIT_TORE__
#define __RT_ISICG_IMPLICIT_TORE__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitTore : public ImplicitSurface
	{
	  public:
		ImplicitTore()			= delete;
		virtual ~ImplicitTore() = default;

		ImplicitTore( const std::string & p_name, const Vec3f & p_center, float pMaxRay, float pMinRay )
			: ImplicitSurface( p_name ), center( p_center ), MaxRay( pMaxRay ), MinRay( pMinRay )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override
		{
			float distance = glm::length( Vec2f( p_point - center ) ); Vec2f OE= Vec2f( distance - MaxRay, ( p_point - center ).z );
			return glm::length( OE ) - MinRay;
		}

	  private:
		const Vec3f center;
		const float MaxRay;
		const float MinRay;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_TORE__

