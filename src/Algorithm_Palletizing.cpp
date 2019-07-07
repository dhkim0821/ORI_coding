#include <Algorithm_Palletizing.hpp>
#include <Part.hpp>
#include <Pallet.hpp>

#define PRINT_DEBUG 0

Algorithm_Palletizing::Algorithm_Palletizing(){
}

Algorithm_Palletizing::~Algorithm_Palletizing(){
}

void Algorithm_Palletizing::run(const std::vector<Part*> & part_list, 
        std::vector<Pallet*> & pallet_list){
    _EariestDueDateMethod(part_list, pallet_list);
    //_Method2(part_list, pallet_list);
}

void Algorithm_Palletizing::_EariestDueDateMethod(const std::vector<Part*> & part_list, 
        std::vector<Pallet*> & pallet_list){
    // part list sorting
    std::vector<Part*> sort_part_list = part_list;
    std::sort(sort_part_list.begin(), sort_part_list.end(), DueDateCompare());

#if (PRINT_DEBUG)
    // Debug) Show sorted part list
    for(int i(0); i<sort_part_list.size(); ++i){
        sort_part_list[i]->printInfo(i);
    }
#endif 

    Pallet* check_pallet;

    for(int i(0); i<pallet_list.size(); ++i){ // Check all pallet list
        check_pallet = pallet_list[i];

        if((!check_pallet->IsProcessing()) && // Pallet is waiting mode
                (check_pallet->_pallet_loc == loc::Outside ) ) { // Pallet is outside
            for(int fix_idx(0); fix_idx < check_pallet->_fixture_type.size(); ++fix_idx){
                if(check_pallet->_loaded_part[fix_idx] == NULL) { // fixture is empty
                    int fixture_type = check_pallet->_fixture_type[fix_idx];

                    // part type check
                    for(int pt_idx(0); pt_idx<sort_part_list.size(); ++pt_idx){
                        if(sort_part_list[pt_idx]->_part_type == fixture_type){ 
                            // Part type and fixture type matched
                            if(sort_part_list[pt_idx]->_part_loc == loc::Outside){ 
                                // Part is in outside
                                // Loading Part
                                check_pallet->_loaded_part[fix_idx] = sort_part_list[pt_idx];
                                // Part location update to Loading station
                                sort_part_list[pt_idx]->_part_loc = loc::LoadingStation;
                                // Delete the loaded part from the list
                                sort_part_list.erase(sort_part_list.begin() + pt_idx);
                            }
                            break;
                        }
                    } // End of Sort part list loop
                }
            } // End of Fixture loop
        } // if( check_pallet->IsProcessing() )
    } // End of Pallet list loop
}


