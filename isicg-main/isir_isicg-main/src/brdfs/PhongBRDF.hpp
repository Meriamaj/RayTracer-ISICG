#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd, const Vec3f & p_reflec, const float p_shininess )	: _kd( p_kd ), _reflec( p_reflec ), _shininess( p_shininess ) {};
		inline Vec3f evaluate( const Vec3f & SurfaceNormal,
							   const Vec3f & ObservationDirection,
							   const Vec3f & IncidenceDirection ) const
		{
			float tetaObser = glm::dot( SurfaceNormal, ObservationDirection );
			float tetaInc	= glm::dot( SurfaceNormal, IncidenceDirection );
			//
			Vec3f Wr = glm::reflect( -IncidenceDirection, SurfaceNormal ); 

			float cosThetaI = glm::max(	0.f, glm::dot( SurfaceNormal, IncidenceDirection ) ); 
			
			float cosAlpha = glm::max(0.f, glm::dot( ObservationDirection, Wr ) ); 

			Vec3f h = glm::normalize( ObservationDirection + IncidenceDirection ); 
			cosAlpha = glm::max(0.f, glm::dot( SurfaceNormal, h ) ); 

			return _kd * INV_PIf + _reflec / cosThetaI * pow( cosAlpha, _shininess );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd	  = WHITE;
		Vec3f _reflec = WHITE;
		float _shininess;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
