#########################################################################
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

cmake_minimum_required(VERSION 2.8)
project(Sylph)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Definitions
set(SYLPH_MAJOR 0)
set(SYLPH_MINOR 2)
set(SYLPH_PATCH 0)
set(SYLPH_VERSION "${SYLPH_MAJOR}.${SYLPH_MINOR}")
set(SYLPH_VERSION_FULL "${SYLPH_VERSION}.${SYLPH_PATCH}")
set(SYLPH_ABI 2) # update when abi changes
set(SYLPH_DEP_LINK gc icuuc) # depending libraries
set(SYLPH_DEP_INCLUDE "") # for future use

# Compile options
option(SYLPH_DEBUG "Enable assertions and exception line info")
set(SYLPH_CONFIG_DEFS "" CACHE STRING "Add extra preprocessor definitions")
option(SYLPH_COMPILER_SUFFICIENT "Set a manual override to make your compiler 
    pass all tests")
set(SYLPH_CXXFLAGS "" CACHE STRING "Add a manual override to the C++ flags
needed to activate C++11 and other stuff")
option(SYLPH_NO_CXX11 "Disable C++11 support (experimental)")
option(SYLPH_ENABLE_COVERAGE "Enable code coverage support [developers]")
option(SYLPH_ENABLE_PROFILING "Enable profiling support [developers]")

if(WIN32 AND NOT CYGWIN)
    set(S_INSTALL_CMAKE_DIR CMake)
else()
    set(S_INSTALL_CMAKE_DIR share/Sylph/CMake)
endif()
set(SYLPH_INSTALL_CMAKE_DIR ${S_INSTALL_CMAKE_DIR} CACHE PATH
    "Installation directory for CMake files")
if(NOT IS_ABSOLUTE "${SYLPH_INSTALL_CMAKE_DIR}")
    set(SYLPH_INSTALL_CMAKE_DIR
            "${CMAKE_INSTALL_PREFIX}/${SYLPH_INSTALL_CMAKE_DIR}")
endif()

#Version & platform checks...
include(DetectGccVersion)
include(DetectClangVersion)

#Yea, I know *BSD, Irix, HP-UX, Solaris, ... != Linux, but for simplicity...
if(UNIX AND NOT APPLE)
    set(LINLIKE 1)
endif()

# Workaround for CMake not detecting this...
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANG 1)
    set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_MODULE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
endif()

# If C++11 is disabled, we rename the library so that C++11 and C++03 versions
# can be installed side by side.
set(SYLPH_TARGET "Sylph")
if(SYLPH_NO_CXX11)
    set(SYLPH_COMPILER_SUFFICIENT 1) # Assume all compilers can compile C++03
    set(SYLPH_TARGET "Sylph03")
endif()

# Check if compiler supports all the required C++11 constructs
if(NOT SYLPH_COMPILER_SUFFICIENT) # manual override
    set(SYLPH_COMPILER_SUFFICIENT 0)

    if(CMAKE_COMPILER_IS_CLANG AND CLANG_VERSION STREQUAL "1")
        # We must check for Clang first as it identifies itself as GCC as
        # well.
        # For Clang, we use feature checks instead of hardcoded version 
        # numbers, as a version number is not a guarantee of a feature (in fact,
        # redistributors may change version numbers at will -- Apple does)
        set(SYLPH_COMPILER_SUFFICIENT 1)
    elseif(CMAKE_COMPILER_IS_GNUCC AND GCC_VERSION STRGREATER "4.5.2")
        # GCC >= 4.5.3 will do the job
        set(SYLPH_COMPILER_SUFFICIENT 1)
    endif()

    # No sufficient compiler found
    if(NOT SYLPH_COMPILER_SUFFICIENT)
        message(FATAL_ERROR "
  Your compiler does not support C++11. Please install a compliant compiler.
  The following compilers are known to work:
   
    * GCC (>= 4.5.3)
    * Clang (>= 3.1) or Apple Clang (>= 4.0, with XCode) with libc++
   
  Use the -DCMAKE_CXX_COMPILER flag to set a compiler." )
    endif()

endif()

# Setting the compile flags to enable C++11 and all warnings/errors.
# Yes, LibSylph has to compile with all warnings on with -Werror. We're that
# awesome.
if(NOT SYLPH_CXXFLAGS)
    set(SYLPH_CXXFLAGS "")
    set(COVERAGE_LIBS "")

    include(EnableCxx11)

    # Flags to enable warnings/errors and code coverage/profiling.
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG)
        if(SYLPH_ENABLE_COVERAGE)
            set(SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} 
                    -fprofile-arcs -ftest-coverage")
            set(COVERAGE_LIBS "gcov")
        endif()

        if(SYLPH_ENABLE_PROFILING)
            set(SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -pg")
        endif()

        if(APPLE)
            # disable warning for 4-param main
            # TODO: don't use 4-param main
            set(SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -Wno-main")
        endif()

        # Enable all the warnings!
        # TODO: use unions instead of -fno-strict-aliasing
        set(SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -Wall -Wextra -Werror")
        set(SYLPH_CXXFLAGS "${SYLPH_CXXFLAGS} -fno-strict-aliasing")
    endif()

endif()

# documentation
add_custom_target(docs doxygen)

# These are extra libraries/includes that are specific to the platform being
# built on (see below)
set(SYLPH_PLATFORM_INCLUDE "")
set(SYLPH_PLATFORM_SRC "")
set(SYLPH_PLATFORM_LINK "")

if(LINLIKE)
    # linlike extras (binreloc)
    set(SYLPH_PLATFORM_INCLUDE "${CMAKE_SOURCE_DIR}/deps/binreloc")
    set(SYLPH_PLATFORM_SRC "${CMAKE_SOURCE_DIR}/deps/binreloc/binreloc.cpp")
endif()

set(SYLPH_LINK ${SYLPH_PLATFORM_LINK} ${SYLPH_DEP_LINK})
set(SYLPH_INCLUDE ${SYLPH_PLATFORM_INCLUDE} ${SYLPH_DEP_INCLUDE})

# Gtest options -- does not compile on Clang without these.
set(GTEST_USE_OWN_TR1_TUPLE 1)
set(GTEST_HAS_TR1_TUPLE 0)

# Subdirs
add_subdirectory(src)
add_subdirectory(deps/gtest EXCLUDE_FROM_ALL)
add_subdirectory(test)

# Scripts and helpers
install(PROGRAMS ${CMAKE_SOURCE_DIR}/bin/sylo DESTINATION bin)

# PkgConfig
configure_file(Sylph.pc.in Sylph.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/Sylph.pc DESTINATION lib/pkgconfig)

# CMake exports
export(TARGETS ${SYLPH_TARGET}
        FILE ${PROJECT_BINARY_DIR}/SylphLibraryDepends.cmake)
export(PACKAGE Sylph)

file(RELATIVE_PATH S_CONF_REL_INCLUDE_DIR "${SYLPH_INSTALL_CMAKE_DIR}"
        "${CMAKE_INSTALL_PREFIX}/include")
configure_file(SylphConfig.cmake.in
        "${PROJECT_BINARY_DIR}/SylphConfig.cmake" @ONLY)
configure_file(SylphConfigVersion.cmake.in
        "${PROJECT_BINARY_DIR}/SylphConfigVersion.cmake" @ONLY)
 
install(FILES
        "${PROJECT_BINARY_DIR}/SylphConfig.cmake"
        "${PROJECT_BINARY_DIR}/SylphConfigVersion.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/DetectGccVersion.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/DetectClangVersion.cmake"
        "${PROJECT_SOURCE_DIR}/cmake/EnableCxx11.cmake"
        DESTINATION "${SYLPH_INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT SylphLibraryDepends DESTINATION
        "${SYLPH_INSTALL_CMAKE_DIR}" COMPONENT dev)
