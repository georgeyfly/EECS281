// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#ifndef TSPOPT_H_
#define TSPOPT_H_
#include <iostream>
#include <vector>
#include "Tsp.h"
#include <limits>
#include <cmath>
using namespace std;

class TspOpt: public Tsp{
    public:

        TspOpt(): curDis(0){};

        void generateOTSP(Heuristics a);

        void printOTSP();

    private:
        // visited from [0, permLength)
        // unvisited from [permLength, pokemonVec.size())
        vector<size_t> pathVerCur;

        double curDis;

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

        vector<vector<double>> distSqVec;

        // fill distSqVec for later use
        void fillDis();

        void genPerms(size_t permLength);

        double generateMST(size_t permLength);

        double generateEST(size_t permLength);

        bool promising(size_t permLength);

        void update();

        // used update the bestpath and bestDis initially by calling fastOPT
        void findBound(Heuristics a);

        double distanceSquareOPTTSP(size_t a, size_t b, vector<pokemon>& vec);
        
};
#endif