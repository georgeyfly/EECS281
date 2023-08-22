// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#ifndef TSP_H_
#define TSP_H_
#include <iostream>
#include <vector>
#include "Map.h"
#include <limits>
#include <cmath>
using namespace std;

enum class Heuristics:uint8_t {NearestOpt, ArbInsert};

class Tsp: public Map{
    public:

        Tsp(): bestDis(0){};

        void generateFTSP(Heuristics a);

        void printFTSP(Heuristics a);

    protected:

        // struct tspVertex{
        //     bool isVisited;
        //     // double distance2Next;
        //     // size_t nextVertex;
        //     tspVertex(): 
        //         isVisited(false)
        //         // distance2Next(numeric_limits<double>::infinity())
        //         // nextVertex(numeric_limits<size_t>::infinity())
        //         {};
        // };
        
        // struct tspNextVertex{
        //     double distance2Next;
        //     size_t nextVertex;
        //     tspNextVertex(): 
        //         distance2Next(numeric_limits<double>::infinity()),
        //         nextVertex(numeric_limits<size_t>::infinity())
        //         {};
        // };

        // for 2-opt algorithm
        // store next vertex, in connected graph order
        // ex. if my graph is 0-2-1-0, my pathVer will be [2,1,0], pathVer[0] 
        // store the index of second vertex, which is 2.
        // This variable is usded to reverse the graph is twoOpt algorithm

        // for arbitary algorithm
        // pathVer[i] stores the vertex comes after i
        vector<size_t> pathVer;
        // best distance
        double bestDis;

        double distanceSquareTSP(size_t a, size_t b);

        double distanceTSP(size_t a, size_t b);

        void generateNearPath();

        void twoOpt();

        void generateArbInsert();

    private:
        // store isVisted in read in order
        // ex. first and second read in Vertex will be stored at 
        // path[0] and path[1]
        // vector<tspVertex> path;
        vector<bool> pathVisited;

        vector<double> pathDis;

};

#endif