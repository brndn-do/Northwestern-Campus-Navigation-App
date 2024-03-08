/*busstop.h*/

//
// A bus stop in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 

#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "curl_util.h"

#include "json.hpp"
using json = nlohmann::json;

using namespace std;

//
// BusStop
//
// Defines a bus stop with an ID, route (e.g. 201),
// name, direction, location, latitude, and longitude
//
class BusStop
{
public:
    long long ID;
    int Route;
    string Name;
    string Direction;
    string Location;
    double Latitude;
    double Longitude;

    //
    // constructor
    //
    BusStop(long long id, int route, string name, string dir, string loc, double lat, double lon);

    //
    // print
    //

    void print() const;

    void printWithDist(const double& dist) const;

    //
    // printBusPredictions
    //
    // prints bus predictions for a bus stop
    //
    void printBusPredictions(CURL* curl, const string& url) const;
};