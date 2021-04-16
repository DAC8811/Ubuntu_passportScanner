#该脚本需要放置在libusb-1.0.23目录下执行
CFLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" \
CXXFLAGS="-O3 -ffast-math -ftree-vectorize -fno-lto -fPIC -fdata-sections -ffunction-sections -Wl,--gc-sections" \
./configure --prefix=/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/install --enable-shared=yes --enable-udev=no
make -j8 && make install
