cp /home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/install/lib/libpassportScanner.so .
cp /home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/install/include/passportScanner.h .
g++ test.cpp -Wl,-rpath='$ORIGIN'  -L.  -lpassportScanner -lwlt -o test
g++ test_open.cpp -o test_open -ldl
