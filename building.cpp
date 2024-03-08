/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 
// Starter code: Prof. Joe Hummel
//

#include "building.h"
#include "curl_util.h"
#include "footways.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{

}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

// 
// print
//
// prints a building and its ID, address, # perimeter nodes, location, closest bus stops, and predicitons for each bus stop
//
void Building::print(const BusStops& busstops, const Nodes& nodes, const Footways& footways, CURL* curl) const
{
  cout << Name << endl;
  cout << "Address: " << StreetAddress << endl;
  cout << "Building ID: " << ID << endl;
  cout << "# perimeter nodes: " << NodeIDs.size() << endl;

  //
  // print location
  //
  pair<double, double> location;
  location = this->getLocation(nodes);
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;

  //
  // print closest bus stops
  //
  double distS = 0;
  double distN = 0;
  pair<BusStop, BusStop> closest = this->getClosestBusStops(busstops, nodes, distS, distN);

  // string-based URLs
  string first_url = "https://ctabustracker.com/bustime/api/v2/getpredictions?key=fir5Jyc8d5a4xYwjXKNn79ERL&rt="
    + to_string(closest.first.Route) + "&stpid=" + to_string(closest.first.ID) + "&format=json";
  string second_url = "https://ctabustracker.com/bustime/api/v2/getpredictions?key=fir5Jyc8d5a4xYwjXKNn79ERL&rt="
    + to_string(closest.second.Route) + "&stpid=" + to_string(closest.second.ID) + "&format=json";

  cout << "Closest southbound bus stop:" << endl;
  cout << "  ";
  closest.first.printWithDist(distS);
  closest.first.printBusPredictions(curl, first_url);
  cout << "Closest northbound bus stop:" << endl;
  cout << "  ";
  closest.second.printWithDist(distN);
  closest.second.printBusPredictions(curl, second_url);
}

//
// getLocation
// 
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes) const
{
  double avgLat = 0;
  double avgLon = 0;
  for (const auto& n : NodeIDs) {
    double lat = 0;
    double lon = 0;
    bool isEntrance;
    nodes.find(n, lat, lon, isEntrance);
    avgLat += lat;
    avgLon += lon;
  }
  avgLat /= NodeIDs.size();
  avgLon /= NodeIDs.size();
  return make_pair(avgLat, avgLon);
}

//
// getClosestBusStops
//
// returns a pair of the closest southbound and northbound bus stops to the building
// also updates distS and distN to the closest distance to each bus stop from the building
//
pair<BusStop, BusStop> Building::getClosestBusStops(const BusStops& busstops, const Nodes& nodes, double& distS, double& distN) const
{
  //
  // get building lat and lon
  //
  pair<double, double> buildingLocation;
  buildingLocation = this->getLocation(nodes);

  double closest_south = __DBL_MAX__; // dist to closest southbound
  double closest_north = __DBL_MAX__; // dist to closest northbound
  int closest_south_index = 0; // index of closest northbound
  int closest_north_index = 0; // index of closest southbound

  int i = 0;

  for (const auto& b: busstops.MapBusStops) {
    double* closest = nullptr; // points to either closest_south/closest_north
    int* closest_index = nullptr; // points to either closest_south_index/closest_north_index

    if (b.Direction == "Southbound") {
      // set pointers to south
      closest = &closest_south;
      closest_index = &closest_south_index;
    }
    else {
      // set pointers to north
      closest = &closest_north;
      closest_index = &closest_north_index;
    }

    // calculate the distance
    double dist = distBetween2Points(buildingLocation.first, buildingLocation.second, b.Latitude, b.Longitude);

    if (dist < *closest) {
      *closest = dist; // update closest_south/closest_north
      *closest_index = i; // update closest_south_index/closest_north_index
    }

    i++; // next bus stop
  }

  distS = closest_south;
  distN = closest_north;

  // return a pair of bus stops (southbound, northbound)
  return make_pair(busstops.MapBusStops[closest_south_index], busstops.MapBusStops[closest_north_index]);
}