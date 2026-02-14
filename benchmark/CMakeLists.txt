#==============================================================================
# nfx-stringutils - Benchmark suite CMake configuration
#==============================================================================

#----------------------------------------------
# Benchmark condition check
#----------------------------------------------

if(NOT NFX_STRINGUTILS_BUILD_BENCHMARKS)
    return()
endif()

#----------------------------------------------
# Benchmarks source files
#----------------------------------------------

set(benchmark_sources)

list(APPEND benchmark_sources
    BM_Splitter.cpp
    BM_CharacterClassification.cpp
    BM_StringValidation.cpp
    BM_StringOperations.cpp
    BM_StringTransform.cpp
    BM_StringComparison.cpp
    BM_NumericParsing.cpp
    BM_NetworkValidation.cpp
)

#----------------------------------------------
# Configure benchmark executables
#----------------------------------------------

foreach(benchmark_source ${benchmark_sources})
    get_filename_component(benchmark_target_name ${benchmark_source} NAME_WE)
    if(NOT TARGET ${benchmark_target_name})
        add_executable(${benchmark_target_name} ${benchmark_source})

        #----------------------------------------------
        # Target linking
        #----------------------------------------------

        target_link_libraries(${benchmark_target_name}
            PRIVATE
                nfx-stringutils::nfx-stringutils
                benchmark::benchmark
        )

        #----------------------------------------------
        # Compiler warnings
        #----------------------------------------------

        target_compile_options(${benchmark_target_name}
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Werror>
        )

        #----------------------------------------------
        # Properties
        #----------------------------------------------

        set_target_properties(${benchmark_target_name}
            PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED ON
                CXX_EXTENSIONS OFF
                POSITION_INDEPENDENT_CODE ON
                DEBUG_POSTFIX "-d"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
                RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
                RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        )
    endif()
endforeach()
