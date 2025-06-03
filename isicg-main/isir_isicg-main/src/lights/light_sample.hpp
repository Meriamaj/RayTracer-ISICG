#ifndef __RT_ISICG_LIGHT_SAMPLE__
#define __RT_ISICG_LIGHT_SAMPLE__

#include "defines.hpp"

namespace RT_ISICG
{
	struct LightSample
	{
	  public:
		LightSample( const Vec3f & p_direction, const float p_distance, const Vec3f & p_radiance, const float p_pdf )
			: _direction( p_direction ), _distance( p_distance ), _radiance( p_radiance ), _pdf( p_pdf )
		{
		}

		Vec3f _direction = VEC3F_ZERO; 
		float _distance	 = 0.f;
		Vec3f _radiance	 = WHITE; // Changed from WHITE to VEC3F_ZERO to avoid unexpected light
		
		float _pdf		 = 1.f;		 
		bool  isValid() const { return _pdf > 0.f && glm::length( _radiance ) > 0.f; }

	};
} // namespace RT_ISICG

#endif // __RT_ISICG_LIGHT_SAMPLE__