#include "plane.hpp"

namespace RT_ISICG
{
	Plane::Plane( const std::string & p_name, const Vec3f & p_point, const Vec3f & p_normal )
		: BaseObject( p_name ), _geometry( p_point, p_normal )
	{
	}

	bool Plane::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_rec ) const
	{
		float t1, t2;
		if ( !_geometry.intersect( p_ray, t1 ) ) return false;

		if ( t1 < p_tMin || t1 > p_tMax ) return false;

		p_rec._distance = t1;
		p_rec._point	= p_ray.pointAt( t1 );
		p_rec._normal	= _geometry.getNormal();
		p_rec.faceNormal( p_ray.getDirection() );
		p_rec._object = this;
		return true;
	}

	bool Plane::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float t;
		if ( !_geometry.intersect( p_ray, t ) ) return false;
		return ( t >= p_tMin && t <= p_tMax );
	}

}
	
 // namespace RT_ISICG
