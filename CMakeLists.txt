cmake_minimum_required(VERSION 2.6)
project(SYLPH)

macro (get_gcc_version version)
    if (CMAKE_COMPILER_IS_GNUCC)
        exec_program( ${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE
                output)
        string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" ${version} ${output})
    endif(CMAKE_COMPILER_IS_GNUCC)
endmacro (get_gcc_version)

get_gcc_version ( S_GCC_VERSION )

if ( NOT CMAKE_COMPILER_IS_GNUCC OR S_GCC_VERSION STRLESS "4.4.0" )
    message ( FATAL_ERROR "Your compiler does not support C++0x. Please install
a compliant compiler. G++ > 4.4.0 supports the required
constructs. Use the -DCMAKE_CXX_COMPILER flag to set a compiler." )
endif ( NOT CMAKE_COMPILER_IS_GNUCC OR S_GCC_VERSION STRLESS "4.4.0" )

if ( UNIX )
set(SYLPH_INCLUDE ${SYLPH_SOURCE_DIR}/deps/binreloc ${SYLPH_SOURCE_DIR}/deps/gc/include)
set(SYLPH_LINK_DIR ${SYLPH_SOURCE_DIR}/deps/binreloc ${SYLPH_SOURCE_DIR}/deps/gc)
set(SYLPH_LINK binreloc gc)
else ( UNIX )
set(SYLPH_INCLUDE ${SYLPH_SOURCE_DIR}/deps/gc/include)
set(SYLPH_LINK_DIR ${SYLPH_SOURCE_DIR}/deps/gc)
set(SYLPH_LINK gc)
endif ( UNIX )

set(SYLPH_ALL_DEPS ${SYLPH_LINK} icuuc)

add_subdirectory(deps/binreloc)
add_subdirectory(src)
add_subdirectory(test)

install( FILES bin/sylphparams RUNTIME DESTINATION bin)