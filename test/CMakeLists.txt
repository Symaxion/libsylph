include(SourcesList.txt)
include(AddFileDependencies)

include_directories(${SYLPH_SOURCE_DIR}/src)

link_directories(${SYLPH_BINARY_DIR}/src ${SYLPH_SOURCE_DIR}/deps/gc)

set(alltests )

foreach(entry ${STEST_ALL_PRE_SRC})
    get_filename_component(basename ${entry} NAME_WE)
    set(outfile ${SYLPH_BINARY_DIR}/test/${basename}.cpp)
    set(alltests ${alltests} ${basename}.tst)
    add_custom_command( OUTPUT ${SYLPH_BINARY_DIR}/test/${basename}.cpp
        COMMAND ${SYLPH_SOURCE_DIR}/test/mktest.pl 
        ARGS ${SYLPH_SOURCE_DIR}/test/${entry} ${SYLPH_BINARY_DIR}/test
        COMMENT "Generated CXX source from MkTest script ${entry}"
        DEPENDS ${SYLPH_SOURCE_DIR}/test/${entry})
endforeach(entry)

add_executable( SylphTestExe EXCLUDE_FROM_ALL ${STEST_ALL_SRC} main.cpp)
add_dependencies( SylphTestExe ${alltests} )
target_link_libraries( SylphTestExe Sylph cppunit )
add_custom_target(test SylphTestExe DEPENDS SylphTestExe)

set_target_properties(SylphTestExe PROPERTIES COMPILE_FLAGS
     "-std=c++0x -Wno-main")
