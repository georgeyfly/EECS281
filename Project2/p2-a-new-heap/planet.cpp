// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement planet class for for EECS403 Project2.

#include <iostream>
#include "planet.h"
using namespace std;

void planet::instigateFight(
    const string &troop,
    const uint32_t &nGeneral,
    const uint32_t &nForce,
    const uint32_t &nQuantity,
    const uint32_t &timestamp
){
    deployment newDeploy(
        nGeneral,
        nForce,
        nQuantity
    );
    if (troop == JEDI){
        jediPQ.push(newDeploy);
        if (doGeneral){
            vecGeneral[nGeneral].jediSum += nQuantity; 
            vecGeneral[nGeneral].jediSurvive += nQuantity; 
        }
        if (doWatch){
            changeAmbushMovieMode(troop, newDeploy, timestamp);
            changeAttackMovieMode(troop, newDeploy, timestamp);
        }
    }
    else{
        sithPQ.push(newDeploy);
        if (doGeneral){
            vecGeneral[nGeneral].sithSum += nQuantity;  
            vecGeneral[nGeneral].sithSurvive += nQuantity; 
        }
        if (doWatch){
            changeAmbushMovieMode(troop, newDeploy, timestamp);
            changeAttackMovieMode(troop, newDeploy, timestamp);
        }
    }
    // if PQ not empty, compare top of two PQ
    if (
        !(sithPQ.empty() || jediPQ.empty())
    ){
        while (sithPQ.top().force >= jediPQ.top().force){
            if (sithPQ.top().quantity > jediPQ.top().quantity){
                sithPQ.top().quantity -= jediPQ.top().quantity;
                ++nBattle;
                nDeath = jediPQ.top().quantity * 2;
                if (doVerbose){
                    printVerbose();
                }
                if (doGeneral){
                    changeGeneral(
                        sithPQ.top(),
                        jediPQ.top()
                    );
                }
                if (doMedian){
                    getMedian();
                }
                jediPQ.pop();
            }
            else if (sithPQ.top().quantity < jediPQ.top().quantity){
                jediPQ.top().quantity -= sithPQ.top().quantity;
                ++nBattle;
                nDeath = sithPQ.top().quantity * 2;
                if (doVerbose){
                    printVerbose();
                }
                if (doGeneral){
                    changeGeneral(
                        sithPQ.top(),
                        jediPQ.top()
                    );
                }
                if (doMedian){
                    getMedian();
                }
                sithPQ.pop();
            }
            else {
                ++nBattle;
                nDeath = sithPQ.top().quantity * 2;
                if (doVerbose){
                    printVerbose();
                }
                if (doGeneral){
                    changeGeneral(
                        sithPQ.top(),
                        jediPQ.top()
                    );
                }
                if (doMedian){
                    getMedian();
                }
                sithPQ.pop();
                jediPQ.pop();
            }
            if (sithPQ.empty() || jediPQ.empty()){
                break;
            }
        }
    }
}

uint32_t planet::getMedian(){
    uint32_t median;
    // special condition
    // check if battle happen
    if (nDeath == 0 && nBattle > 0){
        return nowMedian;
    }
    // smallPQ.empty condition
    else if (smallPQ.empty()){
        smallPQ.push(nDeath);
        nDeath = 0;
        nowMedian = smallPQ.top();
        return smallPQ.top();
    }
    // largePQ.empty condition
    else if (largePQ.empty()){
        smallPQ.push(nDeath);
        largePQ.push(smallPQ.top());
        smallPQ.pop();
        nDeath = 0;
        nowMedian = (smallPQ.top() + largePQ.top()) / 2;
        return (smallPQ.top() + largePQ.top()) / 2;
    }

    // normal condition
    // insert to smallPQ
    if (largePQ.top() >= nDeath){
        smallPQ.push(nDeath);
        if (smallPQ.size() - largePQ.size() == SIZE_UNEQUAL){
            largePQ.push(smallPQ.top());
            smallPQ.pop();
            median = (smallPQ.top() + largePQ.top()) / 2;
        }
        else if (smallPQ.size() - largePQ.size() == SIZE_EQUAL_NO_MEAN){
            median = smallPQ.top();
        }
        else {
            median = (smallPQ.top() + largePQ.top()) / 2;
        }
    }
    // insert to largePQ
    else {
        largePQ.push(nDeath);
        if (largePQ.size() - smallPQ.size() == SIZE_UNEQUAL){
            smallPQ.push(largePQ.top());
            largePQ.pop();
            median = (smallPQ.top() + largePQ.top()) / 2;
        }
        else if (largePQ.size() - smallPQ.size() == SIZE_EQUAL_NO_MEAN){
            median = largePQ.top();
        }
        else {
            median = (smallPQ.top() + largePQ.top()) / 2;
        }
    }
    // initialize nDeath
    nDeath = 0;
    nowMedian = median;
    return median;
}

