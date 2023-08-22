// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include <iostream>
#include <iomanip>
#include "Mst.h"
#include "Tsp.h"
#include "TspOpt.h"
using namespace std;

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    cout << std::setprecision(2); //Always show 2 decimal places
    cout << std::fixed; //Disable scientific notation for large numbers
    Mode mode = get_options(argc, argv);
    // // debug
    // cerr << fixed << showpoint << setprecision(2);
    // cerr << std::boolalpha;  // add these two lines
    if (mode == Mode::Mst){
        Mst aMst;
        aMst.read();
        aMst.generateMST();
        aMst.print();
    }
    else if (mode == Mode::FastTsp){
        Tsp aTsp;
        aTsp.read();
        aTsp.generateFTSP(Heuristics::ArbInsert);
        aTsp.printFTSP(Heuristics::ArbInsert);
    }
    else{
        TspOpt aTsp;
        aTsp.read();
        aTsp.generateOTSP(Heuristics::ArbInsert);
        aTsp.printOTSP();
    }
}