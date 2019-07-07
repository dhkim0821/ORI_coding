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
        Part(int idx, int type, int num_operation, int due_time, bool dependency);
        ~Part(){}

        bool IsDone(bool half_done_is_done = false);
        void SwitchToPostPart();

        void printInfo(int idx);
    public:
        int _part_idx;
        int _due_time;
        int _part_loc;

        int _current_operation;
        int _part_type;
        int _num_operation;
        std::vector<MachiningInfo> _machining_info_list; // length: num operation

        // If this is dependent 
        bool _dependency;
        bool _pre_part_is_done;
        int _dependent_part_type;
        int _post_current_operation;
        int _post_num_operation;
        std::vector<MachiningInfo> _post_machining_info_list;

        History _history;
};

struct DueDateCompare{
    bool operator () (const Part & p1, const Part & p2) const {
        return p1._due_time < p2._due_time; 
    }

    bool operator () (const Part * p1, const Part * p2) const {
        return p1->_due_time < p2->_due_time; 
    }
};
#endif

