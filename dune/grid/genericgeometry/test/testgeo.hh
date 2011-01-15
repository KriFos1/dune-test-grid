// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef TESTGEO_HH
#define TESTGEO_HH

#include <dune/common/polyallocator.hh>

#if HAVE_ALUGRID
#include <dune/grid/alugrid/3d/grid.hh>
#include <dune/grid/alugrid/3d/topology.hh>
#endif
#include <dune/grid/genericgeometry/geometry.hh>

namespace Dune
{

  template <int d1> class YaspGrid;
  template <int d1,int d2> class AlbertaGrid;
  template< int dim, int dimworld > class ALUSimplexGrid;
  template <int dim> class UGGrid;



  // Topology
  // --------

  template< class Grid >
  struct Topology;

  template< int d >
  struct Topology< YaspGrid< d > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: cube;
    static const int dimension = d;
    static const bool correctJacobian = false;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef typename Convert :: type Type;
  };

  template< int d >
  struct Topology< UGGrid< d > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: cube;
    static const int dimension = d;
    static const bool correctJacobian = false;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef typename Convert :: type Type;
  };

  template< int d >
  struct Topology< AlbertaGrid< d, d > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: simplex;
    static const int dimension = d;
    static const bool correctJacobian = false;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef typename Convert :: type Type;
  };

#if HAVE_ALUGRID
  template<>
  struct Topology< ALU3dGrid< tetra > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: simplex;
    static const int dimension = 3;
    static const bool correctJacobian = true;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef Convert :: type Type;
  };

  template<>
  struct Topology< ALUSimplexGrid< 3, 3 > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: simplex;
    static const int dimension = 3;
    static const bool correctJacobian = true;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef Convert :: type Type;
  };

  template<>
  struct Topology< ALUSimplexGrid< 2, 2 > >
  {
    static const GeometryType :: BasicType basicType = GeometryType :: simplex;
    static const int dimension = 2;
    static const bool correctJacobian = true;

    typedef GenericGeometry :: Convert< basicType, dimension > Convert;
    typedef Convert :: type Type;
  };
#endif


  // GeometryTraits
  // --------------

  namespace GenericGeometry
  {

    template< class Grid >
    struct GlobalGeometryTraits
    {
      typedef typename Grid :: template Codim< 0 > :: Geometry DuneGeometryType;

      typedef DuneCoordTraits< typename DuneGeometryType :: ctype > CoordTraits;

      static const int dimGrid = DuneGeometryType :: dimension;
      static const int dimWorld = DuneGeometryType :: coorddimension;

      static const bool hybrid = true;

      static const GeometryType :: BasicType linetype = GeometryType :: simplex;

      template< class Topology >
      struct Mapping
      {
        typedef CornerMapping< CoordTraits, Topology, dimWorld > type;
      };

      struct Caching
      {
        static const EvaluationType evaluateJacobianTransposed = ComputeOnDemand;
        static const EvaluationType evaluateJacobianInverseTransposed = ComputeOnDemand;
        static const EvaluationType evaluateIntegrationElement = ComputeOnDemand;
        static const EvaluationType evaluateNormal = ComputeOnDemand;
      };

      typedef Dune::PolyAllocator Allocator;
    };

  }



  // GeoCoordVector
  // --------------

  template< class Geo >
  struct GeoCoordVector
  {
    explicit GeoCoordVector( const Geo &geo )
      : geo_( geo )
    {}

    typename Geo::GlobalCoordinate operator[] ( const int i ) const
    {
      return geo_.corner( i );
    }

  private:
    const Geo &geo_;
  };

}

#endif // #ifndef TESTGEO_HH
