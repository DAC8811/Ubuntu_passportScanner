#本文件需要置于openjpeg-master/build目录下执行
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu/toolchain_ubuntu.cmake \
-DCMAKE_INSTALL_PREFIX=/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu/install/ \
-DCMAKE_BUILD_TYPE=RELEASE -DBUILD_SHARED_LIBS=FALSE -DBUILD_CODEC=FALSE \
-DCMAKE_C_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" \
-DCMAKE_CXX_FLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections"
make -j8 && make install
