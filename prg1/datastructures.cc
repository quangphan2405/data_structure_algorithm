// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <cmath>
#include <stdexcept>
#include <algorithm>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

using stop        = std::pair<StopID, Stop>;
using region      = std::pair<RegionID, Region>;
using stops_vec   = std::vector<StopID>;
using regions_vec = std::vector<RegionID>;
using name_pair   = std::pair<StopID, Name>;
using coord_pair  = std::pair<StopID, Coord>;

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    stops_map_   = {};
    regions_map_ = {};
}

Datastructures::~Datastructures()
{

}

int Datastructures::stop_count()
{
    if (stops_map_.empty()) {
        return 0;
    } else {
        return int(stops_map_.size());
    }
}

void Datastructures::clear_all()
{
    stops_map_.clear();
    regions_map_.clear();
}

std::vector<StopID> Datastructures::all_stops()
{
    if (stops_map_.empty()) {
        return {};
    }
    std::vector<StopID> stops = {};
    for (auto &pair : stops_map_) {
        stops.push_back(pair.first);
    }
    return stops;
}

bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{   
    if (existStop(id)) {
        return false;
    } else {        
        if (stops_map_.empty()) {
            // Assign max and min to the first stop added.
            old_min_   = {id, xy};
            old_max_   = {id, xy};
            min_coord_ = {id, xy};
            max_coord_ = {id, xy};
        } else {
            // Compare current coord and min/max coord. Assign if satisfied.
            if (compCoord(xy, min_coord_.second, ORIGIN)) {
                old_min_   = min_coord_;
                min_coord_ = {id, xy};
            }
            if (compCoord(max_coord_.second, xy, ORIGIN)) {
                old_max_   = max_coord_;
                max_coord_ = {id, xy};
            }
        }
        // Initially stop does not belong to any region.
        Stop new_stop  = {name, xy, ""};
        stops_map_[id] = new_stop;
        names_map_.insert({name, id});
        return true;
    }
}

Name Datastructures::get_stop_name(StopID id)
{
    if (!existStop(id)) {
        return NO_NAME;
    } else {
        return stops_map_[id].name;
    }
}

Coord Datastructures::get_stop_coord(StopID id)
{
    if (!existStop(id)) {
        return NO_COORD;
    } else {
        return stops_map_[id].coord;
    }
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    if (stops_map_.size() == 0) {
        return {}; // No stop was added.
    }

    // Copy map to vector as map can not be sorted.
    std::vector<name_pair> vec ={};
    for (auto &pair1 : stops_map_) {
        vec.push_back({pair1.first, get_stop_name(pair1.first)});
    }
    // Sort the stops based on their names. If the names are the same,
    // stop with smaller id comes first.
    std::sort(vec.begin(), vec.end(), [](name_pair s1, name_pair s2) {
        if (s1.second == s2.second) {
            return s1.first < s2.first;
        }
        return s1.second < s2.second;
    });

    stops_vec alp_stops = {};
    for (auto &pair : vec) {
        alp_stops.push_back(pair.first); // Get StopIDs.
    }
    return alp_stops;
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    if (stops_map_.size() == 0) {
        return {};
    }

    std::vector<coord_pair> id_coord_vec = {};
    // Copy map to vector as map can not be sorted.
    for (auto &pair : stops_map_) {
        id_coord_vec.push_back({pair.first, get_stop_coord(pair.first)});
    }
    // Sort the coordinates based on function compCoord.
    std::sort(id_coord_vec.begin(), id_coord_vec.end(), [this](coord_pair s1, coord_pair s2)
    { return compCoord(s1.second, s2.second, ORIGIN); });

    std::vector<StopID> coord_stops = {};
    for (auto &pair : id_coord_vec) {
        coord_stops.push_back(pair.first);
    }
    return coord_stops;
}

StopID Datastructures::min_coord()
{
    if (stops_map_.empty()) {
        return NO_STOP;
    }

//    std::vector<int> x_coords = {}, y_coords = {};
//    for (auto &pair : stops_map_) {
//        x_coords.push_back(pair.second.coord.x);
//        y_coords.push_back(pair.second.coord.y);
//    }
//    // Get max and min element in x,y vectors using STL algorithm.
//    Coord min_coord_ = {*std::min_element(x_coords.begin(), x_coords.end()),
//                        *std::min_element(y_coords.begin(), y_coords.end())};

    return min_coord_.first;
}

