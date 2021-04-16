cmake_minimum_required(VERSION 3.4.1)
project (PassportScanner)

set(CMAKE_CXX_STANDARD 14)

set(api_header_files
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )

file(GLOB source_files
"./src/*.cpp"
)

message("================================================================")
message("Building with ${CMAKE_SYSTEM_NAME} and ${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -ftree-vectorize -fexceptions -flto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math -ftree-vectorize -flto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections -fvisibility=hidden")

add_library(getData STATIC IMPORTED)
set_target_properties(getData PROPERTIES
    IMPORTED_LOCATION "${CMAKE_FIND_ROOT_PATH}/lib/static/libgetData.a")
add_library(glog STATIC IMPORTED)
set_target_properties(glog PROPERTIES
    	IMPORTED_LOCATION "${CMAKE_FIND_ROOT_PATH}/lib/libglog.a")
include_directories(${api_header_files} ${GLOG_INCLUDE_DIR})

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    add_compile_definitions(__LINUX_X86_64__)
    # message (" building on x86-64, use est100 to decode sfz image ")
    # set(BUILD_WITH_EST100 TRUE)
endif()

message("CXXFLAGS ${CMAKE_CXX_FLAGS}")
message("CFLAGS ${CMAKE_C_FLAGS}")

add_library(passportScanner STATIC ${source_files})
target_link_libraries(passportScanner getData)
target_include_directories(getData BEFORE PRIVATE include)

install(TARGETS passportScanner
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)

install(FILES ${PROJECT_SOURCE_DIR}/include/passportScanner.h DESTINATION include)
