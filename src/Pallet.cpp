#include <Pallet.hpp>
#include <iostream>

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
