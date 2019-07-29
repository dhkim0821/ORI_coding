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
    // Construct Algorithm
    Algorithm_Palletizing palletizing;
    Algorithm_LoadingUnloading loading_unloading(factory);
    Algorithm_SetupAndMachining setup_and_machining(factory);

    // Simulation Starts
    while(!factory.All_Done()){
        // Forward Onestep 
        factory.ForwardOneStep(); // 1 Tick
        printf("Simulation Time: %d\n", factory._sim_time);
        printf("---------------------------1Tick  start!\n");
        
        // Palletizing
        printf("---------------------------Palletizing  start!\n");
        palletizing.run(factory.part_list, factory.pallet_list);

        // Loading
        printf("---------------------------laoding start!\n");
        loading_unloading.run(factory.pallet_list);

        // Moving and Machining 
        printf("---------------------------Machining start!\n");
        setup_and_machining.run(factory.pallet_list);

        if(factory._sim_time % factory.LU_Time  == 0){
            factory.printAllPartStatus();
            factory.printAllPalletStatus();
        }
        printf("\n");
        }// End of Sim loop

    printf("****** Simulation is done\n");
    factory.printTardiness();
     return 0;
}
