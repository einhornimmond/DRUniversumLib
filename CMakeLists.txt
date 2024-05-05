# Setup inspired from https://alexreinking.com/blog/building-a-dual-shared-and-static-library-with-cmake.html

cmake_minimum_required(VERSION 3.29.2)

enable_language(C CXX)
# for linux, assume that sdl will be installed
if(MSVC) 
    message(STATUS "Download SDL2 Binary")
	# Fetch Content Module
	include(FetchContent)

	# Visual C++
	## SDL2
	FetchContent_Declare(
		sdl2
		URL     https://www.libsdl.org/release/SDL2-devel-2.30.2-VC.zip
		URL_MD5 375d933452c6cf623aedf9a4acc58c33
	)
	FetchContent_MakeAvailable(sdl2)
	message(STATUS "SDL2 source: ${sdl2_SOURCE_DIR}")
	message(STATUS "SDL2 binary: ${sdl2_BINARY_DIR}")
else()
	find_package(SDL2 REQUIRED)
endif()

project(UniversumLib VERSION 1.0)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

if(MSVC)
    #build with multicore support when using visual studio
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

if (NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET AND
    NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
endif ()

if (DEFINED UniversumLib_SHARED_LIBS)
    set(BUILD_SHARED_LIBS "${UniversumLib_SHARED_LIBS}")
endif ()

include_directories(
	"dependencies/DRCore2/include"
	"build/dependencies/DRCore2/include"
	"dependencies/magic_enum/include"
	"dependencies/rapidjson/include"	
	"dependencies/stb/"
	"${sdl2_SOURCE_DIR}/include"
)

FILE(GLOB CONTROLLER_SRC "src/controller/*.cpp" "include/UniversumLib/controller/*.h")
FILE(GLOB EXCEPTION_SRC "src/exception/*.cpp" "include/UniversumLib/exception/*.h")
FILE(GLOB GENERATOR_SRC "src/generator/*.cpp" "include/UniversumLib/generator/*.h")
FILE(GLOB LIB_SRC "src/lib/*.cpp" "include/UniversumLib/lib/*.h")
FILE(GLOB MANAGER_SRC "src/manager/*.cpp" "include/UniversumLib/manager/*.h")
FILE(GLOB MODEL_SRC "src/model/*.cpp" "include/UniversumLib/model/*.h")
FILE(GLOB MODEL_GEOMETRIE_SRC "src/model/geometrie/*.cpp" "include/UniversumLib/model/geometrie/*.h")
FILE(GLOB MODEL_BLOCK_SRC "src/model/block/*.cpp" "include/UniversumLib/model/block/*.h")
FILE(GLOB SERVER_SRC "src/server/*.cpp" "include/UniversumLib/server/*.h")
FILE(GLOB SRC "src/*.cpp" "include/UniversumLib/*.h")
FILE(GLOB TASK_SRC "src/task/*.cpp" "include/UniversumLib/task/*.h")
FILE(GLOB TASK_GPU_SRC "src/task/gpu/*.cpp" "include/UniversumLib/task/gpu/*.h")
FILE(GLOB TASK_NETWORK_SRC "src/task/network/*.cpp" "include/UniversumLib/task/network/*.h")
FILE(GLOB TYPE_INCLUDE "include/UniversumLib/type/*.h")
FILE(GLOB VIEW_SRC "src/view/*.cpp" "include/UniversumLib/view/*.h")
FILE(GLOB VIEW_BLOCK_SRC "src/view/block/*.cpp" "include/UniversumLib/view/block/*.h")

#
SET(UniversumLibSrc 
	${CONTROLLER_SRC}
	${EXCEPTION_SRC}
	${GENERATOR_SRC}
	${LIB_SRC} 
	${MANAGER_SRC}
	${MODEL_SRC} 
	${MODEL_BLOCK_SRC}
	${MODEL_GEOMETRIE_SRC}	
	${SERVER_SRC}
	${SRC}
	${TASK_SRC}
	${TASK_GPU_SRC}
	${TASK_NETWORK_SRC}
	${TYPE_INCLUDE}
	${VIEW_SRC}			     
	${VIEW_BLOCK_SRC}
)

if(MSVC)
	source_group("controller" FILES ${CONTROLLER_SRC} )
	source_group("exception" FILES ${EXCEPTION_SRC})
	source_group("generator" FILES ${GENERATOR_SRC} )
	source_group("lib" FILES ${LIB_SRC} )
	source_group("manager" FILES ${MANAGER_SRC})
	source_group("model\\block" FILES ${MODEL_BLOCK_SRC})
	source_group("model\\geometrie" FILES ${MODEL_GEOMETRIE_SRC})
	source_group("model" FILES ${MODEL_SRC} )
	source_group("server" FILES ${SERVER_SRC} )
	source_group("task\\gpu" FILES ${TASK_GPU_SRC})
	source_group("task\\network" FILES ${TASK_NETWORK_SRC})
	source_group("task" FILES ${TASK_SRC} )
	source_group("type" FILES ${TYPE_INCLUDE})
	source_group("view\\block" FILES ${VIEW_BLOCK_SRC})
	source_group("view" FILES ${VIEW_SRC} )	
endif(MSVC)

add_subdirectory("dependencies/DRCore2")
add_library(UniversumLib ${UniversumLibSrc})
add_library(UniversumLib::UniversumLib ALIAS UniversumLib)

if(BUILD_SHARED_LIBS) 
	target_link_libraries(UniversumLib ${SDL2_LIBRARIES})
endif()

set_target_properties(UniversumLib PROPERTIES
                      VERSION ${UniversumLib_VERSION}
                      SOVERSION ${UniversumLib_VERSION_MAJOR})
target_include_directories(
    UniversumLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
target_compile_features(UniversumLib PUBLIC cxx_std_17)

include(GenerateExportHeader)
generate_export_header(UniversumLib EXPORT_FILE_NAME include/UniversumLib/export.h)
target_compile_definitions(
    UniversumLib PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:UniversumLib_STATIC_DEFINE>")
target_include_directories(
    UniversumLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
option(UniversumLib_INCLUDE_PACKAGING "Include packaging rules for UniversumLib" "${is_top_level}")
if (UniversumLib_INCLUDE_PACKAGING)
    add_subdirectory(packaging)
endif ()

