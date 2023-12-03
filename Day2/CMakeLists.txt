add_executable(Day2 "Day2.cpp" "Day2.h")
target_link_libraries(Day2 Utilities)
target_include_directories(Day2 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Utilities"
                          )
