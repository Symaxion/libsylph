if( SYLPH_DEBUG )
add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG)
else ( SYLPH_DEBUG )
add_definitions(${SYLPH_CONFIG_DEFS})
endif( SYLPH_DEBUG )
include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})

add_library(Sylph SHARED ${SYLPH_ALL_SRC} ${SYLPH_PLATFORM_SRC})
target_link_libraries(Sylph ${SYLPH_LINK})
set_target_properties(Sylph PROPERTIES COMPILE_FLAGS ${SYLPH_CXXFLAGS} VERSION ${SYLPH_VERSION} SOVERSION ${SYLPH_ABI} )

install( TARGETS Sylph LIBRARY DESTINATION lib )
install( DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE )
