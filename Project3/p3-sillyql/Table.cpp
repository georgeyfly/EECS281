// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
#include <algorithm>
#include "Table.h"
using namespace std;

// overload >> to read EntryType
istream& operator>>(istream& is, EntryType& type){
    string strType;
    is >> strType;
    char aChar = strType[0];

    if (aChar == 's'){
        type = EntryType::String;
    }
    else if (aChar == 'd'){
        type = EntryType::Double;
    }
    else if (aChar == 'i'){
        type = EntryType::Int;
    }
    else{
        type = EntryType::Bool;
    }
    return is;
}

// functor
class Comparator{
    private:
        char operation;
        TableEntry value;
        size_t index;
    public:
        Comparator(char aChar, const TableEntry &a, size_t idx): 
        operation{aChar}, value{a}, index{idx}
        {
        };
        // bool operator()(const TableEntry& a, const TableEntry& b) const{
        //     switch(operation){
        //         case '=':
        //             return a == b;
        //         case '>':
        //             return a > b;
        //         case '<':
        //             return a < b;
        //     }
        //     return false;
        // }
        // bool operator()(const TableEntry& a) const{
        //     switch(operation){
        //         case '=':
        //             return a == value;
        //         case '>':
        //             return a > value;
        //         case '<':
        //             return a < value;
        //     }
        //     return false;
        // }
        bool operator()(const vector<TableEntry>& a) const{
            switch(operation){
                case '=':
                    return a[index] == value;
                case '>':
                    return a[index] > value;
                case '<':
                    return a[index] < value;
            }
            return false;
        }
};

class BstComparator{
    public:
        // BstComparator(){};
        bool operator()(
            const TableEntry &a, 
            const pair<TableEntry, vector<size_t> > &pair
            ){
            if (a < pair.first){
                return true;
            }
            return false;
        }
        // bool operator()(
        //     const map<TableEntry, vector<size_t> >::iterator it1,
        //     const map<TableEntry, vector<size_t> >::iterator it2
        //     ){
        //     if (it1 ->first < it2 -> first){
        //         return true;
        //     }
        //     return false;
        // }
};

void Table::insert(){
    string junk;
    size_t numRow;

    string aString;
    int aInt;
    double aDouble;
    bool aBool;

    cin >> numRow >> junk;
    size_t prevNumRow = data.size();
    data.resize(data.size() + numRow);

    for (size_t i = prevNumRow; i < data.size(); ++i){
        data[i].reserve(colTypeVec.size());
        for (auto j:colTypeVec){
            switch(j){
                case(EntryType::String):
                    cin >> aString;
                    data[i].emplace_back(aString);
                    break;
                case(EntryType::Int):
                    cin >> aInt;
                    data[i].emplace_back(aInt);
                    break;
                case(EntryType::Double):
                    cin >> aDouble;
                    data[i].emplace_back(aDouble);
                    break;
                case(EntryType::Bool):
                    cin >> aBool;
                    data[i].emplace_back(aBool);
                    break;
            }
        }
    }
    cout << "Added " << numRow << " rows to " << name << " from position "
         << prevNumRow << " to " << prevNumRow + numRow - 1 << '\n';
    // update indices
    if (indexOfCol != SIZE_MAX){
        if (indexType == "bst"){
            for (size_t i = prevNumRow; i < prevNumRow + numRow; ++i){
                bstIdx[data[i][indexOfCol]].push_back(i);
            }
        }
        else{
            for (size_t i = prevNumRow; i < prevNumRow + numRow; ++i){
                hashIdx[data[i][indexOfCol]].push_back(i);
            }
        }
    }
}

void Table::create(string &tableName){
    size_t numCol;
    EntryType colType;
    string colName;
    size_t index = 0;
    

    name = tableName;
    cin >> numCol;
    colTypeVec.reserve(numCol);
    vector<string> colNameVec; // improve
    colNameVec.reserve(numCol); 
    for (size_t i = 0; i < numCol; ++i){
        cin >> colType;
        colTypeVec.push_back(colType);
    }
    for (size_t j = 0; j < numCol; ++j){
        cin >> colName;
        colNameVec.push_back(colName);
        indexOfColName[colName] = index++;
    }
    cout << "New table " << tableName << " with column(s) ";
    for (auto i:colNameVec){ 
    // for (auto i:indexOfColName){
        cout << i << ' ';
    }
    cout << "created\n";
}

