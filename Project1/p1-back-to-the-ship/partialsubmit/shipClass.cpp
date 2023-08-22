// IDENTIFIER  = 950181F63D0A883F183EC0A5CC67B19928FE896A
#include <iostream>
#include "constant.h"
#include "containerStruct.h"
#include "shipClass.h"
#include <getopt.h>
#include <string>
using namespace std;

// Programmer: Qiaozhi Huang
// Date: Jan 2023
// Purpose: implement shipClass to operate on ship for EECS403 Project1.

shipClass::shipClass(){
    outMode = MAP;
    doFindSolution = false;
    totalLen = 0;
    totalLevel = 0;
}
// Read and process command line options.
void shipClass::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    // use getopt to find command line options
    struct option longOpts[] = {
        { "stack",  no_argument,       nullptr, 's' },
        { "queue",  no_argument,       nullptr, 'q' },
        { "output", required_argument, nullptr, 'o'},
        { "help",   no_argument,       nullptr, 'h' },
        { nullptr,  0,                 nullptr, '\0' },
    };
    
    /*

        TODO: Add the remaining chars to the option string in
                the while loop conditional (currently contains "p:h").
                Options with required_argument (print) need a colon after the
                char, options with no_argument do not (help).

    */
    while ((option = getopt_long(argc, argv, "sqo:h", longOpts, &option_index)) != -1) {
        switch (option) {
            case 's':{
                if (routeScheme == STACK || routeScheme == QUEUE)
                {
                    cerr << "more than one route scheme were given" << '\n';
                    exit(1);
                }
                routeScheme = STACK;
                break;
            }
            case 'q':{
                if (routeScheme == STACK || routeScheme == QUEUE)
                {
                    cerr << "more than one route scheme were given" << '\n';
                    exit(1);
                }
                routeScheme = QUEUE;
                break;
            }
            case 'o':{
                char arg = optarg[0];
                if (arg == LIST){
                    outMode = LIST;
                }
                else if (arg == MAP){
                    outMode = MAP;
                }
                // else{
                    // error
                // }
                break;
            }
            case 'h':{
                cout << "This program reads a txt file that contains ship,\n"
                     << "layout \n"
                     << "It then outputs the escape route\n"
                     << "in the command line arguments (the output option),\n"
                     << "Usage: \'./project1\n\t[--stack | -s]\n"
                     <<                      "\t[--queue | -q]\n"
                     <<                      "\t[--output | -o]" 
                     <<                      " <txt File>\n"
                     <<                      "\t[--help | -h]\n";
                exit(0);
            }
        }
    }
    if (!(routeScheme == STACK || routeScheme == QUEUE)){
        cerr << "No route scheme was given" << '\n';
        exit(1);
    }
}

void shipClass::read_file(){
    char readChar;
    string comment;
    string junk;
    uint32_t nRow;
    uint32_t nCol;
    uint32_t nLevel;
    uint32_t squareOfOneLevel;
    uint32_t totalCount = 0; // the number of square read in
    char square;
    char cRubbish;
    while (cin >> readChar){
        // 1.inMode, level , square length read. 
        // 2. resize map3D
        if (readChar == MAP ||
            readChar == LIST){
            inMode = readChar;
            cin >> totalLevel >> totalLen;
            squareOfOneLevel = totalLen * totalLen;
            map3D.resize(
                totalLevel, 
                vector< vector <map3DStruct> >(
                    totalLen, 
                    vector <map3DStruct> (
                        totalLen
                    )
                )
            );
        }
        // read comment
        else if (readChar == SLASH){
            getline(cin, comment);
        }
        // read coordinate and change map3D
        else if (readChar == LEFT_BRACKET){
            cin >> nLevel >> cRubbish >> nRow >> cRubbish >> nCol 
                >> cRubbish >> square >> cRubbish;
            if (nLevel > totalLevel - 1 ||
                nRow > totalLen - 1 ||
                nCol > totalLen - 1
                ){
                cerr << "coorinate is invalid\n";
                exit(1);
            }
            if (!(square == FLOOR ||
                square == WALL ||
                square == START ||
                square == HANGAR ||
                square == ELEVATOR)
                ){
                cerr << "input character is invalid\n";
                exit(1);
            }
            map3D[nLevel][nRow][nCol].character = square;
            if (square == START){
                startPos.level = nLevel;
                startPos.row = nRow;
                startPos.col = nCol;
                curLoc = startPos;
                searchContainer.push_back(startPos);
                map3D[nLevel][nRow][nCol].discover = true;
            }
        }
        else{
            nLevel = totalCount / squareOfOneLevel;
            nRow = totalCount % squareOfOneLevel / totalLen;
            nCol = totalCount % totalLen;
            totalCount += 1;
            if (!(readChar == FLOOR ||
                readChar == WALL ||
                readChar == START ||
                readChar == HANGAR ||
                readChar == ELEVATOR)
                ){
                cerr << "input character is invalid\n";
                exit(1);
            }
            else if (readChar != FLOOR){
                map3D[nLevel][nRow][nCol].character = readChar;
                if (readChar == START){
                    startPos.level = nLevel;
                    startPos.row = nRow;
                    startPos.col = nCol;
                    curLoc = startPos;
                    searchContainer.push_back(startPos);
                    map3D[nLevel][nRow][nCol].discover = true;
                }
            }
        }
    }
}

void shipClass::discoverPlane(containerStruct &position){
    uint32_t nRow;
    uint32_t nCol;
    uint32_t nLevel;
    if (inBound(position) &&
        !isDiscover(position) &&
        !isWall(position)
        ){
        searchContainer.push_back(position);
        nLevel = position.level;
        nRow = position.row;
        nCol = position.col;
        map3D[nLevel][nRow][nCol].discover = true;
        // check north part and assign forthDirect to north
        if (nRow == curLoc.row - 1){
            map3D[nLevel][nRow][nCol].forthDirect = NORTH;
        }
        // check east part and assign forthDirect to east
        else if (nCol == curLoc.col + 1){
            map3D[nLevel][nRow][nCol].forthDirect = EAST;
        }
        // check south part and assign forthDirect to south
        else if (nRow == curLoc.row + 1){
            map3D[nLevel][nRow][nCol].forthDirect = SOUTH;
        }
        // check west part and assign forthDirect to west
        else if (nCol == curLoc.col - 1){
            map3D[nLevel][nRow][nCol].forthDirect = WEST;
        }
        if (isHangar(position)){
            endPos = position;
            doFindSolution = true;
        }
        
    }
}
void shipClass::discoverAllLevel(containerStruct &position){
    uint32_t nRow;
    uint32_t nCol;
    nRow = position.row;
    nCol = position.col;
    if (isElevator(position)){
        for (uint32_t i = 0; i < totalLevel; ++i){
            containerStruct elevator(i, nRow, nCol);
            if (i != position.level &&
                isElevator(elevator)){
                // if elevator has been discovered, break loop
                if (!map3D[i][nRow][nCol].discover){
                    searchContainer.push_back(elevator);
                    map3D[i][nRow][nCol].discover = true;
                    // why '0' needed?
                    map3D[i][nRow][nCol].forthDirect = static_cast<char>(
                        '0' + position.level
                        );
                }
            }
        }
    }
}
void shipClass::iterateCurLoc(){
    if (routeScheme == QUEUE){
        curLoc = searchContainer.front();
        searchContainer.pop_front();
    }
    else if (routeScheme == STACK){
        curLoc = searchContainer.back();
        searchContainer.pop_back();
    }
}


void shipClass::investigateAndDiscover(){
    uint32_t nRow;
    uint32_t nCol;
    uint32_t nLevel;
    nLevel = curLoc.level;
    nRow = curLoc.row;
    nCol = curLoc.col;
    uint32_t newPara;
    // debug
    // if (nLevel == 0 && nRow == 25 && nCol == 24){
    //     newPara = 24;
    // }
    // if (nLevel == 0 && nRow == 24 && nCol == 23){
    //     newPara = 24;
    // }

    // check NESW in bound or not
    newPara = nRow - 1;
    containerStruct northLoc(nLevel, newPara, nCol);
    newPara = nCol + 1;
    containerStruct eastLoc(nLevel, nRow, newPara);
    // debug
    if (nLevel == 0 && newPara == 24 && nRow == 25){
        newPara = 24;
    }
    newPara = nRow + 1;
    containerStruct southLoc(nLevel, newPara, nCol);
    newPara = nCol - 1;
    containerStruct westLoc(nLevel, nRow ,newPara);
    // if (nLevel == 0 && nRow == 31){
    //     newPara = 30;
    // }
    // if (nLevel == 0 && nRow == 27){
    //     newPara = 30;
    // }
    discoverPlane(northLoc);
    discoverPlane(eastLoc);
    discoverPlane(southLoc);
    discoverPlane(westLoc);
    discoverAllLevel(curLoc);
}

