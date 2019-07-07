#include <Part.hpp>
#include <iostream>

Part::Part(int idx, int type, int num_operation, int due_time, bool dependency):
    _part_idx(idx), _part_type(type), _num_operation(num_operation), _due_time(due_time),
    _dependency(dependency),
    _current_operation(0), _post_current_operation(0){

        _pre_part_is_done = false;
    _part_loc = loc::Outside;

    //printf("Part generated. type: %d, num operation: %d, due_time: %d \n", 
            //_part_type, _num_operation, _due_time);
}


bool Part::IsDone(bool half_done_is_done){
    if(_current_operation == _num_operation) {
        if(half_done_is_done) {
            return true;
        } else{
            if(_dependency) { if(_pre_part_is_done) return true;}
            else return true;
        }
    }
    return false;
}

void Part::SwitchToPostPart(){
    if(!_dependency) printf("[Error] This is not dependent part\n");

    _part_type = _dependent_part_type;
    _current_operation = 0;
    _num_operation = _post_num_operation;
    _pre_part_is_done = true;
}

void Part::printInfo(int idx){
    printf("%dth calling) %d part type: %d, num operation: %d, due_time: %d , part_loc: %d\n", 
            idx, _part_idx, _part_type, _num_operation, _due_time, _part_loc);

    for(int i(0); i<_machining_info_list.size(); ++i){
        printf("%d th operation info: \n", i);
        for(int j(0); j<_machining_info_list[i].machine_name.size(); ++j){
            printf("name: %s, idx: %d, processing_time: %d\n", 
                    _machining_info_list[i].machine_name[j].c_str(),
                    _machining_info_list[i].machine_idx[j],
                    _machining_info_list[i].processing_time[j]);
        }
    }

    if(_dependency){
        printf("*** Dependent part) num operation: %d\n", _post_num_operation);

        for(int i(0); i<_post_machining_info_list.size(); ++i){
            printf("%d th operation info: \n", i);
            for(int j(0); j<_post_machining_info_list[i].machine_name.size(); ++j){
                printf("name: %s, idx: %d, processing_time: %d\n", 
                        _post_machining_info_list[i].machine_name[j].c_str(),
                        _post_machining_info_list[i].machine_idx[j],
                        _post_machining_info_list[i].processing_time[j]);
            }
        }

    }
    printf("\n");
}
