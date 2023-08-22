// IDENTIFIER  = 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef _SHIPCLASS_H_
#define _SHIPCLASS_H_
#include <iostream>
#include <vector>
#include <deque>
#include "containerStruct.h"
#include "map3DStruct.h"


using namespace std;

class shipClass
{
    private:
        vector< vector < vector <map3DStruct> > > map3D;
        containerStruct startPos;
        containerStruct endPos;
        containerStruct curLoc;
        bool doFindSolution;
        uint32_t totalLevel;
        uint32_t totalLen;
        // store command character for route scheme, 's' for stack
        // 'q' for queue, different routescheme can result in different
        // search container
        char routeScheme;
        // 'L' for list while 'M' for map
        char outMode;
        // 'L' for list while 'M' for map
        char inMode;
        deque<containerStruct> searchContainer; 
        deque<containerStruct> routeEscape; 
    public:
        // constructor, initialize member variable
        shipClass();
        // 1. pop a object from search container, assign value to curLoc
        void iterateCurLoc();
        // this function is used for discovering a plane (NEST) direction
        // 1. if a containerStruct object is inBound and not discovered and not
        // a Wall, pushi this object into search container
        // 2. mark this place as discovered in the map3DStruct object
        void discoverPlane(containerStruct &position);
        // this function is used to discover all levels of elevator
        // if the position has an Elevator from level 0 to totalLevel - 1
        void discoverAllLevel(containerStruct &position);
        // 1. investigate NESW in order.
        // 2. if they are walls/ edges / discovered, skip them. if not, call
        // discover()
        // 3. if it is elevator, discover every other level, 
        // from the lowest level (0) to the highest level
        void investigateAndDiscover();
        // Read in the txt file through stdin.
        void read_file();
        // Read and process command line arguments.
        void get_options(int argc, char** argv);
        // check if obj is in bound of map, return true if in bound
        bool inBound(containerStruct &obj);
        // check if obj is discovered, return true if it is discovered
        bool isDiscover(containerStruct &obj);
        // check if obj is wall, return true ifit is Wall 
        bool isWall(containerStruct &obj);
        // check if obj is elevator, return true if it is elevator
        bool isElevator(containerStruct &obj);
        // check if obj is hangar, return true if it is hangar
        bool isHangar(containerStruct &obj);
        // output file
        void output_file();
        // backtrack the escape route and add to routeEscape container like 
        // stack, modify map3D character to output direction
        void addRouteAndModifyMap();
        // run program to find solution
        void run();

};


#endif