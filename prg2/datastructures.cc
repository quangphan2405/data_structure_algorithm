// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <cmath>
#include <stdexcept>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::stop_count()
{
    // Replace this comment and the line below with your implementation
    return NO_VALUE;
}

void Datastructures::clear_all()
{
    // Replace this comment with your implementation
}

std::vector<StopID> Datastructures::all_stops()
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    // Replace this comment and the line below with your implementation
    return false;
}

Name Datastructures::get_stop_name(StopID id)
{
    // Replace this comment and the line below with your implementation
    return NO_NAME;
}

Coord Datastructures::get_stop_coord(StopID id)
{
    // Replace this comment and the line below with your implementation
    return NO_COORD;
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

StopID Datastructures::min_coord()
{
    // Replace this comment and the line below with your implementation
    return NO_STOP;
}

StopID Datastructures::max_coord()
{
    // Replace this comment and the line below with your implementation
    return NO_STOP;
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    // Replace this comment and the line below with your implementation
    return false;
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    // Replace this comment and the line below with your implementation
    return false;
}

bool Datastructures::add_region(RegionID id, const Name &name)
{
    // Replace this comment and the line below with your implementation
    return false;
}

Name Datastructures::get_region_name(RegionID id)
{
    // Replace this comment and the line below with your implementation
    return NO_NAME;
}

std::vector<RegionID> Datastructures::all_regions()
{
    // Replace this comment and the line below with your implementation
    return {NO_REGION};
}

bool Datastructures::add_stop_to_region(StopID id, RegionID parentid)
{
    // Replace this comment and the line below with your implementation
    return false;
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    // Replace this comment and the line below with your implementation
    return false;
}

std::vector<RegionID> Datastructures::stop_regions(StopID id)
{
    // Replace this comment and the line below with your implementation
    return {NO_REGION};
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // You don't have to use this method for anything, if you don't need it
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID id)
{
    // Replace this comment and the line below with your implementation
    return {NO_COORD, NO_COORD};
}

std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

bool Datastructures::remove_stop(StopID id)
{
    // Replace this comment and the line below with your implementation
    return false;
}

RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    // Replace this comment and the line below with your implementation
    return NO_REGION;
}

std::vector<RouteID> Datastructures::all_routes()
{
    // Replace this comment and the line below with your implementation
    return {NO_ROUTE};
}

bool Datastructures::add_route(RouteID id, std::vector<StopID> stops)
{   
    // Replace this comment and the line below with your implementation
    return false;
}

std::vector<std::pair<RouteID, StopID>> Datastructures::routes_from(StopID stopid)
{
    // Replace this comment and the line below with your implementation
    return {{NO_ROUTE, NO_STOP}};
}

std::vector<StopID> Datastructures::route_stops(RouteID id)
{
    // Replace this comment and the line below with your implementation
    return {NO_STOP};
}

void Datastructures::clear_routes()
{
    // Replace this comment and the line below with your implementation
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_any(StopID fromstop, StopID tostop)
{
    // Replace this comment and the line below with your implementation
    return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_least_stops(StopID fromstop, StopID tostop)
{
    // Replace this comment and the line below with your implementation
    return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_with_cycle(StopID fromstop)
{
    // Replace this comment and the line below with your implementation
    return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_shortest_distance(StopID fromstop, StopID tostop)
{
    // Replace this comment and the line below with your implementation
    return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
}

bool Datastructures::add_trip(RouteID routeid, std::vector<Time> const& stop_times)
{
    // Replace this comment and the line below with your implementation
    return false;
}

std::vector<std::pair<Time, Duration>> Datastructures::route_times_from(RouteID routeid, StopID stopid)
{
    // Replace this comment and the line below with your implementation
    return {{NO_TIME, NO_DURATION}};
}

std::vector<std::tuple<StopID, RouteID, Time> > Datastructures::journey_earliest_arrival(StopID fromstop, StopID tostop, Time starttime)
{
    // Replace this comment and the line below with your implementation
    return {{NO_STOP, NO_ROUTE, NO_TIME}};
}

void Datastructures::add_walking_connections()
{
    // Replace this comment and the line below with your implementation
}
