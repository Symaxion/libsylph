#########################################################################
#
# LibSylph Class Library (build script)
# Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source
#     distribution.
#
#########################################################################

if(SYLPH_DEBUG)
    add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG)
else()
    add_definitions(${SYLPH_CONFIG_DEFS})
endif()

if(SYLPH_NO_CXX11)
    add_definitions(-DSYLPH_NO_CXX0X)
endif() 

include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})

add_library(${SYLPH_TARGET} SHARED ${SYLPH_ALL_SRC} ${SYLPH_PLATFORM_SRC})
target_link_libraries(${SYLPH_TARGET} ${SYLPH_LINK} ${COVERAGE_LIBS})
set_target_properties(${SYLPH_TARGET} PROPERTIES 
        COMPILE_FLAGS "${SYLPH_CXXFLAGS}" VERSION ${SYLPH_VERSION} 
        SOVERSION ${SYLPH_ABI})

install(TARGETS ${SYLPH_TARGET} 
        EXPORT SylphLibraryDepends 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin 
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE)
