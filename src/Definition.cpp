#ifndef DEFINITION_H
#define DEFINITION_H

#define NUM_FIXTURE_TYPE 3
#include <string>
#include <vector>

namespace loc{
    constexpr int Outside = 0; // Out of system
    constexpr int LoadingStation = 1;
    constexpr int Buffer = 2;
    constexpr int Machine = 3;

    inline std::string printLocation(int loc){
        std::string pallet_loc_str;
        if(loc == loc::Outside) { pallet_loc_str = "Outside"; }
        if(loc == loc::LoadingStation) { pallet_loc_str = "LoadingStation"; }
        if(loc == loc::Buffer) { pallet_loc_str = "Buffer"; }
        if(loc == loc::Machine) { pallet_loc_str = "Machine"; }

        return pallet_loc_str;
    }
};

namespace process{
    constexpr int Nothing = -1;
    constexpr int Loading = 0;
    constexpr int Unloading = 1;
    constexpr int Machining = 2;
};

struct MachiningInfo{
    std::vector<int> machine_idx;
    std::vector<std::string> machine_name;
    std::vector<int> processing_time;
};

#endif
