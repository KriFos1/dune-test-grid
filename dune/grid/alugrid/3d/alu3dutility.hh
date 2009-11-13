// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_ALU3DUTILITY_HH
#define DUNE_ALU3DUTILITY_HH

//- system includes
#include <vector>

//- local includes
#include "topology.hh"
#include "alu3dinclude.hh"

namespace Dune {

  template <class GeometryImp, int nChild>
  class LocalGeometryStorage
  {
    // array with pointers to the geometries
    std::vector < GeometryImp * > geoms_;
    // count local geometry creation
    int count_;
  public:
    // create empty storage
    LocalGeometryStorage () : geoms_ (nChild) , count_ (0)
    {
      for(size_t i=0 ; i<geoms_.size(); ++i) geoms_[i] = 0;
    }

    // desctructor deleteing geometries
    ~LocalGeometryStorage () {
      for(size_t i=0 ; i<geoms_.size(); ++i)
        if(geoms_[i]) delete geoms_[i];
    }

    // check if geometry has been created
    bool geomCreated(int child) const { return geoms_[child] != 0; }

    // create local geometry
    template <class GridImp, class Geometry>
    void create (const GridImp & grid, const Geometry & father,
                 const Geometry & son, const int child)
    {
      assert( !geomCreated(child) );
      assert( child >=0 && child < nChild );

      assert( count_ < nChild );
      ++count_;

      typedef typename GeometryImp :: ImplementationType ImplType;
      GeometryImp * g = new GeometryImp(ImplType());
      geoms_[child] = g;
      GeometryImp & geo = *g;
      grid.getRealImplementation(geo).buildGeomInFather( father, son );
    }

    // return reference to local geometry
    const GeometryImp & operator [] (int child) const
    {
      assert( geomCreated(child) );
      return *(geoms_[child]);
    }
  };

  //! \brief ALUGrid boundary projection implementation
  //!  DuneBndProjection has to fulfil the DuneBoundaryProjection interface
  template <class GridImp>
  class ALUGridBoundaryProjection : public ALU3DSPACE ProjectVertex
  {
    typedef GridImp GridType;
  protected:
    //! reference to boundary projection implementation
    const GridType& grid_;
  public:
    //! type of boundary projection
    typedef typename GridType :: DuneBoundaryProjectionType DuneBoundaryProjectionType;

    //! type of coordinate vector
    typedef typename DuneBoundaryProjectionType :: CoordinateType CoordinateType;

    //! constructor storing reference to boundary projection implementation
    ALUGridBoundaryProjection(const GridType& grid)
      : grid_( grid )
    {}

    //! (old) method projection vertices defaults to segment 0
    int operator () (const double (&orig)[3],
                     double (&prj)[3]) const
    {
      return this->operator()( orig, 0, prj);
    }

    //! method projection vertices
    int operator () (const double (&orig)[3],
                     const int segmentIndex,
                     double (&prj)[3]) const
    {
      // get boundary projection
      const DuneBoundaryProjectionType& bndPrj = grid_.boundaryProjection( segmentIndex );

      // call projection operator
      reinterpret_cast<CoordinateType &> (* (&prj[0])) =
        bndPrj( reinterpret_cast<const CoordinateType &> (* (&orig[0])) );

      // return 1 for success
      return 1;
    }
  };

  /////////////////////////////////////////////////////////////////////////
  //  some helper functions
  /////////////////////////////////////////////////////////////////////////

  inline const ALU3dImplTraits<tetra>::GEOFaceType*
  getFace(const ALU3DSPACE GEOTetraElementType& elem, int index) {
    assert(index >= 0 && index < 4);
    return elem.myhface3(ElementTopologyMapping<tetra>::dune2aluFace(index));
  }

  inline const ALU3dImplTraits<hexa>::GEOFaceType*
  getFace(const ALU3DSPACE GEOHexaElementType& elem, int index) {
    assert(index >= 0 && index < 6);
    return elem.myhface4(ElementTopologyMapping<hexa>::dune2aluFace(index));
  }

} // end namespace Dune
#endif
