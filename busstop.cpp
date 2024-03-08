/*busstop.cpp*/

//
// A bus stop in the Open Street Map.
// 
// Brandon Do
// Northwestern University
// CS 211
// 

#include "busstop.h"

using namespace std;

//
// Constructor
//
BusStop::BusStop(long long id, int route, string name, string dir, string loc, double lat, double lon)
    : ID(id), Route(route), Name(name), Direction(dir), Location(loc), Latitude(lat), Longitude(lon)
{

}

//
// print
//
void BusStop::print() const
{
    cout << ID << ": bus " << Route << ", " << Name << ", "
        << Direction << ", " << Location << ", location ("
        << Latitude << ", " << Longitude << ")" << endl;
}

//
// printWithDist
// also prints distance from a building
// given reference to double dist
//
void BusStop::printWithDist(const double& dist) const
{
    cout << ID << ": " << Name << ", bus #" << Route 
        << ", " << Location << ", " << dist << " miles" << endl; 
}

//
// printBusPredictions
//
// prints bus predictions for a bus stop
//
void BusStop::printBusPredictions(CURL* curl, const string& url) const
{
    string response;

    if (!callWebServer(curl, url, response)) {
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
    }
    else {
        auto jsondata = json::parse(response);
        auto bus_response = jsondata["bustime-response"];
        auto predictions = bus_response["prd"];
        
        if (predictions.size() < 1) {
            cout << "  <<no predictions available>>" << endl;
        }
        else {
            // for each prediction (a map) in the list:
            for (auto& M : predictions) {
                try {
                    cout << "  vehicle #" << stoi( M["vid"].get_ref<std::string&>() );
                    cout << " on route " << stoi( M["rt"].get_ref<std::string&>() );
                    cout << " travelling " << M["rtdir"].get_ref<std::string&>();
                    cout << " to arrive in " << stoi( M["prdctdn"].get_ref<std::string&>() ) << " mins";
                    cout << endl;
                }
                catch (exception& e) {
                    cout << "  error" << endl;
                    cout << "  malformed CTA response, predicition unavailable"
                         << " (error: " << e.what() << ")" << endl;
                }
            }
        }
    }
}