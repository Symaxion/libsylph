include(SourcesList.txt)
include(AddFileDependencies)

include_directories(${SYLPH_SOURCE_DIR}/src ${SYLPH_SOURCE_DIR}/deps/gtest/include)

link_directories(${SYLPH_BINARY_DIR}/src) 

if( SYLPH_DEBUG )
    add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG -DGTEST_USE_OWN_TR1_TUPLE
            -DGTEST_HAS_TR1_TUPLE)
else ( SYLPH_DEBUG )
    add_definitions(${SYLPH_CONFIG_DEFS} -DGTEST_USE_OWN_TR1_TUPLE
            -DGTEST_HAS_TR1_TUPLE)
endif( SYLPH_DEBUG )

add_executable( SylphTestExe EXCLUDE_FROM_ALL ${STEST_ALL_SRC})
target_link_libraries( SylphTestExe ${SYLPH_TARGET} gtest ${COVERAGE_LIBS})
add_custom_target(test SylphTestExe DEPENDS SylphTestExe)

set_target_properties(SylphTestExe PROPERTIES COMPILE_FLAGS "${SYLPH_CXXFLAGS}")
