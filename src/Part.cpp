#include <Part.hpp>
#include <iostream>

Part::Part(int type, int num_operation, int due_time):
    _part_type(type), _num_operation(num_operation), _due_time(due_time),
    _current_operation(0), _post_current_operation(0){

    printf("Part generated. type: %d, num operation: %d, due_time: %d \n", 
            _part_type, _num_operation, _due_time);

    // TEST
    _dependency = false;
}


bool Part::IsDone(){
    if(_current_operation == _num_operation) {
        if(_dependency){
            if(_post_current_operation == _post_num_operation){ return true; }
        }else{ 
            return true; 
        }
    }
    return false;
}