StopID Datastructures::max_coord()
{
    if (stops_map_.empty()) {
        return NO_STOP;
    }
    return max_coord_.first;
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    stops_vec stops = {};
    // Linear search. I tried to use multimap for this function but it
    // will slow down the performance of the add_stop() drastically.
    for (auto &pair : stops_map_) {
        if (get_stop_name(pair.first) == name) {
            stops.push_back(pair.first);
        }
    }

    if (stops.empty()) {
        return {NO_STOP};
    } else {
        return stops;
    }
}

bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    if (!existStop(id)) {
        return false;
    } else {
        stops_map_[id].name = newname;
        return true;
    }
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    if (!existStop(id)) {
        return false;
    } else {
        stops_map_[id].coord = newcoord;
        return true;
    }
}

bool Datastructures::add_region(RegionID id, const Name &name)
{
    if (existRegion(id)) {
        return false;
    } else {
        // Initially a region is not a subregion of another.
        regions_map_[id].parent = "";
        regions_map_[id].name = name;
        regions_map_[id].subregions = {};
        regions_map_[id].stops = {};
        return true;
    }
}

Name Datastructures::get_region_name(RegionID id)
{
    if (!existRegion(id)) {
        return NO_NAME;
    } else {
        return regions_map_[id].name;
    }
}

std::vector<RegionID> Datastructures::all_regions()
{
    if (regions_map_.size() == 0) {
        return {};
    }
    regions_vec regions = {};
    for (auto &pair : regions_map_) {
        regions.push_back(pair.first); // Get RegionIDs.
    }
    return regions;
}

bool Datastructures::add_stop_to_region(StopID id, RegionID parentid)
{
    if (!existRegion(parentid)) {
        return false;
    }
    stops_vec cur_stops = regions_map_[parentid].stops;
    // Check if given stop already belongs to given region besides existness.
    if ((std::find(cur_stops.begin(), cur_stops.end(), id)
         != cur_stops.end()) || !existStop(id)) {
        return false;
    } else {
        // Connections are made in both stop and region 's properties.
        stops_map_[id].parent = parentid;
        regions_map_[parentid].stops.push_back(id);
        return true;
    }
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if (!existRegion(parentid)) {
        return false;
    }
    std::vector<RegionID> cur_subregions = regions_map_[parentid].subregions;
    // Check if given region is already a subregion of given parent
    // region besides existness.
    if ((std::find(cur_subregions.begin(), cur_subregions.end(), id)
         != cur_subregions.end()) || !existRegion(id)) {
        return false;
    } else {
        // Make connections in both regions' properties.
        regions_map_[id].parent = parentid;
        regions_map_[parentid].subregions.push_back(id);
        return true;
    }
}

std::vector<RegionID> Datastructures::stop_regions(StopID id)
{
    if (!existStop(id)) {
        return {NO_REGION};
    }

    regions_vec v = {};
    RegionID cur_region_id = stops_map_[id].parent;
    // If given stop does not belong to any region.
    if (cur_region_id == "") {
        return {NO_REGION};
    }
    v.push_back(cur_region_id); // Direct region.

    // Check for parents of direct region and add if exist.
    while (regions_map_[cur_region_id].parent != "") {
        v.push_back(regions_map_[cur_region_id].parent);
        cur_region_id = regions_map_[cur_region_id].parent;
    }
    return v;
}

void Datastructures::creation_finished()
{
    // You don't have to use this method for anything, if you don't need it
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID id)
{
    if (!existRegion(id)) {
        return {NO_COORD, NO_COORD};
    }

    stops_vec stops = {};
    get_stops_fromRegion(regions_map_[id], stops);

    // No stops in given region.
    if (stops.empty()) {
        return {NO_COORD, NO_COORD};
    } else {
        std::vector<int> x_coords = {}, y_coords = {};
        for (auto &stop_id : stops) {
            x_coords.push_back(stops_map_[stop_id].coord.x);
            y_coords.push_back(stops_map_[stop_id].coord.y);
        }
        // Get max and min element in x,y vectors using STL algorithm.
        Coord bottom_left = {*std::min_element(x_coords.begin(), x_coords.end()),
                             *std::min_element(y_coords.begin(), y_coords.end())};
        Coord top_right = {*std::max_element(x_coords.begin(), x_coords.end()),
                           *std::max_element(y_coords.begin(), y_coords.end())};

        return {bottom_left, top_right};
    }
}

std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    if (!existStop(id)) {
        return {NO_STOP};
    }

    Stop cur_stop = stops_map_[id];
