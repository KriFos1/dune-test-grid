// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_GENERICGEOMETRY_MAPPINGS_HH
#define DUNE_GENERICGEOMETRY_MAPPINGS_HH

#include <dune/common/smallobject.hh>

#include <dune/grid/genericgeometry/misc.hh>
#include <dune/grid/genericgeometry/topologytypes.hh>
#include <dune/grid/genericgeometry/referenceelements.hh>
#include <dune/grid/genericgeometry/matrix.hh>
#include <dune/grid/genericgeometry/submapping.hh>
#include <dune/grid/genericgeometry/cornermapping.hh>
#include <dune/grid/genericgeometry/geometricmapping.hh>
#include <dune/grid/genericgeometry/hybridmapping.hh>

namespace Dune
{

  namespace GenericGeometry
  {

    // CachedMapping
    // -------------

    template< class Topology, class GeometricMappingTraits >
    class CachedMapping
      : public GeometricMapping< Topology, GeometricMappingTraits >,
        public SmallObject
    {
      typedef GeometricMapping< Topology, GeometricMappingTraits > Base;
      typedef CachedMapping< Topology, GeometricMappingTraits > This;

      static const unsigned int dimension = Topology :: dimension;

      typedef typename GeometricMappingTraits :: template Traits< dimension > Traits;

    public:
      enum { dimG = Traits :: dimG };
      enum { dimW = Traits :: dimW };
      typedef typename Traits :: FieldType FieldType;
      typedef typename Traits :: LocalCoordType LocalCoordType;
      typedef typename Traits :: GlobalCoordType GlobalCoordType;
      typedef typename Traits :: JacobianType JacobianType;
      typedef typename Traits :: JacobianTransposedType JacobianTransposedType;

      typedef typename Traits :: CachingType CachingType;
      typedef typename Base :: ReferenceElement ReferenceElement;

      template< unsigned int codim >
      struct Codim
      {
        typedef typename SubMappingTraits< This, codim > :: SubMapping SubMapping;
        typedef typename SubMappingTraits< This, codim > :: CachingType CachingType;
      };

    public:
      unsigned int referenceCount;

    protected:
      using Base :: baryCenter;
      using Base :: jacobianTransposed_;
      using Base :: jTInv_;
      using Base :: intEl_;
      using Base :: jacobianTransposedComputed_;
      using Base :: jTInvComputed;
      using Base :: intElComputed;

    public:
      template< class CoordVector >
      inline explicit CachedMapping ( const CoordVector &coords,
                                      const CachingType &cache = CachingType() );

      using Base :: affine;
      using Base :: operator[];
      using Base :: global;
      using Base :: local;
      using Base :: volume;
      using Base :: normal;
      using Base :: jacobianInverseTransposed;

      const JacobianTransposedType &jacobianT ( const LocalCoordType &x ) const
      {
        const EvaluationType evaluate = CachingType :: evaluateJacobianTransposed;
        if( (evaluate == ComputeOnDemand) || !affine() )
          Base :: jacobianT( x );
        return jacobianTransposed_;
      }

      // additional methods
      FieldType integrationElement ( const LocalCoordType &x ) const
      {
        const EvaluationType evaluate = CachingType :: evaluateIntegrationElement;
        if( (evaluate == ComputeOnDemand) || !affine() )
          Base :: integrationElement(x);
        return this->intEl_;
      }

      const JacobianType &jacobianInverseTransposed ( const LocalCoordType &x ) const
      {
        const EvaluationType evaluate = CachingType :: evaluateJacobianInverseTransposed;
        if( (evaluate == ComputeOnDemand) || !affine() )
          Base :: jacobianInverseTransposed(x);
        return this->jTInv_;
      }

      template< unsigned int codim >
      typename Codim< codim > :: SubMapping *
      subMapping ( unsigned int i,
                   const typename Codim< codim > :: CachingType &cache ) const
      {
        return SubMappingProvider< This, codim > :: subMapping( *this, i, cache );
      }
    };



    template< class Topology, class GeometricMappingTraits >
    template< class CoordVector >
    inline CachedMapping< Topology, GeometricMappingTraits >
    :: CachedMapping ( const CoordVector &coords, const CachingType &cache )
      : Base( coords )
    {
      if( affine() )
      {
        switch( CachingType :: evaluateJacobianTransposed )
        {
        case IsComputed :
          cache.jacobianT( jacobianTransposed_ );
          jacobianTransposedComputed_ = true;
          break;

        case PreCompute :
          Base :: jacobianT( baryCenter() );
          break;

        case ComputeOnDemand :
          break;
        }

        switch( CachingType :: evaluateJacobianInverseTransposed )
        {
        case IsComputed :
          cache.jacobianInverseTransposed( jTInv_ );
          jTInvComputed = true;
          break;

        case PreCompute :
          Base :: jacobianInverseTransposed( baryCenter() );
          break;

        case ComputeOnDemand :
          break;
        }

        switch( CachingType :: evaluateIntegrationElement )
        {
        case IsComputed :
          cache.integrationElement( intEl_ );
          intElComputed = true;
          break;

        case PreCompute :
          integrationElement( baryCenter() );
          break;

        case ComputeOnDemand :
          break;
        }
      }
    }

  }

}

#endif
