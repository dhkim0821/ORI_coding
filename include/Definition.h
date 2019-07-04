namespace loc{
    constexpr int Outside = 0; // Out of system
    constexpr int LoadingStation = 1;
    constexpr int Buffer = 2;
    constexpr int Machine = 3;
};

struct MachiningInfo{
    std::vector<int> alternative_machine;
    std::vector<int> processing_time;
};
