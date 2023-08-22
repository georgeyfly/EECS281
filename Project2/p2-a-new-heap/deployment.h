// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement deployment struct for PQ for EECS403 Project2.
#ifndef _DEPLOYMENT_H_
#define _DEPLOYMENT_H_
#include <iostream>
#include "constant.h"
using namespace std;

struct deployment{
    uint32_t force;
    mutable uint32_t quantity;
    uint32_t general;
    uint32_t id;

    deployment(){
        force = 0;
        quantity = 0;
        general = 0;
        id = 0;
    }
    deployment(
        const uint32_t &nGeneral,
        const uint32_t &nForce,
        const uint32_t &nQuantity){
        force = nForce;
        quantity = nQuantity;
        general = nGeneral;
        id = nextID;
        ++nextID;
    }

    uint32_t getID() const{
        return id;
    }
    uint32_t getForce() const{
        return force;
    }
};


#endif