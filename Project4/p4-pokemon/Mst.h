// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#ifndef MST_H_
#define MST_H_
#include <iostream>
#include <vector>
#include "Map.h"
#include <limits>
#include <cmath>
using namespace std;


enum class Type: uint8_t{Sea, Land, CoastLine};

// define a Mst class derived from Map
class Mst: public Map{
    private:
        
        struct primVertex{
            bool isVisited;
            double distance2Prev;
            size_t prevVertex;
            primVertex(): 
                isVisited(false), 
                distance2Prev(numeric_limits<double>::infinity()),
                prevVertex(numeric_limits<size_t>::infinity())
                {};
        };
        
        vector<primVertex> primVertexVec;
        
        vector<Type> typeVec;

        double weight;

        void identifyType(); // fill typeVec according to coordinate XY

        double distSquareMST(size_t a, size_t b); 
                             // calculate the distance between two node
    
    public:
        Mst(): weight(0) {};

        void generateMST(); // generate MST by updating primVertexVec 
                            // and modify weight
        void print(); // output result with weight and edges
};

#endif