// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_UGGRIDGEOMETRY_HH
#define DUNE_UGGRIDGEOMETRY_HH

/** \file
 * \brief The UGGridElement class and its specializations
 */

#include "uggridrenumberer.hh"
#include <dune/common/fixedarray.hh>
#include <dune/common/fmatrix.hh>

namespace Dune {

  template<int mydim, int coorddim, class GridImp>
  class UGGridGeometry;

  template<int mydim, int coorddim, class GridImp>
  class UGMakeableGeometry : public Geometry<mydim, coorddim, GridImp, UGGridGeometry>
  {
    typedef typename GridImp::ctype UGCtype;
  public:
    UGMakeableGeometry() :
      Geometry<mydim, coorddim, GridImp, UGGridGeometry>(UGGridGeometry<mydim, coorddim, GridImp>())
    {};

    void setToTarget(typename UG_NS<coorddim>::template Entity<coorddim-mydim>::T* target) {
      this->realGeometry.setToTarget(target);
    }

    void setToTarget(typename UG_NS<coorddim>::template Entity<coorddim-mydim>::T* target,
                     const GridImp* myGrid) {
      this->realGeometry.setToTarget(target, myGrid);
    }

    void setCoords (int n, const UGCtype* pos) {
      this->realGeometry.setCoords(n,pos);
    }

    void coordmode ()
    {
      this->realGeometry.coordmode();
    }
  };

  template<class GridImp>
  class UGMakeableGeometry<2,3,GridImp> : public Geometry<2, 3, GridImp, UGGridGeometry>
  {
    typedef typename GridImp::ctype UGCtype;

  public:
    UGMakeableGeometry() :
      Geometry<2, 3, GridImp, UGGridGeometry>(UGGridGeometry<2,3,GridImp>())
    {};

    void setCoords(int n, const UGCtype* pos) {
      for (int i=0; i<3; i++)
        this->realGeometry.coord_[n][i] = pos[i];
    }

    void setCoords(int n, const FieldVector<UGCtype,3>& pos) {
      this->realGeometry.coord_[n] = pos;
    }

    void setNumberOfCorners(int n) {
      this->realGeometry.setNumberOfCorners(n);
    }

    void setIsoparametricOrder(unsigned int order) {
      this->realGeometry.isoparametricOrder_ = order;
    }

  };

  template<class GridImp>
  class UGMakeableGeometry<1,2,GridImp> : public Geometry<1, 2, GridImp, UGGridGeometry>
  {
    typedef typename GridImp::ctype UGCtype;

  public:
    UGMakeableGeometry() :
      Geometry<1, 2, GridImp, UGGridGeometry>(UGGridGeometry<1,2,GridImp>())
    {};

    void setCoords(int n, const UGCtype* pos) {
      for (int i=0; i<2; i++)
        this->realGeometry.coord_[n][i] = pos[i];
    }

    void setCoords(int n, const FieldVector<UGCtype,2>& pos) {
      this->realGeometry.coord_[n] = pos;
    }
    // Empty.  Boundary elements in a 2d grid have always two corners
    void setNumberOfCorners(int n) {}

    void setIsoparametricOrder(unsigned int order) {
      this->realGeometry.isoparametricOrder_ = order;
    }

  };

