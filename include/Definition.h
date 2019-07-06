#ifndef DEFINITION_H
#define DEFINITION_H

#define NUM_FIXTURE_TYPE 3
#include <string>

namespace loc{
    constexpr int Outside = 0; // Out of system
    constexpr int LoadingStation = 1;
    constexpr int Buffer = 2;
    constexpr int Machine = 3;
};

namespace process{
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
