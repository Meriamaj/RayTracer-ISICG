#ifndef __RT_ISICG_RENDERER__
#define __RT_ISICG_RENDERER__

#include "cameras/base_camera.hpp"
#include "defines.hpp"
#include "integrators/base_integrator.hpp"
#include "texture.hpp"
#include "utils/chrono.hpp"
#include "integrators/direct_lighting_integrator.hpp"
namespace RT_ISICG
{
	class Renderer
	{
	  public:
		Renderer();
		~Renderer() { delete _integrator; }

		void setIntegrator( const IntegratorType p_integratorType );
		void setBackgroundColor( const Vec3f & p_color );

		inline void setNbPixelSamples( const int p_nbPixelSamples ) { _nbPixelSamples = p_nbPixelSamples; }
		inline void setIntegratorNbLightSamples( const int p_nbPixelSamples ) {
			if ( _integrator->getType() == IntegratorType::DIRECT_LIGHT ) {
				DirectLightingIntegrator* directLightingIntegrator = dynamic_cast<DirectLightingIntegrator*>(_integrator);
			
			}
		}

		float renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture );

	  private:
		BaseIntegrator * _integrator	 = nullptr;
		int				 _nbPixelSamples = 1;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_RENDERER__
