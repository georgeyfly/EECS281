// IDENTIFIER  = 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef _CONTAINERSTRUCT_H_
#define _CONTAINERSTRUCT_H_
#include <iostream>
using namespace std;

// Programmer: Qiaozhi Huang
// Date: Jan 2023
// Purpose: implement positionStruct  for search container for EECS403 Project1.

struct containerStruct
{
    uint32_t level;
    uint32_t row;
    uint32_t col;
    containerStruct(){
        level = 0;
        row = 0;
        col = 0;
    };
    containerStruct(uint32_t &l, uint32_t &r, uint32_t &c){
        level = l;
        row = r;
        col = c;
    };
    // containerStruct& ?
    // override assignment operator
    void operator=(const containerStruct& other){
        level = other.level;
        row = other.row;
        col = other.col;
    }
    // override copy ctor
    containerStruct(const containerStruct& other){
        level = other.level;
        row = other.row;
        col = other.col;
    }

    bool operator==(const containerStruct& other){
        if(
            level == other.level &&
            row == other.row &&
            col == other.col){
            return true;
        }
        else{
            return false;
        }
    }
};

#endif