#include <Pallet.hpp>
#include <iostream>
#include <Definition.h>


Pallet::Pallet(int LU_station_idx, std::vector<int> fixture_type): 
    _ini_station_idx(LU_station_idx){
        _fixture_type = fixture_type;
}

Pallet::~Pallet(){  }

bool Pallet::EngagePallet(int ProcessName, int ProcessDuration){

    if(_in_process){ // Already in process
        printf("[Error - Pallet] The pallet is already in process\n");
        return false; 
    }
    _process_duration = ProcessDuration;
    _process_name = ProcessName;
    _current_processing_time = 0; 

    return true;
}

void Pallet::OneStepForward(){
    if(_current_processing_time == _process_duration){
        _in_process = false;
    }else{
        ++_current_processing_time;
    }
}


void Pallet::printPalletInfo(int idx){
    printf("Pallet: %d \n", idx+1);

    printf("Loading Station %d, fixture type: ", _ini_station_idx);
    for(int i(0); i<NUM_FIXTURE_TYPE; ++i) {
        printf("%d,  " , _fixture_type[i]);
    }
    printf("\n");//pallets in a vector ? 
}
