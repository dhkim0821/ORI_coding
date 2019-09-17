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
    _OperationTime1(pallet_list); //SPT (original)
   // _OperationTime2(pallet_list); //EDD
    // _OperationTime3(pallet_list); //STPT
    
    //_MovingAndOperationTime(pallet_list);
}


void Algorithm_SetupAndMachining::_OperationTime1(const std::vector<Pallet*> & pallet_list){

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

                printf("--->shortest_processing_time %d\n", shortest_processing_time);

                int processing_time(0);
                for(int pt_idx(1); pt_idx<candidate_part_list.size(); ++pt_idx){
                    ch_pt = candidate_part_list[pt_idx];
                    processing_time = ch_pt->getProcessingTime(ch_pt->_current_operation, i);
                    printf("--->processing_time %d\n", processing_time);
                    if(shortest_processing_time > processing_time){
                        shortest_processing_time = processing_time;
                        selected_pt_idx = pt_idx;
                    }
                }
                // Operation (machining) starts
                Part* selected_part = candidate_part_list[selected_pt_idx];
                Pallet* selected_pallet = pallet_list[selected_part->_pallet_idx];
            
                //-------------------------------------------
                // Pallet*  selected_pallet_update = pallet_list[selected_part->_pallet_idx];
                // selected_pallet_update->_in_process = true;
                // selected_pallet_update->_process_name = process::Machining;
                // selected_pallet_update->_process_duration = shortest_processing_time;
                // selected_pallet_update->_current_processing_time = 0;
                //-------------------------------------------

                // Pallet process starts
                selected_pallet->_in_process = true;
                selected_pallet->_process_name = process::Machining;
                
                selected_pallet->_process_duration = shortest_processing_time;
                selected_pallet->_current_processing_time = 0;
                //Mac의 LocationUpdate, 여기서 이동시간 추가할지말지 결정-------------------------------------------
                if (i == 0) {
                    printf("shortest_processing_time (before LocationUpate_mac1) %d\n", shortest_processing_time);
                    selected_pallet->LocationUpdate_Mac1(loc::Machine0, selected_pallet,
                            machine_pre_pallet[i], shortest_processing_time);
                   
                    /* Frame of transporation time
                       1. Pallet::LocationUpdate_Mac1 에서 이동시간을 추가할지 판단 후, 필요시 추가하여 
                       다시 Algorithm_SetupAndMachining::_OperationTime으로 연결
                       2. 여기shortest_processing_time 연결되면 Machine Starts 부분에 shortest_processing_time */

                    /* Code Logic
                       1. LocationUpdate_Mac1함수에서 selected_pallet(현재 선택된팔렛)이 직전에 가공했던 머신(_pre_mac)과 현재위치(loc::Machine0)을 비교
                       2. machine i에서 selected_pallet과 해당 머신(i)에서 직전에 가공된 팔렛(machine_pre_pallet[i])를 비교
                       3. 이동시간 발생 시, selected_plt->spt_temp  =  shortest_processing_time + movingtime
                       4. 이동시간이 추가된 spt_temp를 _OperationTime에 연결 
                       (shortest_processing_time를 받는 포인트는 _processing_duration,  machine_processing_time[i]) */

                    /* Today tasks
                       1. shortest_processing_time에 추가된 이동시간(spt_temp) 옮기기
                       2. shortest_processing_time 받는 포인트 바꾸기 
                       3. Debuggin
                       -complete-
                       4. chagne moving time '5' ->  variable */

                    /* Question
                       1. shortest_processing_time을 받는 변수가 machine_processing_time[i], selected_pallet->_process_duration 두개 있는데,
                       두개중 machine_processing_time[i]에만 넣음. _process_duration은 영향 안받는것으로 보인는데 맞는건지..?
                       2. simulation time 
                       */
                }
                else  if (i == 1) {
                    printf("shortest_processing_time (before LocationUpate_mac2) %d\n", shortest_processing_time);
                    selected_pallet->LocationUpdate_Mac2(loc::Machine1, selected_pallet,
                            machine_pre_pallet[i], shortest_processing_time);
                }
                else if (i == 2) {
                    printf("shortest_processing_time (before LocationUpate_mac3) %d\n", shortest_processing_time);
                    selected_pallet->LocationUpdate_Mac3(loc::Machine2, selected_pallet,
                            machine_pre_pallet[i], shortest_processing_time);
                }
               
                shortest_processing_time = selected_pallet->_spt_temp;
                printf("shortest_processing_time (after LcationUpdate_macs) %d\n", shortest_processing_time); 

                //----------------------------------------------------------------------------------------------------


                // Machine Starts
                machine_usage[i] = true;
                machine_processing_time[i] = shortest_processing_time;  
                printf("short process time: %d\n", shortest_processing_time);

                machine_current_time[i] = 0;
                machine_engaged_pallet_idx[i] = selected_pallet->_pallet_idx;
                machine_processing_part[i] = selected_part;


                //printf("======================>part idx : %d, due date : %d \n", selected_part->_part_idx, selected_part->_due_time );

#if (SHOW_DEBUG_MESSAGE)
                printf("\n*** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->printInfo(0);
                selected_pallet->printInfo(0);
#endif

                // pre mac 저장하는 부분(_pre_mac과 loc을 비교)------------------
                printf("\n*** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->print_PartInfo(0);
                selected_pallet->print_PalletMac(0); 



                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while (pl_iter != pallet_list.end()){
                    if ((*pl_iter)->_pallet_idx == selected_pallet[0]._pallet_idx ){
                        if( i == 0 ){
                            (*pl_iter)->_pre_mac = 4; // machine0=4, machine1=5, machine2=6 (Definition.hpp)
                            //machine_pre_pallet[0] = (*pl_iter)->_pallet_idx;
                        }
                       else if( i == 1 ){
                           (*pl_iter)->_pre_mac = 5;
                           //machine_pre_pallet[1] = (*pl_iter)->_pallet_idx;
                       }
                        else if (i == 2){
                            (*pl_iter)->_pre_mac = 6;
                           // machine_pre_pallet[2] = (*pl_iter)->_pallet_idx;
                        }
                    }
                    ++pl_iter;
                }

                //--------------------------------------------------------------

            } else{
#if (SHOW_DEBUG_MESSAGE)
                printf("No candidate part\n");
#endif
            }// End of if(candidate_part_list.size() > 0)
       
        } // End of if(!machine_usage[i])

    } //End of Machine Loop

} 


