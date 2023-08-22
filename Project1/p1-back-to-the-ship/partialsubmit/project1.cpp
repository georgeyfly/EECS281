// IDENTIFIER  = 950181F63D0A883F183EC0A5CC67B19928FE896A
#include <iostream>
#include "shipClass.h"
using namespace std;

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    shipClass ship;
    ship.get_options(argc, argv);
    ship.run();
}
