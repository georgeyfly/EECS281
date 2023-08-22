// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef TABLE_H_
#define TABLE_H_

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "TableEntry.h"
using namespace std;

class Table{
    private:
        vector< vector<TableEntry> > data;
        // vector<string> colNameVec;
        vector<EntryType> colTypeVec;
        unordered_map<string, size_t> indexOfColName;
        string name;

        unordered_map<TableEntry, vector<size_t> > hashIdx;
        map<TableEntry, vector<size_t> > bstIdx;
        // bool doGenerateIndex;
        size_t indexOfCol;
        string indexType;
    public:
        //constructor
        // numCol needed? indexOfCol?
        Table():
                name{""}, 
                indexOfCol{SIZE_MAX}, 
                indexType{"null"}
        {};
        void create(string &tableName);
        void insert();
        void print(bool doQuiet);
        size_t printBST(
            bool doQuiet,
            char operation, 
            const TableEntry& a, 
            vector<size_t>& printColIndexVec);
        size_t printHASH( 
            bool doQuiet,
            const TableEntry& a, 
            vector<size_t>& printColIndexVec);
        size_t printWHERE(
            bool doQuiet,
            char operation, 
            const TableEntry& a, 
            size_t index, 
            vector<size_t>& printColIndexVec);
        void delet();
        void generate();
        void regenerate();
        void join(Table& aTable, bool doQuiet);
        bool isColNameInCol(string &colName){
            return indexOfColName.count(colName);
        };
};


#endif