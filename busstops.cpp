/*busstops.cpp*/

//
// A collection of bus stops in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 

#include "busstops.h"

using namespace std;

//
// idcmp
//
// compares ID's of two bus stops
//
static bool idcmp(const BusStop& a, const BusStop& b)
{
    return a.ID < b.ID;
}

//
// constructor
//
BusStops::BusStops(const string& filename)
{
    string line;
    ifstream input(filename);

    while (getline(input, line)) {
        stringstream parser(line);
        string id, route, name, dir, loc, lat, lon;

        getline(parser, id, ',');
        getline(parser, route, ',');
        getline(parser, name, ',');
        getline(parser, dir, ',');
        getline(parser, loc, ',');
        getline(parser, lat, ',');
        getline(parser, lon);

        MapBusStops.emplace_back(stoll(id), stoi(route), name, dir, loc, stod(lat), stod(lon));
    }

    sort(MapBusStops.begin(), MapBusStops.end(), idcmp);
}

//
// accessors / getters
//
int BusStops::getNumMapBusStops() const
{
    return this->MapBusStops.size();
}

//
// print
//
void BusStops::print() const
{
    for (auto& b: MapBusStops) {
        b.print();
    }
}
