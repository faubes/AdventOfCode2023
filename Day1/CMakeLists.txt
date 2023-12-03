add_executable(Day1 "Day1.cpp" "Day1.h" "CalibrationDocument.h" "CalibrationDocument.cpp")
target_link_libraries(Day1 Utilities)
target_include_directories(Day1 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Utilities"
                          )