if( UNIX AND NOT APPLE )
add_library(binreloc STATIC binreloc.c)
endif( UNIX AND NOT APPLE )