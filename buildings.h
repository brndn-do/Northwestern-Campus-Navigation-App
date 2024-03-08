/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
//
// Brandon Do
// Northwestern University
// CS 211
// 
// Starter code: Prof. Joe Hummel
//

#pragma once

#include <vector>
#include <iostream>

#include "building.h"
#include "curl_util.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
    vector<Building> MapBuildings;

    //
    // readMapBuildings
    //
    // Given an XML document, reads through the document and
    // stores all the buildings into the given vector.
    //
    void readMapBuildings(XMLDocument& xmldoc);

    //
    // accessors / getters
    //
    int getNumMapBuildings() const;

    //
    // print
    //
    // prints all buildings
    //
    void print() const;

    //
    // findAndPrint
    //
    // searches and prints any buildings that
    // contain the user input in its name
    //
    void findAndPrint(const BusStops& busstops, const Nodes& nodes, const Footways& footways, const string& userInput, CURL* curl) const;
};