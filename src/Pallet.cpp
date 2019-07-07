#include <Pallet.hpp>
#include <iostream>
#include <Definition.h>
#include <Part.hpp>

Pallet::Pallet(int pallet_idx, int LU_station_idx, std::vector<int> fixture_type): 
    _pallet_idx(pallet_idx), _ini_station_idx(LU_station_idx), _in_process(false), 
    _loaded(false), _pallet_loc(loc::Outside){
        _fixture_type = fixture_type;
        _loaded_part.resize(fixture_type.size());

        for(int i(0); i<_loaded_part.size(); ++i){
            _loaded_part[i] = NULL;
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
void Pallet::Empty_pallet(){
    std::vector<Part*>::iterator part_iter = _loaded_part.begin();
    while (part_iter != _loaded_part.end()){
        if( (*part_iter) ){ // there is loaded part
            (*part_iter)->_part_loc = loc::Outside;
            if( ((*part_iter)->_dependency) && (! (*part_iter)->_pre_part_is_done) ){
                (*part_iter)->SwitchToPostPart();
            }
            (*part_iter) = NULL;
        }
        ++part_iter;
    }
}

bool Pallet::Loaded_Part_HalfDone(){
    int num_of_done(0);
    int num_loaded_part(0);

    std::vector<Part*>::iterator part_iter = _loaded_part.begin();
    while (part_iter != _loaded_part.end()){
        if( (*part_iter) ){ // there is loaded part
            if( (*part_iter)->IsDone(true) ) ++num_of_done;

            ++num_loaded_part;
        }

        ++part_iter;
    }

    if(num_of_done == num_loaded_part) return true;
    else return false;
}

bool Pallet::IsThereLoadedPart(){
    std::vector<Part*>::iterator part_iter = _loaded_part.begin();
    
    while (part_iter != _loaded_part.end()){
        if( (*part_iter) ) return true;
        ++part_iter;
    }
    return false;
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
        int part_idx(-1);
        if(_loaded_part[i]){ part_idx = _loaded_part[i]->_part_idx; }
        printf("(%d, %d), " , _fixture_type[i], part_idx);
    }
    printf("\n");//pallets in a vector ? 
}
