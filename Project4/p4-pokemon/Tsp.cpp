// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include "Tsp.h"
#include <algorithm>
#include <utility>
using namespace std;

double Tsp::distanceSquareTSP(size_t a, size_t b){
    double deltaX = pokemonVec[a].locX - pokemonVec[b].locX;
    double deltaY = pokemonVec[a].locY - pokemonVec[b].locY;
    return deltaX * deltaX + deltaY * deltaY;
}

double Tsp::distanceTSP(size_t a, size_t b){
    double deltaX = pokemonVec[a].locX - pokemonVec[b].locX;
    double deltaY = pokemonVec[a].locY - pokemonVec[b].locY;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void Tsp::generateNearPath(){
    // path.resize(pokemonVec.size());
    // // pathVer.resize(pokemonVec.size(),0);
    // // pathDis.resize(pokemonVec.size(),0);
    // pathVerDis.resize(pokemonVec.size());
    // size_t curVer = 0;

    // for (size_t i = 0; i < pokemonVec.size() - 1; ++i){
    //     // find nearest closest unvisited vertex and distance
    //     double curDisSq = numeric_limits<double>::infinity();
    //     for (size_t j = 0; j < pokemonVec.size(); ++j){
    //         if (!path[j].isVisited && curVer != j){
    //             double tempDisSq = distanceSquareTSP(curVer, j);
    //             if (tempDisSq < curDisSq){
    //                 curDisSq = tempDisSq;
    //                 // pathVer[i] = j;
    //                 pathVerDis[i].nextVertex = j;
    //             }
    //         }
    //     }
    //     // update curVer's distance to next vertex & add to bestDis
    //     // path[curVer].distance2Next = sqrt(curDisSq);
    //     // bestDis += path[curVer].distance2Next;

    //     pathVerDis[i].distance2Next = sqrt(curDisSq);
    //     bestDis += pathVerDis[i].distance2Next;
    //     // update isVisted to true
    //     path[curVer].isVisited = true;
    //     // update curVer to next Vertex
    //     curVer = pathVerDis[i].nextVertex;
    // }
    // // update last one
    // pathVerDis[pathVerDis.size() - 1].nextVertex = 0;
    // double curDisSq = distanceSquareTSP(curVer, 0);
    // // update curVer's distance to next vertex & add to bestDis
    // // path[curVer].distance2Next = sqrt(curDisSq);
    // // bestDis += path[curVer].distance2Next;

    // pathVerDis[pathVerDis.size() - 1].distance2Next = sqrt(curDisSq);
    // bestDis += pathVerDis[pathVerDis.size() - 1].distance2Next;
    // // update isVisted to true
    // path[curVer].isVisited = true;

    pathVisited.resize(pokemonVec.size(),false);
    pathVer.resize(pokemonVec.size(),0);
    pathDis.resize(pokemonVec.size(),0);
    // pathVerDis.resize(pokemonVec.size());
    size_t curVer = 0;

    for (size_t i = 0; i < pokemonVec.size() - 1; ++i){
        // find nearest closest unvisited vertex and distance
        double curDisSq = numeric_limits<double>::infinity();
        for (size_t j = 0; j < pokemonVec.size(); ++j){
            if (!pathVisited[j]&& curVer != j){
                double tempDisSq = distanceSquareTSP(curVer, j);
                if (tempDisSq < curDisSq){
                    curDisSq = tempDisSq;
                    pathVer[i] = j;
                }
            }
        }
        // update curVer's distance & add to bestDis
        pathDis[i] = sqrt(curDisSq);
        bestDis += pathDis[i];
        // update isVisted to true
        pathVisited[curVer] = true;
        // update curVer to next Vertex
        curVer = pathVer[i];
    }
    // do last one seperately because all vertexes is visited and I can't 
    // run update in the for loop above
    // update last one
    pathDis[pathDis.size() - 1] = 0;
    double curDisSq = distanceSquareTSP(curVer, 0);
    // update curVer's distance to next vertex & add to bestDis
    pathDis[pathDis.size() - 1] = sqrt(curDisSq);
    bestDis += pathDis[pathDis.size() - 1];
    // update isVisted to true
    pathVisited[curVer] = true;
}

void Tsp::twoOpt(){       
    bool isImproved = true;
    size_t count = 0;
    // i-1, i are the outer loop while j-1, j are the inner loop
    // ex. 0-2-3-4-0, 
    // pathVer[i-1] is 0, pathVer[i] is 2
    // pathVer[j-1] is 3, pathVer[j] is 4 
    while (isImproved){
        isImproved = false;
        // initialize nodei0, which is the order of i in path
        size_t nodei0 = 0;
        for (size_t i = 0; i < pathVisited.size() - 2; ++i){
            size_t nodei1 = pathVer[i];
            // initialize nodej0, which is the order of j in path
            size_t nodej0 = pathVer[i + 1];
            for (size_t j = i + 2; j < pathVisited.size(); ++j){
                size_t nodej1 = pathVer[j]; 
                double dis_i0j0 = distanceTSP(nodei0, nodej0);
                double dis_i1j1 = distanceTSP(nodei1, nodej1);
                double change = (dis_i0j0 + dis_i1j1) - 
                                (pathDis[i] + pathDis[j]);
                if (change < 0){
                    // reverse vertex
                    auto it = pathVer.begin();
                    auto itBegin = it + static_cast<vector<size_t>::difference_type>(i);
                    auto itEnd = it + static_cast<vector<size_t>::difference_type>(j);
                    reverse(itBegin, itEnd);
                    // reverse distance
                    auto it2 = pathDis.begin();
                    auto itBegin2 = it2 + static_cast<vector<size_t>::difference_type>(i + 1);
                    auto itEnd2 = it2 + static_cast<vector<size_t>::difference_type>(j);
                    reverse(itBegin2, itEnd2);
                    // swap nodei1 nodej0
                    swap(nodei1, nodej0);
                    bestDis += change;
                    isImproved = true;
                    pathDis[i] = dis_i0j0;
                    pathDis[j] = dis_i1j1;
                }
                // update nodej0 to next node(nodej1)
                nodej0 = nodej1;
            }
            nodei0 = nodei1;
        }
        ++count;
        if (count == 1){
            return;
        }
    }
}

void Tsp::generateFTSP(Heuristics a){
    if (a == Heuristics:: NearestOpt){
        generateNearPath();
        twoOpt();
    }
    else if (a == Heuristics::ArbInsert){
        generateArbInsert();
    }
    
}

void Tsp::printFTSP(Heuristics a){
    if (a == Heuristics:: NearestOpt){
        cout << bestDis << '\n';
        cout << 0 << ' ';
        for (size_t i = 0; i < pathVer.size() - 1; ++i){
            cout << pathVer[i] << ' ';
        }
        cout << '\n';
    }
    else if (a == Heuristics::ArbInsert){
        cout << bestDis << '\n';
        size_t vertex = 0;
        for (size_t i = 0; i < pathVer.size(); ++i){
            cout << vertex << ' ';
            vertex = pathVer[vertex];
        }
        cout << '\n';
    }
}

void Tsp::generateArbInsert(){
    // initialize first 2 elements
    pathVer.resize(pokemonVec.size(), 0);
    pathDis.resize(pokemonVec.size(), 0);
    pathVer[0] = 1;
    pathVer[1] = 2;
    pathDis[0] = distanceTSP(0, 1);
    pathDis[1] = distanceTSP(1, 2);
    pathDis[2] = distanceTSP(2, 0);
    bestDis = pathDis[0] + pathDis[1] + pathDis[2];
    // size_t visitedlength = 3;
    // k is unvisited vertex
    // i is visited vertex
    for (size_t k = 3; k < pokemonVec.size(); ++k){
        double change_best = numeric_limits<double>::infinity();
        size_t i_best = numeric_limits<size_t>::infinity();
        size_t j_best = numeric_limits<size_t>::infinity();
        double dis_ik_best = numeric_limits<double>::infinity();
        double dis_kj_best = numeric_limits<double>::infinity();
        for (size_t i = 0; i < k; ++i){
            size_t j = pathVer[i];
            double dis_ik = distanceTSP(i, k);
            double dis_kj = distanceTSP(k, j);
            double dis_ij = pathDis[i];
            double dis_ijk = dis_ik + dis_kj - dis_ij;
            if (dis_ijk < change_best){
                change_best = dis_ijk;
                i_best = i;
                j_best = j;
                dis_ik_best = dis_ik;
                dis_kj_best = dis_kj;
            }
        }
        bestDis += change_best;
        pathVer[i_best] = k;
        pathVer[k] = j_best;
        pathDis[i_best] = dis_ik_best;
        pathDis[k] = dis_kj_best;
    }
}