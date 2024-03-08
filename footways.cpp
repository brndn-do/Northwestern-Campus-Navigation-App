/*footways.cpp*/

//
// A collection of footways in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "footways.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// readMapFootways
//
// Given an XML document, reads through the document and
// stores all the footways into the given vector.
//
void Footways::readMapFootways(XMLDocument& xmldoc)
{
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);

    //
    // Parse the XML document footway by footway:
    //
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr)
    {
        if (osmContainsKeyValue(way, "highway", "footway") || 
            osmContainsKeyValue(way, "area:highway", "footway")) {
            const XMLAttribute* wayid = way->FindAttribute("id");
            assert(wayid != nullptr);

            long long id = wayid->Int64Value();

            // Create Footway instance
            Footway F(id);

            XMLElement* nd = way->FirstChildElement("nd");

            while (nd!= nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long id = ndref->Int64Value();

                F.add(id);

                // advance to next node ref:
                nd = nd->NextSiblingElement("nd");
            } // while

            //
            // Add footway to vector:
            //
            //
            MapFootways.push_back(F);

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

int Footways::getNumMapFootways() const
{
    return MapFootways.size();
}