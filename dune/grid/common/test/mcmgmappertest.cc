// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

/** \file
    \brief A unit test for the MultipleCodimMultipleGeometryMapper
 */

#include <config.h>

#include <iostream>
#include <set>

#include <dune/common/parallel/mpihelper.hh>
#include <dune/grid/common/mcmgmapper.hh>
#include <dune/grid/uggrid.hh>
#include "../../../../doc/grids/gridfactory/hybridtestgrids.hh"

using namespace Dune;

/*!
 * \brief Check whether the index created for element data is unique,
 * consecutive and starting from zero.
 */
template <class Mapper, class GridView>
void checkElementDataMapper(const Mapper& mapper, const GridView& gridView)
{
  typedef typename GridView::template Codim<0>::Iterator Iterator;

  Iterator eIt    = gridView.template begin<0>();
  Iterator eEndIt = gridView.template end<0>();

  size_t min = 1;
  size_t max = 0;
  std::set<int> indices;

  for (; eIt!=eEndIt; ++eIt)
  {
    size_t index = mapper.map(*eIt);
    min = std::min(min, index);
    max = std::max(max, index);
    std::pair<std::set<int>::iterator, bool> status = indices.insert(index);

    if (!status.second)       // not inserted because already existing
      DUNE_THROW(GridError, "Mapper element index is not unique!");
  }

  if (min != 0)
    DUNE_THROW(GridError, "Mapper element index is not starting from zero!");

  if (max != gridView.indexSet().size(0) - 1)
    DUNE_THROW(GridError, "Mapper element index is not consecutive!");
}

// /////////////////////////////////////////////////////////////////////////////////
//   Check whether the index created for face data is unique, consecutive
//   and starting from zero.
// /////////////////////////////////////////////////////////////////////////////////
template <class Mapper, class IndexSet>
void checkFaceDataMapper(const Mapper& mapper, const IndexSet& indexSet)
{
#if 0
  typedef typename IndexSet::template Codim<0>::template Partition<All_Partition>::Iterator Iterator;

  Iterator eIt    = indexSet.template begin<0,All_Partition>();
  Iterator eEndIt = indexSet.template end<0,All_Partition>();

  // Reset the counting variables
  int min = 1;
  int max = 0;
  indices.clear();

  for (; eIt!=eEndIt; ++eIt) {

    typedef typename GridType::template Codim<0>::Entity::IntersectionIterator IntersectionIterator;

    IntersectionIterator iIt    = eIt->ibegin();
    IntersectionIterator iEndIt = eIt->iend();

    for (; iIt!=iEndIt; ++iIt) {

      int index = mapper.map(*eIt, iIt.numberInSelf());

      //             std::cout << hostIndexSet.template subIndex<1>(*eIt, iIt.numberInSelf())
      //                 << "  Index: " << index << "   type: " << eIt->type() << std::endl;
      min = std::min(min, index);
      max = std::max(max, index);

      std::pair<std::set<int>::iterator, bool> status = indices.insert(index);

      if (!status.second)         // not inserted because already existing
        DUNE_THROW(GridError, "Mapper index is not unique!");

    }

  }

  if (min!=0)
    DUNE_THROW(GridError, "Mapper index for codim 1 is not starting from zero!");

  if (max!=indexSet.size(1))
    DUNE_THROW(GridError, "Mapper index for codim 1 is not consecutive!");

#endif
}

/*!
 * \brief Run checks for a given grid.
 *
 * \param grid Grid to perform the checks.
 */
template<typename Grid>
void checkGrid(const Grid& grid)
{
  static const unsigned dim = Grid::dimension;
  // check leafMCMGMapper
  {   // check constructor without layout class
    LeafMultipleCodimMultipleGeomTypeMapper<Grid, MCMGElementLayout>
    leafMCMGMapper(grid);
    checkElementDataMapper(leafMCMGMapper, grid.leafView());
  }
  {   // check constructor with layout class
    LeafMultipleCodimMultipleGeomTypeMapper<Grid, MCMGElementLayout>
    leafMCMGMapper(grid, MCMGElementLayout<dim>());
    checkElementDataMapper(leafMCMGMapper, grid.leafView());
  }

  // check levelMCMGMapper
  for (int i = 2; i <= grid.maxLevel(); i++)
  {
    {     // check constructor without layout class
      LevelMultipleCodimMultipleGeomTypeMapper<Grid, MCMGElementLayout>
      levelMCMGMapper(grid, i);
      checkElementDataMapper(levelMCMGMapper, grid.levelView(i));
    }
    {     // check constructor with layout class
      LevelMultipleCodimMultipleGeomTypeMapper<Grid, MCMGElementLayout>
      levelMCMGMapper(grid, i, MCMGElementLayout<dim>());
      checkElementDataMapper(levelMCMGMapper, grid.levelView(i));
    }
  }
}

int main(int argc, char** argv)
try
{
  // initialize MPI if neccessary
  Dune::MPIHelper::instance(argc, argv);

  // Check grids with more than one element type.
  // So far only UGGrid does this, so we use them to test the mapper.

  //  Do the test for a 2d UGGrid
  {
    typedef UGGrid<2> Grid;
    std::auto_ptr<Grid> grid(make2DHybridTestGrid<Grid>());

    // create hybrid grid
    grid->mark(1, * grid->leafbegin<0>());
    grid->adapt();
    grid->globalRefine(1);

    checkGrid(*grid);
  }

  //  Do the  test for a 3d UGGrid
  {
    typedef UGGrid<3> Grid;
    std::auto_ptr<Grid> grid(make3DHybridTestGrid<Grid>());

    // create hybrid grid
    grid->mark(1, * grid->leafbegin<0>());
    grid->adapt();
    grid->globalRefine(1);

    checkGrid(*grid);
  }

  return EXIT_SUCCESS;

}
catch (Exception &e) {
  std::cerr << e << std::endl;
  return 1;
} catch (...) {
  std::cerr << "Generic exception!" << std::endl;
  return 2;
}
