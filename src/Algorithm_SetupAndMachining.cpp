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

    //-----------------------------------------
    machine_pre_pallet_idx.clear();
    machine_pre_pallet_idx.resize(_num_Machine, 0); 
    //-----------------------------------------

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
            //----------------------------------
            // candidate_part_list_update.clear();
            //----------------------------------

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
                                     printf("-------------------check_part->_part_idx%d\n", check_part->_part_idx);
                                        //------------------------------------------------
                                        // candidate_part_list_update.push_back(check_part);
                                        //------------------------------------------------

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

                //-----------------------------------
              
                printf("\n*** [Machine %d] Selected Part & Pallet *** \n", i);
                selected_part->print_PartInfo(0);
                selected_pallet->print_PalletMac(0); 

                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while (pl_iter != pallet_list.end()){
                    if ((*pl_iter)->_pallet_idx == selected_pallet[0]._pallet_idx )
                    {
                        (*pl_iter)->_pre_mac = i;    //update에서 확인할 방금 막 가공 끝난 팔렛의 직전머신(_pre_mac)에 i 저장 selected_pallet 루프 못벗어나니까 factory.pallet_list에 표시 
                        machine_pre_pallet_idx[i] = (*pl_iter)->_pallet_idx;  //update에서 확인할  방금 막 가공끝난 머신의 팔렛 저장

                        printf("*********************************************************************\n");
                        printf("i got a pallet%d!!!\n",(*pl_iter)->_pallet_idx);
                        printf("machine pre pallet idx? %d\n", machine_pre_pallet_idx[i]);
                        printf("we will work in mac%d\n", (*pl_iter)->_post_mac);
                        printf("*********************************************************************4\n");
                    }
                    pl_iter++;
                }

                //-----------------------------------

            } else{
#if (SHOW_DEBUG_MESSAGE)
                printf("No candidate part\n");
#endif
            }// End of if(candidate_part_list.size() > 0)
       
        } // End of if(!machine_usage[i])

    } //End of Machine Loop


   
    //---------------------------------------
    //1. _post_mac : machine to start processing, _pre_mac : machine just finished processing
    //   (팔렛class에 이제 가공시작할머신과 방금 가공끝난머신 정보저장)
    //2. update에서 방금 막 가공 끝난 팔렛 찾는다 -> _current_pallet_idx
    //3. update에서 방금 막 가공 끝난 팔렛의 _post_mac, _pre_mac  같은지/다른지 비교하여
    // 다르면 이동시간 추가
    // 같으면  이동시간 추가 x
    //---------------------------------------
}

void Algorithm_SetupAndMachining::_Update(const std::vector<Pallet*> & pallet_list){
  

    //----------------------------------------
    //is there machine transportation? 
    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){  // Machining is done
                printf("===============update(moving) information================\n");
                printf("just finished pallet%d at mac%d\n", machine_pre_pallet_idx[i], i); //방금 끝난 팔렛 
               
                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while(pl_iter != pallet_list.end()){
                    (*pl_iter)->_post_mac = i; //새로 선택될 팔렛이 가공될 머신
                    printf("pre_pallet_idx%d ", machine_pre_pallet_idx[i]);  //직전에 가공 끝난 팔렛
                    printf("pallet idx%d :  ", (*pl_iter)->_pallet_idx); //새로 선택된 팔렛을 여기서 찍어야함!!!!!!!!!!!!알고리즘에서 팔렛 선택하는부분 여기서 다시 한번( 미리) 계산해보기!!!!!!!!!!!!!!!!


                    _PredictNextPallet(pallet_list);


                    //새로운 팔렛 미리 계산해 보는중 
                    printf("pre mac%d, post mac%d\n ", (*pl_iter)->_pre_mac, (*pl_iter)->_post_mac); // 팔렛들의 직전에 끝난 머신,새로 가공될 머신 
                    pl_iter++;
                }
                printf("===========================================================\n");
            }
        }
    }
    //----------------------------------------



   //if there is no moving
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









    //if there is moving -> call '_MovingAndOperationTime' funtion
    printf("Add the moving time!\n");



}


void Algorithm_SetupAndMachining::_MovingAndOperationTime(const std::vector<Pallet*> & pallet_list){
//이동시간 추가 로직은 2가지를 생각해 볼 수 있음
//1. loc::Machine을 머신 개수만큼 추가해서 pallet loc이 바뀔때마다 이동시간 추가하는 방식
//2. pallet class에 _pre_mac, _post_mac 변수 추가해서 update될때마다 이동발생했는지 체크하는 방식

//2번 방식으로 구현중
//1. 일단은 버퍼<->machine area로 옮겨질때마다 바꿔보자 -> 가공시간에 MovingTime 추가하면됨(ok)
//2. 머신간 이동있을때 바꿔보자. (이부분 하는중)


}


