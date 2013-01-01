###########################################################
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

include(SourcesList.txt)
include(AddFileDependencies)

include_directories(${CMAKE_SOURCE_DIR}/src 
        ${CMAKE_SOURCE_DIR}/deps/gtest/include)

link_directories(${CMAKE_BINARY_DIR}/src) 

if(SYLPH_DEBUG)
    add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG -DGTEST_USE_OWN_TR1_TUPLE
            -DGTEST_HAS_TR1_TUPLE)
else()
    add_definitions(${SYLPH_CONFIG_DEFS} -DGTEST_USE_OWN_TR1_TUPLE
            -DGTEST_HAS_TR1_TUPLE)
endif()

add_executable(SylphTestExe EXCLUDE_FROM_ALL ${STEST_ALL_SRC})
target_link_libraries(SylphTestExe ${SYLPH_TARGET} gtest ${COVERAGE_LIBS})
add_custom_target(test SylphTestExe DEPENDS SylphTestExe)

set_target_properties(SylphTestExe PROPERTIES COMPILE_FLAGS "${SYLPH_CXXFLAGS}")
