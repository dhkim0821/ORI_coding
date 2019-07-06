#ifndef AlGORITHM_LOADINGUNUNLOADING_H
#define AlGORITHM_LOADINGUNUNLOADING_H

#include  <vector>
class Pallet;
class Factory;
class Algorithm_LoadingUnloading {
    public : 
        Algorithm_LoadingUnloading(Factory factory);
        ~Algorithm_LoadingUnloading();

        void run(const std::vector<Pallet*> & pallet_list);


    private:
        void _FirstInFirstOut(const std::vector<Pallet*> & pallet_list);

};

#endif