void Algorithm_SetupAndMachining::_PredictNextPallet(const std::vector<Pallet*> & pallet_list){
    // pallet, machien off (다음 팔렛 미리 계산해 보기 위해 잠시 끔)
    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){  // Machining is done

                // Part: current operaiton +1
                machine_processing_part[i]->_current_operation++; 

                // Pallet: Process is done
                pallet_list[machine_engaged_pallet_idx[i]]->_in_process = false;
                pallet_list[machine_engaged_pallet_idx[i]]->LocationUpdate(loc::Buffer);

                //  machine_current_time[i] = 0;
                machine_usage[i] = false;
                continue;
            }
            // ++machine_current_time[i];
        }
    } // End of machine loop


    std::vector<Part*> candidate_part_list_temp;

    for(int i(0); i< _num_Machine; ++i){
        if(!machine_usage[i]){ //Machine is available 

            candidate_part_list_temp.clear();
            machine_post_pallet_idx.clear();
            

            std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
            while(pl_iter != pallet_list.end()){
                if((!(*pl_iter)->_in_process) &&
                        ((*pl_iter)->_pallet_loc == loc::Buffer)){

                    for(int pt_idx(0); pt_idx<(*pl_iter)->_loaded_part.size(); ++pt_idx){
                        if((*pl_iter)->_loaded_part[pt_idx]){ //there is loaded part
                            Part* check_part = (*pl_iter)->_loaded_part[pt_idx];
                            printf("1\n");
                            if(check_part->IsDone(true)){
                                printf("2\n");
                                continue;
                            }
                            else{ //check machine info
                                MachiningInfo m_info = 
                                    check_part->_machining_info_list[check_part->_current_operation];

                                for(int m_idx(0); m_idx<m_info.machine_idx.size(); ++m_idx){
                                    if(m_info.machine_idx[m_idx] == i){
                                        candidate_part_list_temp.push_back(check_part);
                                    }
                                }
                            }
                        }  
                    }//end of loaded part loop 
                }
                ++pl_iter;
            } // end of pallet loop

            if(candidate_part_list_temp.size() > 0){
                //pick a machine with shortest operation time 
                int selected_pt_idx(0);
                Part* ch_pt = candidate_part_list_temp[0];

                int shortest_processing_time =
                    ch_pt->getProcessingTime(ch_pt->_current_operation, i); 

                int processing_time(0); 
                for (int pt_idx(1); pt_idx < candidate_part_list_temp.size(); ++pt_idx){
                    ch_pt = candidate_part_list_temp[pt_idx];
                    processing_time = ch_pt->getProcessingTime(ch_pt->_current_operation , i );

                    if(shortest_processing_time > processing_time){
                        shortest_processing_time = processing_time; 
                        selected_pt_idx = pt_idx;
                    }
                }
                Part* selected_part = candidate_part_list_temp[selected_pt_idx];
                Pallet* selected_pallet = pallet_list[selected_part->_pallet_idx];


                // printf("\n$$$ [Machine %d] Selected Part & Pallet $$$ \n", i);
                // selected_part->print_PartInfo(0);
                // selected_pallet->print_PalletMac(0); 
                std::vector<Pallet*>::const_iterator pl_iter = pallet_list.begin();
                while (pl_iter != pallet_list.end()){
                    if ((*pl_iter)->_pallet_idx == selected_pallet[0]._pallet_idx ){
                        printf("i got a new pallet%d!!!\n", (*pl_iter)->_pallet_idx);
                        machine_post_pallet_idx.push_back((*pl_iter)->_pallet_idx);
                        printf("i got a new pallet%d!!!\n", machine_post_pallet_idx[0]); //찾았따!!!!!!!1!!다음 tick에서 가공될 팔렛!!
                    }
                    pl_iter++;
                }
            } else {
                printf("no candidate part (update\n");
            }//end of if(candidate_part_list_temp.size() > 0)
        }//end of if(!machine_usage[i])
    } //end of machine loop 



    //pallet, machine on (원상복구) 
    for(int i(0); i<_num_Machine; ++i){
        if(machine_usage[i]){
            if(machine_processing_time[i] == machine_current_time[i]){  // Machining is done

                // Part: current operaiton +1
                machine_processing_part[i]->_current_operation--; 

                // Pallet: Process is done
                pallet_list[machine_engaged_pallet_idx[i]]->_in_process = true;
                pallet_list[machine_engaged_pallet_idx[i]]->LocationUpdate(loc::Machine);

                //   machine_current_time[i] = 0;
                machine_usage[i] = true;
                continue;
            }
            // ++machine_current_time[i];
        }
    } // End of machine loop

}


void Algorithm_SetupAndMachining::printInfo(){
    printf("Num of Machine: %d\n", _num_Machine);
}
