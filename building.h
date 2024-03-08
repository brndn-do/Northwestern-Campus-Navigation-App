/*building.h*/

//
// A building in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 
// Starter code: Prof. Joe Hummel
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <utility>

#include "dist.h"
#include "node.h"
#include "nodes.h"
#include "footway.h"
#include "footways.h"
#include "busstop.h"
#include "busstops.h"
#include "curl_util.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  // 
  // print
  //
  // prints a building and its ID, address, # perimeter nodes, location, closest bus stops, and predicitons for each bus stop
  //
  void print(const BusStops& busstops, const Nodes& nodes, const Footways& footways, CURL* curl) const;

  //
  // getLocation
  //
  // gets the center (lat, lon) of the building based
  // on the nodes that form the perimeter
  //
  pair<double, double> getLocation(const Nodes &nodes) const;

  //
  // getClosestBusStops
  //
  // returns a pair of the closest southbound and northbound bus stops to the building
  // also updates distS and distN to the closest distance to each bus stop from the building
  //
  pair<BusStop, BusStop> getClosestBusStops(const BusStops& busstops, const Nodes& nodes, double& distS, double& distN) const;

};
