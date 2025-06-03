#ifndef __RT_ISICG_BRDF_BLINN_PHONG__
#define __RT_ISICG_BRDF_BLINN_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class BlinnPhongBRDF
	{
	  public:
		BlinnPhongBRDF( const Vec3f & p_kd, const Vec3f & p_ks, const float p_shininess )
			: _kd( p_kd ), _ks( p_ks ), _shininess( p_shininess )
		{
		}

		inline Vec3f evaluate( const Vec3f & normal,
							   const Vec3f & wo,		// direction d'observation
							   const Vec3f & wi ) const // direction d'incidence
		{
			Vec3f h		   = glm::normalize( wo + wi ); // demi-vecteur
			float cosTheta = glm::max( 0.f, glm::dot( normal, wi ) );
			float cosAlpha = glm::max( 0.f, glm::dot( normal, h ) );

			// Partie diffuse Lambertienne + partie spéculaire Blinn-Phong
			return _kd * INV_PIf + _ks * pow( cosAlpha, _shininess ) / glm::max( cosTheta, 0.0001f );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd;
		Vec3f _ks;
		float _shininess;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_BLINN_PHONG__
