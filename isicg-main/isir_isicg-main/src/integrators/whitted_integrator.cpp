#include "whitted_integrator.hpp"
namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return trace( p_scene, p_ray, p_tMin, p_tMax, true );
	}

	Vec3f WhittedIntegrator::trace( const Scene & p_scene,
									const Ray &	  p_ray,
									const float	  p_tMin,
									const float	  p_tMax,
									bool		  p_isNotInObject ) const
	{
		if ( p_ray.NbreBounces >= maxBounces ) return BLACK; 

		HitRecord hitRecord;
		//checks Material Type
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) ) 
		{
			if ( hitRecord._object->getMaterial()->isMirror() ) 
				return IntersecIsMirror( p_ray, hitRecord, p_scene, p_tMin, p_tMax, p_isNotInObject );

			else if ( hitRecord._object->getMaterial()->isTransparent() )
				return IntersectTransparent( p_ray, hitRecord, p_scene, p_tMin, p_tMax, p_isNotInObject );

			else { return _directLighting( p_scene, p_ray, p_tMin, p_tMax, hitRecord ); }
		}
	}

	const RT_ISICG::Vec3f & WhittedIntegrator::IntersectTransparent( const RT_ISICG::Ray &	 p_ray,
																	 RT_ISICG::HitRecord &	 hitRecord,
																	 const RT_ISICG::Scene & p_scene,
																	 const float			 p_tMin,
																	 const float			 p_tMax,
																	 bool					 p_isNotInObject ) const
	{
		{
			Vec3f reflect			 = glm::reflect( p_ray.getDirection(), hitRecord._normal );
			Ray * reflectedRay		 = new Ray( Vec3f( hitRecord._point ), glm::normalize( reflect ) );
			reflectedRay->NbreBounces = p_ray.NbreBounces + 1;
			reflectedRay->offset( hitRecord._normal );
			Vec3f reflex = trace(p_scene, *reflectedRay, p_tMin, p_tMax, p_isNotInObject ); 
			float ior = hitRecord._object->getMaterial()->getIor();
			float n1, n2;
			if ( p_isNotInObject ) { n1 = 1.f ; n2 = ior; }
			else { n1 = ior; n2 = 1.f; }
			
			float CosTetaI = glm::dot( -p_ray.getDirection(), hitRecord._normal ); float SinTetaI = glm::sin( glm::acos( CosTetaI ) );
			if ( SinTetaI > 1.f ) return reflex;

			float CosTetaT = glm::sqrt( 1.f - ( n1 / n2 ) * ( n1 / n2 ) * ( 1.f - CosTetaI * CosTetaI ) );
			float Rs	   = pow( abs( ( n1 * CosTetaI - n2 * CosTetaT ) / ( n1 * CosTetaI + n2 * CosTetaT ) ), 2 );

			float Rp = pow( abs( ( n2 * CosTetaT - n1 * CosTetaI ) / ( n2 * CosTetaT + n1 * CosTetaI ) ), 2 );
			float kr = 0.5f * ( Rs + Rp );

			if ( kr > 1.f ) return reflex;

			Vec3f refracted			 = glm::refract( p_ray.getDirection(), hitRecord._normal, n1 / n2 );
			Ray * refractedRay		 = new Ray( Vec3f( hitRecord._point ), glm::normalize( refracted ) );
			refractedRay->NbreBounces = p_ray.NbreBounces + 1;
			refractedRay->offset( -hitRecord._normal );
			Vec3f refract = trace( p_scene, *refractedRay, p_tMin, p_tMax, !p_isNotInObject );
			return reflex * kr + refract * ( 1.f - kr );
		}
	}

	const RT_ISICG::Vec3f & WhittedIntegrator::IntersecIsMirror( const RT_ISICG::Ray &	 p_ray, RT_ISICG::HitRecord &	 hitRecord,const RT_ISICG::Scene & p_scene,const float p_tMin, const float p_tMax, bool p_isNotInObject ) const{
		{
			Vec3f reflect			 = glm::reflect( p_ray.getDirection(), hitRecord._normal );
			Ray * reflectedRay		 = new Ray( Vec3f( hitRecord._point ), glm::normalize( reflect ) );
			reflectedRay->NbreBounces = p_ray.NbreBounces + 1;
			reflectedRay->offset( hitRecord._normal );
			return trace(p_scene, *reflectedRay, p_tMin, p_tMax, p_isNotInObject ); 
		}
	}

} // namespace RT_ISICG
