#include "passportScanner.h"

int main(){
    setParam("/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/Demo_passportScanner/user");
    openConnection();
    scanAndReadCardInfo(10000);
    closeConnection();
}