
#pragma once

#include "stdafx.h"

using namespace std;

void initialize_Machine_List(ifstream * in, Mac_list * ML, int Num_Mac, Rmc_T * Rmc, int Num_Rmc, int Num_pallet, Pallet_T * Pallet_type);
void initialize_Job_List(ifstream * in, int Num_parttype, int *Num_Jobs, Part_Type_T * PT, Part_T * P, Mac_list * ML);


int max(int a, int b);

double TWKR(Part_T * P, int Current_Process);
int TWKR2(Job_T * J); //Job의 총 남아있는 가공시간

int input_Last_to_Machine_List(Mac_list * ML, Machine_T * M);\
int input_Last_to_Job_Queue(Queue_job * Q, Job_T * J); //job queue 에 넣는것
int input_Last_to_Queue(Queue * Q, Part_T * P);
int input_Last_to_Machine_Sched_List(Mac_list * ML, Machine_T * M, int St, int Ed, char * Str);
int input_Last_to_Job_List(Job_List * JL, Job_T * J, int trans); //Job 리스트에 넣는것
int Total_Proc_Time_in_Buffer(Queue_job * Q, Machine_T *T); //Buffer에 해당 machine의 processing time들을 더한것 찾기

void initialize_Job_List(Job_List * JL);

Job_T * Find_last_job (Job_List * JL);

void initialize_Machine_Queue(Queue * Q);
void initialize_Joblist_Queue(Queue_job * Q);
int initialize_Setting(int Num_Parts, Part_T * P, Mac_list * ML, Queue * Dummy, Queue * System);

int event_Excuter(Pallet_T * Pallet_type, int Num_pallet, int Num_Parts, int Num_parttype, int Num_RMC,Part_T * P, Job_T * J, Queue_job * Job_queue, Mac_list * ML, Rmc_T * RMC, Queue * Dummy, int Time, int Machine_Selection_Option, Config * Job_INDEX, int Job_index, Queue *System, int Num_machine, int Input_Sequence_Option, int Dispatching_Option, int Job_route_Option, int transportation_time);

Machine_T * Machine_Selection_SPT(Part_T * P);
Machine_T * Machine_Selection_MNPB(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX);
Machine_T * Machine_Selection_MNPB2(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX); // 앞에 part 고려없이

Job_T * Dispatching(int Opt, Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_FIFO(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_SPT(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_Dependent_SPT(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_TWKR(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_Dependent_TWKR(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_MST(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_Dependent_MST(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_MDD(Machine_T * M, Queue_job * Job_queue, int Time);
Job_T * Dispatching_Dependent_MDD(Machine_T * M, Queue_job * Job_queue, int Time);


void Loading(Pallet_T * Pallet_type, Part_T * P, Job_T *J, int Num_pallet, Queue * Dummy, int Job_index, Queue_job * Job_list, Config * Job_IDNEX, int Machine_Selection_Option, int Num_machine, Mac_list * ML, int Input_Sequence_Option, int Job_route_Option);

Job_T Job_Define_FIFO(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy);
Job_T Job_Define_SPPT(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy, int Machine_Selection_Option, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX);
Job_T Job_Define_EDD(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy, int Machine_Selection_Option, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX);


void Job_route(Job_T *J); //그리디
void Job_route_DP(Job_T *J, Config * Job_IDNEX); //DP
void Job_route_HU(Job_T *J, Config * Job_IDNEX); // heuristic 
int recursive(int step, int * mat, int * num, int * Job_route, int total_num_operation, int Num_part_on_pallet, int *part_position_index, Job_T *J, int  *temp_op_index2, Config * Job_IDNEX);

void recursive_temp(int step, int * mat, int * num);

int movement_cal2(int * temp_route,  int*part_position_index, Job_T *J, int total_num_operation, int  *temp_op_index2, Config * Job_IDNEX);
int movement_cal_HU(int * temp_route, int*part_position_index, Job_T *J , int total_num_operation, int  *temp_op_index2, Config * Job_IDNEX);
int *movement_cal(Part_T * current_part, int current_part_op, int *temp_op_index, Job_T *J, int *part_position_index);


int Simulation_Start(Pallet_T * Pallet_type, int Num_pallet, int Num_Parts, int Num_parttype, int Num_RMC,Part_T * P, Job_T * J, Queue_job * Job_queue, Mac_list * ML, Rmc_T * RMC, Queue * Dummy, int Machine_Selection_Option, Config * Job_INDEX, int Job_index, Queue *System, int Num_machine, int Input_Sequence_Option, int Dispatching_Option, int  Job_route_Option, int transportation_time);

void initialize_Job_INDEX(Config * Job_INDEX);
