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

using stop = std::pair<StopID, Stop>;
using region = std::pair<RegionID, Region>;
using stops_vec = std::vector<StopID>;
using regions_vec = std::vector<RegionID>;
using coord_pair = std::pair<Coord, StopID>;

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
    stops_map_ = {};
    regions_map_ = {};
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::stop_count()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return 0;
    } else {
        return int(stops_map_.size());
    }
}

void Datastructures::clear_all()
{
    // Replace this comment with your implementation
    stops_map_ = {};
    regions_map_ = {};
}

std::vector<StopID> Datastructures::all_stops()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return {};
    }
    std::vector<StopID> v = {};
    for (auto &pair : stops_map_) {
        v.push_back(pair.first);
    }
    return v;
}

bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    // Replace this comment and the line below with your implementation    
    if (checkStop(id)) {
        return false;
    } else {        
        if (stops_map_.empty()) {
            min_coord_ = {id, xy};
            max_coord_ = {id, xy};
        } else {
            if (compCoord(xy, min_coord_.second, ORIGIN)) {
                min_coord_ = {id, xy};
            }
            if (compCoord(max_coord_.second, xy, ORIGIN)) {
                max_coord_ = {id, xy};
            }
        }
        Stop new_stop = {name, xy, ""};
        stops_map_[id] = new_stop;
        return true;
    }
}

Name Datastructures::get_stop_name(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return NO_NAME;
    } else {
        return stops_map_[id].name;
    }
}

Coord Datastructures::get_stop_coord(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return NO_COORD;
    } else {
        return stops_map_[id].coord;
    }
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return {};
    }

    std::vector<name_pair> vec ={};
    for (auto &pair1 : stops_map_) {
        vec.push_back({pair1.first, get_stop_name(pair1.first)});
//        vec[get_stop_name(pair1.first)] = pair1.first;
    }
    std::sort(vec.begin(), vec.end(), [](name_pair s1, name_pair s2) {
        if (s1.second == s2.second) {
            return s1.first < s2.first;
        }
        return s1.second < s2.second;
    });
    stops_vec alp_stops_vec = {};
    for (auto &pair2 : vec) {
        alp_stops_vec.push_back(pair2.first);
    }
    return alp_stops_vec;
//    std::vector<Name> vec = {};
//    for (auto &pair : stops_map_) {
//        vec.push_back(get_stop_name(pair.first));
//    }
//    std::sort(vec.begin(), vec.end());
//    for (auto name : vec) {

//    }
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return {};
    }

    std::vector<coord_pair> coords_vec = {};
    for (auto &pair : stops_map_) {
        coords_vec.push_back({get_stop_coord(pair.first), pair.first});
    }
    std::sort(coords_vec.begin(), coords_vec.end(), [this](coord_pair p1, coord_pair p2)
    { return compCoord(p1.first, p2.first, ORIGIN); });

    std::vector<StopID> coord_id_vec = {};
    for (auto &pair : coords_vec) {
        coord_id_vec.push_back(pair.second);
    }
    return coord_id_vec;
}

StopID Datastructures::min_coord()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return NO_STOP;
    }
    return min_coord_.first;
}

StopID Datastructures::max_coord()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return NO_STOP;
    }
    return max_coord_.first;
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    // Replace this comment and the line below with your implementation
    std::vector<std::pair<StopID, Name>> stop_vec = {};
    for (auto &pair : stops_map_) {
        stop_vec.push_back({pair.first, get_stop_name(pair.first)});
    }
    std::sort(stop_vec.begin(), stop_vec.end(), [](std::pair<StopID, Name> s1, std::pair<StopID, Name> s2)
    { return s1.second < s2.second; });

    std::vector<std::pair<StopID, Name>>::iterator l = stop_vec.begin(), r = stop_vec.end() - 1;
    stops_vec v = {};

    while (true) {
        if (r < l) {
            break;
        }
        std::vector<std::pair<StopID, Name>>::iterator mid = l + (r - l)/2;
        if (mid->second == name) {
            v.push_back(mid->first);
        } else if (mid->second > name) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

//    for (auto &pair : stops_map_) {
//        if (pair.second.name == name) {
//            v.push_back(pair.first);
//        }
//    }

    if (v.empty()) {
        return {NO_STOP};
    } else {
        return v;
    }
}

bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return false;
    } else {
        stops_map_[id].name = newname;
        return true;
    }
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return false;
    } else {
        stops_map_[id].coord = newcoord;
        return true;
    }
}

bool Datastructures::add_region(RegionID id, const Name &name)
{
    // Replace this comment and the line below with your implementation
    if (checkRegion(id)) {
        return false;
    } else {
        regions_map_[id].name = name;
        regions_map_[id].parent = "";
        regions_map_[id].subregions = {};
        regions_map_[id].stops = {};
        return true;
    }
}

Name Datastructures::get_region_name(RegionID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkRegion(id)) {
        return NO_NAME;
    } else {
        return regions_map_[id].name;
    }
}

std::vector<RegionID> Datastructures::all_regions()
{
    // Replace this comment and the line below with your implementation
    if (regions_map_.size() == 0) {
        return {};
    }
    regions_vec v = {};
    for (auto &pair : regions_map_) {
        v.push_back(pair.first);
    }
    return v;
}

