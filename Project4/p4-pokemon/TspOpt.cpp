// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include "TspOpt.h"
#include "Tsp.h"
#include <iomanip>

double TspOpt::generateMST(size_t permLength){
    // generate vector of coordinate of unvisited vertex [permLength, pokemonVec.size())
    vector<pokemon> unVisitCoord;
    unVisitCoord.resize(pokemonVec.size() - permLength);
    for (size_t i = permLength; i < pokemonVec.size(); ++i){
        // index of unVisitedCoord
        size_t idx = i - permLength;
        // vertex number
        size_t vertexi = pathVerCur[i];
        unVisitCoord[idx] = pokemonVec[vertexi];
    }

    // generate MST from partA

    // declare variable
    vector<primVertex> primVertexVec;
    double weight = 0;
    // set initial distance to 0
    primVertexVec.resize(unVisitCoord.size());
    primVertexVec[0].distance2Prev = 0;
    // loop N times
    for (size_t i = 0; i < primVertexVec.size(); ++i){
        // used for store the smallest distance and this vertex
        double nowDis = numeric_limits<double>::infinity();
        size_t nowVer = numeric_limits<size_t>::infinity();
        
        // find smallest false distance
        for (size_t j = 0; j < primVertexVec.size(); ++j){
            if (!primVertexVec[j].isVisited && 
                primVertexVec[j].distance2Prev < nowDis){
                nowDis = primVertexVec[j].distance2Prev;
                nowVer = j;
            }
        }
        
        // set this nowVer to be visited and add weight
        primVertexVec[nowVer].isVisited = true;
        weight += primVertexVec[nowVer].distance2Prev;
        
        // update the all false vertex's distance to nowVer if shorter than before
        for (size_t k = 0; k < primVertexVec.size(); ++k){
            if (!primVertexVec[k].isVisited){
                double tempDis = distanceSquareOPTTSP(k, nowVer, unVisitCoord);
                double prevDis = primVertexVec[k].distance2Prev;
                // tempDis is squared distance
                if (tempDis < prevDis * prevDis){
                    primVertexVec[k].distance2Prev = sqrt(tempDis);
                    primVertexVec[k].prevVertex = nowVer;
                }
            }
        }
    }
    return weight;
}

double TspOpt::generateEST(size_t permLength){
    double lenMST = generateMST(permLength);
    // two variable used to represent the nearest distance from first vertex to MST
    // and from last vertex(from visited vertex) to MST
    double bestFirstSq = numeric_limits<double>::infinity();
    double bestLastSq  = numeric_limits<double>::infinity();
    // declare first & last visited vertex 
    size_t vertexFirst = pathVerCur[0];
    size_t vertexLast = pathVerCur[permLength - 1];
    for (size_t i = permLength; i < pokemonVec.size(); ++i){
        // double curFirstSq = distanceSquareTSP(vertexFirst, pathVerCur[i]);
        // double curLastSq  = distanceSquareTSP(vertexLast , pathVerCur[i]);
        // use table
        double curFirstSq = distSqVec[vertexFirst][pathVerCur[i]];
        double curLastSq  = distSqVec[vertexLast][pathVerCur[i]];
        if (curFirstSq < bestFirstSq){
            bestFirstSq = curFirstSq;
        }
        if (curLastSq < bestLastSq){
            bestLastSq = curLastSq;
        }
    }
    // // debug
    // cerr << setw(10) << sqrt(bestFirstSq) << setw(10) << sqrt(bestLastSq);
    // cerr << setw(10) << lenMST << setw(10) << sqrt(bestFirstSq) + sqrt(bestLastSq) + lenMST + curDis<< "  ";
    return sqrt(bestFirstSq) + sqrt(bestLastSq) + lenMST + curDis;
}

bool TspOpt::promising(size_t permLength){
    // // debug
    // for (size_t i = 0; i < pathVerCur.size(); ++i)
    //     cerr << setw(2) << pathVerCur[i] << ' ';
    // cerr << setw(4) << permLength << setw(10) << curDis;
    if ((pathVerCur.size() - permLength) < 5) return true;
    double estimate = generateEST(permLength);
    if (estimate < bestDis){
        // // debug
        // cerr << true << '\n';
        return true;
    }
    // // debug
    // cerr << false << '\n';
    return false;
}

void TspOpt::genPerms(size_t permLength){
    if (permLength == pokemonVec.size()) {
        // calculate distance from last elements to first element
        // double disLast = distanceTSP(0, pathVerCur.back());
        // use fill table
        double disLast = sqrt(distSqVec[0][pathVerCur.back()]);
        curDis += disLast;
        update();
        curDis -= disLast;
        return;
    }  // if ..complete path

    if (!promising(permLength)) {
        return;
    }  // if ..not promising

    for (size_t i = permLength; i < pokemonVec.size(); ++i) {
        swap(pathVerCur[permLength], pathVerCur[i]);
        // double curEdge = distanceTSP(
        //     pathVerCur[permLength - 1], 
        //     pathVerCur[permLength]
        // );
        // use fill table
        double curEdge = sqrt(distSqVec[pathVerCur[permLength - 1]][pathVerCur[permLength]]);
        curDis += curEdge;
        genPerms(permLength + 1);
        curDis -= curEdge;
        swap(pathVerCur[permLength], pathVerCur[i]);
    }  // for ..unpermuted elements
}

void TspOpt::update(){
    if (curDis < bestDis){
        bestDis = curDis;
        pathVer = pathVerCur;
    }
}

void TspOpt::generateOTSP(Heuristics a){
    findBound(a);
    // begin from 1 because the 0 index is always visited
    genPerms(1);
}

void TspOpt::printOTSP(){
    cout << bestDis << '\n';
    for (size_t i = 0; i < pathVer.size(); ++i){
        cout << pathVer[i] << ' ';
    }
    cout << '\n';
}

void TspOpt::findBound(Heuristics a){
    if (a ==Heuristics::NearestOpt){
        generateFTSP(a);
        // use fill table
        fillDis();
        // because in FTSP the pathVer's structure is like [1,2,0]
        // needed to be changed to [0,1,2] for convenience for code
        pathVer.pop_back();
        pathVer.insert(pathVer.begin(), 0);
        pathVerCur = pathVer;
    }
    else if (a == Heuristics::ArbInsert){
        generateFTSP(a);
        // use fill table
        fillDis();
        vector<size_t> pathVerCopy = pathVer;
        // pathVer[i] stores vertex comes after i, needed to be changed to 
        // normal order like 0-1-2
        size_t vertex = 0;
        pathVer[0] = 0;
        for (size_t i = 1; i < pathVer.size(); ++i){
            pathVer[i] = pathVerCopy[vertex];
            vertex = pathVerCopy[vertex];
        }
        pathVerCur = pathVer;
    }
    // // debug
    // pathVer = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10};
    // pathVerCur = pathVer;
    // bestDis = 336.74;
}

double TspOpt::distanceSquareOPTTSP(size_t a, size_t b, vector<pokemon>& vec){
    double deltaX = vec[a].locX - vec[b].locX;
    double deltaY = vec[a].locY - vec[b].locY;
    return deltaX * deltaX + deltaY * deltaY;
}

void TspOpt::fillDis(){
    distSqVec.resize(pokemonVec.size(), vector<double>(pokemonVec.size(), 0));
    for (size_t i = 0; i < pokemonVec.size(); ++i){
        for (size_t j = 0; j < pokemonVec.size(); ++j){
            distSqVec[i][j] = distanceSquareTSP(i, j);
        }
    }
}