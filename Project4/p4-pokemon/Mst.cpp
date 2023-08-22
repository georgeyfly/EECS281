// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include "Mst.h"

void Mst::generateMST(){
    // fill in typeVec
    identifyType();
    // set initial distance to 0
    primVertexVec.resize(pokemonVec.size());
    primVertexVec[0].distance2Prev = 0;
    // loop N times
    for (size_t i = 0; i < primVertexVec.size(); ++i){
        // used for store the smallest distance and this vertex
        double curDis = numeric_limits<double>::infinity();
        size_t curVer = numeric_limits<size_t>::infinity();
        
        // find smallest false distance
        for (size_t j = 0; j < primVertexVec.size(); ++j){
            if (!primVertexVec[j].isVisited && 
                primVertexVec[j].distance2Prev < curDis){
                curDis = primVertexVec[j].distance2Prev;
                curVer = j;
            }
        }
        
        // set this curVer to be visited and add weight
        primVertexVec[curVer].isVisited = true;
        weight += primVertexVec[curVer].distance2Prev;
        
        // update the all false vertex's distance to curVer if shorter than before
        for (size_t k = 0; k < primVertexVec.size(); ++k){
            if (!primVertexVec[k].isVisited){
                double tempDis = distSquareMST(k, curVer);
                double prevDis = primVertexVec[k].distance2Prev;
                // tempDis is squared distance
                if (tempDis < prevDis * prevDis){
                    primVertexVec[k].distance2Prev = sqrt(tempDis);
                    primVertexVec[k].prevVertex = curVer;
                }
            }
        }
    }
}

void Mst::print(){
    // not find mst
    if (weight == numeric_limits<double>::infinity()){
        cerr << "Cannot construct MST" << '\n';
        exit(1);
    }
    // print mst
    cout << weight << '\n';
    for (size_t i = 1; i < primVertexVec.size(); ++i){
        if (i < primVertexVec[i].prevVertex){
            cout << i << ' ' << primVertexVec[i].prevVertex << '\n';
        }
        else {
            cout << primVertexVec[i].prevVertex << ' ' << i << '\n';
        }
    }
}

double Mst::distSquareMST(size_t a, size_t b){
    if ((typeVec[a] == Type::Sea && typeVec[b] == Type::Land) ||
        (typeVec[b] == Type::Sea && typeVec[a] == Type::Land)
    ){
        return numeric_limits<double>::infinity();
    }
    else {
        double deltaX = pokemonVec[a].locX - pokemonVec[b].locX;
        double deltaY = pokemonVec[a].locY - pokemonVec[b].locY;
        return deltaX * deltaX + deltaY * deltaY;
    } 
}

void Mst::identifyType(){
    typeVec.resize(pokemonVec.size());
    for (size_t i = 0; i < pokemonVec.size(); ++i){
        if (pokemonVec[i].locX > 0 || pokemonVec[i].locY > 0){
            typeVec[i] = Type::Land;
        }
        else if (pokemonVec[i].locX < 0 && pokemonVec[i].locY < 0){
            typeVec[i] = Type::Sea;
        }
        else {
            typeVec[i] = Type::CoastLine;
        }
    }
}