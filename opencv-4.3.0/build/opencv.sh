#本文件需要放置在opencv-4.3.0/build目录下执行
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/toolchain_ubuntu.cmake \
-DCMAKE_INSTALL_PREFIX=/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/install/ \
-DBUILD_TESTS=FALSE -DBUILD_PERF_TESTS=FALSE -DBUILD_ZLIB=TRUE \
-DCMAKE_BUILD_TYPE=RELEASE -DBUILD_SHARED_LIBS=FALSE \
-DWITH_WEBP=FALSE -DBUILD_WEBP=FALSE -DWITH_PNG=FALSE \
-DBUILD_opencv_apps=FALSE \
-DCMAKE_C_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" \
-DCMAKE_CXX_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" 
make -j8 
make install

#cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/ash1/lab_pro/QinLin_cross_build/QiLin_ARM_aarch64/toolchain_qilin.cmake \
#-DCMAKE_INSTALL_PREFIX=/home/ash1/lab_pro/QinLin_cross_build/QiLin_ARM_aarch64/install/ \
#-DBUILD_TESTS=FALSE -DBUILD_PERF_TESTS=FALSE -DBUILD_ZLIB=TRUE \
#-DCMAKE_BUILD_TYPE=RELEASE -DBUILD_SHARED_LIBS=TRUE \
#-DCMAKE_C_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" \
#-DCMAKE_CXX_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" 
