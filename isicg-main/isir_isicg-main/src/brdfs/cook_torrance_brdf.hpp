#ifndef __RT_ISICG_BRDF_COOKTORRANCE__
#define __RT_ISICG_BRDF_COOKTORRANCE__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const float p_teta ) : _kd( p_kd ), _teta( p_teta ) {};

		inline Vec3f evaluate( const Vec3f & SurfaceNormal,
							   const Vec3f & ObservationDirection,
							   const Vec3f & IncidenceDirection ) const
		{
			// demi vecteur h.
			Vec3f h = glm::normalize( ObservationDirection + IncidenceDirection ); 
			//D pour NDF//G pour MASQUAGE selon smith model//F pour Fresnel
			float D, G;Vec3f F;
			// calcul angle incidence et observation
			float tetaObservation = glm::dot( SurfaceNormal, ObservationDirection );	float tetaIncidence	= glm::dot( SurfaceNormal, IncidenceDirection );

			D = CalculD( h, SurfaceNormal ); 
			G = CalculG1( glm::dot( SurfaceNormal, ObservationDirection ) )* CalculG1( glm::dot( SurfaceNormal, IncidenceDirection ) ); 
			F = Calculf( ObservationDirection, h );

			return D * F * G / 4.f * tetaObservation * tetaIncidence;
		}

		inline const Vec3f & getKd() const { return _kd; }
		float CalculD( const Vec3f & p_h, const Vec3f & p_SurfaceNormal ) const
		{
			float alpha = _teta * _teta;
			float cosnh = glm::dot( p_SurfaceNormal, p_h );
			return ( alpha * alpha ) / ( PIf * pow( cosnh * cosnh * ( alpha * alpha - 1.f ) + 1.f, 2 ) );
		}

		inline float CalculG1( const float p_x ) const {
			float k = ( _teta + 1.f ) * ( _teta + 1.f ) / 8.f;
			return p_x / ( p_x * ( 1.f - k ) + k );
		}

		inline Vec3f Calculf( const Vec3f & p_ObservationDirection, const Vec3f & p_h ) const
		{
			return _kd + ( 1.f - _kd ) * float( pow( 1.f - ( glm::dot( p_h, p_ObservationDirection ) ), 5 ) );
		}

	  private:
		Vec3f _kd = WHITE;float _teta;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_COOKTORRANCE__
