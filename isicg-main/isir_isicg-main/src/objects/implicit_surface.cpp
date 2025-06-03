#include "implicit_surface.hpp"

namespace RT_ISICG
{
	//https://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/#the-raymarching-algorithm
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		/// TODO
		float mn = p_tMin; float dist = _sdf( p_ray.getOrigin() + mn * p_ray.getDirection() ); 
		// on compare chaque fois la distance par rapport au min (epsilon)
		while ( dist> _minDistance ) 
		{//calcul et m-à-j de distance dans chaque itér
			dist = _sdf( p_ray.getOrigin() + mn * p_ray.getDirection() ); 
											 
			mn += dist;						  
			//condition arrêt
			if ( mn > p_tMax ) return false; 
		}

		p_hitRecord._distance = mn; p_hitRecord._object	  = this;
		p_hitRecord._point	  = Vec3f( p_ray.getOrigin() + mn * p_ray.getDirection() );
		p_hitRecord._normal = _evaluateNormal( p_ray.getOrigin() + mn * p_ray.getDirection() );
		p_hitRecord.faceNormal( p_ray.getDirection() );

		return true;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		float min = p_tMin;
		float dist = _sdf( p_ray.getOrigin() + min * p_ray.getDirection() ); 
		while ( dist > _minDistance )
		{
			dist = _sdf( p_ray.getOrigin() + min * p_ray.getDirection() );								
			min += dist; 
			if ( min > p_tMax ) { return false; }
		}
		return true;

	}
} // namespace RT_ISICG
