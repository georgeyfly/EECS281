// Project identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
// Programmer: Qiaozhi Huang
// Date: Feb 2023
// Purpose: implement constants value for for EECS403 Project2.
#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include <iostream>
#include <string>
using namespace std;

const string PSEUDO_RAND = "PR";
const string DEPLOY_LIST = "DL";

const uint32_t RANDOM_SEED_INDEX = 13;
const uint32_t NUM_DEPLOYMENTS_INDEX = 17;
const uint32_t ARRIVAL_RATE_INDEX = 14;

const string JEDI = "JEDI";
const string SITH = "SITH";

static uint32_t nextID = 0;

const uint32_t SIZE_UNEQUAL = 2;
const uint32_t SIZE_EQUAL_NO_MEAN = 1;
#endif