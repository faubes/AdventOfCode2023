add_executable(Day3 "Day3.cpp" "Day3.h" "EngineSchematic.h" "EngineSchematic.cpp")
target_link_libraries(Day3 Utilities)
target_include_directories(Day3 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Utilities"
                          )
