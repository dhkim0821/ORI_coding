#ifndef PALLET_H
#define PALLET_H

#include <vector> 

class Pallet{
    public:
        Pallet(int LU_station_idx, std::vector<int> fixture_type);
        ~Pallet();

        bool IsProcessing(){ return _in_process; }
        bool EngagePallet(int ProcessName, int ProcessDuration);

        void OneStepForward();

        void printPalletInfo(int idx);

        // Variables
        int _ini_station_idx;
        std::vector<int> _fixture_type;

        bool _in_process;
        int _process_name;
        int _process_duration;
        int _current_processing_time;
};

#endif

