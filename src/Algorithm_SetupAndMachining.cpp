#include <Algorithm_SetupAndMachining.hpp>
#include <Pallet.hpp>
#include <Part.hpp>
#include <Factory.hpp>
#include <Definition.h>

#define SHOW_DEBUG_MESSAGE 0

Algorithm_SetupAndMachining::Algorithm_SetupAndMachining(const Factory & factory){
    _num_Machine = factory.Num_Machine;
    _MovingTime = factory.MovingTime;

    machine_usage.clear();
    machine_processing_time.clear();
    machine_current_time.clear();
    machine_engaged_pallet_idx.clear();
    machine_processing_part.clear();

    machine_usage.resize(_num_Machine, false);
    machine_processing_time.resize(_num_Machine, 0);
    machine_current_time.resize(_num_Machine, 0);
    machine_engaged_pallet_idx.resize(_num_Machine, -1);
    machine_processing_part.resize(_num_Machine, NULL);

}
void Algorithm_SetupAndMachining::run(const std::vector<Pallet*> & pallet_list){

    _Update(pallet_list);
    _OperationTime(pallet_list);
    //_MovingAndOperationTime(pallet_list);
    //_MovingAndOperationAndWaitingTime();
}


void Algorithm_SetupAndMachining::_OperationTime(const std::vector<Pallet*> & pallet_list){

    std::vector<Part*> candidate_part_list;

    for(int i(0); i< _num_Machine; ++i){
        if(!machine_usage[i]){ // Machine is available

            candidate_part_list.clear();
            // gather all pallets (part) that can be operated in this machine
            std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
            while (pl_iter != pallet_list.end()){
                if((!(*pl_iter)->_in_process) && 
                        ((*pl_iter)->_pallet_loc == loc::Buffer) ){
                    for(int pt_idx(0); pt_idx<(*pl_iter)->_loaded_part.size(); ++pt_idx){
                        if( (*pl_iter)->_loaded_part[pt_idx]){ // There is loaded part
                            Part* check_part = (*pl_iter)->_loaded_part[pt_idx];
                            printf("1\n");
                            if(check_part->IsDone(true)){ 
                                printf("2\n");
                                check_part->print_PartInfo(pt_idx);
                                continue; 
                            }
                            else {
                                // check machine info
                                MachiningInfo m_info = 
                                    check_part->_machining_info_list[check_part->_current_operation];

                                for(int m_idx(0); m_idx < m_info.machine_idx.size(); ++m_idx){
                                    if(m_info.machine_idx[m_idx] == i){
                                        candidate_part_list.push_back(check_part);
                                    }
                                }
                            }
                        }
                    } // End of loaded part loop
                }
                ++pl_iter;
            } // End of Pallet loop
#if (SHOW_DEBUG_MESSAGE)
            printf("*** [Machine %d] Selected Candidate *** \n", i);
            for(int i(0); i<candidate_part_list.size(); ++i ) 
            candidate_part_list[i]->printInfo(i);
#endif

            if(candidate_part_list.size() > 0){
                // Pick a machine with shortest operation time
                int selected_pt_idx(0); // Find this

                Part* ch_pt = candidate_part_list[0];
                int shortest_processing_time = 
                    ch_pt->getProcessingTime(ch_pt->_current_operation, i);

                int processing_time(0);
                for(int pt_idx(1); pt_idx<candidate_part_list.size(); ++pt_idx){
                    ch_pt = candidate_part_list[pt_idx];

                    processing_time = ch_pt->getProcessingTime(ch_pt->_current_operation, i);

                    if(shortest_processing_time > processing_time){
                        shortest_processing_time = processing_time;
                        selected_pt_idx = pt_idx;
                    }
                }

                // Operation (machining) starts
                Part* selected_part = candidate_part_list[selected_pt_idx];
                Pallet* selected_pallet = pallet_list[selected_part->_pallet_idx];

                // Pallet process starts
                selected_pallet->_in_process = true;
                selected_pallet->_process_name = process::Machining;
                selected_pallet->_process_duration = shortest_processing_time;
                selected_pallet->_current_processing_time = 0;


                // Machine Starts
                machine_usage[i] = true;
                machine_processing_time[i] = shortest_processing_time;
                printf("short process time: %d\n", shortest_processing_time);
                machine_current_time[i] = 0;
                machine_engaged_pallet_idx[i] = selected_pallet->_pallet_idx;
                machine_processing_part[i] = selected_part;
#if (SHOW_DEBUG_MESSAGE)
                printf("\n*** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->printInfo(0);
                selected_pallet->printInfo(0);
#endif

            } else{
#if (SHOW_DEBUG_MESSAGE)
                printf("No candidate part\n");
#endif
            }// End of if(candidate_part_list.size() > 0)

        } // End of if(!machine_usage[i])

    } //End of Machine Loop
}

void Algorithm_SetupAndMachining::_Update(const std::vector<Pallet*> & pallet_list){

    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){  // Machining is done
                
                // Part: current operaiton +1
                machine_processing_part[i]->_current_operation++; 

                // Pallet: Process is done
                pallet_list[machine_engaged_pallet_idx[i]]->_in_process = false;
                pallet_list[machine_engaged_pallet_idx[i]]->LocationUpdate(loc::Buffer);

                machine_current_time[i] = 0;
                machine_usage[i] = false;
                continue;
            }
            ++machine_current_time[i];
        }
    } // End of machine loop
}

void Algorithm_SetupAndMachining::printInfo(){
    printf("Num of Machine: %d\n", _num_Machine);
}
