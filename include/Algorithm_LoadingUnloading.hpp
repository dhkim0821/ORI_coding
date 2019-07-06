#ifndef AlGORITHM_LOADINGUNUNLOADING_H
#define AlGORITHM_LOADINGUNUNLOADING_H

#include  <vector>
class Pallet;
class Factory;
class Algorithm_LoadingUnloading {
    public : 
        Algorithm_LoadingUnloading(const Factory & factory);
        ~Algorithm_LoadingUnloading();

        void run(const std::vector<Pallet*> & pallet_list);
        void printInfo(int i);
    private:
        std::vector<bool> LU_station_usage;
        std::vector<int> LU_station_using_time;
        std::vector<int> LU_station_engaged_pallet_idx;
        int _LU_time;
        int _num_LU_station;

        void _FirstInFirstOut(const std::vector<Pallet*> & pallet_list);
        void _Update();
};

#endif
