#==============================================================================
# nfx-stringutils - Samples
#==============================================================================

#----------------------------------------------
# Sample condition check
#----------------------------------------------

if(NOT NFX_STRINGUTILS_BUILD_SAMPLES)
    message(STATUS "Samples disabled, skipping...")
    return()
endif()

#----------------------------------------------
# Samples source files
#----------------------------------------------

set(sample_sources)

list(APPEND sample_sources
    Sample_Network.cpp
    Sample_StringSplitter.cpp
    Sample_StringBasics.cpp
    Sample_StringOperations.cpp
    Sample_StringPredicates.cpp
    Sample_StringEncoding.cpp
    Sample_StringFormatting.cpp
    Sample_StringComparison.cpp
    Sample_Unicode.cpp
)

#----------------------------------------------
# Configure samples executables
#----------------------------------------------

foreach(sample_source ${sample_sources})
    get_filename_component(sample_target_name ${sample_source} NAME_WE)

    if(NOT TARGET ${sample_target_name})
        add_executable(${sample_target_name} ${sample_source})

        #----------------------------------------------
        # Target linking
        #----------------------------------------------

        target_link_libraries(${sample_target_name} PRIVATE
            nfx-stringutils::nfx-stringutils
        )

        #----------------------------------------------
        # Properties
        #----------------------------------------------

        set_target_properties(${sample_target_name}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            POSITION_INDEPENDENT_CODE ON
            DEBUG_POSTFIX "-d"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/samples"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/samples"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/samples"
        )
    endif()
endforeach()
