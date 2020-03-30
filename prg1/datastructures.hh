// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <iostream>

// Types for IDs
using StopID    = long int;
using RegionID  = std::string;
using Name      = std::string;

// Return values for cases where required thing was not found
StopID const NO_STOP = -1;
RegionID const NO_REGION = "!!NO_REGION!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

struct Stop
{
    Name name;
    Coord coord;
    RegionID parent;
};

struct Region
{
    RegionID parent;
    Name name;
    std::vector<RegionID> subregions;
    std::vector<StopID> stops;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};
Coord const ORIGIN = {0, 0};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1).
    // Short rationale for estimate: const time for size() method.
    int stop_count();

    // Estimate of performance: O(n).
    // Short rationale for estimate: linear in the size of map for clear() method.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: traverse through n elements of a map.
    std::vector<StopID> all_stops();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map [] operator and multimap::insert() method.
    bool add_stop(StopID id, Name const& name, Coord xy);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map [] operator.
    Name get_stop_name(StopID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map [] operator.
    Coord get_stop_coord(StopID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: traverse through n elements of a multimap.
    std::vector<StopID> stops_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: std::sort complexity.
    std::vector<StopID> stops_coord_order();

    // Estimate of performance: O(n) ~ O(1)
    // Short rationale for estimate: Worst case happens RARELY when all stops
    // have the same coordinates.
    StopID min_coord();

    // Estimate of performance: O(n) ~ O(1)
    // Short rationale for estimate: Worst case happens RARELY when all stops
    // have the same coordinates.
    StopID max_coord();

    // Estimate of performance: O(n) ~ O(log n)
    // Short rationale for estimate: Worst case happens RARELY when all stops
    // have the same name. On average, the complexity of equal_range is O(log n).
    std::vector<StopID> find_stops(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find_if complexity.
    bool change_stop_name(StopID id, Name const& newname);

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find_if complexity.
    bool change_stop_coord(StopID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map [] operator.
    bool add_region(RegionID id, Name const& name);

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map [] operator.
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: traverse through n elements of a map.
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find complexity is at most n.
    bool add_stop_to_region(StopID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find complexity is at most n.
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Worst case happen RARELY when we are going
    // from the leaf to the root and there are n regions in total.
    std::vector<RegionID> stop_regions(StopID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: get_stops_fromRegion results in n,
    // same for loops and std::min(max)_element.
    std::pair<Coord, Coord> region_bounding_box(RegionID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: std::sort complexity.
    std::vector<StopID> stops_closest_to(StopID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find_if complexity.
    bool remove_stop(StopID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: at most n for std::find_first_of and two while loops.
    RegionID stops_common_region(StopID id1, StopID id2);

private:
    // Add stuff needed for your class implementation here
    std::unordered_map<StopID, Stop> stops_map_ = {};
    std::multimap<Name, StopID> names_map_ = {};
    std::multimap<int, StopID> distance_map_ = {};
    std::unordered_map<RegionID, Region> regions_map_ = {};
    bool existStop(StopID id);    
    bool existRegion(RegionID id);
    void get_stops_fromRegion(Region &cur_region, std::vector<StopID> &stops);
    bool compCoord(Coord c1, Coord c2, Coord root);
};

#endif // DATASTRUCTURES_HH
