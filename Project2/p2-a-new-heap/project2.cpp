// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: main for EECS403 Project2.
#include <iostream>
#include "galaxy.h"
using namespace std;

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    galaxy aGalaxy;
    aGalaxy.get_options(argc, argv);
    aGalaxy.read_file();
    return 0;
}