# Install script for directory: /home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/build/lib/libopencv_video.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video/include/opencv2/video.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/video" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video/include/opencv2/video/video.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/video" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video/include/opencv2/video/tracking.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/video" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video/include/opencv2/video/background_segm.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/video/legacy" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/video/include/opencv2/video/legacy/constants_c.h")
endif()

