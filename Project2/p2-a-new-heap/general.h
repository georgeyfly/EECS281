// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement general struct for general mode for EECS403 Project2.
#ifndef _GENERAL_H_
#define _GENERAL_H_
#include <iostream>
using namespace std;

struct general{
    uint32_t sithSum;
    uint32_t jediSum;
    uint32_t sithSurvive;
    uint32_t jediSurvive;

    general(){
        sithSum = 0;
        jediSum = 0;
        sithSurvive = 0;
        jediSurvive = 0;
    }
    general& operator+=(const general &rhs){
        sithSum += rhs.sithSum;
        jediSum += rhs.jediSum;
        sithSurvive += rhs.sithSurvive;
        jediSurvive += rhs.jediSurvive;
        return *this;
    }
};
#endif