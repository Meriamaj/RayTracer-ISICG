#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "aabb.hpp"
#include "base_geometry.hpp"

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const unsigned int p_v0,
							  const unsigned int p_v1,
							  const unsigned int p_v2,
							  MeshTriangle *	 p_refMesh );

		bool intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v ) const;

		bool VerifIntersc( float			 inverseDet,
						   RT_ISICG::Vec3f & e2,
						   RT_ISICG::Vec3f & sCrossEdge1,
						   const float		 epsilon,
						   float &			 p_t ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }
		Vec3f				 NormalInterp( const float & p_v, const float & p_u ) const;
		MeshTriangle *		 getRefMesh() { return _refMesh; };
		const Vec3f &		 getSommet( int id ) const;
		const Vec3f			 getCentre();

	  private:
		MeshTriangle * _refMesh;
		AABB		   _aabb;
		union
		{
			struct{	unsigned int _v0, _v1, _v2;};
			unsigned int _v[ 3 ] = { 0, 0, 0 };
		};

		Vec3f _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
