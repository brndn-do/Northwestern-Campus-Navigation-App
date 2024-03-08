/*main.cpp*/

//
// Main program for Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 
// Starter code: Prof. Joe Hummel
//

#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "busstop.h"
#include "busstops.h"
#include "curl_util.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

//
// interactive_loop
//
// Given referencees to Nodes and Buildings objects,
// Repeatedly prompts user for command and executes it
// if input is $, ends loop
// if input is *, outputs each building in Buildings
// else, searches buildings that contains input,
// outputs each building and its nodes 
static void interactive_loop(const Nodes& nodes, const Buildings& buildings, const BusStops& busstops, const Footways& footways, CURL* curl) {
    while (true) {
        //prompt user and get input
        cout << endl << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;
        string userInput;
        getline(cin, userInput);

        if (userInput == "$") {
            break;
        }
        else if (userInput == "*") {
            // print buildings
            buildings.print();
        }
        else if (userInput == "@") {
            // print bus stops
            busstops.print();
        }
        else {
            // search buildings
            buildings.findAndPrint(busstops, nodes, footways, userInput, curl);
        }
    }
}

int main() {

    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        cout << "**ERROR:" << endl;
        cout << "**ERROR: unable to initialize curl library" << endl;
        cout << "**ERROR:" << endl;
        return 0;
    }

    XMLDocument doc;
    string filename;
    cout << "** NU open street map **" << endl << endl;
    cout << "Enter map filename> " << endl;
    getline(cin, filename);
    
    if (!osmLoadMapFile(filename, doc)) {
        // unsuccessful
        cout << "Error: unable to load file" << endl;
        return 0;
    }

    // print # of nodes
    Nodes nodes;
    nodes.readMapNodes(doc);
    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;

    // print # of buildings
    Buildings buildings;
    buildings.readMapBuildings(doc);
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
    
    // print # of footways
    Footways footways;
    footways.readMapFootways(doc);
    // cout << "# of footways: " << footways.getNumMapFootways() << endl;

    // print # of bus stops
    BusStops busstops("bus-stops.txt");
    cout << "# of bus stops: " << busstops.getNumMapBusStops() << endl;

    // call interative_loop
    interactive_loop(nodes, buildings, busstops, footways, curl);

    // done
    curl_easy_cleanup(curl);

    cout << endl;
    cout << "** Done **" << endl;

    return 0;
}