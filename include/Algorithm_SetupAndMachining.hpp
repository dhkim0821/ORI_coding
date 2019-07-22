#ifndef ALGORITHM_SETUP_AND_MACHINING
#define ALGORITHM_SETUP_AND_MACHINING

#include <vector>

class Pallet;
class Part;
class Factory;

class Algorithm_SetupAndMachining{
    public:
        Algorithm_SetupAndMachining(const Factory & factory);
        ~Algorithm_SetupAndMachining(){}

        void run(const std::vector<Pallet*> & pallet_list);
        void printInfo();
    private:
        int _num_Machine;
        int _MovingTime;

        std::vector<bool> machine_usage;
        std::vector<int> machine_processing_time;
        std::vector<int> machine_current_time;
        std::vector<int> machine_engaged_pallet_idx;
        std::vector<Part*> machine_processing_part;

        std::vector<Pallet*> selected_pallet_update; //

        void _OperationTime(const std::vector<Pallet*> & pallet_list);
        void _MovingAndOperationTime(const std::vector<Pallet*> & pallet_list);
        void _Update(const std::vector<Pallet*> & pallet_list, 
                const std::vector<Pallet*> & selected_pallet_update);
};
#endif