//    std::vector<std::pair<StopID, Stop>> stops(stops_map_.begin(), stops_map_.end());
//    std::sort(stops.begin(), stops.end(), [cur_stop, this](stop stop1, stop stop2)
//    { return compCoord(get_stop_coord(stop1.first), get_stop_coord(stop2.first), cur_stop.coord); });

    std::vector<std::pair<StopID, Coord>> stops = {};
    for (auto &pair : stops_map_) {
        stops.push_back({pair.first, get_stop_coord(pair.first)});
    }
    std::sort(stops.begin(), stops.end(), [cur_stop, this](coord_pair stop1, coord_pair stop2)
    { return compCoord(get_stop_coord(stop1.first), get_stop_coord(stop2.first), cur_stop.coord); });

    // Get StopIDs from resulting sorted vector.
    stops_vec closest_stops = {};
    for (auto it = stops.begin(); it!= stops.end(); it++) {
        closest_stops.push_back(it->first);
    }

    stops_vec sub_vec = {};
    if (closest_stops.size() < 6) {
        // Output everything if there are less than 6 stops.
        sub_vec = stops_vec(closest_stops.begin() + 1, closest_stops.end());
    } else {
        // Output first five closest stops.
        sub_vec = stops_vec(closest_stops.begin() + 1, closest_stops.begin() + 6);
    }
    return sub_vec;
}

bool Datastructures::remove_stop(StopID id)
{
    if (!existStop(id)) {
        return false;
    }

    auto stop_it = stops_map_.find(id);
    // If given stop belongs to a region, then delete the connection there.
    if (stop_it->second.parent != "") {
        auto region_it = regions_map_.find(stop_it->second.parent);
        if (region_it != regions_map_.end()) {
            auto pos = std::find(region_it->second.stops.begin(),
                                 region_it->second.stops.end(), id);
            region_it->second.stops.erase(pos);
        }
    }
    // Delete the stop in the main container.
    stops_map_.erase(stop_it);
    return true;
}

RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    if (!existStop(id1) || !existStop(id2)) {
        return NO_REGION;
    }

    RegionID region_id1 = stops_map_[id1].parent;
    RegionID region_id2 = stops_map_[id2].parent;
    // If any of the given stop has no direct region, then no need to check.
    if (region_id1 == "" || region_id2 == "") {
        return NO_REGION;
    }

    std::vector<RegionID> parent1 = {region_id1}, parent2 = {region_id2};
    // Get all parents of the two given stops using while loops.
    while (regions_map_[region_id1].parent != "") {
        parent1.push_back(regions_map_[region_id1].parent);
        region_id1 = regions_map_[region_id1].parent;
    }
    while (regions_map_[region_id2].parent != "") {
        parent2.push_back(regions_map_[region_id2].parent);
        region_id2 = regions_map_[region_id2].parent;
    }

    // Find first common region between two stops.
    auto common_dir = std::find_first_of(parent1.begin(), parent1.end(),
                                         parent2.begin(), parent2.end());
    if (common_dir == parent1.end()) {
        return NO_REGION;
    } else {
        return *common_dir;
    }
}

bool Datastructures::existStop(StopID id) {
    // Check if given stop id is added to main stop container.
    if (stops_map_.find(id) != stops_map_.end()) {
        return true;
    } else {
        return false;
    }
}

bool Datastructures::existRegion(RegionID id) {
    // Check if given region id is added to main region container.
    if (regions_map_.find(id) != regions_map_.end()) {
        return true;
    } else {
        return false;
    }
}

void Datastructures::get_stops_fromRegion(Region &cur_region, std::vector<StopID> &stops) {
    // A recursive function to get direct stops of current region, and then
    // apply for its subregions.
    for (auto &stop_id : cur_region.stops) {
        stops.push_back(stop_id); // Get direct stops.
    }
    // Trivial case when current regions has no subregions.
    if (cur_region.subregions.empty()) {
        return;
    }
    for (auto &subregion_id : cur_region.subregions) {
        get_stops_fromRegion(regions_map_[subregion_id] , stops);
    }
}

bool Datastructures::compCoord(Coord c1, Coord c2, Coord root) {
    // A function to check the distances between two coordinates and the root.
    int d_c1 = (c1.x - root.x)*(c1.x - root.x) + (c1.y - root.y)*(c1.y - root.y);
    int d_c2 = (c2.x - root.x)*(c2.x - root.x) + (c2.y - root.y)*(c2.y - root.y);

    // Coordinate with smaller distance or similar distance but smaller
    // relative y-coordinate comes first.
    if ((d_c1 < d_c2) || ((d_c1 == d_c2) && (c1.y - root.y < c2.y - root.y))) { return true; }
    else { return false; }
}
