cmake_minimum_required(VERSION 2.6)
project(SYLPH)

macro (get_gcc_version version)
    if (CMAKE_COMPILER_IS_GNUCC)
        exec_program( ${SYLPH_SOURCE_DIR}/gccver.sh ARGS ${CMAKE_CXX_COMPILER} OUTPUT_VARIABLE ${version})
    endif(CMAKE_COMPILER_IS_GNUCC)
endmacro (get_gcc_version)

get_gcc_version ( S_GCC_VERSION )

if ( NOT CMAKE_COMPILER_IS_GNUCC OR S_GCC_VERSION STRLESS "4.4.0" )
    message ( FATAL_ERROR "Your compiler does not support C++0x. Please install
a compliant compiler. G++ > 4.4.0 supports the required
constructs. Use the -DCMAKE_CXX_COMPILER flag to set a compiler." )
endif ( NOT CMAKE_COMPILER_IS_GNUCC OR S_GCC_VERSION STRLESS "4.4.0" )

if ( UNIX AND NOT APPLE )
set(SYLPH_INCLUDE ${SYLPH_SOURCE_DIR}/deps/binreloc)
set(SYLPH_LINK_DIR ${SYLPH_SOURCE_DIR}/deps/binreloc)
set(SYLPH_LINK binreloc)
endif ( UNIX AND NOT APPLE )

set(SYLPH_ALL_DEPS ${SYLPH_LINK} gc icuuc)

add_subdirectory(deps/binreloc)
add_subdirectory(src)
add_subdirectory(test)

configure_file( bin/sylphparams.in bin/sylphparams )

install( PROGRAMS ${SYLPH_BINARY_DIR}/bin/sylphparams DESTINATION bin )
