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
const Coord ORIGIN = {0, 0};

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
    for (auto [key, value] : stops_map_) {
        v.push_back(key);
    }
    return v;
}

bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    // Replace this comment and the line below with your implementation    
    if (checkStop(id)) {
        return false;
    } else {
        Stop new_stop = {name, xy, nullptr};
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

    std::vector<std::pair<StopID, Stop>> vec = {};
    std::copy(stops_map_.begin(), stops_map_.end(), std::back_inserter(vec));
    std::sort(vec.begin(), vec.end(), [this](stop stop1, stop stop2) {
        return (get_stop_name(stop1.first) < get_stop_name(stop2.first)); });

    stops_vec alp_stops_vec = {};
    for (auto &pair : vec) {
        alp_stops_vec.push_back(pair.first);
    }
    return alp_stops_vec;
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return {};
    }

    stops_vec coord_stops_vec = sort_coord(ORIGIN);
    return coord_stops_vec;
}

StopID Datastructures::min_coord()
{
    // Replace this comment and the line below with your implementation
    stops_vec coord_stops_vec = stops_coord_order();
    if (coord_stops_vec.empty()) {
        return NO_STOP;
    } else {
        return coord_stops_vec.front();
    }
}

StopID Datastructures::max_coord()
{
    // Replace this comment and the line below with your implementation
    stops_vec coord_stops_vec = stops_coord_order();
    if (coord_stops_vec.empty()) {
        return NO_STOP;
    } else {
        return coord_stops_vec.back();
    }
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    // Replace this comment and the line below with your implementation
    stops_vec v = {};
    for (stop element : stops_map_) {
        if (element.second.name == name) {
            v.push_back(element.first);
        }
    }
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
        regions_map_[id].parent = nullptr;
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
    for (auto [key, value] : regions_map_) {
        v.push_back(key);
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
        stops_map_[id].parent = &parentid;
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
        regions_map_[id].parent = &parentid;
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
//    RegionID *direct_region = *stops_map_[id].parent;
    std::cout << *stops_map_[id].parent << std::endl;
    if (stops_map_[id].parent == nullptr) {
        return {NO_REGION};
    }
    v.push_back(*stops_map_[id].parent);
    RegionID *region_ptr = nullptr;
    region_ptr = stops_map_[id].parent;
    while (region_ptr != nullptr) {
        v.push_back(*regions_map_[*region_ptr].parent);
        *region_ptr = *regions_map_[*region_ptr].parent;
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

    for (auto &stop : stops) {
        std::cout << stop << std::endl;
    }

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
    if (stop_it->second.parent != nullptr) {
        auto region_it = regions_map_.find(*stop_it->second.parent);
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
    RegionID *dir1 = stops_map_[id1].parent;
    RegionID *dir2 = stops_map_[id2].parent;
    if (dir1 == nullptr || dir2 == nullptr) {
        return NO_REGION;
    }
    std::vector<RegionID> parent1 = {*dir1}, parent2 = {*dir2}, common_dir = {};
    while (dir1 != nullptr) {
        parent1.push_back(*regions_map_[*dir1].parent);        
        *dir1 = *regions_map_[*dir1].parent;        
    }
    while (dir2 != nullptr) {
        parent2.push_back(*regions_map_[*dir2].parent);
        *dir2 = *regions_map_[*dir2].parent;
    }
    std::set_intersection(parent1.begin(), parent1.end(), parent2.begin(),
                          parent2.end(), common_dir.begin());
    if (common_dir.empty()) {
        return NO_REGION;
    } else {
        return *common_dir.begin();
    }
}

bool Datastructures::checkStop(StopID id) {
    auto it = stops_map_.find(id);
    if (it != stops_map_.end()) {
        return true;
    } else {
        return false;
    }
}

bool Datastructures::checkRegion(RegionID id) {
    auto it = regions_map_.find(id);
    if (it != regions_map_.end()) {
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

bool Datastructures::sortCoord(Coord c1, Coord c2, Coord root) {
    int d_c1 = static_cast<int>(pow(c1.x - root.x, 2) + 0.5)
               + static_cast<int>(pow(c1.y - root.y, 2) + 0.5);
    int d_c2 = static_cast<int>(pow(c2.x - root.x, 2) + 0.5)
               + static_cast<int>(pow(c2.y - root.y, 2) + 0.5);

    if ((d_c1 < d_c2) || ((d_c1 == d_c2) && (c1.y - root.y < c2.y - root.y))) { return true; }
    else { return false; }
}

std::vector<StopID> Datastructures::sort_coord(Coord root) {
    std::vector<std::pair<StopID, Stop>> vec(stops_map_.begin(), stops_map_.end());
    std::sort(vec.begin(), vec.end(), [root, this](stop stop1, stop stop2)
    { return sortCoord(get_stop_coord(stop1.first), get_stop_coord(stop2.first), root); });
    std::for_each(vec.begin(), vec.end(), [](stop stop3) {std::cout << stop3.first << std::endl; });
    stops_vec v = {};
    for (auto &pair : vec) {
        v.push_back(pair.first);
    }
    return v;
}

