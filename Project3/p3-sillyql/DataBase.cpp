// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
#include "DataBase.h"

using namespace std;

void DataBase::create(){
    string tableName;
    cin >> tableName;
    auto it = allTable.find(tableName);
    if (it == allTable.end()){
        allTable[tableName].create(tableName);
    }
    else {
        cout << "Error during " << "CREATE" 
             << ": Cannot create already existing table "<< tableName << '\n';
        string junk;
        getline(cin, junk);
    }
}

void DataBase::comment(){
    string comment;
    getline(cin, comment);
}

void DataBase::remove(){
    string tableName;
    cin >> tableName;
    auto it = allTable.find(tableName);
    if (it != allTable.end()){
        allTable.erase(it);
        cout << "Table " << tableName << " deleted" << '\n';
    }
    else{
        cout << "Error during " << "REMOVE: " << tableName 
             << " does not name a table in the database\n";
        string junk;
        getline(cin, junk);
    }
}

void DataBase::insert(){
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto it = allTable.find(tableName);
    if (it != allTable.end()){
        (it -> second).insert();
    }
    else{
        cout << "Error during " << "INSERT: " << tableName 
             << " does not name a table in the database\n";
        // size_t numCol;
        // cin >> numCol >> junk;
        getline(cin, junk);
        // for (size_t i = 0; i < numCol; ++i){
        //     getline(cin, junk);
        // }
    }
}

void DataBase::print(){
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto it = allTable.find(tableName);
    if (it != allTable.end()){
        (it -> second).print(doQuiet);
    }
    else{
        cout << "Error during " << "PRINT: " << tableName 
             << " does not name a table in the database\n";
        getline(cin, junk);
    }

}

void DataBase::delet(){
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto it = allTable.find(tableName);
    if (it != allTable.end()){
        (it -> second).delet();
    }
    else{
        cout << "Error during " << "DELETE: " << tableName 
             << " does not name a table in the database\n";
        getline(cin, junk);
    }
}

void DataBase::generate(){
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto it = allTable.find(tableName);
    if (it != allTable.end()){
        (it -> second).generate();
    }
    else{
        cout << "Error during " << "GENERATE: " << tableName 
             << " does not name a table in the database\n";
        getline(cin, junk);
    }
}

void DataBase::join(){
    string junk;
    string tableName;
    cin >> tableName >> junk;
    auto itFirst = allTable.find(tableName);
    if (itFirst == allTable.end()){
        cout << "Error during " << "JOIN: " << tableName 
             << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }

    cin >> tableName;
    auto itSecond = allTable.find(tableName);
    if (itSecond != allTable.end()){
        (itFirst -> second).join(itSecond -> second, doQuiet);
    }
    else{
        cout << "Error during " << "JOIN: " << tableName 
             << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
}