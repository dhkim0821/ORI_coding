#ifndef ALGORITHM_SETUP_AND_MACHINING
#define ALGORITHM_SETUP_AND_MACHINING

#include <vector>

class Pallet;

class Algorithm_SetupAndMachining{
    public:
        Algorithm_SetupAndMachining(){}
        ~Algorithm_SetupAndMachining(){}

        void run(std::vector<Pallet*> & pallet_list);
};
#endif
