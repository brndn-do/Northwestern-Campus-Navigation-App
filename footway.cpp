/*footway.cpp*/

//
// A footway in the Open Street Map.
//
// Brandon Do
// Northwestern University
// CS 211
// 


#include "footway.h"

using namespace std;

//
// Constructor
//
Footway::Footway(long long id)
    : ID(id) 
{

}

//
// adds the given nodeid to the end of the vector.
//
void Footway::add(long long nodeid)
{
    this->NodeIDs.insert(nodeid);
}