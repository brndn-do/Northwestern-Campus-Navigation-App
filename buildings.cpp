/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
//
// Brandon Do
// Northwestern University
// CS 211
// 
// Starter code: Prof. Joe Hummel
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "buildings.h"
#include "footways.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// readMapBuildings
//
// Given an XML document, reads through the document and
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);

    //
    // Parse the XML document building by building:
    //
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr)
    {
        if (osmContainsKeyValue(way, "building", "university")) {
            const XMLAttribute* wayid = way->FindAttribute("id");
            assert(wayid != nullptr);

            long long id = wayid->Int64Value();
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber")
                + " "
                + osmGetKeyValue(way, "addr:street");

            // Create Building instance
            Building B(id, name, streetAddr);

            XMLElement* nd = way->FirstChildElement("nd");

            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long id = ndref->Int64Value();

                B.add(id);

                // advance to next node ref:
                nd = nd->NextSiblingElement("nd");
            } // while

            //
            // Add building to vector:
            //
            //
            MapBuildings.push_back(B);

        } // if

    //
    // next way element
    //
    way = way->NextSiblingElement("way");
    }
}

//
// accessors / getters
//

int Buildings::getNumMapBuildings() const
{
    return MapBuildings.size();
}

//
// print
//
// prints all buildings
//

void Buildings::print() const
{
    for (const auto& b: MapBuildings) {
        cout << b.ID << ": " << b.Name << ", " << b.StreetAddress << endl;
    }
}

//
// findAndPrint
//
// searches and prints any buildings that
// contain the user input in its name
//
void Buildings::findAndPrint(const BusStops& busstops, const Nodes& nodes, const Footways& footways, const string& userInput, CURL* curl) const
{
    bool found = false;
    for (const auto& b: MapBuildings) {
        if (b.Name.find(userInput) != string::npos) {
            // found!
            b.print(busstops, nodes, footways, curl);
            found = true;
        }
    }
    if (!found) {
        cout << "No such building" << endl;
    }
}