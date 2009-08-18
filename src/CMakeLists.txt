if( SYLPH_DEBUG )
add_definitions(${SYLPH_CONGIF_DEFS} -DSYLPH_DEBUG)
else ( SYLPH_DEBUG )
add_definitions(${SYLPH_CONFIG_DEFS})
endif( SYLPH_DEBUG )
include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})
link_libraries(${SYLPH_ALL_DEPS})

add_library(Sylph SHARED ${SYLPH_ALL_SRC})
set_target_properties(Sylph PROPERTIES COMPILE_FLAGS "-std=c++0x -Wno-main")
