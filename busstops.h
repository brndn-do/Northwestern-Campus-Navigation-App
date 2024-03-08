/*busstops.h*/

//
// A collection of bus stops in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 

#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "busstop.h"

using namespace std;

//
// Keeps track of all the bus stops in the map.
//
class BusStops
{
public:
    vector<BusStop> MapBusStops;

    //
    // constructor
    //
    BusStops(const string& filename);

    //
    // accessors / getters
    //
    int getNumMapBusStops() const;

    //
    // print
    //
    void print() const;
};