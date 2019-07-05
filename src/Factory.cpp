#include <Factory.hpp>
#include <Part.hpp>
#include <Pallet.hpp>

Factory::Factory(const std::string & file_name):_sim_time(-1){
    // Read file
    ifstream fin(file_name);
    



    // TEST
    part_list.push_back(new Part(1, 2, 960)); // idx 0
    part_list.push_back(new Part(1, 2, 960));
    part_list.push_back(new Part(1, 2, 960));
    part_list.push_back(new Part(1, 2, 960));
    part_list.push_back(new Part(3, 1, 1460)); // 
    part_list.push_back(new Part(3, 1, 1460));
    part_list.push_back(new Part(3, 1, 1460));
    part_list.push_back(new Part(3, 1, 1460));
    part_list.push_back(new Part(4, 2, 1060));

    _num_part = part_list.size();
}

Factory::~Factory(){}

bool Factory::All_Done(){
    // TEST
    if(_sim_time > 100){return true;}
    for(int i(0); i<_num_part; ++i){
        if(!part_list[i]->IsDone()){
            return false;
        }
    }
    return true;
}

void Factory::ForwardOneStep(){
    ++_sim_time; // Tick

    // Increase Pallet time only when it is in process
    for(int i(0); i<_num_pallet; ++i){
        if(pallet_list[i]->IsProcessing()){
            pallet_list[i]->OneStepForward();
        }
    }

    printf("[Factor] Simulation Time: %d\n", _sim_time);
}
