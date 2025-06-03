#ifndef __RT_ISICG_MICROFACET_MATERIAL__
#define __RT_ISICG_MICROFACET_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/cook_torrance_brdf.hpp"
#include "brdfs/PhongBRDF.hpp"
namespace RT_ISICG
{
	class MicrofacetMaterial : public BaseMaterial
	{
	  public:
		MicrofacetMaterial( const std::string & p_name,
							const Vec3f &		p_diffuse,
							const float			p_teta,
							const float			p_metalness )
			: BaseMaterial( p_name ), _CookTorrancebrdf( p_diffuse, p_teta ),
			  _lambertBrdf( p_diffuse ), 
			  _metalness( p_metalness ){};

		virtual ~MicrofacetMaterial() = default;

	LambertBRDF _lambertBrdf = LambertBRDF( _CookTorrancebrdf.getKd() );

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f n	 = p_hitRecord._normal; Vec3f wi = p_lightSample._direction;	Vec3f wo = -p_ray.getDirection();

			Vec3f diffuse  = _lambertBrdf.evaluate();
			Vec3f specular = _CookTorrancebrdf.evaluate( n, wo, wi );

			return ( 1.f - _metalness ) * diffuse + _metalness * specular;
		}


		inline const Vec3f & getFlatColor() const override { return _CookTorrancebrdf.getKd(); }

	  protected:
		CookTorranceBRDF _CookTorrancebrdf;
		float			 _metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MICROFACET_MATERIAL__
