#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;
		Texture img = Texture( imgWidth, imgHeight );
		Scene scene;

		//scene.init(); // tp4
		
		//scene.loadFileTriangleMesh( "conference", DATA_PATH + "conference/conference.obj" );
		
		//scene.initTP5();
		
		//scene.initTp6();
		scene.init7();
		// Create a perspective camera.
		
		/* PerspectiveCamera camera( Vec3f( 0.f, 2.f, -5.f ), // Vec3f( 0.f, 2.f, -7.f ) tp4
								  Vec3f( 0.f, 0.f, 79.f),
								  Vec3f( 0.f, 0.f, 1.f ),
								  40.f,
								  float( imgWidth ) / imgHeight );*/
		/* PerspectiveCamera camera( Vec3f( 0.f, 1.f, -7.f ), // Position de la caméra (en hauteur, en arrière)
								  Vec3f( 0.f, 0.f, 0.f ),  // Point regardé (le centre de la scène)
								  Vec3f( 0.f, 1.f, 0.f ),  // Up vector
								  40.f,					   // Champ de vision
								  float( imgWidth ) / imgHeight );
*/

		PerspectiveCamera camera( Vec3f( 0.f, 0.1f, -3.f ), // Vec3f( 0.f, 2.f, -7.f ) tp4
								  Vec3f( 0.f, 0.f, 79.f ),
								  Vec3f( 0.f, 0.f, 1.f ),
								  80.f,
								  float( imgWidth ) / imgHeight );
		//PerspectiveCamera camera(Vec3f( -250, 500, 330 ), Vec3f( 0, 350, 100 ), Vec3f( 0, 1, 0 ), 70, float( imgWidth ) / imgHeight );
		/* PerspectiveCamera camera( Vec3f( 300, 250, 200 ),	// Position rapprochée et ajustée
								  Vec3f( 300, 150, -100 ), // Regarde le centre estimé des objets principaux
								  Vec3f( 0, 1, 0 ),		   // Up
								  60.0f,				   // FOV
								  float( imgWidth ) / imgHeight );*/
		/* PerspectiveCamera camera( Vec3f( 0, 150, 300 ), // Position ajustée
								  Vec3f( 0, 100, 0 ),	// Regarde le centre estimé
								  Vec3f( 0, 1, 0 ),		// Up
								  60.0f,				// FOV
								  float( imgWidth ) / imgHeight );*/

		Renderer renderer;
		renderer.setIntegrator( IntegratorType::DIRECT_LIGHT );
		renderer.setNbPixelSamples(4);						
		renderer.setIntegratorNbLightSamples(1);
		renderer.setBackgroundColor( GREY );

		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;
		const std::string imgName = "tp7-ImpliciteSphere.jpg";

		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}