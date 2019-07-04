#include <iostream>
#include <vector>
#include <Part.hpp>
#include <Pallet.hpp>
#include <Factory.hpp>
#include <Configuration.h>

int main(int argc, char ** argv ){
    printf("ORI test\n");

    std::string file_name = THIS_COM"setup_file/multi_LU_fms.txt";
    // Reading files and setup problem
    Factory factory(file_name);

    // Construct Algorithm 
    //Algorithm_Palletizing palletizing; 
    //Algorithm_LoadingUnloading loading_unloading;
    //Algorithm_SetupAndMachining setup_and_machining;

    // Simulation Starts
    while(!factory.All_Done()){
        factory.ForwardOneStep(); // 1 Tick
        // Forward Onestep of all Pallets that are currrently under process

        // Palletizing
        //palletizing.run(factory.part_list, factory.pallet_list);

        // Loading
        //loading_unloading.run(factory.pallet_list);

        // Moving and Machining 
        //setup_and_machining.run(factory.pallet_list);
    }

    //for(int i(0); i<part_list.size(); ++i){
        //printf("tarty: %f\n", part_list[i]->_due_time - part_list[i]->_process_time);
    //}
    return 0;
}
