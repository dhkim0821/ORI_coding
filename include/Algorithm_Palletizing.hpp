#ifndef PALLETIZING_H
#define PALLETIZING_H

#include <vector>

class Part;
class Pallet;

class Algorithm_Palletizing{
    public:
        Algorithm_Palletizing();
        ~Algorithm_Palletizing();

        void run(const std::vector<Part*> & part_list, 
                std::vector<Pallet*> & pallet_list);

    private:
        void _EariestDueDateMethod(const std::vector<Part*> & part_list, 
                std::vector<Pallet*> & pallet_list);
};

#endif
