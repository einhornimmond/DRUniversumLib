# Network src
SET(NetworkSrc NetworkMain Network Connection Request NetCallback BufferedConnection)
SET(PA ../../../import/lib)
SET(PATH_SDL_NET2 ../dependencies/SDL_net/lib/x86)
find_library(SDL2_LIB SDL2 PATHS ${PA})
find_library(CORE_LIB DRCore2 PATHS ${PA})
if(WIN32)
find_library(SDLNET_LIB2 SDL2_net PATHS ${PA} ${PATH_SDL_NET2})
SET(NetworkLibs ${SDL2_LIB} ${CORE_LIB} DRUniversumLib ${SDLNET_LIB2})
else(UNIX)
SET(NetworkLibs ${SDL2_LIB} DRCore2 DRUniversumLib SDL2_net)
endif(WIN32)
#ENABLE_EXPORTS()
#DEFINE_SYMBOL(BUILD_DLL)
#IF(WIN32)
SET(NetworkSrc ${NetworkSrc} ../include/Network ../include/NetworkMain
			     ../include/Connection ../include/Request ../include/NetCallback ../include/BufferedConnection)
#ENDIF(WIN32)

ADD_LIBRARY(Network SHARED ${NetworkSrc})
TARGET_LINK_LIBRARIES(Network ${NetworkLibs})

set_target_properties(Network PROPERTIES DEFINE_SYMBOL BUILD_DLL_NETWORK)
SET_TARGET_PROPERTIES(Network PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../lib)
SET_TARGET_PROPERTIES(Network PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../bin)
