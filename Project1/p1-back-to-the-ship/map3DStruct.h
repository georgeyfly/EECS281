// IDENTIFIER  = 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef _MAP3DSTRUCT_H_
#define _MAP3DSTRUCT_H_
#include <iostream>
#include "constant.h"
using namespace std;

// Programmer: Qiaozhi Huang
// Date: Jan 2023
// Purpose: implement map3DStruct for 3D map for EECS403 Project1.

struct map3DStruct
{
    bool discover;
    // direction that will be output as solution
    char forthDirect;
    char character;
    map3DStruct(){
        discover = 0;
        forthDirect = NONE;
        character = FLOOR;
    }
};

#endif
