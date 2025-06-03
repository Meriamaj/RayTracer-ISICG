#ifndef __RT_ISICG_AABB__
#define __RT_ISICG_AABB__

#include "ray.hpp"

namespace RT_ISICG
{
	struct AABB
	{
	  public:
		AABB() = default;
		AABB( const Vec3f & p_min, const Vec3f & p_max ) : _min( p_min ), _max( p_max ) {}
		~AABB() = default;
		inline const Vec3f & getMin() const { return _min; }
		inline const Vec3f & getMax() const { return _max; }
		inline bool isValid() const { return ( ( _min.x <= _max.x ) && ( _min.y <= _max.y ) && ( _min.z <= _max.z ) ); }
		inline void extend( const Vec3f & p_point )
		{
			_min = glm::min(_min, p_point);
			_max = glm::max(_max, p_point);
		}
		inline void extend( const AABB & p_aabb )
		{
			_min = glm::min(_min, p_aabb._min);
    		_max = glm::max(_max, p_aabb._max);
		}
		inline Vec3f diagonal() const { return _max - _min; }
		inline Vec3f centroid() const { return ( _min + _max ) * 0.5f; }

		inline size_t AxeMax() const
		{
			const Vec3f d = diagonal();
			if ( d.x > d.y && d.x > d.z )	return 0;
			else if ( d.y > d.z )	return 1;
			else return 2;
		}
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;
	  private:
		Vec3f _min = Vec3f( FLT_MAX );
		Vec3f _max = Vec3f( -FLT_MAX );
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_AABB__
