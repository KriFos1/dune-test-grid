// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
// $Id: shapefunctions.hh 337 2006-05-03 13:32:40Z oliver $

#ifndef DUNE_UG_SHAPEFUNCTIONS_HH
#define DUNE_UG_SHAPEFUNCTIONS_HH

#include <iostream>
#include <dune/common/fvector.hh>
#include <dune/common/exceptions.hh>
#include <dune/common/geometrytype.hh>

/**
 * @file
 * @brief  abstract base class for shape functions
 * @author Peter Bastian
 */


namespace Dune {

  namespace UGShapeFunctions {

    /*! Abstract base class for a shape function.

          A shape function \f$ \phi : \Omega_E \to R^N \f$ has the following properties:

          - It is a function defined on the reference element \f$ \Omega_E \subset R^d \f$.
          - It is associated with a degree of freedom of the finite element space.
          - A transformation from the reference element to the actual element
        yields a finite element basis function restricted to that element.

          In the case N=1 the shape function (and the finite element space)
          is scalar, otherwise it is vector-valued. The last point is understood
          as follows let \f$ \Omega_e \f$ be the domain of an element \f$ e \f$ and \f$T : \Omega_E \to \Omega_e \f$
          the transformation from the reference element to the element e. Then
       the basis function \f$ b \f$ defined by \f$ \phi \f$ is: \f$ b(T(x)) = \phi(x) \f$.

       A ShapeFunction has the following template parameters:

       -   C       type for input coordinates x \in R^d
       -   T       return type for function values and derivatives
       -   d       the dimension of the reference domain
       -   N       number of components per shape function

     */
    template<typename T, int d, int N>
    class ShapeFunction
    {
    public:
      // compile time sizes

      /** \brief Dimension of the reference domain */
      enum { dim=d };

      /** \brief Number of components per shape function */
      enum { comps=N };      // must be available at compile time

      /** \brief Type used for the coordinates */
      typedef T CoordType;

      /** \brief Type used for the result values */
      typedef T ResultType;

      //! evaluate component comp at point x
      virtual ResultType evaluateFunction (int comp, const FieldVector<CoordType,dim>& x) const = 0;

      //! evaluate derivative of component comp in direction dir at point x
      virtual ResultType evaluateDerivative (int comp, int dir, const FieldVector<CoordType,dim>& x) const = 0;

      //! consecutive number of associated dof within element
      virtual int localindex (int comp) const = 0;

      //! codim of associated dof
      virtual int codim () const = 0;

      //! entity (of codim) of associated dof
      virtual int entity () const = 0;

      //! consecutive number of dof within entity
      virtual int entityindex () const = 0;

      //! virtual destructor
      virtual ~ShapeFunction () {}
    };



    /*! Abstract base class for a set of shape functions.

       A set of shape functions is used to define finite element functions.
          The construction is element by element and on each element the shape
          functions are combined linearly:
          \f[ v(x) = \sum_{i=0}^{m-1} c_i \phi_i(x). \f]
          \f$ c_i \f$ is a degree of freedom and \f$ \phi_i \f$ is a shape function.

          A ShapeFunctionSet has the following template parameters

       -    C       type for input coordinates
       -    T       return type for function values and derivatives
       -    d       the dimension of the reference domain
       -    N       number of components per shape function

     */
    template<typename T, int d, int N>
    class ShapeFunctionSet
    {
    public:
      // compile time sizes
      /** \brief Dimension of the reference domain */
      enum { dim=d };

      /** \brief Number of components per shape function */
      enum { comps=N };

      // exported types
      /** \brief Type used for the coordinates */
      typedef T CoordType;

      /** \brief Type used for the result values */
      typedef T ResultType;

      /** \brief The type of the entries in this container */
      typedef ShapeFunction<T,d,N> value_type;

      //! total number of shape functions, i.e. degrees of freedom
      virtual int size () const = 0;

      //! total number of shape functions associated with entity in codim
      virtual int size (int entity, int codim) const = 0;

      //! random access to i'th ShapeFunction
      virtual const value_type& operator[] (int i) const = 0;

      //! return order
      virtual int order () const = 0;

      //! return type of element where this ShapeFunctionSet is for
      virtual GeometryType type () const = 0;

      //! virtual destructor
      virtual ~ShapeFunctionSet () {}
    };



    /*! Abstract base class for a container of sets of shape functions.

       ShapeFunctionSets are needed for different element types and orders
       of a finite element space. A ShapeFunctionSetContainer is a container
          of ShapeFunctionSets and its elements can be accessed by providing
          an element type and the order.

          A ShapeFunctionSetContainer has the following template parameters

       -    C       type for input coordinates
       -    T       return type for function values and derivatives
       -    d       the dimension of the reference domain
       -    N       number of components per shape function
          -    M       maximum size of any ShapeFunctionSet in the container

     */
    template<typename T, int d, int N, int M>
    class ShapeFunctionSetContainer
    {
    public:
      // compile time sizes
      /** \brief Dimension of the reference domain */
      enum { dim=d };

      /** \brief Number of components per shape function */
      enum { comps=N };

      /** \brief Maximum size of any ShapeFunctionSet in the container */
      enum { maxsize=M };

      // exported types
      /** \brief Type used for the coordinates */
      typedef T CoordType;

      /** \brief Type used for the result values */
      typedef T ResultType;

      /** \brief The type of the entries in this container */
      typedef ShapeFunctionSet<T,d,N> value_type;

      //! access a shape function via type and order
      virtual const value_type& operator() (GeometryType type, int order) const = 0;

      //! virtual destructor
      virtual ~ShapeFunctionSetContainer () {}
    };


  }
}
#endif
