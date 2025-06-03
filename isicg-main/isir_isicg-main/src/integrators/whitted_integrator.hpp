#ifndef __RT_ISICG_WITTED_INTEGRATOR__
#define __RT_ISICG_WITTED_INTEGRATOR__

#include "integrators/direct_lighting_integrator.hpp"
namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }
		Vec3f trace( const Scene & p_scene,
					 const Ray &   p_ray,
					 const float   p_tMin,
					 const float   p_tMax,
					 bool		   p_isNotIn ) const;
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;
		Vec3f demiL( const Scene & p_scene, const Ray & p_ray, const float p_tMin );
		const RT_ISICG::Vec3f & IntersectTransparent( const RT_ISICG::Ray &	  p_ray,
													  RT_ISICG::HitRecord &	  hitRecord,
													  const RT_ISICG::Scene & p_scene,
													  const float			  p_tMin,
													  const float			  p_tMax,
													  bool					  p_isNotInObject ) const;

		const RT_ISICG::Vec3f & IntersecIsMirror( const RT_ISICG::Ray &	  p_ray,
												  RT_ISICG::HitRecord &	  hitRecord,
												  const RT_ISICG::Scene & p_scene,
												  const float			  p_tMin,
												  const float			  p_tMax,
												  bool					  p_isNotInObject ) const;

	  private:
		int _nbLightSamples = 1;
		int maxBounces		= 5;
		int count			= 0;

	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WITTED_INTEGRATOR__
