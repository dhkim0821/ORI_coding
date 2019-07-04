#ifndef FACTORY_H
#define FACTORY_H

#include <vector>

class Part;
class Pallet;

class Factory{
    public:
        Factory(const std::string & file_name);
        ~Factory();

        // Functions
        bool All_Done();
        void ForwardOneStep();

        // Variables
        std::vector<Part*> part_list;
        std::vector<Pallet*> pallet_list;

        int _num_part;
        int _num_pallet;
        int _num_machine;
        int _num_loading_station;

        int _sim_time;
};
#endif
