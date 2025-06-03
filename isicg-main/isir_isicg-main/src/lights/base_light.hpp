#ifndef __RT_ISICG_BASE_LIGHT__
#define __RT_ISICG_BASE_LIGHT__

#include "light_sample.hpp"

namespace RT_ISICG
{
    class BaseLight
    {
      public:
		BaseLight( const Vec3f & p_color, const float p_power, const bool p_isSurface )
			: _color( p_color ), _power( p_power ), _isSurface( p_isSurface )
		{
		}

		virtual ~BaseLight() = default;

        inline const Vec3f& getFlatColor() const { return _color; }
        inline bool isSurface() const { return _isSurface; }
		inline const float	getPower() const { return _power; }

        virtual LightSample sample(const Vec3f& p_point) const = 0;
      protected:
        Vec3f _color = WHITE;
        float _power ;
        bool  _isSurface = false;
    };
} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_LIGHT__