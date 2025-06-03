#include "plane_geometry.hpp"
#include <cmath>

namespace RT_ISICG
{
	

	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t1 ) const
	{
		float angle = glm::dot( this->getNormal(), p_ray.getDirection() );
		//le plan et le rayon non parallèles
		if ( angle != 0.f )
		{ 
			Vec3f po = this->get_Point() - p_ray.getOrigin();
			p_t1		 = glm::dot( po, this->getNormal() ) / angle;
			return true;
		}
		return false;
	}
} // namespace RT_ISICG
