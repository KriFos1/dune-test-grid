/* begin dune-grid
   put the definitions for config.h specific to
   your project here. Everything above will be
   overwritten
*/
/* begin private */
/* Name of package */
#define PACKAGE "@DUNE_MOD_NAME"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "@DUNE_MAINTAINER@"

/* Define to the full name of this package. */
#define PACKAGE_NAME "@DUNE_MOD_NAME@"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "@DUNE_MOD_NAME@ @DUNE_MOD_VERSION@"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "@DUNE_MOD_NAME@"

/* Define to the home page for this package. */
#define PACKAGE_URL "@DUNE_MOD_URL@"

/* Define to the version of this package. */
#define PACKAGE_VERSION "@DUNE_MOD_VERSION@"

/* end private */

/* Define to the version of dune-grid */
#define DUNE_GRID_VERSION "${DUNE_GRID_VERSION}"

/* Define to the major version of dune-grid */
#define DUNE_GRID_VERSION_MAJOR ${DUNE_GRID_VERSION_MAJOR}

/* Define to the minor version of dune-grid */
#define DUNE_GRID_VERSION_MINOR ${DUNE_GRID_VERSION_MINOR}

/* Define to the revision of dune-grid */
#define DUNE_GRID_VERSION_REVISION ${DUNE_GRID_VERSION_REVISION}

/* This is only true if alugrid-library was found by configure _and_ if the
   application uses the ALUGRID_CPPFLAGS */
#cmakedefine HAVE_ALUGRID ENABLE_ALUGRID

/* Define to 1 if you have the <alugrid_parallel.h> header file. */
#cmakedefine HAVE_ALUGRID_PARALLEL_H @HAVE_ALUGRID_PARALLEL_H@

/* Define to 1 if you have the <alugrid_serial.h> header file. */
#cmakedefine HAVE_ALUGRID_SERIAL_H @HAVE_ALUGRID_SERIAL_H@

/* Alberta version found by configure, either 0x200 for 2.0 or 0x300 for 3.0 */
#cmakedefine DUNE_ALBERTA_VERSION @DUNE_ALBERTA_VERSION@

/* This is only true if alberta-library was found by configure _and_ if the
   application uses the ALBERTA_CPPFLAGS */
#cmakedefine HAVE_ALBERTA ENABLE_ALBERTA

/* This is only true if UG was found by configure _and_ if the application
   uses the UG_CPPFLAGS */
#cmakedefine HAVE_UG ENABLE_UG

/* Grid type magic for DGF parser */
@GRID_CONFIG_H_BOTTOM@
/* end dune-grid */
