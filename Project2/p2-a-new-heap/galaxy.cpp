// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement galaxy class for for EECS403 Project2.
#include <iostream>
#include <string>
#include "galaxy.h"
#include "planet.h"
#include <getopt.h>
#include "constant.h"
#include "P2random.h"
using namespace std;


// Read and process command line options.
void galaxy::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    // use getopt to find command line options
    struct option longOpts[] = {
        { "verbose",      no_argument, nullptr, 'v' },
        { "median",       no_argument, nullptr, 'm' },
        { "general-eval", no_argument, nullptr, 'g'},
        { "watcher",      no_argument, nullptr, 'w' },
        { nullptr,        0,           nullptr, '\0' },
    };
    
    while ((option = getopt_long(argc, argv, "vmgw", longOpts, &option_index)) != -1) {
        switch (option) {
            case 'v':{
                doVerbose = true;
                break;
            }
            case 'm':{
                doMedian = true;
                break;
            }
            case 'g':{
                doGeneral = true;
                break;
            }
            case 'w':{
                doWatch = true;
                break;
            }
        }
    }
}
void galaxy::read_head(){
    string header;
    // get comment
    getline(cin, header);
    // get mode
    getline(cin, header);
    mode = header.substr(header.size() - 2);
    // get number of generals
    // getline(cin, header);
    // numGeneral = static_cast<uint32_t>(
    //     stoi(
    //         header.substr(header.size() - 2)
    //     )
    // );
    cin >> header >> numGeneral;
    // get number of planet
    // getline(cin, header);
    // numPlanet = static_cast<uint32_t>(
    //     stoi(
    //         header.substr(header.size() - 2)
    //     )
    // );
    cin >> header >> numPlanet;
    // get junk
    getline(cin, header);
    // resize vecPlanet
    vecPlanet.resize(numPlanet);
}

