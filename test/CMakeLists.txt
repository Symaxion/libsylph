include(SourcesList.txt)

include_directories(${SYLPH_SOURCE_DIR}/src)

link_directories(${SYLPH_BINARY_DIR}/src ${SYLPH_SOURCE_DIR}/deps/gc)

add_executable( SylphTestExe ${STEST_ALL_SRC} )
target_link_libraries( SylphTestExe Sylph cppunit )
add_custom_target(test SylphTestExe)

set_target_properties(SylphTestExe PROPERTIES COMPILE_FLAGS
     "-std=c++0x -Wno-main")