void Table::print(bool doQuiet){
    size_t numCol;
    string colName;
    string conditionString;
    char conditionChar;

    cin >> numCol;
    vector<size_t> printColIndexVec;
    printColIndexVec.reserve(numCol);
    // improve
    vector<string> printColNameVec;
    printColNameVec.reserve(numCol);
    for (size_t i = 0; i < numCol; ++i){
        cin >> colName;
        auto it = indexOfColName.find(colName);
        if (it != indexOfColName.end()){
            printColIndexVec.push_back(it -> second);
            printColNameVec.push_back(colName);
        }
        else{
            cout << "Error during " << "PRINT" << ": " << colName 
                 << " does not name a column in " << name << '\n';
            string junk;
            getline(cin, junk);
            return;
        }
    }
    // sort printColIndexVec to make print in insert order
    // sort(printColIndexVec.begin(), printColIndexVec.end(), less<size_t>());
    cin >> conditionString;
    conditionChar = conditionString[0];
    // print All
    if (conditionChar == 'A'){
        // print colnum name need to be printed
        if (!doQuiet){
            // for (auto k:printColIndexVec){ //improve
            //     cout << colNameVec[k] << ' ';
            for (auto i:printColNameVec){
                cout << i << ' '; // improve
            }
            cout << '\n';
            for (size_t i = 0; i < data.size(); ++i){
                for (auto j:printColIndexVec){
                    cout << data[i][j] << ' ';
                }
                cout << '\n';
            }
        }
        cout << "Printed " << data.size() << " matching rows from " << name 
             << '\n';
    }
    // print where
    else{
        char operation;
        EntryType type;
        size_t index;
        cin >> colName >> operation;
        // count rows printed
        size_t count = 0;
        auto it = indexOfColName.find(colName);
        if (it != indexOfColName.end()){
            index = it -> second;
            type = colTypeVec[index];
            // print colnum name need to be printed
            if (!doQuiet){
                // for (auto k:printColIndexVec){ //improve
                //     cout << colNameVec[k] << ' ';
                for (auto i:printColNameVec){ //improve
                    cout << i << ' ';
                }
                cout << '\n';
            }
            switch(type){
                case(EntryType::String):{
                    string aVal;
                    cin >> aVal;
                    if (index == indexOfCol && indexType == "bst"){
                        count = printBST(
                            doQuiet,
                            operation, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else if (
                        index == indexOfCol && 
                        indexType == "hash" && 
                        operation == '='
                        ){
                        count = printHASH(
                            doQuiet, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else{
                        count = printWHERE(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            index, 
                            printColIndexVec
                        );
                    }
                    // printwhere
                    // // declare functor
                    // Comparator compare(operation, TableEntry(aVal), index);
                    // for (size_t i = 0; i < data.size(); ++i){
                    //     if (compare(data[i])){
                    //         for (auto j:printColIndexVec){
                    //             cout << data[i][j] << ' ';
                    //         }
                    //         ++count;
                    //         cout << '\n';
                    //     }
                    // }
                    break;
                }
                case(EntryType::Int):{
                    int aVal;
                    cin >> aVal;
                    if (index == indexOfCol && indexType == "bst"){
                        count = printBST(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else if (
                        index == indexOfCol && 
                        indexType == "hash" && 
                        operation == '='
                        ){
                        count = printHASH( 
                            doQuiet, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else{
                        count = printWHERE(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            index, 
                            printColIndexVec
                        );
                    }
                    // // declare functor
                    // Comparator compare(operation, TableEntry(aVal), index);
                    // for (size_t i = 0; i < data.size(); ++i){
                    //     if (compare(data[i])){
                    //         for (auto j:printColIndexVec){
                    //             cout << data[i][j] << ' ';
                    //         }
                    //         ++count;
                    //         cout << '\n';
                    //     }
                    // }
                    break;
                }
                case(EntryType::Double):{
                    double aVal;
                    cin >> aVal;
                    if (index == indexOfCol && indexType == "bst"){
                        count = printBST(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal),                
                            printColIndexVec
                        );
                    }
                    else if (
                        index == indexOfCol && 
                        indexType == "hash" && 
                        operation == '='
                        ){
                        count = printHASH(
                            doQuiet, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else{
                        count = printWHERE(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            index, 
                            printColIndexVec
                        );
                    }
                    // // declare functor
                    // Comparator compare(operation, TableEntry(aVal), index);
                    // for (size_t i = 0; i < data.size(); ++i){
                    //     if (compare(data[i])){
                    //         for (auto j:printColIndexVec){
                    //             cout << data[i][j] << ' ';
                    //         }
                    //         ++count;
                    //         cout << '\n';
                    //     }
                    // }
                    break;
                }
                case(EntryType::Bool):{
                    bool aVal;
                    cin >> aVal;
                    if (index == indexOfCol && indexType == "bst"){
                        count = printBST(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else if (
                        index == indexOfCol && 
                        indexType == "hash" && 
                        operation == '='
                        ){
                        count = printHASH(
                            doQuiet, 
                            TableEntry(aVal), 
                            printColIndexVec
                        );
                    }
                    else{
                        count = printWHERE(
                            doQuiet, 
                            operation, 
                            TableEntry(aVal), 
                            index, 
                            printColIndexVec
                        );
                    }
                    // // declare functor
                    // Comparator compare(operation, TableEntry(aVal), index);
                    // for (size_t i = 0; i < data.size(); ++i){
                    //     if (compare(data[i])){
                    //         for (auto j:printColIndexVec){
                    //             cout << data[i][j] << ' ';
                    //         }
                    //         ++count;
                    //         cout << '\n';
                    //     }
                    // }
                    break;
                }
            }
            cout << "Printed " << count << " matching rows from " << name 
                 << '\n';
        }
        else{
            cout << "Error during " << "PRINT" << ": " << colName 
                 << " does not name a column in " << name << '\n';
            string junk;
            getline(cin, junk);
            return;
        }
    }
}

size_t Table::printBST(
    bool doQuiet, 
    char operation, 
    const TableEntry& a,  
    vector<size_t>& printColIndexVec
){
    size_t count = 0;
    if (operation == '='){
        auto it = bstIdx.find(a);
        if (it != bstIdx.end()){
            for (size_t rowIdx:it -> second){
                if (!doQuiet){
                    for (size_t colIdx:printColIndexVec){
                        cout << data[rowIdx][colIdx] << ' ';
                    }
                    cout << '\n';
                }
                ++count;
            }
        }
    }
    else if (operation == '<'){
        auto it = bstIdx.lower_bound(a);
        if (it != bstIdx.begin()){
            // for (auto i:bstIdx){
            for (auto i = bstIdx.begin(); i != it; ++i){
                for (size_t rowIdx:i -> second){
                    if (!doQuiet){
                        for (size_t colIdx:printColIndexVec){
                            cout << data[rowIdx][colIdx] << ' ';
                        }
                        cout << '\n';
                    }
                    ++count;
                } 
            }
                // if (i.first < a){
                //     for (size_t rowIdx:i.second){
                //         if (!doQuiet){
                //             for (size_t colIdx:printColIndexVec){
                //                 cout << data[rowIdx][colIdx] << ' ';
                //             }
                //             cout << '\n';
                //         }
                //         ++count;
                //     }
                // }
                // else { //improve
                //     break;
                // }
            // }
        }
    }
    else{
        // auto it = upper_bound(bstIdx.begin(), bstIdx.end(), a, BstComparator());
        auto it = bstIdx.upper_bound(a);
        if (it != bstIdx.end()){
            for (auto i = it; i != bstIdx.end(); ++i){
                for (size_t rowIdx:i -> second){
                    if (!doQuiet){
                        for (size_t colIdx:printColIndexVec){
                            cout << data[rowIdx][colIdx] << ' ';
                        }
                        cout << '\n';
                    }
                    ++count;
                } 
            }
        }
    }
    return count;
}

size_t Table::printHASH(
    bool doQuiet, 
    const TableEntry& a, 
    vector<size_t>& printColIndexVec
){
    size_t count = 0;
    auto it = hashIdx.find(a);
    if (it != hashIdx.end()){
        for (auto i:it -> second){
            if (!doQuiet){
                for (auto j:printColIndexVec){
                    cout << data[i][j] << ' ';
                }
                cout << '\n';
            }
            ++count;
        }
    }
    return count;
}

size_t Table::printWHERE(
    bool doQuiet, 
    char operation, 
    const TableEntry& a, 
    size_t index, 
    vector<size_t>& printColIndexVec
){
    // // declare functor
    Comparator compare(operation, a, index);
    size_t count = 0;
    for (size_t i = 0; i < data.size(); ++i){
        if (compare(data[i])){
            if (!doQuiet){
                for (auto j:printColIndexVec){
                    cout << data[i][j] << ' ';
                }
                cout << '\n';
            }
            ++count;
        }
    }
    return count;
}

void Table::delet(){
    string junk;
    char operation;
    EntryType type;
    size_t index;
    string colName;
    cin >> junk >> colName >> operation;
    // declare 4 EntryType
    string aString;
    int aInt;
    double aDouble;
    bool aBool;
    // prev vecotr size
    size_t prevDataSize = data.size();

    auto it = indexOfColName.find(colName);
    if (it != indexOfColName.end()){
        index = it -> second;
        type = colTypeVec[index];
        switch(type){
            case(EntryType::String):{
                cin >> aString;
                // declare functor
                Comparator compare(operation, TableEntry(aString), index);
                data.erase(
                    remove_if(data.begin(), data.end(), compare), 
                    data.end()
                );
                break;
            }
            case(EntryType::Int):{
                cin >> aInt;
                // declare functor
                Comparator compare(operation, TableEntry(aInt), index);
                data.erase(
                    remove_if(data.begin(), data.end(), compare), 
                    data.end()
                );
                break;
            }
            case(EntryType::Double):{
                cin >> aDouble;
                // declare functor
                Comparator compare(operation, TableEntry(aDouble), index);
                data.erase(
                    remove_if(data.begin(), data.end(), compare), 
                    data.end()
                );
                break;
            }
            case(EntryType::Bool):{
                cin >> aBool;
                // declare functor
                Comparator compare(operation, TableEntry(aBool), index);
                data.erase(
                    remove_if(data.begin(), data.end(), compare), 
                    data.end()
                );
                break;
            }
        }
        cout << "Deleted " << prevDataSize - data.size() << " rows from " 
                << name << '\n';
        if (indexOfCol != SIZE_MAX){
            regenerate();
        }
    }
    else{
        cout << "Error during " << "DELETE" << ": " << colName 
             << " does not name a column in " << name << '\n';
        string junk;
        getline(cin, junk);
    }
    
}

void Table::generate(){
    string junk;
    string colName;
    string type;
    cin >> type >> junk >> junk >> colName;
    auto it = indexOfColName.find(colName);
    if (it != indexOfColName.end()){
        size_t index = it -> second;
        // clear all the idx if type not equal to previous type
        if (type != indexType || index != indexOfCol){
            hashIdx.clear();
            bstIdx.clear();
            indexType = type;
            indexOfCol = index;
            if (type == "hash"){
                // // check if idx of same column has generate
                // if (index != indexOfCol){
                // hashIdx.clear();
                for (size_t i = 0; i < data.size(); ++i){
                    hashIdx[data[i][index]].push_back(i);
                }
                // }
            }
            else{
                // check if idx of same column has generate
                // if (index != indexOfCol){
                //     bstIdx.clear();
                for (size_t i = 0; i < data.size(); ++i){
                    bstIdx[data[i][index]].push_back(i);
                }
                // }
            }
        }
        cout << "Created " << indexType << " index for table " << name 
             << " on column " << colName << '\n';
    }
    else{
        cout << "Error during " << "GENERATE" << ": " << colName 
             << " does not name a column in " << name << '\n';
        string junk;
        getline(cin, junk);
    }
}

void Table::regenerate(){
    if (indexType == "hash"){
        hashIdx.clear();
        for (size_t i = 0; i < data.size(); ++i){
            hashIdx[data[i][indexOfCol]].push_back(i);
        }
    }
    else{
        bstIdx.clear();
        for (size_t i = 0; i < data.size(); ++i){
            bstIdx[data[i][indexOfCol]].push_back(i);
        }
    }
}

void Table::join(Table& aTable, bool doQuiet){
    vector<string> printColNameVec;
    vector<size_t> printTableVec;
    vector<size_t> printIndexVec;
    size_t numCol, index;
    string junk, colName1, colName2, colName;
    char operation;
    size_t count = 0;
    // read cin and push colname to vec
    cin >> junk >> colName1 >> operation;
    if (isColNameInCol(colName1)){
        cin >> colName2;
        if (aTable.isColNameInCol(colName2)){
            cin >> junk >> junk >> numCol;
            for (size_t i = 0; i < numCol; ++i){
                cin >> colName;
                cin >> index;
                if (index == 1){
                    auto it = indexOfColName.find(colName);
                    if (it != indexOfColName.end()){
                        printColNameVec.push_back(colName);
                        printTableVec.push_back(index);
                        printIndexVec.push_back(it -> second);
                    }
                    else{
                        cout << "Error during " << "JOIN" << ": " << colName 
                             << " does not name a column in " 
                             << name << '\n';
                        getline(cin, junk);
                        return;
                    }
                }
                else{
                    auto it = aTable.indexOfColName.find(colName);
                    if (it != aTable.indexOfColName.end()){
                        printColNameVec.push_back(colName);
                        printTableVec.push_back(index);
                        printIndexVec.push_back(it -> second);
                    }
                    else{
                        cout << "Error during " << "JOIN" << ": " << colName 
                             << " does not name a column in " 
                             << aTable.name << '\n';
                        getline(cin, junk);
                        return;
                    }
                }
            }
        }
        else{
            cout << "Error during " << "JOIN" << ": " << colName2 
                 << " does not name a column in " << aTable.name << '\n';
            getline(cin, junk);
            return;
        }
    }
    else{
        cout << "Error during " << "JOIN" << ": " << colName1 
             << " does not name a column in " << name << '\n';
        getline(cin, junk);
        return;
    }
    // address vec and print

    // print colName
    if (!doQuiet){
        for (size_t i = 0; i < printColNameVec.size(); ++i){
            cout << printColNameVec[i] << ' ';
        }
    cout << '\n';
    }
    // create idx for table2 on colName2
    unordered_map<TableEntry, vector<size_t> > tempHashIdx;
    size_t index1 = indexOfColName[colName1];
    size_t index2 = aTable.indexOfColName[colName2];
    for (size_t i = 0; i < aTable.data.size(); ++i){
        tempHashIdx[aTable.data[i][index2]].push_back(i);
    }
    // print join
    // iterate every row in table1
    for (size_t i = 0; i < data.size(); ++i){
        auto it = tempHashIdx.find(data[i][index1]);
        // iterate every row found in table2
        if (it != tempHashIdx.end()){
            for (size_t idx:it -> second){
                // iterate number of columns to be printed
                if (!doQuiet){
                    for (size_t j = 0; j < printIndexVec.size(); ++j){
                        if (printTableVec[j] == 1){
                            cout << data[i][printIndexVec[j]] << ' ';
                        }
                        else{
                            cout << aTable.data[idx][printIndexVec[j]] << ' ';
                        }
                    }
                    cout << '\n';
                }
                ++count;
            }
        }
    }
    cout << "Printed " << count << " rows from joining " << name 
         << " to " << aTable.name << '\n';
}