  //**********************************************************************
  //
  // --UGGridElement
  /** \brief Defines the geometry part of a mesh entity.
   * \ingroup UGGrid

     \param mydim An element is a polygon in a hyperplane of dimension dim. 0 <= dim <= 3 is typically
     dim=0 is a point.

     \param dimworld Each corner is a point with dimworld coordinates.

     This version is actually used only for mydim==coorddim. The manifold
     versions are in specializations below.
   */
  template<int mydim, int coorddim, class GridImp>
  class UGGridGeometry :
    public GeometryDefaultImplementation <mydim, coorddim, GridImp, UGGridGeometry>
  {
    typedef typename GridImp::ctype UGCtype;

    template <int codim_, int dim_, class GridImp_>
    friend class UGGridEntity;

    friend class UGMakeableGeometry<mydim,coorddim,GridImp>;

  public:

    /** Default constructor. Puts geometry in element mode
     */
    UGGridGeometry()
    {
      mode_ = element_mode;
      jacobianInverseIsUpToDate_ = false;
    }

    //! put object in coord_mode
    void coordmode ()
    {
      // set the mode
      mode_ = coord_mode;

      // initialize pointers to data
      for (int i=0; i<((mydim==2) ? 4 : 8); i++)
        cornerpointers_[i] = &(coord_[i][0]);

      jacobianInverseIsUpToDate_ = false;
    }

    /** \brief Return the element type identifier
     *
     * UGGrid supports triangles and quadrilaterals in 2D, and
     * tetrahedra, pyramids, prisms, and hexahedra in 3D.
     */
    GeometryType type () const;

    //! return the number of corners of this element.
    int corners () const {
      return UG_NS<coorddim>::Corners_Of_Elem(target_);
    }

    //! access to coordinates of corners. Index is the number of the corner
    const FieldVector<UGCtype, coorddim>& operator[] (int i) const;

    /** \brief Maps a local coordinate within reference element to
     * global coordinate in element  */
    FieldVector<UGCtype, coorddim> global (const FieldVector<UGCtype, mydim>& local) const;

    /** \brief Maps a global coordinate within the element to a
     * local coordinate in its reference element */
    FieldVector<UGCtype, mydim> local (const FieldVector<UGCtype, coorddim>& global) const;

    //! Returns true if the point is in the current element
    bool checkInside(const FieldVector<UGCtype, mydim> &local) const;

    /**
       Integration over a general element is done by integrating over the reference element
       and using the transformation from the reference element to the global element as follows:
       \f[\int\limits_{\Omega_e} f(x) dx = \int\limits_{\Omega_{ref}} f(g(l)) A(l) dl \f] where
       \f$g\f$ is the local to global mapping and \f$A(l)\f$ is the integration element.

       For a general map \f$g(l)\f$ involves partial derivatives of the map (surface element of
       the first kind if \f$d=2,w=3\f$, determinant of the Jacobian of the transformation for
       \f$d=w\f$, \f$\|dg/dl\|\f$ for \f$d=1\f$).

       For linear elements, the derivatives of the map with respect to local coordinates
       do not depend on the local coordinates and are the same over the whole element.

       For a structured mesh where all edges are parallel to the coordinate axes, the
       computation is the length, area or volume of the element is very simple to compute.

       Each grid module implements the integration element with optimal efficiency. This
       will directly translate in substantial savings in the computation of finite element
       stiffness matrices.
     */
    UGCtype integrationElement (const FieldVector<UGCtype, mydim>& local) const;

    UGCtype volume() const {

      if (myGrid_->isoparametricOrder_ != 1)
        DUNE_THROW(NotImplemented, "UGGridGeometry::volume() for isoparametric geometry");

      if (mode_==element_mode) {
        // coorddim*coorddim is an upper bound for the number of vertices
        UGCtype* cornerCoords[coorddim*coorddim];
        UG_NS<coorddim>::Corner_Coordinates(target_, cornerCoords);
        return UG_NS<coorddim>::Area_Of_Element(corners(),
                                                const_cast<const double**>(cornerCoords));
      } else {
        return UG_NS<coorddim>::Area_Of_Element(corners(),
                                                const_cast<const double**>(cornerpointers_));
      }
    }

    //! The Jacobian matrix of the mapping from the reference element to this element
    const FieldMatrix<UGCtype, mydim,mydim>& jacobianInverseTransposed (const FieldVector<UGCtype, mydim>& local) const;


  private:
    // mode that decides whether coordinates are taken from the element or given explicitely
    enum SourceMode {element_mode, coord_mode};

    // mode is set by constructor
    SourceMode mode_;

    /** \brief Init the element with a given UG element */
    void setToTarget(typename UG_NS<coorddim>::template Entity<coorddim-mydim>::T* target)
    {
      target_ = target;
      jacobianInverseIsUpToDate_ = false;
    }

    /** \brief Init the element with a given UG element for a given multigrid */
    void setToTarget(typename UG_NS<coorddim>::template Entity<coorddim-mydim>::T* target,
                     GridImp* myGrid)
    {
      target_ = target;
      jacobianInverseIsUpToDate_ = false;
      myGrid_ = myGrid;
    }

    //! \brief set a corner
    void setCoords (int i, const UGCtype* pos)
    {
      if (mode_!=coord_mode)
        DUNE_THROW(GridError,"mode must be coord_mode!");

      for (int j=0; j<coorddim; j++)
        coord_[i][j] = pos[j];

      jacobianInverseIsUpToDate_ = false;
    }

    //! Get all p2 nodes of this element
    void computeIsoparametricNodes() const;

    //! the vertex coordinates
    mutable array<FieldVector<UGCtype, coorddim>, (mydim==2) ? 4 : 8> coord_;

    //! The jacobian inverse
    mutable FieldMatrix<UGCtype,coorddim,coorddim> jac_inverse_;

    /** \brief For simplices the Jacobian matrix is a constant, hence it needs
        to be computed only once for each new element.  This can save some
        assembly time. */
    mutable bool jacobianInverseIsUpToDate_;

    // in element mode this points to the element we map to
    // in coord_mode this is the element whose reference element is mapped into the father's one
    typename UG_NS<coorddim>::template Entity<coorddim-mydim>::T* target_;

    // in coord_mode we explicitely store an array of coordinates
    // containing the position in the fathers reference element
    mutable UGCtype* cornerpointers_[(mydim==2) ? 4 : 8];

    /** \brief The nodes for p2 isoparametric geometries

       The nodes are stored following the Dune shape function ordering */
    mutable array<FieldVector<UGCtype,coorddim>, (coorddim==2) ? 9 : 27> isoparametricNodes_;

    /** \brief UG multigrid, which contains the actual grid hierarchy structure
        We need this so computeIsoparametricNodes() can access the domain boundary */
    const GridImp* myGrid_;

  };



