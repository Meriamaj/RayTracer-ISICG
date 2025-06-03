#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO
		_root = new BVHNode();

		_buildRec( _root, 0, p_triangles->size(), 1 );

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		/// TODO
		for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ ) 
		{
			//ajoutSommets
			p_node->_aabb.extend(( *_triangles )[ i ].getSommet( 0 ) ); 
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 1 ) );
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 2 ) );
		}
		p_node->_firstTriangleId = p_firstTriangleId;
		p_node->_lastTriangleId	 = p_lastTriangleId;

		if ( p_depth >= _maxDepth || _maxTrianglesPerLeaf >= p_lastTriangleId - p_firstTriangleId )
			return; 
		Vec3f middle = p_node->_aabb.centroid();
		int	  axe	 = p_node->_aabb.AxeMax(); 
		/* int AxeMax()
		{
			const Vec3f d = diagonal();
			if ( d.x > d.y && d.x > d.z )
				return 0;
			else if ( d.y > d.z )
				return 1;
			else
				return 2;
		*/
		std::function<bool( TriangleMeshGeometry )> DIVISE;

		DIVISE = [ middle, axe ]( TriangleMeshGeometry triangle ) -> bool 
		{ return triangle.getCentre()[ axe ] < middle[ axe ]; };

		std::vector<TriangleMeshGeometry>::iterator Milieu= std::partition(_triangles->begin() + p_firstTriangleId,_triangles->begin() + p_lastTriangleId,DIVISE );

		int id = std::distance( _triangles->begin(), Milieu );

		// on initialise les deux noeuds enfants.

		p_node->_left  = new BVHNode();
		p_node->_right = new BVHNode();

		_buildRec( p_node->_left, p_firstTriangleId, id, p_depth + 1 );
		_buildRec( p_node->_right, id, p_lastTriangleId, p_depth + 1 );

		// on partitionne les triangles selon l'axe le plus grand
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO

		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
			return false; // on vérifie d'abord s'il intersecte l'aabb du noeud

		// dans la feuille

		if ( p_node->isLeaf() )
		{
			bool isIntersection = false;

			for ( int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId;  i++ ){
				float t, u, v;
				float tClosest = 0;
				bool  first	   = true;
				if ( _triangles->at( i ).intersect(
						 p_ray, t, u, v ) ) 
				{
					if ( t >= p_tMin && t <= p_tMax )
					{
						if ( p_hitRecord._object == nullptr || t < p_hitRecord._distance ) 							
						{
							p_hitRecord._point	  = p_ray.pointAt( t );
							p_hitRecord._normal	  = _triangles->at( i ).NormalInterp( u, v );
							p_hitRecord._distance = t;
							p_hitRecord._object	  = reinterpret_cast<BaseObject *>( _triangles->at( i ).getRefMesh() );
							p_hitRecord.faceNormal( p_ray.getDirection() );
							isIntersection = true;
						}
					}
				}
			}
			return isIntersection;
		}
		//pas une feuille
		else 
		{
			if ( p_node->_left != nullptr )
				_intersectRec(
					p_node->_left,
					p_ray,
					p_tMin,
					p_tMax,
					p_hitRecord );
			if ( p_node->_right != nullptr ) _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, p_hitRecord );
		}
		return false;
	}

	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		/// TODO
		// verif intersection aabb
		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )return false; 

		if ( p_node != nullptr )
		{
			//verif feuille ou non
			bool tr;
			bool Value = nodeNormal( p_node, p_ray, p_tMin, p_tMax, tr );
			if ( tr ) return Value;
			bool tr2;
			bool Value2 = LeafNode( p_node, p_ray, p_tMin, p_tMax, tr2 );
			if ( tr ) return Value2;
		}
		return false;
	}

	bool BVH::LeafNode( const RT_ISICG::BVHNode * p_node,
						const RT_ISICG::Ray &	  p_ray,
						const float				  p_tMin,
						const float				  p_tMax,
						bool &					  retFlag ) const
	{
		retFlag = true;
		for ( int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId;
			  i++ ) 
		{
			float t, u, v;
			if ( _triangles->at( i ).intersect(p_ray, t, u, v ) )
			{
				if ( t >= p_tMin && t <= p_tMax ){return true;}
			}
		}
		retFlag = false;
		return {};
	}
	bool BVH::nodeNormal( const RT_ISICG::BVHNode * p_node,
						  const RT_ISICG::Ray &		p_ray,
						  const float				p_tMin,
						  const float				p_tMax,
						  bool &					retFlag ) const
	{
		retFlag = true;
		if ( !p_node->isLeaf() )
		{
			if ( p_node->_left != nullptr )
				if ( _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax ) ) return true;

			if ( p_node->_right != nullptr )
				if ( _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax ) ) return true;
		}
		retFlag = false;
		return {};
	}
} // namespace RT_ISICG
