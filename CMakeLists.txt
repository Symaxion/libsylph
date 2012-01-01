#
# LibSylph Class Library (build script)
# Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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

cmake_minimum_required(VERSION 2.6)
project(SYLPH)

# Definitions
set( SYLPH_VERSION "0.2" )
set( SYLPH_ABI 2 ) # update when abi changes
set( SYLPH_DEP_LINK gc icuuc ) # dependent libraries
set( SYLPH_DEP_INCLUDE "" ) # for future use

# Compile options
option(SYLPH_DEBUG "Enable assertions and exception line info")
set(SYLPH_CONFIG_DEFS "" CACHE STRING "Add extra preprocessor definitions")
option(SYLPH_COMPILER_SUFFICIENT "Set a manual override to make your compiler pass all tests")
set(SYLPH_CXXFLAGS "" CACHE STRING "Add a manual override to the C++ flags needed to activate C++0x and other stuff")
option(SYLPH_NO_CXX0X "Disable C++0x support (experimental)")
option(SYLPH_ENABLE_COVERAGE "Enable code coverage support [developers]")
option(SYLPH_ENABLE_PROFILING "Enable profiling support [developers]")

# Dependencies
find_package(Threads)

#Version & platform checks...
macro (get_gcc_version version)
    if (CMAKE_COMPILER_IS_GNUCC)
        exec_program( ${SYLPH_SOURCE_DIR}/deps/bin/gccver.sh ARGS ${CMAKE_CXX_COMPILER} OUTPUT_VARIABLE ${version})
    endif(CMAKE_COMPILER_IS_GNUCC)
endmacro (get_gcc_version)

#Yea, I know *BSD, Irix, HP-UX, Solaris, ... != Linux, but for simplicity...
if( UNIX AND NOT APPLE )
    set(LINLIKE 1)
endif ( UNIX AND NOT APPLE )

# Get Versions
get_gcc_version ( S_GCC_VERSION )

# C++0x disabled
# Assume each compiler can compile at least C++99 or C++03
set( SYLPH_TARGET "Sylph")
if( SYLPH_NO_CXX0X )
    SET ( SYLPH_COMPILER_SUFFICIENT 1 )
    SET ( SYLPH_TARGET "Sylph03" )
endif ( SYLPH_NO_CXX0X )

# Check if compiler supports all constructs
if ( NOT SYLPH_COMPILER_SUFFICIENT ) # manual override
    SET( SYLPH_COMPILER_SUFFICIENT 0 )

    # GCC == 4.5.3 will do the job
    if ( CMAKE_COMPILER_IS_GNUCC AND S_GCC_VERSION STREQUAL "4.5.3" )
        SET( SYLPH_COMPILER_SUFFICIENT 1 )
        SET( CXX_GCC 1 )
    endif ( CMAKE_COMPILER_IS_GNUCC AND S_GCC_VERSION STREQUAL "4.5.3" )

    # No compiler found
    if ( NOT SYLPH_COMPILER_SUFFICIENT )
        message ( FATAL_ERROR "Your compiler does not support C++0x. Please install a compliant compiler. G++ > 4.4.0 supports the required constructs. Use the -DCMAKE_CXX_COMPILER flag to set a compiler." )
    endif ( NOT SYLPH_COMPILER_SUFFICIENT )

endif ( NOT SYLPH_COMPILER_SUFFICIENT )

# CXXFlags
if ( NOT SYLPH_CXXFLAGS )
    set ( SYLPH_CXXFLAGS "" )
    set ( COVERAGE_LIBS "" )

    # GCC >= 4.4.0
    # Enable C++0x and disable some warnings
    if ( CXX_GCC )
        if( NOT SYLPH_NO_CXX0X )
            set( SYLPH_CXXFLAGS "-std=c++0x")
        endif ( NOT SYLPH_NO_CXX0X )

        if( SYLPH_ENABLE_COVERAGE )
            set( SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -fprofile-arcs -ftest-coverage" )
            set( COVERAGE_LIBS "gcov" )
        endif( SYLPH_ENABLE_COVERAGE )

        if( SYLPH_ENABLE_PROFILING )
            set( SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -pg" )
        endif( SYLPH_ENABLE_PROFILING )

        if ( APPLE )
            # disable warning for 4-param main
            set ( SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -Wno-main" )
        endif ( APPLE )

        # Enable all warnings
        set ( SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -Wall -Werror -fno-strict-aliasing" )
    endif ( CXX_GCC )

    if ( NOT SYLPH_CXXFLAGS )
    endif ( NOT SYLPH_CXXFLAGS )

endif ( NOT SYLPH_CXXFLAGS )

# documentation
add_custom_target(docs doxygen)

# platform extras
set(SYLPH_PLATFORM_INCLUDE "")
set(SYLPH_PLATFORM_SRC "")
set(SYLPH_PLATFORM_LINK "" )

if ( LINLIKE )
    # linlike extras (binreloc)
    set(SYLPH_PLATFORM_INCLUDE "${SYLPH_SOURCE_DIR}/deps/binreloc")
    set(SYLPH_PLATFORM_SRC "${SYLPH_SOURCE_DIR}/deps/binreloc/binreloc.cpp" )
endif ( LINLIKE )

set(SYLPH_LINK ${SYLPH_PLATFORM_LINK} ${SYLPH_DEP_LINK})
set(SYLPH_INCLUDE ${SYLPH_PLATFORM_INCLUDE} ${SYLPH_DEP_INCLUDE})

# Subdirs

add_subdirectory(src)

add_subdirectory(deps/gtest EXCLUDE_FROM_ALL)
add_subdirectory(test)

# Scripts and helpers

install( PROGRAMS ${SYLPH_SOURCE_DIR}/bin/sylo DESTINATION bin )

# PkgConfig

configure_file ( Sylph.pc.in Sylph.pc @ONLY )
install( FILES ${SYLPH_BINARY_DIR}/Sylph.pc DESTINATION lib/pkgconfig )
