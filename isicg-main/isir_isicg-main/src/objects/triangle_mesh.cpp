#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	bool MeshTriangle::intersect( const Ray & p_ray,
								  const float p_tMin,
								  const float p_tMax,
								  HitRecord & p_hitRecord ) const
	{
		float  u, v;
		float  tClosest = p_tMax;			 
		size_t hitTriID	= _triangles.size(); 
		for ( size_t i = 0; i < _triangles.size(); i++ )
		{
			float t, uTemp, vTemp;
			if ( _triangles[ i ].intersect( p_ray, t, uTemp, vTemp ) ) 
			{
				if ( t >= p_tMin && t <= tClosest )
				{
					tClosest = t;
					hitTriID = i;
					u		 = uTemp;
					v		 = vTemp;
				}
			}
		}
		if ( hitTriID != _triangles.size() ) 
		{
			p_hitRecord._point	= p_ray.pointAt( tClosest );
			p_hitRecord._normal = _triangles[ hitTriID ].NormalInterp( u, v );
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = tClosest;
			p_hitRecord._object	  = this;

			return true;
		}

		return false;
		return _bvh.intersect( p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool MeshTriangle::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		for ( size_t i = 0; i < _triangles.size(); i++ )
		{
			float t, u, v;
			if ( _triangles[ i ].intersect( p_ray, t, u, v ) )
			{
				if ( t >= p_tMin && t <= p_tMax ) return true; 
			}
		}
		return false;
	}

	void MeshTriangle::createBVH() { _bvh.build( &_triangles ); };
} // namespace RT_ISICG
