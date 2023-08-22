// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement comparator struct for EECS403 Project2.
#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_
#include <iostream>
#include "deployment.h"
using namespace std;

struct deploymentLessComparator{
    bool operator()(const deployment &left,
                    const deployment &right) const{
        if (left.getForce() == right.getForce()){
            return left.getID() > right.getID();
        }
        return left.getForce() < right.getForce();
    }
};
struct deploymentGreaterComparator{
    bool operator()(const deployment &left,
                    const deployment &right) const{
        if (left.getForce() == right.getForce()){
            return left.getID() > right.getID();
        }
        return left.getForce() > right.getForce();
    }
};

#endif