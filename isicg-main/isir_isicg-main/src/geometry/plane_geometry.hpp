#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "geometry/base_geometry.hpp"
#include <glm/glm.hpp>

namespace RT_ISICG
{
	/// Géométrie d’un plan (infini) défini par un point et une normale
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry() = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_normale ) : _point( p_point ), _normal( p_normale ) {}
//		virtual ~PlaneGeometry() = default;
		inline const Vec3f & get_Point() const { return _point; }

		bool intersect( const Ray & p_ray, float & p_t1 ) const;

		Vec3f getNormal() const { return _normal; }

	  private:
		Vec3f _point  = { 0, 0, 0 };
		Vec3f _normal = { 0, 0, 0 };
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
