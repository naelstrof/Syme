FIND_PATH(GLFW_INCLUDE_DIRS GL/glfw.h DOC "Path to GLFW include directory."
	HINTS
	$ENV{GLFW_ROOT}
	PATH_SUFFIX include
	PATHS
	/usr/include/
	/usr/local/include/
	/usr/include/GL
	/usr/local/include/GL
	${GLFW_ROOT_DIR}/include/
)

FIND_LIBRARY(GLFW_LIBRARIES DOC "Absolute path to GLFW library."
	NAMES glfw GLFW.lib
	HINTS
	$ENV{GLFW_ROOT}
	PATH_SUFFIXES lib/win32 lib lib64
	PATHS
	/usr/local/lib
	/usr/lib
	${GLFW_ROOT_DIR}/lib-msvc100/release
)

IF(GLFW_LIBRARIES AND GLFW_INCLUDE_DIRS)
	SET(GLFW_FOUND TRUE)
ELSE()
	SET(GLFW_FOUND FALSE)
ENDIF()
