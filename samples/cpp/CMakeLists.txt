target_include_directories(classification PRIVATE
${OpenCV_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}/../opencv4_4_x86_gcc4_9/include/opencv4
)
add_subdirectory(engine)
add_subdirectory(api)
add_subdirectory(run_model)
add_subdirectory(others)
