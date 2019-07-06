#include <Pallet.hpp>
#include <iostream>
#include <Definition.h>


Pallet::Pallet(int pallet_idx, int LU_station_idx, std::vector<int> fixture_type): 
    _pallet_idx(pallet_idx), _ini_station_idx(LU_station_idx), _in_process(false), 
    _loaded(false){
        _fixture_type = fixture_type;
        _loaded_part_idx = fixture_type;

        for(int i(0); i<_loaded_part_idx.size(); ++i){
            _loaded_part_idx[i] = -1;
        }
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


void Pallet::printInfo(int idx){
    printf("%dth call) Pallet: %d \n", idx, _pallet_idx);

    printf("Loading Station %d, (fixture type, laoded part idx): ", _ini_station_idx);
    for(int i(0); i<NUM_FIXTURE_TYPE; ++i) {
        printf("(%d, %d), " , _fixture_type[i], _loaded_part_idx[i]);
    }
    printf("\n");//pallets in a vector ? 
}
