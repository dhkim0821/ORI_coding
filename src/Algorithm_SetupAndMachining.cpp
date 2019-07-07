#include <Algorithm_SetupAndMachining.hpp>
#include <Pallet.hpp>
#include <Factory.hpp>
#include <Definition.h>


Algorithm_SetupAndMachining::Algorithm_SetupAndMachining(const Factory & factory){
    _num_Machine = factory.Num_Machine;
    _MovingTime = factory.MovingTime;

    machine_usage.clear();
    machine_processing_time.clear();
    machine_current_time.clear();
    machine_engaged_pallet_idx.clear();
    machine_processing_part_idx.clear();

    machine_usage.resize(_num_Machine, false);
    machine_processing_time.resize(_num_Machine, 0);
    machine_current_time.resize(_num_Machine, 0);
    machine_engaged_pallet_idx.resize(_num_Machine, -1);
    machine_processing_part_idx.resize(_num_Machine, -1);

}
void Algorithm_SetupAndMachining::run(const std::vector<Pallet*> & pallet_list){

    _Update(pallet_list);
    _MovingAndOperationTime(pallet_list);
    //_MovingAndOperationAndWaitingTime();

    //printInfo();
}


void Algorithm_SetupAndMachining::_MovingAndOperationTime(const std::vector<Pallet*> & pallet_list){
    printf("Setup and Machining\n");

    for(int i(0); i< _num_Machine; ++i){
        if(!machine_usage[i]){ // Machine is available


        }

    } //End of Machine Loop
}

void Algorithm_SetupAndMachining::_Update(const std::vector<Pallet*> & pallet_list){

    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){

                continue;
            }
            ++machine_current_time[i];
        }
    } // End of machine loop
}

void Algorithm_SetupAndMachining::printInfo(){
    printf("Num of Machine: %d\n", _num_Machine);
}
