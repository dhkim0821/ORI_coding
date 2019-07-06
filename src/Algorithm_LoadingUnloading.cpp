#include <Algorithm_LoadingUnloading.hpp>
#include <Pallet.hpp>
#include <Factory.hpp>
#include <Definition.h>

Algorithm_LoadingUnloading::Algorithm_LoadingUnloading(const Factory & factory ){
    _num_LU_station = factory.Num_LU_Station;

    LU_station_usage.clear();
    LU_station_using_time.clear();
    LU_station_engaged_pallet_idx.clear();

    LU_station_usage.resize(_num_LU_station, false);
    LU_station_using_time.resize(_num_LU_station, 0);
    LU_station_engaged_pallet_idx.resize(_num_LU_station, -1);
    _LU_time = factory.LU_Time;
}

Algorithm_LoadingUnloading::~Algorithm_LoadingUnloading(){
}


void Algorithm_LoadingUnloading::run(const std::vector<Pallet*> & pallet_list) {
    _Update();
    _FirstInFirstOut(pallet_list);

}
void Algorithm_LoadingUnloading::_Update(){

    for(int i(0); i< _num_LU_station; ++i){
        if(LU_station_usage[i]){ // LU station is used
            // Is there any completed LU task
            if(LU_station_using_time[i] == _LU_time){
                LU_station_usage[i] = false;
            }
            ++LU_station_using_time[i];
        }
    } //END of LU station loop

}


void Algorithm_LoadingUnloading::_FirstInFirstOut(const std::vector<Pallet*> &
        pallet_list){
    printf("loading start\n");

    for(int i(0); i< _num_LU_station; ++i){
        if(!LU_station_usage[i]){ // LU station is available
            // Unloading

            // Loading
            for(int pl_idx(0); pl_idx<pallet_list.size(); ++pl_idx){
                if((pallet_list[pl_idx]->_ini_station_idx == i) && 
                      (!pallet_list[pl_idx]->_in_process)  ){
                    // LU station update 
                    LU_station_usage[i] = true;
                    LU_station_using_time[i] = 0;
                    LU_station_engaged_pallet_idx[i] = pallet_list[pl_idx]->_pallet_idx;

                    // Pallet update
                    pallet_list[pl_idx]->_in_process = true;
                    pallet_list[pl_idx]->_process_name = process::Loading;
                    pallet_list[pl_idx]->_process_duration = _LU_time;
                    pallet_list[pl_idx]->_current_processing_time = 0;
                    break;
                }
            }

        }
    } //END of LU station loop

    //for(int i(0); i<_num_LU_station; ++i){ printInfo(i); }
}

void Algorithm_LoadingUnloading::printInfo(int i){
    printf("LU station %d, using_time: %d, engaged_pallet_idx:%d\n",
            i, LU_station_using_time[i], LU_station_engaged_pallet_idx[i]);
}
