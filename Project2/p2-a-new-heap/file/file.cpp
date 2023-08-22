#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include "P2random.h"
using namespace std;

// int main(){
//     // uint32_t n;
//     // string a;
//     // string b;
//     // vector<string> vec;
//     // cin >> n;
//     // vec.reserve(n);
//     // getline(cin, a);
//     // vec.push_back(a);
//     // cout << vec.capacity() << '\n';
//     // // cin >> b;
//     // getline(cin, b);
//     // cout << vec.capacity() << '\n';
//     // vec.push_back(b);
//     // cout << vec.capacity() << '\n';
//     // getline(cin, b);
//     // vec.push_back(b);
//     // cout << vec.capacity() << '\n';

//     // lab 3 Jan 24
//     // char str1 [] = "B ING";
//     // char x;
//     // x = str1[1];
//     // cout << x << '\n';
//     // return 0;
//     // char a = '\0';
//     // cout << (int)a;
//     // string b = "a\n";
//     // cout << b.length() << endl;
    
// }
// class MyClass
// {
//     public:
//         int data;

//         // version with the "&" before operator=
//         MyClass& operator=(const MyClass& other)
//         {
//             data = other.data;
//             cout << "Assignment with &: data set to " << data << endl;
//             return *this;
//         }

//         // version without the "&" before operator=
//         // MyClass operator=(const MyClass& other)
//         // {
//         //     data = other.data;
//         //     cout << "Assignment without &: data set to " << data << endl;
//         //     return *this;
//         // }
// };

// int main()
// {
//     MyClass obj1, obj2, obj3;
//     obj1.data = 5;
//     obj2.data = 10;
//     obj3.data = 15;
//     // using the version with the "&" before operator=
//     obj1 = obj2; // Assignment with &: data set to 10
//     cout << obj1.data << endl; // 10
//     cout << obj2.data << endl; // 10
//     obj2 = obj3;
//     cout << obj1.data << endl;
//     cout << obj2.data << endl;
//     cout << obj3.data << endl;

//     // using the version without the "&" before operator=
//     // obj1 = obj2; // Assignment without &: data set to 10
//     // cout << obj1.data << endl; // 5
//     // cout << obj2.data << endl; // 10
//     return 0;
// }

// int& getValue() {
//     static int value = 5; // 全局variable，所以不会destory
//     return value;
// }
int main() {
    stringstream ss;
    uint32_t seed = 29;
    uint32_t numDeployment = 30;
    uint32_t arrivalRate = 3;
    uint32_t numGeneral = 100; 
    uint32_t numPlanet = 2;
    ss << "COMMENT: random."<< seed <<"\n";
    ss << "MODE: DL\n";
    ss << "NUM_GENERALS: " << numGeneral << "\n";
    ss << "NUM_PLANETS: " << numPlanet << "\n";
    P2random::PR_init(
        ss, 
        seed, 
        numGeneral, 
        numPlanet, 
        numDeployment, 
        arrivalRate
    );
    ofstream file;
    file.open("test-9-v.txt");
    file << ss.str();
    file.close();
    
}
