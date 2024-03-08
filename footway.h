/*footway.h*/

//
// A footway in the Open Street Map.
//
// Brandon Do
// Northwestern University
// CS 211
// 


#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

#include "node.h"
#include "nodes.h"

using namespace std;

//
// Footway
//
class Footway
{
public:
    long long ID;
    set<long long> NodeIDs;

    //
    // Constructor
    //
    Footway(long long id);

    //
    // adds the given nodeid to the end of the vector.
    //
    void add(long long nodeid);
};