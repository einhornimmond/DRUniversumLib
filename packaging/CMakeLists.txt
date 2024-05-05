include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT DEFINED UniversumLib_INSTALL_CMAKEDIR)
   set(UniversumLib_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/UniversumLib"
       CACHE STRING "Path to UniversumLib CMake files")
endif ()

install(TARGETS UniversumLib EXPORT UniversumLib_Targets
    RUNTIME COMPONENT UniversumLib_Runtime
    LIBRARY COMPONENT UniversumLib_Runtime
    NAMELINK_COMPONENT UniversumLib_Development
    ARCHIVE COMPONENT UniversumLib_Development
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(DIRECTORY "${UniversumLib_SOURCE_DIR}/include/" "${UniversumLib_BINARY_DIR}/include/"
    TYPE INCLUDE
    COMPONENT UniversumLib_Development)

if (BUILD_SHARED_LIBS)
    set(type shared)
else ()
    set(type static)
endif ()
    
install(EXPORT UniversumLib_Targets
    DESTINATION "${UniversumLib_INSTALL_CMAKEDIR}"
    NAMESPACE UniversumLib::
    FILE UniversumLib-${type}-targets.cmake
    COMPONENT UniversumLib_Development)

write_basic_package_version_file(
    UniversumLibConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/UniversumLibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/UniversumLibConfigVersion.cmake"
    DESTINATION "${UniversumLib_INSTALL_CMAKEDIR}"
    COMPONENT UniversumLib_Development)