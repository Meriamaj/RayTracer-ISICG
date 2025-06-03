/*#include "QuadLight.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		float u = randomFloat();
		float v = randomFloat();
		Vec3f samplePoint = _position + u * _u + v * _v;

		// Debug log to verify sampling
		static int sampleCount = 0;
		if (sampleCount % 10000 == 0)
		{
			std::cout << "QuadLight sample point: (" << samplePoint.x << ", " << samplePoint.y << ", " << samplePoint.z
					  << "), Normal: (" << _n.x << ", " << _n.y << ", " << _n.z << ")" << std::endl;
		}
		sampleCount++;

		Vec3f direction = glm::normalize( samplePoint - p_point );
		float distance = glm::length( samplePoint - p_point );
		float cosThetaLight = glm::max( 0.001f, glm::dot( -direction, _n ) );

		float pdf = 1.f / _area;
		Vec3f radiance = _color * _power / _area;

		return LightSample( direction, distance, radiance, pdf );
	}
} // namespace RT_ISICG*/