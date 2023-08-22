// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement watcher mode for movie watcher mode for EECS403 Project2.
#ifndef _WATCHER_H_
#define _WATCHER_H_
#include <iostream>
using namespace std;
struct watcher{
    uint32_t force;
    uint32_t timestamp;
    watcher(){
        force = 0;
        timestamp = 0;
    }
    // watcher(
    //     uint32_t &iforce,
    //     uint32_t &itime
    // ){
    //     force = iforce;
    //     timestamp = itime;
    // }
};
#endif