void planet::printVerbose(){
    cout << "General " << sithPQ.top().general 
         << "'s battalion attacked General " << jediPQ.top().general
         << "'s battalion on planet " << nPlanet << ". "
         << nDeath << " troops were lost.\n";
}

void planet::changeGeneral(
    const deployment &sith,
    const deployment &jedi
){
    uint32_t nGeneralSith = sith.general;
    uint32_t nGeneralJedi = jedi.general;
    vecGeneral[nGeneralSith].sithSurvive -= nDeath / 2; 
    vecGeneral[nGeneralJedi].jediSurvive -= nDeath / 2; 
}
void planet::changeAttackMovieMode(
    const string &troop,
    const deployment &newDeploy,
    const uint32_t &timestamp
){
    if (troop == JEDI){
        if (attackState == state::Initial){
            attackState = state::SeenOne;
            attackBestJedi.force = newDeploy.force;
            attackBestJedi.timestamp = timestamp;
        }
        else if (attackState == state::SeenOne){
            if (newDeploy.force < attackBestJedi.force){
                attackBestJedi.force = newDeploy.force;
                attackBestJedi.timestamp = timestamp;
            }
        }
        else if (attackState == state::SeenBoth){
            if (newDeploy.force < attackBestJedi.force){
                attackState = state::Maybe;
                attackMaybeJedi.force = newDeploy.force;
                attackMaybeJedi.timestamp = timestamp;
            }
        }
        else {
            if (newDeploy.force < attackMaybeJedi.force){
                attackMaybeJedi.force = newDeploy.force;
                attackMaybeJedi.timestamp = timestamp;
            }
        }
    } 

    else {
        if (attackState == state::SeenOne){
            if (newDeploy.force >= attackBestJedi.force){
                attackState = state::SeenBoth;
                attackBestSith.force = newDeploy.force;
                attackBestSith.timestamp = timestamp;
            }
        }
        else if (attackState == state::SeenBoth){
            if (newDeploy.force > attackBestSith.force){
                attackBestSith.force = newDeploy.force;
                attackBestSith.timestamp = timestamp;
            }
        }
        else if (attackState == state::Maybe){
            if (
                (newDeploy.force + attackBestJedi.force) > 
                (attackBestSith.force + attackMaybeJedi.force)
            ){
                attackState = state::SeenBoth;
                attackBestJedi.force = attackMaybeJedi.force;
                attackBestJedi.timestamp = attackMaybeJedi.timestamp;
                attackBestSith.force = newDeploy.force;
                attackBestSith.timestamp = timestamp;
            }
        }
    } 
}


void planet::changeAmbushMovieMode(
    const string &troop,
    const deployment &newDeploy,
    const uint32_t &timestamp
){
    if (troop == SITH){
        if (ambushState == state::Initial){
            ambushState = state::SeenOne;
            ambushBestSith.force = newDeploy.force;
            ambushBestSith.timestamp = timestamp;
        }
        else if (ambushState == state::SeenOne){
            if (newDeploy.force > ambushBestSith.force){
                ambushBestSith.force = newDeploy.force;
                ambushBestSith.timestamp = timestamp;
            }
        }
        else if (ambushState == state::SeenBoth){
            if (newDeploy.force > ambushBestSith.force){
                ambushState = state::Maybe;
                ambushMaybeSith.force = newDeploy.force;
                ambushMaybeSith.timestamp = timestamp;
            }
        }
        else {
            if (newDeploy.force > ambushMaybeSith.force){
                ambushMaybeSith.force = newDeploy.force;
                ambushMaybeSith.timestamp = timestamp;
            }
        }
    } 

    else {
        if (ambushState == state::SeenOne){
            if (newDeploy.force <= ambushBestSith.force){
                ambushState = state::SeenBoth;
                ambushBestJedi.force = newDeploy.force;
                ambushBestJedi.timestamp = timestamp;
            }
        }
        else if (ambushState == state::SeenBoth){
            if (newDeploy.force < ambushBestJedi.force){
                ambushBestJedi.force = newDeploy.force;
                ambushBestJedi.timestamp = timestamp;
            }
        }
        else if (ambushState == state::Maybe){
            if (
                (ambushMaybeSith.force + ambushBestJedi.force) > 
                (ambushBestSith.force + newDeploy.force)
            ){
                ambushState = state::SeenBoth;
                ambushBestSith.force = ambushMaybeSith.force;
                ambushBestSith.timestamp = ambushMaybeSith.timestamp;
                ambushBestJedi.force = newDeploy.force;
                ambushBestJedi.timestamp = timestamp;
            }
        }
    } 
}

void planet::change_nPlanet(uint32_t &i){
    nPlanet = i;
}
void planet::change_command(
    bool &Verbose,
    bool &Median,
    bool &General,
    bool &Watch
){
    doVerbose = Verbose;
    doMedian = Median;
    doGeneral = General;
    doWatch = Watch;
}
void planet::change_numGeneral(uint32_t &i){
    numGeneral = i;
}