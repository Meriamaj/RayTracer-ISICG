#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v )
		const 
		{
		const Vec3f & origin	= p_ray.getOrigin();
		const Vec3f & direction = p_ray.getDirection();
		const Vec3f & v0		= _refMesh->_vertices[ _v0 ];
		const Vec3f & v1		= _refMesh->_vertices[ _v1 ];
		const Vec3f & v2		= _refMesh->_vertices[ _v2 ];

		constexpr float epsilon = std::numeric_limits<float>::epsilon();
		Vec3f e1, e2; e1 = v1 - v0;e2 = v2 - v0;

		Vec3f rayE2 = cross( direction, e2 ); float det	   = dot( e1, rayE2 );
		if ( det > -epsilon && det < epsilon ) return false;
		float inverseDet = 1.f / det;
		Vec3f se	 = origin - v0;
		p_u	 = inverseDet * dot( se, rayE2 );
		if ( p_u < 0.f || p_u > 1.f ) return false;
		Vec3f sCE1 = cross( se, e1 );
		p_v				  = inverseDet * dot( direction, sCE1 );
		if ( p_v < 0.f || p_u + p_v > 1.f ) return false;
		return VerifIntersc( inverseDet, e2, sCE1, epsilon, p_t );
	}

	bool TriangleMeshGeometry::VerifIntersc( float	inverseDet,RT_ISICG::Vec3f & e2,RT_ISICG::Vec3f & sCE1,const float epsilon,float & p_t ) const	{
		float t = inverseDet * dot( e2, sCE1 );
		if ( t > epsilon )
		{
			p_t = t;
			return true;
		}
		else
		{
			p_t = -1.f;
			return false;
		}
	}

	Vec3f TriangleMeshGeometry::NormalInterp( const float & p_u, const float & p_v ) const
	{
		Vec3f & n0 = _refMesh->_normals[ _v0 ];
		Vec3f & n1 = _refMesh->_normals[ _v1 ];
		Vec3f & n2 = _refMesh->_normals[ _v2 ];

		Vec3f normalInterpolated = normalize( ( 1 - p_u - p_v ) * n0 + p_u * n1 + p_v * n2 );
		return normalInterpolated;
	}

	const Vec3f & TriangleMeshGeometry::getSommet( int id ) const { return _refMesh->_vertices[ _v[ id ] ]; };

	const Vec3f TriangleMeshGeometry::getCentre()	{	return Vec3f( ( _refMesh->_vertices[ _v0 ] + _refMesh->_vertices[ _v1 ] + _refMesh->_vertices[ _v2 ] ) / 3.f );};

} // namespace RT_ISICG
