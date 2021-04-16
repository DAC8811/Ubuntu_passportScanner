#注意：使用该文件前可能需要为Configure设置系统和编译器，否则Configure可能会直接使用默认或者之前指定的编译器(arm64使用linux-aarch64 x86使用linux-x86_64)
#如果使用config文件进行配置，则会导致--prefix参数失效，即无法指定安装位置
export CC=gcc \
CXX=g++
./Configure --prefix=/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/install  linux-x86_64 shared -fPIC -ffast-math -ftree-vectorize -flto -fdata-sections -ffunction-sections -Wl,--gc-sections
make -j8 & make install
