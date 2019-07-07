#ifndef FACTORY_H
#define FACTORY_H

#include <vector>

class Part;
class Pallet;

class Factory{
    public:
        Factory(const std::string & file_name);
        ~Factory();

        // Functions
        bool All_Done();
        void ForwardOneStep();

        // Variables
        std::vector<Part*> part_list;
        std::vector<Pallet*> pallet_list;

        int Num_LU_Station;
        int Num_Machine;
        int Num_Parttype;
        int Part_Info_Size;
        int Num_Pallet;
        int Num_Dependency;
        int Num_Total_Part;
        int Num_Dependency_Pre;  //dependencyÆÄÆ®¼±Çà
        int Num_Dependency_Suc;  //dependencyÆÄÆ®¼±Çà
        int General_Parttype;    //generalÆÄÆ®
        int LU_Time;
        
        //Trnasportation time
        int **Transportation_Time;
        int TransTime;


        // LU station available time
        std::vector<int> Machine_Schedule;

        int _num_pallet;
        int _num_machine;
        int _num_loading_station;

        int _sim_time;

        void printInfo();
};
#endif
