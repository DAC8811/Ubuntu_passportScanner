#请记得autogen.sh以及configure文件一定要有读写权限
./autogen.sh
./configure CC=gcc CXX=g++ --prefix=/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/install/ CPPFLAGS="-fPIC"
make -j8 && make install
