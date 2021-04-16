# Install script for directory: /home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/build/lib/libopencv_gapi.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/operators.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/opencv_includes.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcompiled_async.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gproto.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/garray.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcompoundkernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcommon.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gtransform.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/render.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gtype_traits.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcomputation.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/infer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gopaque.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gstreaming.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gasync_context.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gmetaarg.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gscalar.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gkernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gmat.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/garg.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gtyped.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcall.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcomputation_async.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/imgproc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gcompiled.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/cpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/cpu/gcpukernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/cpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/cpu/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/cpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/cpu/imgproc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/fluid" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/fluid/gfluidbuffer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/fluid" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/fluid/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/fluid" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/fluid/gfluidkernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/fluid" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/fluid/imgproc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/gpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gpu/ggpukernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/gpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gpu/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/gpu" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/gpu/imgproc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/infer" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/infer/ie.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/ocl" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/ocl/goclkernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/ocl" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/ocl/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/ocl" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/ocl/imgproc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/scalar.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/mat.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/cvdefs.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/saturate.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/assert.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/convert.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/exports.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/own" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/own/types.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/render" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/render/render.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/streaming" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/streaming/source.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/streaming" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/streaming/cap.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/plaidml" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/plaidml/gplaidmlkernel.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/plaidml" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/plaidml/plaidml.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/plaidml" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/plaidml/core.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/variant.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/any.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/throw.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/optional.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/util.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv4/opencv2/gapi/util" TYPE FILE OPTIONAL FILES "/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/opencv-4.3.0/modules/gapi/include/opencv2/gapi/util/compiler_hints.hpp")
endif()

