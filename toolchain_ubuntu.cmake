# this is required
SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_SYSROOT1 /home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu/install)

# specify the cross compiler
SET(CMAKE_C_COMPILER   gcc )
SET(CMAKE_CXX_COMPILER g++ )

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT1})

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
