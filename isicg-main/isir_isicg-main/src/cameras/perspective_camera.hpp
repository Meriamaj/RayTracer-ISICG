#ifndef RT_ISICG_PERSPECTIVE_CAMERA
#define RT_ISICG_PERSPECTIVE_CAMERA

#include "base_camera.hpp"

namespace RT_ISICG
{
	class PerspectiveCamera : public BaseCamera
	{
	  public:
		PerspectiveCamera( const float p_aspectRatio );

		PerspectiveCamera( const Vec3f & p_position,
						   const Vec3f & p_lookAt,
						   const Vec3f & p_up,
						   const float	 p_fovy,
						   const float	 p_aspectRatio );

		//Ray generateRay( float p_sx, float p_sy ) const override;

		inline Ray generateRay( const float p_sx, const float p_sy ) const override
		{
			Vec3f dir = _viewportTopLeftCorner + _viewportU * p_sx - _viewportV * p_sy - _position;

			return Ray( Vec3f( _position ), glm::normalize( dir ) );
		}
		~PerspectiveCamera() = default;

	  private:
		void _updateViewport();

	  private:
		float _fovy			 = 60.f;
		float _focalDistance = 1.f;
		float _aspectRatio	 = 1.f;

		// u, v et w
		Vec3f _u = Vec3f( 1.f, 0.f, 0.f );
		Vec3f _v = Vec3f( 0.f, 1.f, 0.f );
		Vec3f _w = Vec3f( 0.f, 0.f, -1.f );

		// Viewport data
		Vec3f _viewportTopLeftCorner = VEC3F_ZERO; // Top left corner position
		Vec3f _viewportU			 = VEC3F_ZERO; // Horizontal vector
		Vec3f _viewportV			 = VEC3F_ZERO; // Vertical vector

		/// <summary>
		/// ///////
		/// </summary>
		float _viewportHeight; // Hauteur du viewport
		float _viewportWidth;  // Largeur du viewport
	};
} // namespace RT_ISICG

#endif // RT_ISICG_PERSPECTIVE_CAMERA