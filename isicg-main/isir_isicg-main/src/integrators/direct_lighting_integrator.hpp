﻿#ifndef __RT_ISICG_DIRECT_LIGHTING_INTEGRATOR__
#define __RT_ISICG_DIRECT_LIGHTING_INTEGRATOR__

#include "integrators/base_integrator.hpp"

namespace RT_ISICG
{
	class DirectLightingIntegrator : public BaseIntegrator
	{
	  public:
		DirectLightingIntegrator() : BaseIntegrator() {}
		virtual ~DirectLightingIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::DIRECT_LIGHT; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f _directLighting( const Scene &   p_scene,
							   const Ray &	   p_ray,
							   const float	   p_tMin,
							   const float	   p_tMax,
							   const HitRecord hitRecord ) const;

	  private:
		int _nbLightSamples = 1;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_RAY_CAST_INTEGRATOR__