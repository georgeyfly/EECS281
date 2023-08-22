// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef DATABASE_H_
#define DATABASE_H_
#include <iostream>
#include <string>
#include <unordered_map>
#include "Table.h"

using namespace std;

class DataBase{
    private:
        unordered_map<string, Table> allTable;
        bool doQuiet;
    public:
        DataBase(): doQuiet{false}{};
        void beQuiet(){
            doQuiet = true;
        };
        void create();
        void comment();
        void remove();
        void insert();
        void print();
        void delet();
        void generate();
        void join();
};

#endif