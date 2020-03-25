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
using return_vec = std::vector<StopID>;

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
    if (stops_map_.size() > 0) {
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
    auto it = std::find_if(stops_map_.begin(), stops_map_.end(),
                      [id](stop &element){
                            return (element.first == id);
                      });

    if (it != stops_map_.end()) {
        return false;
    } else {
        Stop new_stop = {name, xy};
        stops_map_[id] = new_stop;
        return true;
    }
}

Name Datastructures::get_stop_name(StopID id)
{
    // Replace this comment and the line below with your implementation
    auto it = std::find_if(stops_map_.begin(), stops_map_.end(),
                      [id](stop &element){
                            return (element.first == id);
                      });

    if (it == stops_map_.end()) {
        return NO_NAME;
    } else {
        return stops_map_[id].name;
    }
}

Coord Datastructures::get_stop_coord(StopID id)
{
    // Replace this comment and the line below with your implementation
    auto it = std::find_if(stops_map_.begin(), stops_map_.end(),
                      [id](stop &element){
                            return (element.first == id);
                      });

    if (it == stops_map_.end()) {
        return NO_COORD;
    } else {
        return stops_map_[id].coord;
    }
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return {NO_STOP};
    }

    std::unordered_map<StopID, Stop> alp_stops_map = sort_map(stops_map_, "name");
    return_vec v = {};
    for (stop element : alp_stops_map) {
        v.push_back(element.first);
    }
    return v;
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return {NO_STOP};
    }

    std::unordered_map<StopID, Stop> coord_stops_map = sort_map(stops_map_, "coord");
    return_vec v = {};
    for (stop element : coord_stops_map) {
        v.push_back(element.first);
    }
    return v;
}

StopID Datastructures::min_coord()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return NO_STOP;
    }
    std::unordered_map<StopID, Stop> coord_stops_map = sort_map(stops_map_, "coord");
    return coord_stops_map.begin()->first;

}

StopID Datastructures::max_coord()
{
    // Replace this comment and the line below with your implementation
    if (stops_map_.size() == 0) {
        return NO_STOP;
    }
    std::unordered_map<StopID, Stop> coord_stops_map = sort_map(stops_map_, "coord");
    return coord_stops_map.end()->first;
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    // Replace this comment and the line below with your implementation
    return_vec v = {};
    for (stop element : stops_map_) {
        if (element.second.name == name) {
            v.push_back(element.first);
        }
    }
    if (v.size() == 0) {
        return {NO_STOP};
    } else {
        return v;
    }
}

bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    // Replace this comment and the line below with your implementation
    bool exist = checkID(stops_map_, id);
    if (!exist) {
        return false;
    } else {
        stops_map_[id].name = newname;
        return true;
    }
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    // Replace this comment and the line below with your implementation
    bool exist = checkID(stops_map_, id);
    if (!exist) {
        return false;
    } else {
        stops_map_[id].coord = newcoord;
        return true;
    }
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

bool Datastructures::checkID(std::map<StopID, Stop> m, StopID id) {
    auto it = std::find_if(m.begin(), m.end(),
                      [id](stop &element){
                            return (element.first == id);
                      });
    if (it != m.end()) {
        return true;
    } else {
        return false;
    }
}

std::unordered_map<StopID, Stop> Datastructures::sort_map(std::map<StopID, Stop> m, std::string key) {
    std::unordered_map<StopID, Stop> alp_stops_map = {};
    for (auto element : m) {
        alp_stops_map[element.first] = element.second;
    }
    std::sort(alp_stops_map.begin(), alp_stops_map.end(),
              [key](stop a, stop b) {
        if (key == "name") {
            return (a.second.name < b.second.name);
        } else if (key == "coord") {
            return (a.second.coord < b.second.coord);
        } else {
            return true;
        }
    });
    return alp_stops_map;
}
