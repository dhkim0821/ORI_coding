#include <iostream>
#include <vector>
#include <Part.hpp>
#include <Pallet.hpp>
#include <Factory.hpp>
#include <Configuration.h>
#include <Algorithm_Palletizing.hpp>
#include <Algorithm_LoadingUnloading.hpp>
#include <Algorithm_SetupAndMachining.hpp>


int main(int argc, char ** argv ){

    std::string file_name = THIS_COM"input_data/TEST_DATA4_2.txt";
   // Reading files and setup problem
    Factory factory(file_name);


    //factory.printInfo();
    // Construct Algorith
    Algorithm_Palletizing palletizing;
    Algorithm_LoadingUnloading loading_unloading(factory);
    Algorithm_SetupAndMachining setup_and_machining(factory);

    // Simulation Starts
    while(!factory.All_Done()){
        // Forward Onestep 
        factory.ForwardOneStep(); // 1 Tick

        // Palletizing
        palletizing.run(factory.part_list, factory.pallet_list);

        // Loading
        loading_unloading.run(factory.pallet_list);

        // Moving and Machining 
        setup_and_machining.run(factory.pallet_list);
    }
 
    //for(int i(0); i<factory.pallet_list.size(); ++i){
        //factory.pallet_list[i]->printInfo(i);
    //}
    //for(int i(0); i<factory.part_list.size(); ++i){
        //factory.part_list[i]->printInfo(i);
    //}

    //for(int i(0); i<part_list.size(); ++i){
        //printf("tarty: %f\n", part_list[i]->_due_time - part_list[i]->_process_time);
    //}
    return 0;
}
