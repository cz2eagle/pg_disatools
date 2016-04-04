#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
# 

if (MINGW)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		${DEPENDENCIES_PATH}/glew.MinGW/include/
	)

    FIND_LIBRARY( GLEW_LIBRARY
        NAMES glew32.dll
        PATHS
        ${DEPENDENCIES_PATH}/glew.MinGW/lib
    )
	
	INSTALL(
		DIRECTORY ${DEPENDENCIES_PATH}/glew.MinGW/bin/ 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		FILES_MATCHING PATTERN "*.dll"
	)
elseif(UNIX)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		${PACKAGE_PREFIX_DIR}/include
		${DEPENDENCIES_PATH}/glew.MinGW/include/
	)

	    FIND_LIBRARY( GLEW_LIBRARY
		NAMES libGLEW.so
		PATHS
		${PACKAGE_PREFIX_DIR}/lib/x86_64-linux-gnu
	    )

elseif (MSVC)
    FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
        ${DEPENDENCIES_PATH}/glew-1.11.0/include/
    )

    FIND_LIBRARY( GLEW_LIBRARY
        NAMES glew32
        PATHS
        ${DEPENDENCIES_PATH}/glew-1.11.0/lib/Release/Win32/
    )
 
 	INSTALL(
		DIRECTORY ${DEPENDENCIES_PATH}/glew-1.11.0/bin/Release/Win32/
		DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		FILES_MATCHING PATTERN "*.dll"
	)
 
else()
	FIND_PATH(GLEW_INCLUDE_PATH GL/glew.h)
	FIND_LIBRARY(GLEW_LIBRARY
		NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64
		)
endif()
    

SET(GLEW_FOUND "NO")
if (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)
	SET(ALL_LIBRARIES ${ALL_LIBRARIES} ${GLEW_LIBRARY})
	SET(ALL_INCLUDE_PATHS ${ALL_INCLUDE_PATHS} ${GLEW_INCLUDE_PATH})
	SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
	SET(GLEW_FOUND "YES")
    message("EXTERNAL LIBRARY 'GLEW' FOUND")
    message("GLEW_LIBRARY: " ${GLEW_LIBRARY})
    message("GLEW_INCLUDE_PATH: " ${GLEW_INCLUDE_PATH})
else()
    message(SEND_ERROR "ERROR: EXTERNAL LIBRARY 'GLEW' NOT FOUND")
endif (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)