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
    if (stops_map_.size() > 0) {
        return int(stops_map_.size());
    } else {
        return NO_VALUE;
    }
}

void Datastructures::clear_all()
{
    // Replace this comment with your implementation
}

std::vector<StopID> Datastructures::all_stops()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return {NO_STOP};
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
    if (checkStop(stops_map_, id)) {
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
    if (!checkStop(stops_map_, id)) {
        return NO_NAME;
    } else {
        return stops_map_[id].name;
    }
}

Coord Datastructures::get_stop_coord(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(stops_map_, id)) {
        return NO_COORD;
    } else {
        return stops_map_[id].coord;
    }
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return {NO_STOP};
    }

    stops_vec alp_stops_vec = sort_map(stops_map_, "name", ORIGIN);
    return alp_stops_vec;
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.empty()) {
        return {NO_STOP};
    }

    stops_vec coord_stops_vec = sort_map(stops_map_, "coord", ORIGIN);
    return coord_stops_vec;
}

StopID Datastructures::min_coord()
{
    // Replace this comment and the line below with your implementation
    stops_vec coord_stops_vec = stops_coord_order();
    return *coord_stops_vec.begin();

}

StopID Datastructures::max_coord()
{
    // Replace this comment and the line below with your implementation
    stops_vec coord_stops_vec = stops_coord_order();
    return *coord_stops_vec.end();
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
    if (!checkStop(stops_map_, id)) {
        return false;
    } else {
        stops_map_[id].name = newname;
        return true;
    }
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(stops_map_, id)) {
        return false;
    } else {
        stops_map_[id].coord = newcoord;
        return true;
    }
}

bool Datastructures::add_region(RegionID id, const Name &name)
{
    // Replace this comment and the line below with your implementation
    if (checkRegion(regions_map_, id)) {
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
    if (!checkRegion(regions_map_, id)) {
        return NO_NAME;
    } else {
        return regions_map_[id].name;
    }
}

std::vector<RegionID> Datastructures::all_regions()
{
    // Replace this comment and the line below with your implementation
    if (regions_map_.empty()) {
        return {NO_REGION};
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
    if (!checkRegion(regions_map_, parentid)) {
        return false;
    }
    stops_vec cur_stops = regions_map_[parentid].stops;
    if (!checkStop(stops_map_, id) ||
        (std::find(cur_stops.begin(), cur_stops.end(), id) != cur_stops.end())) {
        return false;
    } else {
        regions_map_[parentid].stops.push_back(id);
        return true;
    }
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    // Replace this comment and the line below with your implementation
    if (!checkRegion(regions_map_, parentid)) {
        return false;
    }
    std::vector<RegionID> cur_subregions = regions_map_[parentid].subregions;
    if (!checkRegion(regions_map_, id) ||
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
    if (!checkStop(stops_map_, id)) {
        return {NO_REGION};
    }
    regions_vec v = {};
    RegionID *direct_region = stops_map_[id].parent;
    if (direct_region == nullptr) {
        return v;
    }
    v.push_back(*direct_region);
    RegionID *region_ptr = direct_region;
    while (region_ptr != nullptr) {
        RegionID *cur_region_id = (regions_map_[*region_ptr].parent);
        v.push_back(*cur_region_id);
        region_ptr = cur_region_id;
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
    if (!checkRegion(regions_map_, id)) {
        return {NO_COORD, NO_COORD};
    }

    std::unordered_map<StopID, Stop> stops = {};
    stops = get_stops_fromRegion(id, {});
//    Region cur_region = regions_map_[id];
//    std::for_each(cur_region.stops.begin(), cur_region.stops.end(),
//                  [stops, this](StopID x) mutable { stops[x] = stops_map_[x]; });

    stops_vec v = sort_map(stops, "coord", ORIGIN);
    if (v.empty()) {
        return {NO_COORD, NO_COORD};
    } else {
        return {stops_map_[*v.begin()].coord, stops_map_[*v.end()].coord};
    }

}

std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(stops_map_, id)) {
        return {NO_STOP};
    }

    Stop cur_stop = stops_map_[id];
    stops_vec closest_id_vec = sort_map(stops_map_, "coord", cur_stop.coord);
    stops_vec sub_vec = {};
    unsigned int length = closest_id_vec.size();
    if (length < 6) {
        sub_vec = stops_vec(closest_id_vec.begin() + 1, closest_id_vec.end());
    } else {
        sub_vec = stops_vec(closest_id_vec.begin() + 1, closest_id_vec.begin() + 5);
    }
    return sub_vec;
}

bool Datastructures::remove_stop(StopID id)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(stops_map_, id)) {
        return false;
    }

    auto stop_it = stops_map_.find(id);
    auto region_it = regions_map_.find(*stop_it->second.parent);
    auto pos = std::find(region_it->second.stops.begin(), region_it->second.stops.end(), id);
    if (pos != region_it->second.stops.end()) {
        region_it->second.stops.erase(pos);
    }
    stops_map_.erase(stop_it);
    return true;
}

RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    // Replace this comment and the line below with your implementation
    if (!checkStop(stops_map_, id1) || !checkStop(stops_map_, id2)) {
        return NO_REGION;
    }
    RegionID *dir1 = stops_map_[id1].parent;
    RegionID *dir2 = stops_map_[id2].parent;
    if (dir1 == nullptr || dir2 == nullptr) {
        return NO_REGION;
    }
    std::vector<RegionID> parent1 = {*dir1}, parent2 = {*dir2}, common_dir = {};
    while (dir1 != nullptr && dir2 != nullptr) {
        parent1.push_back(*regions_map_[*dir1].parent);
        parent2.push_back(*regions_map_[*dir2].parent);
        *dir1 = *regions_map_[*dir1].parent;
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

bool closerCoord(Coord c1, Coord c2, Coord ORIGIN) {
    bool closer = (pow(c1.x - ORIGIN.x, 2) + pow(c1.y - ORIGIN.y, 2))
                < (pow(c2.x - ORIGIN.x, 2) + pow(c2.y - ORIGIN.y, 2))? true:false;
    if (closer || (!closer && (c1.y - ORIGIN.y < c2.y - ORIGIN.y))) { return true; }
    else { return false; }
}

bool Datastructures::checkStop(std::unordered_map<StopID, Stop> m, StopID id) {
    auto it = m.find(id);
    if (it != m.end()) {
        return true;
    } else {
        return false;
    }
}

bool Datastructures::checkRegion(std::unordered_map<RegionID, Region> m, RegionID id) {
    auto it = m.find(id);
    if (it != m.end()) {
        return true;
    } else {
        return false;
    }
}

std::unordered_map<StopID, Stop> Datastructures::get_stops_fromRegion(RegionID cur_region_id, std::unordered_map<StopID, Stop> stops) {
    Region cur_region = regions_map_[cur_region_id];
    std::unordered_map<StopID, Stop> cur_stops = stops;
    std::for_each(cur_region.stops.begin(), cur_region.stops.end(),
                  [stops, this](StopID x) mutable { stops[x] = stops_map_[x]; });
    if (cur_region.subregions.empty() == 0) {
        return cur_stops;
    }
    for (auto it = cur_region.subregions.begin(); it != cur_region.subregions.end(); it++) {
        get_stops_fromRegion(*it ,cur_stops);
    }
}

std::vector<StopID> Datastructures::sort_map(std::unordered_map<StopID, Stop> m, std::string key, Coord root) {
    std::sort(m.begin(), m.end(),
              [key, root, this](stop a, stop b) {
        if (key == "name") {
            return (a.second.name < b.second.name);
        } else {
            bool closer = closerCoord(a.second.coord, b.second.coord, root);
            return closer;
        }
    });
    stops_vec v = {};
    std::for_each(m.begin(), m.end(), [v](stop x) mutable { v.push_back(x.first); });
    return v;
}
