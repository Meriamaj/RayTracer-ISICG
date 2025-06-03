#ifndef __RT_ISICG_RAY__
#define __RT_ISICG_RAY__

#include "defines.hpp"

namespace RT_ISICG
{
	class Ray
	{
	  public:
		Ray() = delete;
		Ray( const Vec3f & p_origin, const Vec3f & p_direction ) : _origin( p_origin ), _direction( p_direction ) {}

		inline const Vec3f & getOrigin() const { return _origin; }
		inline const Vec3f & getDirection() const { return _direction; }
		inline Vec3f pointAt( const float p_t ) const { return _origin + _direction * p_t; }

		inline void offset( const Vec3f p_normal )
		{
			/// TODO
			//static const float EPS = 1e-4f;
			this->_origin += 0.01f * p_normal;
		
		}
		int NbreBounces = 0;

	  private:
		Vec3f _origin	 = VEC3F_ZERO;
		Vec3f _direction = VEC3F_ZERO;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_RAY__
