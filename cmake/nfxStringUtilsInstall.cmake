#==============================================================================
# nfx-stringutils - Library installation
#==============================================================================

#----------------------------------------------
# Installation condition check
#----------------------------------------------

if(NOT NFX_STRINGUTILS_INSTALL_PROJECT)
    message(STATUS "Installation disabled, skipping...")
    return()
endif()

#----------------------------------------------
# Install headers
#----------------------------------------------

install(
    DIRECTORY "${NFX_STRINGUTILS_INCLUDE_DIR}/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT Development
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl"
)

#----------------------------------------------
# Install library targets
#----------------------------------------------

set(install_targets)

# Header-only interface library
list(APPEND install_targets ${PROJECT_NAME})

if(install_targets)
    install(
        TARGETS ${install_targets}
        EXPORT nfx-stringutils-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT Development
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT Runtime
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT Runtime
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()

#----------------------------------------------
# Install CMake config files
#----------------------------------------------

install(
    EXPORT nfx-stringutils-targets
    FILE nfx-stringutils-targets.cmake
    NAMESPACE nfx-stringutils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-stringutils
    COMPONENT Development
)

# Install separate target files for each configuration (multi-config generators)
if(CMAKE_CONFIGURATION_TYPES)
    foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    install(
        EXPORT nfx-stringutils-targets
        FILE nfx-stringutils-targets-${CONFIG}.cmake
        NAMESPACE nfx-stringutils::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-stringutils
        CONFIGURATIONS ${CONFIG}
        COMPONENT Development
    )
    endforeach()
endif()

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/nfx-stringutils-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/nfx-stringutils-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/nfx-stringutils-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-stringutils
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/nfx-stringutils-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/nfx-stringutils-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-stringutils
    COMPONENT Development
)

#----------------------------------------------
# Install license files
#----------------------------------------------

install(
    FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/licenses"
    RENAME "LICENSE-${PROJECT_NAME}.txt"
)

file(GLOB LICENSE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/licenses/LICENSE-*")
foreach(LICENSE_FILE ${LICENSE_FILES})
    get_filename_component(LICENSE_NAME ${LICENSE_FILE} NAME)
    install(
        FILES ${LICENSE_FILE}
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/licenses"
        RENAME "${LICENSE_NAME}.txt"
    )
endforeach()

#----------------------------------------------
# Install documentation
#----------------------------------------------

if(NFX_STRINGUTILS_BUILD_DOCUMENTATION)
    install(
        DIRECTORY "${CMAKE_BINARY_DIR}/doc/html"
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        OPTIONAL
        COMPONENT Documentation
    )

    if(WIN32)
    # Install Windows .cmd batch file
    install(
        FILES "${CMAKE_BINARY_DIR}/doc/index.html.cmd"
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        OPTIONAL
        COMPONENT Documentation
    )
    else()
    # Install Unix symlink
    install(
        FILES "${CMAKE_BINARY_DIR}/doc/index.html"
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        OPTIONAL
        COMPONENT Documentation
    )
    endif()
endif()

message(STATUS "Installation configured for targets: ${install_targets}")
