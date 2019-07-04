#ifndef PALLET_H
#define PALLET_H

class Pallet{
    public:
        bool IsProcessing(){ return _in_process; }
        bool EngagePallet(int ProcessName, int ProcessDuration);

        void OneStepForward();

        // Variables
        int _fixture_type[4];

        bool _in_process;
        int _process_name;
        int _process_duration;
        int _current_processing_time;
};

#endif

