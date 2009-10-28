if( SYLPH_DEBUG )
add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG)
else ( SYLPH_DEBUG )
add_definitions(${SYLPH_CONFIG_DEFS})
endif( SYLPH_DEBUG )
include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})

add_library(Sylph SHARED ${SYLPH_ALL_SRC})
target_link_libraries(Sylph ${SYLPH_ALL_DEPS})
set_target_properties(Sylph PROPERTIES COMPILE_FLAGS "-std=c++0x -Wno-main")

install( TARGETS Sylph LIBRARY DESTINATION lib )
install( DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE )
