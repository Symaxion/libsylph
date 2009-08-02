add_definitions(${SYLPH_CONFIG_DEFS})
include(SourcesList.txt)

include_directories(${SYLPH_INCLUDE})
link_directories(${SYLPH_LINK_DIR})
link_libraries(${SYLPH_ALL_DEPS})

add_library(Sylph SHARED ${SYLPH_ALL_SRC})
set_target_properties(Sylph PROPERTIES COMPILE_FLAGS "-std=c++0x")