  /****************************************************************/
  /*                                                              */
  /*       Specialization for faces in 3d                         */
  /*                                                              */
  /****************************************************************/

  template<class GridImp>
  class UGGridGeometry<2, 3, GridImp> :
    public GeometryDefaultImplementation <2, 3, GridImp, UGGridGeometry>
  {

    template <int codim_, int dim_, class GridImp_>
    friend class UGGridEntity;

    template <class GridImp_>
    friend class UGGridIntersectionIterator;

    friend class UGMakeableGeometry<2,3,GridImp>;

    typedef typename GridImp::ctype UGCtype;

  public:

    /** \brief Default constructor */
    UGGridGeometry() : isoparametricOrder_(1)
    {elementType_=GeometryType(GeometryType::simplex,2);}

    //! return the element type identifier (triangle or quadrilateral)
    GeometryType type () const {
      return elementType_;
    }

    //! return the number of corners of this element. Corners are numbered 0...n-1
    int corners () const {return (elementType_.isSimplex()) ? 3 : 4;}

    //! access to coordinates of corners. Index is the number of the corner
    const FieldVector<UGCtype, 3>& operator[] (int i) const
    {
      return coord_[UGGridRenumberer<2>::verticesDUNEtoUG(i, elementType_)];
    }

    //! maps a local coordinate within reference element to
    //! global coordinate in element
    FieldVector<UGCtype, 3> global (const FieldVector<UGCtype, 2>& local) const;

    //! Maps a global coordinate within the element to a
    //! local coordinate in its reference element
    FieldVector<UGCtype, 2> local (const FieldVector<UGCtype, 3>& global) const;



    //! Returns true if the point is in the current element
    bool checkInside(const FieldVector<UGCtype, 2> &local) const {

      // These two conditions must be fulfilled for triangles and quadrilaterals
      if (local[0] < 0 || local[1] < 0)
        return false;

      // Now distinguish between the element types
      return (corners()==3) ? (local[0]+local[1] <= 1) : (local[0] <= 1 && local[1] <= 1);
    }

    // A(l)
    UGCtype integrationElement (const FieldVector<UGCtype, 2>& local) const;

    //! !
    const FieldMatrix<UGCtype,2,2>& jacobianInverseTransposed (const FieldVector<UGCtype, 2>& local) const;

  private:

    void setNumberOfCorners(int n) {
      assert(n==3 || n==4);
      elementType_ = GeometryType( (n==3) ? GeometryType::simplex : GeometryType::cube,2);
    }

    //! The element type, either triangle or quadrilateral
    GeometryType elementType_;

    //! the vertex coordinates in UG numbering
    // This array has nine entries because this is the max number it may need to have
    // (isoparametric quad face)
    mutable array<FieldVector<UGCtype, 3>, 9> coord_;

    //! The jacobian inverse
    mutable FieldMatrix<UGCtype,2,2> jacobianInverseTransposed_;

    /** \brief The isoparametric geometry order.

       This may differ from the order stored in the grid, because we may be e.g., an intersectionInSelf(),
       which is never isoparametric.
     */
    unsigned int isoparametricOrder_;
  };


  /****************************************************************/
  /*                                                              */
  /*       Specialization for faces in 2d                         */
  /*                                                              */
  /****************************************************************/

  template<class GridImp>
  class UGGridGeometry <1, 2, GridImp> :
    public GeometryDefaultImplementation <1, 2, GridImp, UGGridGeometry>
  {

    template <int codim_, int dim_, class GridImp_>
    friend class UGGridEntity;

    template <class GridImp_>
    friend class UGGridIntersectionIterator;

    friend class UGMakeableGeometry<1,2,GridImp>;

    typedef typename GridImp::ctype UGCtype;

  public:

    /** \brief Default constructor */
    UGGridGeometry() : isoparametricOrder_(1)
    {}

    /** \brief Return the element type identifier.  */
    GeometryType type () const {return GeometryType(GeometryType::simplex,1);}

    //! return the number of corners of this element. This class always returns 2
    int corners () const {return 2;}

    //! access to coordinates of corners. Index is the number of the corner
    const FieldVector<UGCtype, 2>& operator[] (int i) const {
      // 1D -> 2D, nothing to renumber
      return coord_[i];
    }

    //! maps a local coordinate within reference element to
    //! global coordinate in element
    FieldVector<UGCtype, 2> global (const FieldVector<UGCtype, 1>& local) const;

    //! Maps a global coordinate within the element to a
    //! local coordinate in its reference element
    FieldVector<UGCtype, 1> local (const FieldVector<UGCtype, 2>& global) const {

      if (isoparametricOrder_ != 1)
        DUNE_THROW(NotImplemented, "UGGridGeometry<1,2>::local() for isoparametric geometry");

      FieldVector<UGCtype, 2> segment = coord_[1];
      segment -= coord_[0];
      FieldVector<UGCtype, 1> result;
      result[0] = (global-coord_[0]) * segment / segment.two_norm() / segment.two_norm();
      return result;
    }

    //! Returns true if the point is in the reference element
    bool checkInside(const FieldVector<UGCtype, 1>& local) const {
      return local[0]>=0 && local[0]<=1;
    }

    // A(l)
    UGCtype integrationElement (const FieldVector<UGCtype, 1>& local) const;

    //! can only be called for dim=dimworld!
    const FieldMatrix<UGCtype,1,1>& jacobianInverseTransposed (const FieldVector<UGCtype, 1>& local) const;

  private:

    // Do nothing: faces in a 2d grid always have 2 corners
    void setNumberOfCorners(int n) {}

    //! the vertex coordinates
    // There are three (instead of two) array entries because this element may be quadratic
    array<FieldVector<UGCtype, 2>, 3> coord_;

    //! The jacobian inverse
    mutable FieldMatrix<UGCtype,1,1> jacobianInverseTransposed_;

    /** \brief The isoparametric geometry order.

       This may differ from the order stored in the grid, because we may be e.g., an intersectionInSelf(),
       which is never isoparametric.
     */
    unsigned int isoparametricOrder_;
  };

}  // namespace Dune

// Include method definitions
#include "uggridgeometry.cc"

#endif
