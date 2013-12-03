FIND_PATH(NOWIDE_INCLUDE_DIRS boost/nowide/iostream.hpp DOC "Path to boost-nowide include directory."
	HINTS
	$ENV{NOWIDE_ROOT}
	PATH_SUFFIX include
	PATHS
	/usr/include/
	/usr/local/include/
	/usr/include/boost
	/usr/local/include/boost
	/usr/include/boost/nowide
	/usr/local/include/boost/nowide
	${NOWIDE_ROOT_DIR}/include/
)

FIND_LIBRARY(NOWIDE_LIBRARIES DOC "Absolute path to boost-nowide library."
	NAMES boost_nowide boost_nowide.lib
	HINTS
	$ENV{NOWIDE_ROOT}
	PATH_SUFFIXES lib/win32 lib lib64 so a
	PATHS
	/usr/local/lib
	/usr/lib
	${NOWIDE_ROOT_DIR}/lib-msvc100/release
)

IF(NOWIDE_LIBRARIES AND NOWIDE_INCLUDE_DIRS)
	SET(NOWIDE_FOUND TRUE)
ELSE()
	SET(NOWIDE_FOUND FALSE)
ENDIF()
