#ifndef PART_H
#define PART_H

#include <iostream>
#include <string>
#include <vector>
#include <Definition.h>

class History{
    public:
        void Summary(std::iostream file ){ 
            //file<< "loading_time:"<<_loading_time[iter]<<"\t";
            //file<<"\n";
        }

        std::vector<int> _loading_time;
        std::vector<int> _loading_station_idx;
        std::vector<int> _unloading_time;
        std::vector<int> _unloading_station_idx;

        std::vector<int> _machine_start_time;
        std::vector<int> _machine_end_time;
        std::vector<int> _machine_idx;
};


class Part{
    public:
        Part(int type, int num_operation, int due_time);
        ~Part(){}

        bool IsDone();

    public:
        int _due_time;

        int _current_operation;
        int _part_type;
        int _num_operation;
        std::vector<MachiningInfo> _machining_info_list; // length: num operation

        // If this is dependent 
        bool _dependency;
        int _post_current_operation;
        int _post_num_operation;
        std::vector<MachiningInfo> _post_machining_info_list;

        History _history;
};

#endif

