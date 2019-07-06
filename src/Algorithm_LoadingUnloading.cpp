#include <Algorithm_LoadingUnloading.hpp>
#include <Pallet.hpp>
#include <Factory.hpp>

Algorithm_LoadingUnloading::Algorithm_LoadingUnloading(Factory factory ){
}

Algorithm_LoadingUnloading::~Algorithm_LoadingUnloading(){
}


void Algorithm_LoadingUnloading::run(const std::vector<Pallet*> & pallet_list) {
    _FirstInFirstOut(pallet_list);
}



void Algorithm_LoadingUnloading::_FirstInFirstOut(const std::vector<Pallet*> &
        pallet_list){

printf("loading start\n");




}

