#include <Factory.hpp>
#include <Part.hpp>
#include <Pallet.hpp>
#include <fstream>
#include <Definition.h>

Factory::Factory(const std::string & file_name):_sim_time(-1){
    // Read file
    std::ifstream fin(file_name);

    fin >> Num_LU_Station;
    fin >> Num_Machine;
    fin >> Part_Info_Size;
    fin >> Num_Parttype;
    fin >> Num_Pallet;
    fin >> Num_Dependency;
    fin >> Num_Total_Part;
    fin >> Num_Dependency_Pre; //dependency¼±Çà 
    fin >> Num_Dependency_Suc; //dependencyÈÄÇà
    fin >> LU_Time;

    int Trans_temp;
    fin >> Trans_temp;
    TransTime = Trans_temp * 3; // Distance btw machines

    // Transportation time table
    Transportation_Time = new int *[Num_Machine + 1];
    for (int i = 0; i < Num_Machine + 1; i++)
    {
        Transportation_Time[i] = new int[Num_Machine + 1];
        for (int j = 0; j < Num_Machine + 1; j++)
        {
            Transportation_Time[i][j] = Trans_temp * i;

            if (j > i) { Transportation_Time[i][j] = Trans_temp * (j + 1); }
            if (i == j) { Transportation_Time[i][j] = 0; }
            if (j < i) { Transportation_Time[i][j] = Trans_temp * (i + 1); }
            if (j == (Num_Machine) && i == (Num_Machine - 1)) { Transportation_Time[i][j] = Trans_temp * j; }
            if (j == (Num_Machine - 1) && i == (Num_Machine)) { Transportation_Time[i][j] = Trans_temp * i; }
        }
    }

    // Pallet & LU statation
    int num_pallet;
    Pallet* pallet_pt;
    std::vector<int> fixture_type(NUM_FIXTURE_TYPE);
    for(int LU_station_idx(0); LU_station_idx < Num_LU_Station; ++LU_station_idx){
        fin >> num_pallet;
        for(int i(0); i<num_pallet; ++i){

            for(int j(0); j<NUM_FIXTURE_TYPE; ++j){
                fin >> fixture_type[j];
            }
            pallet_pt = new Pallet(LU_station_idx, fixture_type);
            pallet_list.push_back(pallet_pt);
        }
    }

    //LU Station available time
    int Mac_temp;
    while(true)	 {
        fin >> Mac_temp;
        Machine_Schedule.push_back(Mac_temp);

        if (Mac_temp == -1) {
            break;
        }
    }

    // Part Generation
    Part* part_pt;
    int part_type;
    int num_part;
    int num_operation;
    bool dependency;
    int due_date;
    int num_alternative_machine;
    int tmp;

    MachiningInfo machine_info;
    std::vector<MachiningInfo> machine_info_list; // length: num operation

    int start_idx(0);
    for(int i(0); i<Num_Parttype; ++i){
        fin >> part_type;
        fin >> num_operation;
        fin >> tmp;
        
        if(tmp == -1) dependency = true;
        else if(tmp == -2) dependency = false;

        fin >> num_part;
        for(int j(0); j<num_part; ++j){
            fin >> due_date;
            part_pt = new Part(part_type, num_operation, due_date, dependency);
            part_list.push_back(part_pt);
        }

        machine_info_list.resize(num_operation);
        for(int k(0); k<num_operation; ++k){
            fin >> num_alternative_machine;
            machine_info.machine_name.resize(num_alternative_machine);
            machine_info.machine_idx.resize(num_alternative_machine);
            machine_info.processing_time.resize(num_alternative_machine);

            for(int j(0); j<num_alternative_machine; ++j){
                fin >> machine_info.machine_name[j];
                fin >> machine_info.processing_time[j];
                fin >> machine_info.machine_idx[j];
            }
            machine_info_list[k] = machine_info;
        }

        for(int j(0); j<num_part; ++j){
            part_list[start_idx + j]->_machining_info_list = machine_info_list;
        }

        // IF DEFENDENCY
        if(dependency){
            int depend_part_type, post_num_operation;

            fin >> depend_part_type;
            if(depend_part_type != part_type){ 
                printf("[error] part types are different\n"); 
            }
            fin >> post_num_operation;
            fin >> tmp;
            if(tmp != 0){
                printf("[error] this is not post part\n");
             }

            machine_info_list.resize(post_num_operation);

            for(int k(0); k<post_num_operation; ++k){
                fin >> num_alternative_machine;
                machine_info.machine_name.resize(num_alternative_machine);
                machine_info.machine_idx.resize(num_alternative_machine);
                machine_info.processing_time.resize(num_alternative_machine);

                for(int j(0); j<num_alternative_machine; ++j){
                    fin >> machine_info.machine_name[j];
                    fin >> machine_info.processing_time[j];
                    fin >> machine_info.machine_idx[j];
                }
                machine_info_list[k] = machine_info;
            }

            for(int j(0); j<num_part; ++j){
                part_list[start_idx + j]->_post_num_operation = post_num_operation;
                part_list[start_idx + j]->_post_machining_info_list = machine_info_list;
            }
        }

        start_idx += num_part;
    }

    Num_Total_Part = part_list.size();

    printf("Num of (LU station, Machine, Pallet): %d, %d, %d\n", 
            Num_LU_Station, Num_Machine, Num_Pallet);

    printf("Part (Num, Type): %d, %d \n", Num_Total_Part, Num_Parttype);

    for(int i(0);i < part_list.size(); ++i){
        part_list[i]->printPartInfo(i);
    }

    //for(int i(0); i<pallet_list.size(); ++i){
        //pallet_list[i]->printPalletInfo(i);
    //}
}

Factory::~Factory(){}

bool Factory::All_Done(){
    // TEST
    if(_sim_time > 5){return true;}

    for(int i(0); i<Num_Total_Part; ++i){
        if(!part_list[i]->IsDone()){
            return false;
        }
    }
    return true;
}

void Factory::ForwardOneStep(){
    ++_sim_time; // Tick

    // Increase Pallet time only when it is in process
    for(int i(0); i<_num_pallet; ++i){
        if(pallet_list[i]->IsProcessing()){
            pallet_list[i]->OneStepForward();
        }
    }

    printf("[Factor] Simulation Time: %d\n", _sim_time);
}
