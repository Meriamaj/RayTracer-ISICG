#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "integrators/base_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include <chrono> 

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator();}

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator ) delete _integrator;
		switch ( p_integratorType )
		{
		case IntegratorType::DIRECT_LIGHT:
		{
			_integrator = new DirectLightingIntegrator();
			break;
		}
		case IntegratorType::RAY_CAST:
		{
		default: _integrator = new RayCastIntegrator(); break;
		}
		case IntegratorType::WHITTED:
		{
			_integrator = new WhittedIntegrator();
			break;
		}
		}
	}
	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();

		auto debut = std::chrono::high_resolution_clock::now();
		//paralléliser boucle avec openMP temps réduit de 10s à 2s
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				// 1) Centre du pixel en [0,1]
				//float sx = ( i + 0.5f ) / float( width - 1 );
				//float sy = ( j + 0.5f ) / float( height - 1 );
				
				// 2) Générer le rayon primaire
				//Ray ray = p_camera->generateRay( sx, sy );

				// 3) Utiliser l’intégrateur pour la couleur
				//Vec3f color = _integrator->Li( p_scene, ray, 0.f, FLT_MAX );

				// 4) Écrire le pixel
				//p_texture.setPixel( i, j, glm::clamp( color, 0.0f, 1.0f ) );
				Vec3f color1;


				 Vec3f accumColor( 0.0f );
				// cast _nbPixelSamples rays per pixel
				 color1 = { 0.f, 0.f, 0.f };
				 // Vec3f color=(ray.getDirection() + 1.f) * 0.5f;
				 // Lancer _nbPixelSamples rayons par pixel
				 for ( int comp = 0; comp < _nbPixelSamples; comp++ )
				 {
					 Ray ray = p_camera->generateRay( ( i + randomFloat() ) / ( width - 1.f ),
													  ( j + randomFloat() ) / ( height - 1.f ) );
					 // Ray ray = p_camera->generateRay( x, y );

					 color1 += _integrator->Li( p_scene, ray, 0.f, 1000 );
				 }
				 // p_texture.setPixel( i, j, (color1 / (float) _nbPixelSamples ));
				 //clamping values between 0 & 1 
				 p_texture.setPixel( i,
									 j,
								 glm::clamp( ( color1 / (float)_nbPixelSamples ), 0.f,1.f ) ); 
			}
			progressBar.next();
		}
		auto fin = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = fin - debut;
		std::cout << "Temps de rendu : " << duration.count() << " secondes" << std::endl;

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
