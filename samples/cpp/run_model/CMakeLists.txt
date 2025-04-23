if(NOT PPLNN_USE_X86 OR NOT PPLNN_ENABLE_ONNX_MODEL)
    message(WARNING "x86 and onnx support are disabled. `classification` will not be built.")
    return()
endif()

find_package(OpenCV QUIET)
if (NOT OpenCV_FOUND)
    message(WARNING "OpenCV not found. Samples need opencv will not be built!")
    return()
endif()

target_include_directories(classification PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/../opencv4_4_x86_gcc4_9/include/opencv4
    )
target_link_libraries(classification PRIVATE pplnn_static ${OpenCV_LIBS})
