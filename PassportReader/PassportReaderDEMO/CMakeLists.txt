project(PassportReaderDEMO)
cmake_minimum_required(VERSION 3.4.1)

file(GLOB source_files
        "./src/*.cpp"
        )

add_executable(PassportReaderDEMO ${source_files})

target_include_directories(PassportReaderDEMO BEFORE PRIVATE include)
target_include_directories(PassportReaderDEMO BEFORE PRIVATE ../PassportReaderAPI/include)
target_link_libraries(PassportReaderDEMO PassportReaderAPI stdc++ glog)

install(TARGETS PassportReaderDEMO
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/WorkingFolder DESTINATION sample)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/capi DESTINATION sample)
install(FILES ${PROJECT_SOURCE_DIR}/src/main.cpp DESTINATION sample)
install(FILES ${PROJECT_SOURCE_DIR}/include/internalLogging.h DESTINATION sample)