bool Datastructures::add_stop_to_region(StopID id, RegionID parentid)
{
    // Replace this comment and the line below with your implementation
    if (!checkRegion(parentid)) {
        return false;
    }
    stops_vec cur_stops = regions_map_[parentid].stops;
    if (!checkStop(id) ||
        (std::find(cur_stops.begin(), cur_stops.end(), id) != cur_stops.end())) {
        return false;
    } else {
        stops_map_[id].parent = parentid;
        regions_map_[parentid].stops.push_back(id);
        return true;
    }
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    // Replace this comment and the line below with your implementation
    if (!checkRegion(parentid)) {
        return false;
    }
    std::vector<RegionID> cur_subregions = regions_map_[parentid].subregions;
    if (!checkRegion(id) ||
        (std::find(cur_subregions.begin(), cur_subregions.end(), id) != cur_subregions.end())) {
        return false;
    } else {
        regions_map_[parentid].subregions.push_back(id);
        regions_map_[id].parent = parentid;
        return true;
    }
}

std::vector<RegionID> Datastructures::stop_regions(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return {NO_REGION};
    }
    regions_vec v = {};
    RegionID cur_region_id = stops_map_[id].parent;
    if (cur_region_id == "") {
        return {NO_REGION};
    }
    v.push_back(cur_region_id);
    while (regions_map_[cur_region_id].parent != "") {
        v.push_back(regions_map_[cur_region_id].parent);
        cur_region_id = regions_map_[cur_region_id].parent;
    }
    return v;
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // You don't have to use this method for anything, if you don't need it
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkRegion(id)) {
        return {NO_COORD, NO_COORD};
    }

    std::vector<StopID> stops = {};
    get_stops_fromRegion(regions_map_[id], stops);

    if (stops.empty()) {
        return {NO_COORD, NO_COORD};
    } else {
        std::vector<int> x_coords = {}, y_coords = {};
        for (auto &stop_id : stops) {
            x_coords.push_back(stops_map_[stop_id].coord.x);
            y_coords.push_back(stops_map_[stop_id].coord.y);
        }
        Coord bottom_left = {*std::min_element(x_coords.begin(), x_coords.end()),
                             *std::min_element(y_coords.begin(), y_coords.end())};
        Coord top_right = {*std::max_element(x_coords.begin(), x_coords.end()),
                           *std::max_element(y_coords.begin(), y_coords.end())};

        return {bottom_left, top_right};
    }
}

std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return {NO_STOP};
    }

    Stop cur_stop = stops_map_[id];
    stops_vec closest_id_vec = sort_coord(cur_stop.coord);
    stops_vec sub_vec = {};
    if (closest_id_vec.size() < 6) {
        sub_vec = stops_vec(closest_id_vec.begin() + 1, closest_id_vec.end());
    } else {
        sub_vec = stops_vec(closest_id_vec.begin() + 1, closest_id_vec.begin() + 6);
    }
    return sub_vec;
}

bool Datastructures::remove_stop(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id)) {
        return false;
    }

    auto stop_it = stops_map_.find(id);
    if (stop_it->second.parent != "") {
        auto region_it = regions_map_.find(stop_it->second.parent);
        if (region_it != regions_map_.end()) {
            auto pos = std::find(region_it->second.stops.begin(), region_it->second.stops.end(), id);
            region_it->second.stops.erase(pos);
        }
    }
    stops_map_.erase(stop_it);
    return true;
}

RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(id1) || !checkStop(id2)) {
        return NO_REGION;
    }
    RegionID region_id1 = stops_map_[id1].parent;
    RegionID region_id2 = stops_map_[id2].parent;

    if (region_id1 == "" || region_id2 == "") {
        return NO_REGION;
    }
    std::vector<RegionID> parent1 = {region_id1}, parent2 = {region_id2};
    while (regions_map_[region_id1].parent != "") {
        parent1.push_back(regions_map_[region_id1].parent);
        region_id1 = regions_map_[region_id1].parent;
    }
    while (regions_map_[region_id2].parent != "") {
        parent2.push_back(regions_map_[region_id2].parent);
        region_id2 = regions_map_[region_id2].parent;
    }

    auto common_dir = std::find_first_of(parent1.begin(), parent1.end(),
                                         parent2.begin(), parent2.end());

    if (common_dir == parent1.end()) {
        return NO_REGION;
    } else {
        return *common_dir;
    }
}

bool Datastructures::checkStop(StopID id) {
    if (stops_map_.find(id) != stops_map_.end()) {
        return true;
    } else {
        return false;
    }
}

bool Datastructures::checkRegion(RegionID id) {
    if (regions_map_.find(id) != regions_map_.end()) {
        return true;
    } else {
        return false;
    }
}

void Datastructures::get_stops_fromRegion(Region cur_region, std::vector<StopID> &stops) {
    for (auto &stop_id : cur_region.stops) {
        stops.push_back(stop_id);
    }
    if (cur_region.subregions.empty()) {
        return;
    }
    for (auto &subregion_id : cur_region.subregions) {
        get_stops_fromRegion(regions_map_[subregion_id] , stops);
    }
}

bool Datastructures::compCoord(Coord c1, Coord c2, Coord root) {
    int d_c1 = (c1.x - root.x)*(c1.x - root.x) + (c1.y - root.y)*(c1.y - root.y);
    int d_c2 = (c2.x - root.x)*(c2.x - root.x) + (c2.y - root.y)*(c2.y - root.y);

    if ((d_c1 < d_c2) || ((d_c1 == d_c2) && (c1.y - root.y < c2.y - root.y))) { return true; }
    else { return false; }
}

std::vector<StopID> Datastructures::sort_coord(Coord root) {
    std::vector<std::pair<StopID, Stop>> vec(stops_map_.begin(), stops_map_.end());
    std::sort(vec.begin(), vec.end(), [root, this](stop stop1, stop stop2)
    { return compCoord(get_stop_coord(stop1.first), get_stop_coord(stop2.first), root); });

    stops_vec v = {};
    for (auto &pair : vec) {
        v.push_back(pair.first);
    }
    return v;
}

