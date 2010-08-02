if( SYLPH_DEBUG )
    add_definitions(${SYLPH_CONFIG_DEFS} -DSYLPH_DEBUG)
else ( SYLPH_DEBUG )
    add_definitions(${SYLPH_CONFIG_DEFS})
endif( SYLPH_DEBUG )

if ( SYLPH_NO_CXX0X )
    add_definitions( -DSYLPH_NO_CXX0X )
endif ( SYLPH_NO_CXX0X ) 

include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})

add_library(${SYLPH_TARGET} SHARED ${SYLPH_ALL_SRC} ${SYLPH_PLATFORM_SRC})
target_link_libraries(${SYLPH_TARGET} ${SYLPH_LINK})
set_target_properties(${SYLPH_TARGET} PROPERTIES COMPILE_FLAGS "${SYLPH_CXXFLAGS}" VERSION ${SYLPH_VERSION} SOVERSION ${SYLPH_ABI} )

install( TARGETS ${SYLPH_TARGET} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install( DIRECTORY . DESTINATION include FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE )
