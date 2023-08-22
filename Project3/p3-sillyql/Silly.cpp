// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <iostream>
#include <string>
#include "TableEntry.h"
#include "Table.h"
#include "DataBase.h"
// using namespace std;

int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;
    string cmd;
    char firstCmd;
    string junk;
    DataBase dataBase;
    string command;
    

    if (argc > 1){
        command = argv[1];
        // if (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "--quiet") == 0){
        if (command == "-q" || command == "--quiet"){
            dataBase.beQuiet();
        }
        else if (command == "-h" || command == "--help"){
            cout << "help info\n";
            exit(0);
    }
    }

    do {
        cout << "% ";
        cin >> cmd;
        firstCmd = cmd[0];
        switch(firstCmd){
            case 'C':
                dataBase.create();
                break;
            case '#':
                dataBase.comment();
                break;
            case 'R':
                dataBase.remove();
                break;
            case 'I':
                dataBase.insert();
                break;
            case 'P':
                dataBase.print();
                break;
            case 'D':
                dataBase.delet();
                break;
            case 'G':
                dataBase.generate();
                break;
            case 'J':
                dataBase.join();
                break;
            case 'Q':
                break;
            default:
                getline(cin, junk);
                cout << "Error: unrecognized command\n";
                break;
        }
    } while (firstCmd != 'Q');
    cout << "Thanks for being silly!\n";
}