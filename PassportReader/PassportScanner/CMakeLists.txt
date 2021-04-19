cmake_minimum_required(VERSION 3.4.1)
project (PassportScanner)

set(CMAKE_CXX_STANDARD 14)

file(GLOB source_files
"./src/*.cpp"
"./src/json/*.cpp"
)

add_library(passportScanner SHARED ${source_files})

target_include_directories(passportScanner BEFORE PRIVATE include include/json ../PassportReaderAPI/include)

target_link_libraries(passportScanner getData libImageProcess)

install(TARGETS passportScanner
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

install(FILES ${PROJECT_SOURCE_DIR}/include/passportScanner.h DESTINATION include)
