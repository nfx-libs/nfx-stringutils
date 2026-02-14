#==============================================================================
# nfx-stringutils - Top-level CMake configuration
#==============================================================================

#----------------------------------------------
# Project definition
#----------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(nfx-stringutils
    VERSION 0.6.4
    DESCRIPTION "Modern C++20 header-only library providing high-performance string utilities and zero-allocation splitting"
    HOMEPAGE_URL "https://github.com/nfx-libs/nfx-stringutils"
    LANGUAGES CXX
)

#----------------------------------------------
# Installation prefix configuration
#----------------------------------------------

include(GNUInstallDirs)

# Set default installation path to nfx
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "C:/Program Files/nfx" CACHE PATH "Installation directory" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "/usr/local/nfx" CACHE PATH "Installation directory" FORCE)
    endif()
    message(STATUS "Setting install prefix to '${CMAKE_INSTALL_PREFIX}'")
endif()

#----------------------------------------------
# Version configuration
#----------------------------------------------

set(NFX_STRINGUTILS_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE INTERNAL "nfx-stringutils major version")
set(NFX_STRINGUTILS_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE INTERNAL "nfx-stringutils minor version")
set(NFX_STRINGUTILS_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE INTERNAL "nfx-stringutils patch version")
set(NFX_STRINGUTILS_VERSION       ${PROJECT_VERSION}       CACHE INTERNAL "nfx-stringutils version")

#----------------------------------------------
# Project metadata
#----------------------------------------------

set(NFX_STRINGUTILS_LICENSE "MIT")
set(NFX_STRINGUTILS_LICENSE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

#----------------------------------------------
# Testing setup
#----------------------------------------------

enable_testing()

#----------------------------------------------
# Build options
#----------------------------------------------

# --- Build components (header-only library) ---
option(NFX_STRINGUTILS_BUILD_TESTS         "Build tests"                        OFF)
option(NFX_STRINGUTILS_BUILD_SAMPLES       "Build samples"                      OFF)
option(NFX_STRINGUTILS_BUILD_BENCHMARKS    "Build benchmarks"                   OFF)
option(NFX_STRINGUTILS_BUILD_DOCUMENTATION "Build Doxygen documentation"        OFF)

# --- Installation ---
option(NFX_STRINGUTILS_INSTALL_PROJECT     "Install project"                    OFF)

# --- Packaging ---
option(NFX_STRINGUTILS_PACKAGE_SOURCE      "Enable source package generation"   OFF)
option(NFX_STRINGUTILS_PACKAGE_ARCHIVE     "Enable TGZ/ZIP package generation"  OFF)
option(NFX_STRINGUTILS_PACKAGE_DEB         "Enable DEB package generation"      OFF)
option(NFX_STRINGUTILS_PACKAGE_RPM         "Enable RPM package generation"      OFF)
option(NFX_STRINGUTILS_PACKAGE_WIX         "Enable WiX Windows installer (MSI)" OFF)

#----------------------------------------------
# CMake modules configuration
#----------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#----------------------------------------------
# Main configuration
#----------------------------------------------

include(nfxStringUtilsBuildConfig)
include(nfxStringUtilsDependencies)
include(nfxStringUtilsTarget)

#----------------------------------------------
# Installation and packaging
#----------------------------------------------

include(nfxStringUtilsInstall)
include(nfxStringUtilsPackaging)

#----------------------------------------------
# Targets
#----------------------------------------------

add_subdirectory(test)
add_subdirectory(samples)
add_subdirectory(benchmark)
add_subdirectory(doc)
