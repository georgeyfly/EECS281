// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement galaxy class for for EECS403 Project2.
#ifndef _GALAXY_H_
#define _GALAXY_H_
#include <iostream>
#include <string>
#include <vector>
#include "planet.h"
#include "general.h"
using namespace std;

class galaxy
{
    private:
        // read in member
        string mode;
        uint32_t numGeneral;
        uint32_t numPlanet;
        bool doVerbose;
        bool doMedian;
        bool doGeneral;
        bool doWatch;
        // member for median 
        uint32_t currentTimestamp;
        // member for general
        vector <general> vecGeneral;
        // member for other
        vector <planet> vecPlanet;
        uint32_t totalBattle;
    public:
        // ctor
        galaxy(){
            doVerbose = false;
            doMedian = false;
            doGeneral = false;
            doWatch = false;
            totalBattle = 0;
            currentTimestamp = 0;
        }
        // get options from command line
        void get_options(int argc, char** argv);
        // read head
        void read_head();
        // read file from stdin
        void read_file();
        void sumBattle(const planet &aPlanet);
};


#endif