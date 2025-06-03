#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		const Vec3f & origin	= p_ray.getOrigin();
		const Vec3f & direction = p_ray.getDirection();
		float tmin = p_tMin;
		float tmax = p_tMax;
		for ( int i = 0; i < 3; ++i )
		{
			if ( std::abs( direction[ i ] ) < 1e-8f ) 
			{
				if ( origin[ i ] < _min[ i ] || origin[ i ] > _max[ i ] )
					return false; 
				continue;
			}

			float invD = 1.f / direction[ i ];
			float t0   = ( _min[ i ] - origin[ i ] ) * invD;
			float t1   = ( _max[ i ] - origin[ i ] ) * invD;

			if ( invD < 0.f ) std::swap( t0, t1 );

			tmin = glm::max( tmin, t0 );
			tmax = glm::min( tmax, t1 );
		}

		return tmax > tmin; 
	}
} // namespace RT_ISICG