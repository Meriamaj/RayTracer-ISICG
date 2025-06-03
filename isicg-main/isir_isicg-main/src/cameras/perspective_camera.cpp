#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy, 
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// build camera basis (_u,_v,_w)
		// flip sign: direction = lookAt – position
		_w = glm::normalize( p_lookAt - _position );

		// don’t re-normalize p_up (already unit Y), only normalize the cross
		_u = glm::normalize( glm::cross( p_up, _w ) );
		_v = glm::cross( _w, _u );

		_updateViewport();
	}


	void PerspectiveCamera::_updateViewport()
	{
		
		float halfAng		 = glm::radians( _fovy ) * 0.5f;
		float viewportHeight = 2.0f * _focalDistance * tanf( halfAng );
		float viewportWidth	 = viewportHeight * _aspectRatio;

		_viewportU = _u * viewportWidth;
		_viewportV = _v * viewportHeight;

		_viewportTopLeftCorner = _position + ( _w * _focalDistance ) + ( _viewportV * 0.5f ) - ( _viewportU * 0.5f );
	}
} // namespace RT_ISICG
