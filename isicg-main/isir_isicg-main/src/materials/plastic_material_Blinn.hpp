#ifndef __RT_ISICG_PLASTIC_MATERIAL_BLINN__
#define __RT_ISICG_PLASTIC_MATERIAL_BLINN__

#include "base_material.hpp"
#include "brdfs/BlinnPhongBRDF.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterialBlinn : public BaseMaterial
	{
	  public:
		PlasticMaterialBlinn( const std::string & p_name,
							  const Vec3f &		  p_diffuse,
							  const Vec3f &		  p_specular,
							  const float		  p_shininess )
			: BaseMaterial( p_name ), _LambertBrdf( p_diffuse ), _BlinnPhongBrdf( p_diffuse, p_specular, p_shininess )
		{
		}

		virtual ~PlasticMaterialBlinn() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _LambertBrdf.evaluate() ;
				   //+ _BlinnPhongBrdf.evaluate( p_hitRecord._normal, -p_ray.getDirection(), p_lightSample._direction )
					//	 * 0.3f;
		}

		inline const Vec3f & getFlatColor() const override { return _LambertBrdf.getKd(); }

	  protected:
		LambertBRDF	   _LambertBrdf; BlinnPhongBRDF _BlinnPhongBrdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL_BLINN__
