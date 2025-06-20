#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta...
			
			Vec3f N			= hitRecord._normal;
			Vec3f V			= -p_ray.getDirection();
			float cosTheta	= glm::max( glm::dot( N, V ), 0.0f );
			Vec3f baseColor = hitRecord._object->getMaterial()->getFlatColor();
			return baseColor * cosTheta;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
