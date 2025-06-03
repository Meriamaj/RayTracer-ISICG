#include "scene.hpp"
#include "lights/QuadLight.hpp"
#include "geometry/plane.hpp"
#include "lights/point_light.hpp"
#include "materials/color_material.hpp"
#include "objects/base_object.hpp"
#include "objects/implicit_surface.hpp"
#include "objects/implicit_sphere.hpp"
#include "objects/sphere.hpp"
#include "objects/triangle_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "materials/base_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/transparent_material.hpp"
#include "materials/lambert_material.hpp"
#include "brdfs/PhongBRDF.hpp"
#include "materials/plastic_material.hpp"
#include "materials/plastic_material_Blinn.hpp"
#include "materials/microfacet_material.hpp"
using namespace RT_ISICG;

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init()
	{
		// Add materials (from Annexe A).
		_addMaterial( new ColorMaterial( "RedColor", RED ) );
		_addMaterial( new ColorMaterial( "GreenColor", GREEN ) );
		_addMaterial( new ColorMaterial( "BlueColor", BLUE ) );
		_addMaterial( new ColorMaterial( "GreyColor", GREY ) );
		_addMaterial( new ColorMaterial( "MagentaColor", MAGENTA ) );
		_addMaterial( new ColorMaterial( "YellowColor", YELLOW ) );
		_addMaterial( new ColorMaterial( "CyanColor", CYAN ) );

		// Add objects (from Annexe A).
		// Pseudo Cornell box made with infinite planes.
		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "GreyColor", "PlaneGround" );
		_addObject( new Plane( "PlaneLeft", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "RedColor", "PlaneLeft" );
		_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "GreenColor", "PlaneCeiling" );
		_addObject( new Plane( "PlaneRight", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "BlueColor", "PlaneRight" );
		_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( "MagentaColor", "PlaneFront" );
		_addObject( new Plane( "PlaneRear", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
		_attachMaterialToObject( "YellowColor", "PlaneRear" );

		// Add lights (from Annexe A).
		_addLight(
			new QuadLight( Vec3f( 0, 400, 100 ), Vec3f( 100, 0, 0 ), Vec3f( 0, 0, 100 ), Vec3f( 1, 1, 1 ), 1000 ) );
	}
	void Scene::initTP5() {
		// ================================================================
		// Add materials.
		// ================================================================
		//_addMaterial( new MatteMaterial( "default", Vec3f( 0, 0, 1 ), 1.f ) ); // Set reflectance to 1
		_addMaterial( new MatteMaterial( "WhiteMatte", WHITE, 0.6f ) );
		_addMaterial( new MatteMaterial( "RedMatte", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreenMatte", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( "BlueMatte", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreyMatte", GREY, 0.6f ) );
		_addMaterial( new MatteMaterial( "MagentaMatte", MAGENTA, 0.6f ) );
		_addMaterial( new MirrorMaterial( "Mirror" ) );
		_addMaterial( new TransparentMaterial( "Transaprent" ) );


		// ================================================================
		// Add objects.
		// ================================================================
		// Spheres.
		_addObject( new Sphere( "Sphere1", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( "transparent", "Sphere1" );
		_addObject( new Sphere( "Sphere2", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( "Mirror", "Sphere2" );
		// Pseudo Cornell box made with infinite planes.
		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "GreyMatte", "PlaneGround" );
		_addObject( new Plane( "PlaneLeft", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "RedMatte", "PlaneLeft" );
		_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "GreenMatte", "PlaneCeiling" );
		_addObject( new Plane( "PlaneRight", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "BlueMatte", "PlaneRight" );
		_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( "MagentaMatte", "PlaneFront" );
		// ================================================================
		// Add lights.
		// ================================================================
		_addLight( new PointLight( WHITE, 150.f, Vec3f( 0.f, 4.f, -3.f ) ) );
		/* _addLight(
			new QuadLight( Vec3f( 1.f, 5.f, -2.f ),
		Vec3f(-2.f, 0.f, 0.f ),
		Vec3f( 0.f, 1.f, 2.f ), WHITE, 170.f ) );
		//_addLight(new QuadLight( Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 100.f	) );
		*/
	}
	void Scene::initTp6() {
	

		/*//_addMaterial( new LambertMaterial( "GreyL", GREY ) );
		_addMaterial( new LambertMaterial( "RedL", RED ) );
		_addMaterial( new LambertMaterial( "GreyL", GREY ) );
		_addMaterial( new MatteMaterial( "GreyM", GREY, 1.f ) );
		//configuration de 70% 30% dans plastic material
		_addMaterial( new PlasticMaterial( "GreyP", GREY, GREY, 64.f ) );

		
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

		_attachMaterialToObject( "RedL", " PlaneGround " );
		_addObject( new Sphere( "Sphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		_attachMaterialToObject( "GreyP", "Sphere" );*/
		//_addMaterial( new LambertMaterial( "RedLa", RED ) );
		//_addMaterial( new MatteMaterial( "RedMat", RED ) );
		//_addMaterial( new PlasticMaterialBlinn( "RedP", RED, RED, 128.f ) ); // Phong classique puis changé à Blinn
		//_attachMaterialToObject( "RedP", " PlaneGround " );

		
		//objets 
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		//_addObject( new Sphere( "Sphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
	    //materials
		_addMaterial( new PlasticMaterial( "RedP", RED, RED, 128.f ) );
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 1.f ) );
		
		_attachMaterialToObject( "RedP", " PlaneGround " );
		_attachMaterialToObject( "Gold", "Sphere" );
		loadFileTriangleMesh( "Bunny", "data/Bunny.obj" );
		_attachMaterialToObject( "Gold", "Bunny_defaultobject" );
		_addLight( new PointLight( WHITE, 80.f, Vec3f( 1.f, 0.f, -2.5f ) ) );
	}

	void Scene::init7() {
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "RedP", " PlaneGround " );

		_addObject( new ImplicitSphere( "implicitSphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		_attachMaterialToObject( "Gold", "implicitSphere" );
		_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 0.f, -2.f ) ) );



	}
	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		//const aiScene * const scene = importer.ReadFile(
			//p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_FlipUVs );
		const aiScene * const scene
			= importer.ReadFile( p_path,
								 aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FixInfacingNormals
									 | aiProcess_GenUVCoords | aiProcess_FlipUVs );
		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		unsigned int cptTriangles = 0;
		unsigned int cptVertices  = 0;

		// Variables pour calculer la bounding box
		Vec3f minBounds = Vec3f( FLT_MAX, FLT_MAX, FLT_MAX );
		Vec3f maxBounds = Vec3f( -FLT_MAX, -FLT_MAX, -FLT_MAX );

#pragma omp parallel for
		for ( int m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName );
			for ( unsigned int v = 0; v < mesh->mNumVertices; ++v )
			{
				Vec3f vertex = Vec3f( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addVertex( vertex.x, vertex.y, vertex.z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );

				// Mettre à jour les bornes
				minBounds.x = std::min( minBounds.x, vertex.x );
				minBounds.y = std::min( minBounds.y, vertex.y );
				minBounds.z = std::min( minBounds.z, vertex.z );
				maxBounds.x = std::max( maxBounds.x, vertex.x );
				maxBounds.y = std::max( maxBounds.y, vertex.y );
				maxBounds.z = std::max( maxBounds.z, vertex.z );
			}
			for ( unsigned int f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}
			_addObject( triMesh );

			triMesh->createBVH();

			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{
				std::cerr << "Material undefined, " << meshName << " assigned to default material" << std::endl;
				_attachMaterialToObject( "DefaultMaterial", meshName );
			}
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;

		// Afficher la bounding box
		std::cout << "Scene bounding box: Min(" << minBounds.x << ", " << minBounds.y << ", " << minBounds.z
				  << "), Max(" << maxBounds.x << ", " << maxBounds.y << ", " << maxBounds.z << ")" << std::endl;

		// Ajouter le quad lumineux pour la scène "conference"
		 if ( p_name == "conference" )
		{
			/*_addLight( new QuadLight( Vec3f( 900, 600, -330 ), // Adjusted position to be above the scene
									  Vec3f( -800, 0, 0 ),	// _u
									  Vec3f( 0, 0, 300 ),	// _v
									  WHITE,		// White color
									  200000.f				// Reduced power for balanced lighting
									  ) );*/
		}
	}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;

		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance;
				hit	 = true;
			}
		}

		return hit;
	}

	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		for ( const ObjectMapPair & object : _objectMap )
			if ( object.second->intersectAny( p_ray, p_tMin, p_tMax ) ) return true;
		return false;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::_addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			std::cout << "Material \'" << name << "\' added." << std::endl;
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }


	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else { _objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] ); }
	}

	
} // namespace RT_ISICG
