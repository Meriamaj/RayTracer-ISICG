#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_object.hpp"

namespace RT_ISICG
{
	class ImplicitSurface : public BaseObject
	{
	  public:
		ImplicitSurface()		   = delete;
		virtual ~ImplicitSurface() = default;

		ImplicitSurface( const std::string & p_name ) : BaseObject( p_name ) {}

		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		// Check for any intersection between p_tMin and p_tMax.
		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		virtual float _sdf( const Vec3f & p_point ) const = 0;

		virtual Vec3f _evaluateNormal( const Vec3f & p_point ) const
		{
			/// TODO
			float fx= _sdf( p_point + Vec3f( _minDistance, 0.f, 0.f ) ) - _sdf( p_point - Vec3f( _minDistance, 0.f, 0.f ) );
			float fy= _sdf( p_point + Vec3f( 0.f, _minDistance, 0.f ) ) - _sdf( p_point - Vec3f( 0.f, _minDistance, 0.f ) );
			float fz= _sdf( p_point + Vec3f( 0.f, 0.f, _minDistance ) ) - _sdf( p_point - Vec3f( 0.f, 0.f, _minDistance ) );

			return glm::normalize( Vec3f( fx, fy, fz ) );
		}

	  private:
		const float _minDistance = 1e-4f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