bool shipClass::inBound(containerStruct &obj){
    if (obj.row < 0 ||
        obj.row > (totalLen - 1) ||
        obj.col < 0 ||
        obj.col > (totalLen - 1)
        ){
        return false;
    }
    return true;
}

bool shipClass::isDiscover(containerStruct &obj){
    return map3D[obj.level][obj.row][obj.col].discover;
}
bool shipClass::isWall(containerStruct &obj){
    return map3D[obj.level][obj.row][obj.col].character == WALL;
}
bool shipClass::isElevator(containerStruct &obj){
    return map3D[obj.level][obj.row][obj.col].character == ELEVATOR;
}
bool shipClass::isHangar(containerStruct &obj){
    return map3D[obj.level][obj.row][obj.col].character == HANGAR;
}
void shipClass::output_file(){

    if (outMode == MAP){
        if (doFindSolution){
            addRouteAndModifyMap();
            cout << "Start in level " << startPos.level 
                << ", row " << startPos.row
                << ", column " << startPos.col 
                << '\n';
            for (size_t i = 0; i < totalLevel; ++i){
                cout << "//level " << i << '\n'; 
                for (size_t j = 0; j < totalLen; ++j){
                    for (size_t k = 0; k < totalLen; ++k){
                        cout << map3D[i][j][k].character;
                    }
                    cout << '\n';
                }
            }
        }
    }
    else{
        cout << "//path taken\n";
        if (doFindSolution){
            addRouteAndModifyMap();
            while (!routeEscape.empty()){
                curLoc = routeEscape.back();
                routeEscape.pop_back(); 
                cout << LEFT_BRACKET << curLoc.level << COMMA << curLoc.row 
                     << COMMA << curLoc.col << COMMA 
                     << map3D[curLoc.level][curLoc.row][curLoc.col].character
                     << RIGHT_BRACKET << '\n';
            }
        }
        else{
            return;
        }
    }
}
void shipClass::addRouteAndModifyMap(){
    uint32_t level;
    char forthDirectRoute;
    curLoc = endPos;
    while (!(curLoc == startPos)){
        forthDirectRoute = 
            map3D[curLoc.level][curLoc.row][curLoc.col].forthDirect;
        if (forthDirectRoute == NORTH) {
            // previous position will be opposite of the forth direction
            uint32_t temp = curLoc.row + 1;
            containerStruct prevStruct(
                curLoc.level,
                temp,
                curLoc.col
            );
            // update curLoc to previous location
            curLoc = prevStruct;
            // change character to the output direction
            map3D[curLoc.level][curLoc.row][curLoc.col].character = 
                forthDirectRoute;
        }
        else if (forthDirectRoute == EAST) {
            uint32_t temp = curLoc.col - 1;
            containerStruct prevStruct(
                curLoc.level,
                curLoc.row,
                temp
            );
            // update curLoc to previous location
            curLoc = prevStruct;
            // change character to the output direction
            map3D[curLoc.level][curLoc.row][curLoc.col].character = 
                forthDirectRoute;
        }
        else if (forthDirectRoute == SOUTH) {
            uint32_t temp = curLoc.row - 1;
            containerStruct prevStruct(
                curLoc.level,
                temp,
                curLoc.col
            );
            // update curLoc to previous location
            curLoc = prevStruct;
            // change character to the output direction
            map3D[curLoc.level][curLoc.row][curLoc.col].character = 
                forthDirectRoute;
        }
        else if (forthDirectRoute == WEST) {
            uint32_t temp = curLoc.col + 1;
            containerStruct prevStruct(
                curLoc.level,
                curLoc.row,
                temp
            );
            // update curLoc to previous location
            curLoc = prevStruct;
            // change character to the output direction
            map3D[curLoc.level][curLoc.row][curLoc.col].character = 
                forthDirectRoute;
        }
        else {
            level = static_cast<uint32_t>(forthDirectRoute - '0');
            char forthDirect = static_cast<char>('0' + curLoc.level);
            containerStruct prevStruct(
                level,
                curLoc.row,
                curLoc.col
            );
            // update curLoc to previous location
            curLoc = prevStruct;
            // change character to the output level
            map3D[curLoc.level][curLoc.row][curLoc.col].character = 
                forthDirect;
        }
        routeEscape.push_back(curLoc);
    }
}

void shipClass::run(){
    read_file();
    while (!
        (doFindSolution)
    ){
        iterateCurLoc();
        investigateAndDiscover();
        if (searchContainer.empty()){
            break;
        }
    }
    output_file();
}