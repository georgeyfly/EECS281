// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement planet class for for EECS403 Project2.
#ifndef _PLANET_H_
#define _PLANET_H_
#include <iostream>
#include <queue>
#include "deployment.h"
#include "comparator.h"
#include "general.h"
#include "watcher.h"
#include "state.h"
using namespace std;


class planet{
    private:
        priority_queue<
            deployment, 
            vector<deployment>, 
            deploymentLessComparator > sithPQ;
        priority_queue<
            deployment, 
            vector<deployment>, 
            deploymentGreaterComparator > jediPQ;
        uint32_t nBattle;
        // for median mode
        uint32_t nDeath;
        uint32_t nowMedian;
        // for median mode, largePQ is a minheap storing larger value
        priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t> > largePQ;
        // for median mode, smallPQ is a maxheap storing smaller value
        priority_queue<uint32_t, vector<uint32_t>, less<uint32_t> > smallPQ;
        // verbose mode
        uint32_t nPlanet;
        // geneal mode
        uint32_t numGeneral;
        vector <general> vecGeneral;
        // watcher mode attack
        watcher attackBestJedi;
        watcher attackBestSith;
        watcher attackMaybeJedi;
        state attackState;
        // watcher mode attack
        watcher ambushBestJedi;
        watcher ambushBestSith;
        watcher ambushMaybeSith;
        state ambushState;
        // command line variable
        bool doVerbose;
        bool doMedian;
        bool doGeneral;
        bool doWatch;
    public:
        planet(){
            nBattle = 0;
            nDeath = 0;
            nowMedian = 0;
            nPlanet = 0;
            doVerbose = false;
            doMedian = false;
            doGeneral = false;
            doWatch = false;
            attackState = state::Initial;
            ambushState = state::Initial;
        };
        // instigateFight
        void instigateFight(
            const string &troop,
            const uint32_t &nGeneral,
            const uint32_t &nForce,
            const uint32_t &nQuantity,
            const uint32_t &timestamp
        );
        // print median result
        uint32_t getMedian();
        // print verbose result
        void printVerbose();
        // General output
        void changeGeneral(
            const deployment &sith,
            const deployment &jedi
        );
        // change attack movie mode
        void changeAttackMovieMode(
            const string &troop,
            const deployment &newDeploy,
            const uint32_t &timestamp
        );
        // change ambush movie mode
        void changeAmbushMovieMode(
            const string &troop,
            const deployment &newDeploy,
            const uint32_t &timestamp
        );
        // change nPlanet
        void change_nPlanet(uint32_t &i);
        // change command line variable
        void change_command(
            bool &Verbose,
            bool &Median,
            bool &General,
            bool &Watch
        );
        // change numGeneral
        void change_numGeneral(uint32_t &i);
        // friend void sumBattle(const planet &aPlanet);
        friend class galaxy;


};


#endif