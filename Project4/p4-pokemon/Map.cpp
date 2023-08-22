// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include "Map.h"

void Map::read(){
    size_t numVertex;
    int readX;
    int readY;
    cin >> numVertex;
    pokemonVec.reserve(numVertex);
    for (size_t i = 0; i < numVertex; ++i){
        cin >> readX >> readY;
        pokemonVec.emplace_back(readX, readY);
    }
}

// Read and process command line options.
Mode get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    // use getopt to find command line options
    struct option longOpts[] = {
        { "mode",   required_argument, nullptr, 'm' },
        { "help",   no_argument,       nullptr, 'h' },
        { nullptr,  0,                 nullptr, '\0' },
    };
    
    /*

        TODO: Add the remaining chars to the option string in
                the while loop conditional (currently contains "p:h").
                Options with required_argument (print) need a colon after the
                char, options with no_argument do not (help).

    */
    while ((option = getopt_long(argc, argv, "m:h", longOpts, &option_index)) != -1) {
        switch (option) {
            case 'm':{
                char arg = optarg[0];
                if (arg == MST){
                    return Mode::Mst;
                }
                else if (arg == FAST_TSP){
                    return Mode::FastTsp;
                }
                else if (arg == OPT_TSP){
                    return Mode::OptTsp;
                }
                else {
                    cerr << "Error: Invalid mode\n";
                    exit(1);
                }
                break;
            }
            case 'h':{
                cout << "This program reads a txt file that contains,\n"
                     << "pokemon's coordinates \n";
                exit(0);
            }
        }
    }
    return Mode::NoMode;
    // if (!(mode == Mode::Mst || mode == Mode::FastTsp || mode == Mode::OptTsp)){
    //     cerr << "Error: No mode specified" << '\n';
    //     exit(1);
    // }
}