//-----------------------------
void Algorithm_SetupAndMachining::_OperationTime2(const std::vector<Pallet*> & pallet_list){

    std::vector<Part*>candidate_part_list;

    for(int i(0); i< _num_Machine; ++i){
        if(!machine_usage[i]){ //Machine is available

            candidate_part_list.clear();

            //gather all pallets (part) that can be oprated in this machine
            std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
            while(pl_iter != pallet_list.end()){
                if((!(*pl_iter)->_in_process) &&
                        ((*pl_iter)->_pallet_loc == loc::Buffer) ){

                    for(int pt_idx(0); pt_idx<(*pl_iter)->_loaded_part.size(); ++pt_idx){
                        if( (*pl_iter)->_loaded_part[pt_idx]){ // There is loaded part
                            Part* check_part = (*pl_iter)->_loaded_part[pt_idx];
                            printf("1\n");
                            if (check_part->IsDone(true)){
                                printf("2\n");
                                check_part->print_PartInfo(pt_idx);
                                continue;
                            }
                            else { 
                                //check machine info
                                MachiningInfo m_info = 
                                    check_part->_machining_info_list[check_part->_current_operation];

                                for(int m_idx(0); m_idx < m_info.machine_idx.size(); ++m_idx){
                                    if(m_info.machine_idx[m_idx] == i){
                                        candidate_part_list.push_back(check_part);
                                    }
                                }
                            }
                        }
                    } //End of loaded part loop
                }
                ++pl_iter;
            } //End of Pallet loop
#if (SHOW_DEBUG_MESSAGE)
            printf("*** [Machine %d] Selected Candidate *** \n", i );
            for(int i(0); i<candidate_part_list.size(); ++i)
                candidate_part_list[i]->printInfo(i);
#endif
            if(candidate_part_list.size() > 0){
                //Pick a machine with shortest operation time
                int selected_pt_idx(0);  //Find this
                Part* ch_pt = candidate_part_list[0];


//여기 하는중
//해당 팔렛에 올라와있는 파트별 납기 다 받아서 
//가장 납기 빠른 파트 (shortest_processing_time 자리) 선택해서
//shortest_processing_time 만큼 가공시간 돌아가듯이 
//선택된 파트의 이번차례 오퍼레이션의 가공시간만큼 머신가공시간에 인풋 


                // int earliest_due_date = ch_pt->getDueDate(ch_pt->_current_operation, i);
                int earliest_due_date = ch_pt->_due_time; 
                
                printf("!!!!!!!!!!!!!!!!!!!!!duedate %d\n", ch_pt->_due_time);
                printf("!!!!!!!!!!earliest due date %d\n", earliest_due_date);

                int due_date(0);
                for(int pt_idx(1); pt_idx<candidate_part_list.size(); ++pt_idx){
                    ch_pt = candidate_part_list[pt_idx];
                    due_date = ch_pt->_due_time;
                    printf("!!!!!!!!!!!due_date %d\n", due_date);
                    if(earliest_due_date > due_date){
                        earliest_due_date = due_date;
                        selected_pt_idx = pt_idx;
                    }
                }
             // Operation (machining) starts
             Part* selected_part = candidate_part_list[selected_pt_idx];
             Pallet* selected_pallet = pallet_list[selected_part->_pallet_idx];

             //Pallet process starts
             selected_pallet->_in_process = true;
             selected_pallet->_process_name = process::Machining;

             // 가공시간 인풋
             int process_time(0);
             process_time = selected_part->getProcessingTime(selected_part->_current_operation, i);

             selected_pallet->_process_duration = process_time;
             selected_pallet->_current_processing_time = 0;

             //Mac의 LocationUpdate, 여기서 이동시간 추가할지말지 결정-------------------------------------------
                if (i == 0) {
                    printf("process_time (before LocationUpate_mac1) %d\n", process_time);
                    selected_pallet->LocationUpdate_Mac1(loc::Machine0, selected_pallet,
                            machine_pre_pallet[i], process_time);
                   
                    /* Frame of transporation time
                       1. Pallet::LocationUpdate_Mac1 에서 이동시간을 추가할지 판단 후, 필요시 추가하여 
                       다시 Algorithm_SetupAndMachining::_OperationTime으로 연결
                       2. 여기shortest_processing_time 연결되면 Machine Starts 부분에 shortest_processing_time */

                    /* Code Logic
                       1. LocationUpdate_Mac1함수에서 selected_pallet(현재 선택된팔렛)이 직전에 가공했던 머신(_pre_mac)과 현재위치(loc::Machine0)을 비교
                       2. machine i에서 selected_pallet과 해당 머신(i)에서 직전에 가공된 팔렛(machine_pre_pallet[i])를 비교
                       3. 이동시간 발생 시, selected_plt->spt_temp  =  shortest_processing_time + movingtime
                       4. 이동시간이 추가된 spt_temp를 _OperationTime에 연결 
                       (shortest_processing_time를 받는 포인트는 _processing_duration,  machine_processing_time[i]) */

                    /* Today tasks
                       1. shortest_processing_time에 추가된 이동시간(spt_temp) 옮기기
                       2. shortest_processing_time 받는 포인트 바꾸기 
                       3. Debuggin
                       -complete-
                       4. chagne moving time '5' ->  variable */

                    /* Question
                       1. shortest_processing_time을 받는 변수가 machine_processing_time[i], selected_pallet->_process_duration 두개 있는데,
                       두개중 machine_processing_time[i]에만 넣음. _process_duration은 영향 안받는것으로 보인는데 맞는건지..?
                       2. simulation time 
                       */
                }
                else  if (i == 1) {
                    printf("process_time (before LocationUpate_mac2) %d\n", process_time);
                    selected_pallet->LocationUpdate_Mac2(loc::Machine1, selected_pallet,
                            machine_pre_pallet[i], process_time);
                }
                else if (i == 2) {
                    printf("process_time (before LocationUpate_mac3) %d\n", process_time);
                    selected_pallet->LocationUpdate_Mac3(loc::Machine2, selected_pallet,
                            machine_pre_pallet[i], process_time);
                }
               
                process_time = selected_pallet->_spt_temp;
                printf("process_time (after LcationUpdate_macs) %d\n", process_time); 

                //----------------------------------------------------------------------------------------------------

                // Machine Stats
                machine_usage[i] = true;
                machine_processing_time[i] = process_time;
                printf("process time : %d\n", process_time);

                machine_current_time[i] = 0;
                machine_engaged_pallet_idx[i] = selected_pallet->_pallet_idx;
                machine_processing_part[i] = selected_part;

#if (SHOW_DEBUG_MESSAGE)
                printf("\n***[Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->printInfo(0);
                selected_pallet->printInfo(0);
#endif
                //pre mac 저장하는 부분 (_pre_mac과 loc을 비교) ------------------
                printf("\n *** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->print_PartInfo(0);
                selected_pallet->print_PalletMac(0);
               

                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while (pl_iter != pallet_list.end()){
                    if((*pl_iter)->_pallet_idx == selected_pallet[0]._pallet_idx){
                        if( i == 0 ){
                            (*pl_iter)->_pre_mac = 4; //machine0 = 4
                        }
                        else if( i == 1){
                            (*pl_iter)->_pre_mac = 5;
                        }
                        else if( i == 2){
                            (*pl_iter)->_pre_mac = 6;
                        } 
                    }
                    ++pl_iter;
                }
                //---------------------------------------
            } else{
#if (SHOW_DEBUG_MESSAGE)
                printf("No candidate part\n");
#endif
            } //End of if(candidate_part_list.size() > 0 
        } // End of if(!machine_usage[i])
    } //End of Machine Loop
}

//-----------------------------

//------------------------------
void Algorithm_SetupAndMachining::_OperationTime3(const std::vector<Pallet*> & pallet_list){

    std::vector<Part*> candidate_part_list;

    for(int i(0); i< _num_Machine ; ++i){
        if(!machine_usage[i]){ // Machine is available

            candidate_part_list.clear(); 

            //gather all pallets (part) that can be operated in this machine
            std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
            while(pl_iter != pallet_list.end()){
                if((!(*pl_iter)->_in_process) && 
                        ((*pl_iter)->_pallet_loc == loc::Buffer)){
                    for(int pt_idx(0); pt_idx< (*pl_iter)->_loaded_part.size(); ++pt_idx){
                        if((*pl_iter)->_loaded_part[pt_idx]){  //There is loaded part 
                            Part* check_part = (*pl_iter)->_loaded_part[pt_idx];
                            printf("1\n"); 
                            if(check_part->IsDone(true)){
                                printf("2\n");
                                check_part->print_PartInfo(pt_idx);
                                continue;
                            }
                            else{
                                //check machine info 
                                MachiningInfo m_info =
                                    check_part->_machining_info_list[check_part->_current_operation];

                                for(int m_idx(0); m_idx < m_info.machine_idx.size(); ++m_idx){
                                    if(m_info.machine_idx[m_idx] == i){
                                        candidate_part_list.push_back(check_part); 
                                    }
                                }
                            }
                        }
                    } //End of part loop  
                }
                ++pl_iter;
            } //End of pallet loop
#if (SHOW_DEBUG_MESAGE)
            printf("*** [Machine %d] Selected Candidate *** \n", i);
            for(int i(0); i<candidaet_part_list.size() ; ++i)
                candidate_part_list[i]->printInfo(i);
#endif
            if(candidate_part_list.size() > 0){
                //Pirck a macine with operation time 
                int selected_pt_idx(0);
                Part* ch_pt = candidate_part_list[0];

                int shortest_total_processing_time = ch_pt->_sum_pt;
                int total_processing_time(0); 
                for(int pt_idx(1); pt_idx<candidate_part_list.size(); ++pt_idx){
                    ch_pt = candidate_part_list[pt_idx];
                    total_processing_time = ch_pt->_sum_pt;
                    printf("--->total processing time %d\n",total_processing_time);
                    if(shortest_total_processing_time > total_processing_time){
                        shortest_total_processing_time = total_processing_time;
                        selected_pt_idx = pt_idx;
                    }
                }
                printf(" --->shortest total processing time %d\n", shortest_total_processing_time);        

                //Operation (macing) starts
                Part* selected_part = candidate_part_list[selected_pt_idx];
                Pallet* selected_pallet = pallet_list[selected_part->_pallet_idx];

                //Pallet process starts
                selected_pallet->_in_process = true;
                selected_pallet->_process_name = process::Machining;

                int processing_time(0);  //STPT인 파트의 가공시간 맞는지체크하기 
                processing_time = selected_part->getProcessingTime(selected_part->_current_operation, i);

                selected_pallet->_process_duration = processing_time;
                selected_pallet->_current_processing_time = 0;

                //Transportation time
                if(i ==0){
                    selected_pallet->LocationUpdate_Mac1(loc::Machine0, selected_pallet,
                            machine_pre_pallet[i], processing_time);
                }
                else if(i==1){
                    selected_pallet->LocationUpdate_Mac2(loc::Machine1, selected_pallet, 
                            machine_pre_pallet[i], processing_time);
                }
                else if(i==2){
                    selected_pallet->LocationUpdate_Mac3(loc::Machine2, selected_pallet,
                            machine_pre_pallet[i], processing_time);
                }
                processing_time = selected_pallet->_spt_temp; //spt_temp:processing time with trans time
                printf("processing_time(after LocationUpdate) : %d\n", processing_time);

                //Machine Starts
                machine_usage[i] = true; 
                machine_processing_time[i] = processing_time;
                printf("selected processing time %d\n", machine_processing_time[i]);

                machine_current_time[i] = 0;
                machine_engaged_pallet_idx[i] = selected_pallet->_pallet_idx;
                machine_processing_part[i] = selected_part;

#if (SHOW_DEBUG_MESSAGE)
                printf("\n*** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->printInfo(0);
                selected_pallet->printInfo(0);
#endif 
                //record _pre_mac for adding transportation time
                printf("\n *** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->print_PartInfo(0);
                selected_pallet->print_PalletMac(0);

                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while (pl_iter != pallet_list.end()){
                    if ((*pl_iter)->_pallet_idx == selected_pallet[0]._pallet_idx){
                        if(i==0){
                            (*pl_iter)->_pre_mac = 4;
                        }
                        else if(i==1){
                            (*pl_iter)->_pre_mac = 5;
                        }
                        else if(i==2){
                            (*pl_iter)->_pre_mac = 6;
                        }
                    }
                    ++pl_iter;
                }
            } else{
#if (SHOW_DEBUG_MESSAGE)
                printf("No candidate part\n");
#endif
            } //End of if(candidated_part_list.size() > 0)
        } //End of Machine usage
    } //End of Machine loop
}
//------------------------------

void Algorithm_SetupAndMachining::_Update(const std::vector<Pallet*> & pallet_list){


    /*post mac저장 하는 부분--------------
    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){  // Machining is done
                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while(pl_iter != pallet_list.end()){
                    (*pl_iter)->_post_mac = i; 
                    printf("post mac %d\n", (*pl_iter)->_post_mac);
                    pl_iter++;
                }
            }
        }
    }*/


    //simulation time 2188 -> simulation time 2725 (after adding movingtime)
    //-> simulation time 2733 (after adjusting simulation time)
    machine_pre_pallet.resize(3);
    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] -1  == machine_current_time[i]){  // Machining is done

               // Part: current operaiton +1
                machine_processing_part[i]->_current_operation++; 

                // Pallet: Process is done
                //--------------------------------------------------------------
                //pre pallet저장 
                machine_pre_pallet[i] = pallet_list[machine_engaged_pallet_idx[i]]->_pallet_idx;
                //--------------------------------------------------------------

                pallet_list[machine_engaged_pallet_idx[i]]->_in_process = false;
                pallet_list[machine_engaged_pallet_idx[i]]->LocationUpdate(loc::Buffer,
                        pallet_list[machine_engaged_pallet_idx[i]]->_pallet_idx);


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




