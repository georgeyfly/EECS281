// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#ifndef MAP_H_
#define MAP_H_
#include <iostream>
#include <vector>
#include <getopt.h>
#include "constant.h"
using namespace std;

struct pokemon{
    int locX;
    
    int locY;

    pokemon(): locX(0), locY(0){};

    pokemon(int a, int b): locX(a), locY(b){};
};

enum class Mode: uint8_t {Mst, FastTsp, OptTsp, NoMode};

// read command line
Mode get_options(int argc, char** argv);

class Map{
    private:

        // Mode mode;

        // Map(): mode(Mode::NoMode){};

    protected:

        vector<pokemon> pokemonVec;

    public:

        void read(); // read in the input file and 
                     // assign coordinateXY to vecPokemon
};

#endif