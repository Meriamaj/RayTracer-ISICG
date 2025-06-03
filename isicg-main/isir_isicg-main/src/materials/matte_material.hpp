#ifndef __RT_ISICG_MATTE_MATERIAL__
#define __RT_ISICG_MATTE_MATERIAL__

#include "base_material.hpp"

namespace RT_ISICG
{
	class MatteMaterial : public BaseMaterial
	{
	  public:
		MatteMaterial( const std::string & p_name, const Vec3f & p_diffuse, const float p_reflectance = 1.f )
			: BaseMaterial( p_name ), _diffuse( p_diffuse ), _reflectance( p_reflectance )
		{
		}

		Vec3f shade( const Ray &		 p_ray, const HitRecord &	 p_hitRecord, const LightSample & p_lightSample ) const override
		{
			return _diffuse * _reflectance * p_lightSample._radiance / p_lightSample._pdf;
		}

		inline const Vec3f & getFlatColor() const override { return _diffuse; }

	  private:
		Vec3f _diffuse;
		float _reflectance;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__