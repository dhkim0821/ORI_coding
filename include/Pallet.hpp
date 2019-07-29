#ifndef PALLET_H
#define PALLET_H

#include <vector> 
class Part;

class Pallet{
    public:
        Pallet(int pallet_idx, int LU_station_idx, std::vector<int> fixture_type);
        ~Pallet();

        bool IsProcessing(){ return _in_process; }
        bool EngagePallet(int ProcessName, int ProcessDuration);
        bool Loaded_Part_HalfDone();
        bool IsThereLoadedPart();

        void Empty_pallet();

        void OneStepForward();
        void LocationUpdate(int loc, int plt_idx);

        void print_PalletInfo(int idx);
        void print_PalletMac(int idx);

        // Variables
        int _ini_station_idx;
        int _pallet_idx;
        int _pallet_loc;
        bool _in_process;

        std::vector<int> _fixture_type;
        std::vector<Part*> _loaded_part; // NULL: empty,  others : part 

        int _process_name;
        int _process_duration;
        int _current_processing_time;
        //----------
        int _pre_mac;
        int _current_mac;
        //----------
};

#endif

