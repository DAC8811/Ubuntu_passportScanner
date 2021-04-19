#include "passportScanner.h"

int main(){
    setParam("/home/ashone/lab_pro/Ubuntu_16_passportReader/ubuntu/Demo_passportScanner/user");
    openConnection();
    scanAndReadCardInfo(500);
    closeConnection();
}