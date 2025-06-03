#ifndef __RT_ISICG_TRANSPARENT_MATERIAL__
#define __RT_ISICG_TRANSPARENT_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class TransparentMaterial : public BaseMaterial
	{
	  public:
		TransparentMaterial( const std::string & p_name ) : BaseMaterial( p_name ) {}

		virtual ~TransparentMaterial() = default;

		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const override
		{
			return BLACK;
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }
		inline const bool	 isTransparent() const override { return true; }
		inline float const	 getIor() const override { return _ior; }

	  protected:
		float _ior	 = 1.33f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
