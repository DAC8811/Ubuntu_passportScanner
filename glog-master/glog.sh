#请记得autogen.sh以及configure文件一定要有读写权限
./autogen.sh
./configure CC=gcc CXX=g++ --prefix=/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu_edition/install/ CPPFLAGS="-fPIC"
make -j8 && make install