void galaxy::read_file(){
    read_head();
    // PR mode variable
    stringstream ss;
    uint32_t seed;
    uint32_t numDeployment;
    uint32_t arrivalRate;
    string s;
    // istream read variable
    uint32_t timestamp;
    string troop;
    string general;
    string planet;
    string force;
    string quantity;
    // changed from string variable
    uint32_t nPlanet;
    uint32_t nGeneral;
    uint32_t nForce;
    uint32_t nQuantity;
    // int variable
    int nPlanetint;
    int nGeneralint;
    int nForceint;
    int nQuantityint;
    char aChar;
    if (mode == PSEUDO_RAND){
        // get seed
        getline(cin, s);
        seed =  static_cast<uint32_t>(
            stoi(
                s.substr(RANDOM_SEED_INDEX)
            )
        );
        // get number of deployment
        getline(cin, s);
        numDeployment = static_cast<uint32_t>(
            stoi(
                s.substr(NUM_DEPLOYMENTS_INDEX)
            )
        );
        // get arrival rate
        getline(cin, s);
        arrivalRate = static_cast<uint32_t>(
            stoi(
                s.substr(ARRIVAL_RATE_INDEX)
            )
        );
        // store info in ss
        P2random::PR_init(
            ss, 
            seed, 
            numGeneral, 
            numPlanet, 
            numDeployment, 
            arrivalRate
        );
    }
    istream &inputStream = mode == "PR" ? ss : cin;
    // change size of vecGeneral
    if (doGeneral){
        vecGeneral.resize(numGeneral);
    }
    // change nPlanet and command vecGeneral for each planet
    for (uint32_t i = 0; i < vecPlanet.size(); ++i){
        vecPlanet[i].change_nPlanet(i);
        vecPlanet[i].change_command(
            doVerbose,
            doMedian,
            doGeneral,
            doWatch
        );
        if (doGeneral){
            vecPlanet[i].change_numGeneral(numGeneral);
            vecPlanet[i].vecGeneral.resize(numGeneral);
        }
    }
    // print start up
    cout << "Deploying troops...\n";
    // read deployment line by line
    // while (inputStream >> timestamp >> troop >> general 
    //                    >> planet >> force >> quantity){
    while (inputStream >> timestamp >> troop
                       >> aChar >> nGeneralint  
                       >> aChar >> nPlanetint 
                       >> aChar >> nForceint 
                       >> aChar >> nQuantityint){
        // nPlanet = stoi(planet.substr(1));
        // nGeneral = stoi(general.substr(1));
        // nForce = stoi(force.substr(1));
        // nQuantity = stoi(quantity.substr(1));
        nPlanet = static_cast<uint32_t> (nPlanetint);
        nGeneral = static_cast<uint32_t> (nGeneralint);
        nForce = static_cast<uint32_t> (nForceint);
        nQuantity = static_cast<uint32_t> (nQuantityint);
        // error check
        if (nForceint <= 0 || nQuantityint <= 0 ){
            cerr << " force or quantitiy is not greater than 0\n";
            exit(1);
        }
        if (nPlanetint < 0 || 
            nPlanetint >= static_cast<int> (numPlanet) || 
            nGeneralint < 0 ||
            nGeneralint >= static_cast<int> (numGeneral)){
            cerr << " numPlant or numGeneral is not in range\n";
            exit(1);
        }
        if (timestamp < currentTimestamp){
            cerr << " timestamp is decreasing\n";
            exit(1);
        }
        // median output
        if (timestamp != currentTimestamp){
            if (doMedian){
                for (size_t i = 0; i < vecPlanet.size(); ++i){
                    if (vecPlanet[i].nBattle > 0){
                        uint32_t median = vecPlanet[i].getMedian();
                        cout << "Median troops lost on planet " << i 
                             << " at time " << currentTimestamp << " is " 
                             <<  median << ".\n";
                    }        
                }
            }
        }
        currentTimestamp = timestamp;
        // instigate fight
        vecPlanet[nPlanet].instigateFight(
            troop,
            nGeneral,
            nForce,
            nQuantity,
            timestamp
        );
    }
    // median output last day
    if (doMedian){
        for (size_t i = 0; i < vecPlanet.size(); ++i){
            if (vecPlanet[i].nBattle > 0){
                uint32_t median = vecPlanet[i].getMedian();
                cout << "Median troops lost on planet " << i 
                     << " at time " << currentTimestamp << " is " 
                     <<  median << ".\n";
            }        
        }
    }
    // summary output
    for (size_t i = 0; i < vecPlanet.size(); ++i){
        sumBattle(vecPlanet[i]);
    }
    cout << "---End of Day---\n";
    cout << "Battles: " << totalBattle << '\n';
    // general output
    if (doGeneral){
        cout << "---General Evaluation---\n";
        for (uint32_t i = 0; i < vecGeneral.size(); ++i){
            for (uint32_t j = 0; j < vecPlanet.size(); ++j){
                vecGeneral[i] += vecPlanet[j].vecGeneral[i];
            }
            cout << "General " << i << " deployed " << vecGeneral[i].jediSum
                 << " Jedi troops and " << vecGeneral[i].sithSum
                 << " Sith troops, and " 
                 << vecGeneral[i].sithSurvive + vecGeneral[i].jediSurvive << "/" 
                 << vecGeneral[i].sithSum + vecGeneral[i].jediSum
                 << " troops survived.\n";
        }
    }
    // movie watcher output
    if (doWatch){
        cout << "---Movie Watcher---\n";
        for (uint32_t i = 0; i < vecPlanet.size(); ++i){
            if (
                vecPlanet[i].ambushState == state::SeenBoth ||
                vecPlanet[i].ambushState == state::Maybe
            ){
                cout << "A movie watcher would enjoy an ambush on planet " << i
                     << " with Sith at time " 
                     << vecPlanet[i].ambushBestSith.timestamp 
                     << " and Jedi at time "
                     << vecPlanet[i].ambushBestJedi.timestamp
                     << " with a force difference of "
                     << vecPlanet[i].ambushBestSith.force - 
                        vecPlanet[i].ambushBestJedi.force
                     << ".\n";
            }
            if (
                vecPlanet[i].ambushState == state::Initial ||
                vecPlanet[i].ambushState == state::SeenOne
            ){
                cout << "A movie watcher would not see an" 
                     << " interesting ambush on planet "
                     << i << ".\n";
            }
            if (
                vecPlanet[i].attackState == state::SeenBoth ||
                vecPlanet[i].attackState == state::Maybe
            ){
                cout << "A movie watcher would enjoy an attack on planet " << i
                     << " with Jedi at time " 
                     << vecPlanet[i].attackBestJedi.timestamp 
                     << " and Sith at time "
                     << vecPlanet[i].attackBestSith.timestamp
                     << " with a force difference of "
                     << vecPlanet[i].attackBestSith.force - 
                        vecPlanet[i].attackBestJedi.force
                     << ".\n";
            }
            if (
                vecPlanet[i].attackState == state::Initial ||
                vecPlanet[i].attackState == state::SeenOne
            ){
                cout << "A movie watcher would not see an" 
                     << " interesting attack on planet "
                     << i << ".\n";
            }
        }
    }

}

void galaxy::sumBattle(const planet &aPlanet){
    totalBattle += aPlanet.nBattle;
}
