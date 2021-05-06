#include "passportScanner.h"
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
    setParam("/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/Demo_passportScanner/user");
    openConnection();
    int value = 1;
    int last_value = value;
    while(1){
        getMediaStatus(&value);
        if(value == 0 && last_value == 1){
            cout << scanAndReadCardInfo(10000) << endl;
        }
        last_value = value;
        usleep(100*1000);
    }
    closeConnection();
    
}