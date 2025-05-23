file(GLOB __SRC__
    ${CMAKE_CURRENT_SOURCE_DIR}/pplnn.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_flags.cc)
add_executable(pplnn ${__SRC__})
target_link_libraries(pplnn PRIVATE pplnn_static)

# -------------------------------------------------------------------------- #

file(GLOB __SRC__
    ${CMAKE_CURRENT_SOURCE_DIR}/pplnn_llm.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_flags.cc)
add_executable(pplnn_llm ${__SRC__})
target_link_libraries(pplnn_llm PRIVATE pplnn_static)

if(PPLNN_CUDA_ENABLE_NCCL)
    set(PPLNN_ENABLE_MPI_TOOLS ON)
endif()

if (PPLNN_ENABLE_MPI_TOOLS)
    find_package(MPI)
    if (NOT MPI_CXX_FOUND)
        message(FATAL_ERROR "MPI CXX not found")
    endif()
    target_link_libraries(pplnn_llm PRIVATE ${MPI_CXX_LIBRARIES})
    target_compile_definitions(pplnn_llm PRIVATE ${MPI_CXX_COMPILE_DEFINITIONS} PPLNN_ENABLE_MPI_TOOLS)
    target_compile_options(pplnn_llm PRIVATE ${MPI_CXX_COMPILE_OPTIONS})
    target_include_directories(pplnn_llm PRIVATE ${MPI_CXX_INCLUDE_DIRS})
endif()

if(PPLNN_USE_LLM_CUDA)
    file(GLOB_RECURSE BENCHMARK_LLAMA_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_llama/*.cc)
    add_executable(benchmark_llama
        ${BENCHMARK_LLAMA_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_flags.cc)
    target_link_libraries(benchmark_llama pplnn_static)
    target_include_directories(benchmark_llama PRIVATE ${HPCC_DEPS_DIR}/rapidjson/include)

    # keep it for compare
    file(GLOB_RECURSE BENCHMARK_LLAMA_DEPRECATED_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_llama_deprecated/*.cc)
    add_executable(benchmark_llama_deprecated
        ${BENCHMARK_LLAMA_DEPRECATED_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_flags.cc)
        target_link_libraries(benchmark_llama_deprecated pplnn_static)
    target_include_directories(benchmark_llama_deprecated PRIVATE ${HPCC_DEPS_DIR}/rapidjson/include)

    if(PPLNN_CUDA_ENABLE_NCCL)
        find_package(OpenMP REQUIRED)
        add_executable(test_nccl ${CMAKE_CURRENT_SOURCE_DIR}/test_nccl.cc)
        target_link_libraries(test_nccl pplcommon_static OpenMP::OpenMP_CXX)
    endif()
endif()
