#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/PhongBRDF.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name,
						 const Vec3f &		 p_diffuse,
						 const Vec3f &		 p_reflec,
						 const float		 p_shininess )
			: BaseMaterial( p_name ), _LambertBRDF( p_diffuse ), _PhongBRDF( p_diffuse, p_reflec, p_shininess )
		{
		}
		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _LambertBRDF.evaluate();
				//   + _PhongBRDF.evaluate( p_hitRecord._normal, -p_ray.getDirection(), p_lightSample._direction ) * 0.3f;
		}

		inline const Vec3f & getFlatColor() const override { return _LambertBRDF.getKd(); }

	  protected:
		LambertBRDF _LambertBRDF;
		PhongBRDF	_PhongBRDF;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
