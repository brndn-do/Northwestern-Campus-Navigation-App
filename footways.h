/*footways.h*/

//
// A collection of footways in the Open Street Map.
//
// Brandon Do
// Northwestern University
// CS 211
// 


#pragma once

#include <vector>
#include <iostream>

#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the footways in the map.
//
class Footways
{
public:
    vector<Footway> MapFootways;

    //
    // readMapFootways
    //
    // Given an XML document, reads through the document and
    // stores all the buildings into the given vector.
    //
    void readMapFootways(XMLDocument& xmldoc);

    //
    // accessors / getters
    //
    int getNumMapFootways() const;
};