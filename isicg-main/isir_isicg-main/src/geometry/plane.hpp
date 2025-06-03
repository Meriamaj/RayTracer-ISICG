#ifndef __RT_ISICG_PLANE__
#define __RT_ISICG_PLANE__

#include "plane_geometry.hpp"
#include "objects/base_object.hpp"

namespace RT_ISICG
{
	/// Objet Plan infini
	class Plane : public BaseObject
	{
	  public:
		Plane()			 = delete;
		virtual ~Plane() = default;

		Plane( const std::string & p_name, const Vec3f & p_point, const Vec3f & p_normal );

		// Intersection la plus proche (avec HitRecord)
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_rec ) const override;

		// Intersection any (shadow rays)
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		PlaneGeometry _geometry;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE__
