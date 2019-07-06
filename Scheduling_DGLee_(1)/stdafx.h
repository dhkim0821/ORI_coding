struct Cell;
struct Queue;
struct Job_List;
struct Machine_T;
struct Cell_machine;
struct Mac_list;
struct Part_Type_T;
struct Part_T;
struct Pallet_T;
struct Fixture_T;
struct Cell_job;
struct Job_T;
struct Cell_job;
struct Queue_job;

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 



struct Cell_job
{
	Cell_job * pre;
	Cell_job * next;
	
	Job_T * Job;
	Part_T * Part;
	
	int operation; //그때의 operation
	int start_time;
	int ending_time;
	char * PID;
};

struct Config
{
	int Job_index;
	Machine_T ** machine_name; // 프로세싱 타임들 받아서 다음 machine 결정할때 이전꺼의 machine 고려한다
	int * machine_pro; // 프로세싱 타임들 받아서 다음 machine 결정할때 이전꺼의 processing time도 고려한다

	int last_processing_time ; //시뮬레이션에서 타임 마지막에다가 마지막 processing time을 더해준다 makespan을위해
	int total_movement;
	int temp;
};

struct Cell
{
	Cell * pre;
	Cell * next;
	
	Part_T * Part;
	int start_time;
	int ending_time;
	char * PID;
};

struct Queue
{
	Cell * Head;
	Cell * Tail;
	
	int Length;
	int Queue_size;
};

struct Queue_job
{
	Cell_job * Head;
	Cell_job * Tail;
	
	int Length;
	int Queue_size;
};

struct Machine_T
{
	char * Machine_Name;
	
	int Current_State; //0 이면 machine 가능 1이면 불가
	int Current_Job_No;
	int Current_Part_ID;
	int Current_Part_No;
	int Current_Job_Start_Time;
	int Current_Job_End_Time;
	int Total_Working_Time;

	int End_time; // 계속해서 End 업데이트해서 들고있는다. 왜냐면 dispacting 할대 end time과 현재 time이 같을때 동일한 machine에서 process되는지 체크하기위해
	
	Job_List * Job_Sequence;
	Queue * Machine_Queue; // 굳이 필요없음
	
	int release_time; //필요없음
	int idle_time; // 필요없음
	
	int Machine_State; //Auto(1) or Manual(0) machine, 나랑 관계없음 
	int * Machine_Schedule;
	int Working_or_Rest; //if time is at working hour, 1, otherwise 0; 1이면 가능, 0이면 불가
	int Next_Working_time;
	int Next_Rest_Time;
	int Number_Schedule;
	int Current_Schedule;
	int Machine_No;
};


struct Fixture_T
{

	int number_Fixture; // fixture는 무한대
	int rest_Fixture; // 사용중이면 1 아니면 0
	int fixture_no;

};
struct Pallet_T
{

	Fixture_T ** Fixture;

	int Pallet_index;
	int Num_Fixt;

	int number_Pallet; // 1로 둔다
	int rest_Pallet; // 1 또는 들어가면 0으로 바뀌고 



};

struct Job_List
{
	
	Cell_job * Head;
	Cell_job * Tail;
	
	int Length;
};


struct Cell_machine
{
	Cell_machine * pre;
	Cell_machine * next;

	int Start_time;
	int End_time;
	char * PID;
	
	Machine_T * Mac;
};


struct Mac_list
{
	Cell_machine * head;
	Cell_machine * tail;
	
	int length;
};



struct Part_Type_T
{
	int demand;
	//int type;
	int Job_ID; //어떤 part type인지 !!
	//int Priority;
	int Due_Date;
	int Fixture_Type;
	int Pre_part;

	int * part_due ; // due_date 서로 다르게 받는다 저장해뒀다가

	int release_time;
	
	int Num_Operation;
	char **PID;
	int **Process_Plan;
	int *Num_Alternative_Machine;
	int **Standard_Time;
	char *** Alterntive_Machine_Name;
	Machine_T *** Alternative_Mac;

};


struct Rmc_T
{
	int next_working_time; //다음번째 일하는 시간(u/lu)
	int next_rest_time; //다음번째 쉬는 시간(u/lu)
	int current_state;//지금 l/ul 이 사용 가능한지
	int number_schedule;
	int current_schedule;//몇번째 스케쥴인지..
	int immedieat_working_time;
	int * Machine_Schedule;
	int Rmc_No;
	Queue * RMC_Q;
	Fixture_T * Fixture; //pallet에서 사용
	int Num_Fixt; //pallet에서 사용
	Machine_T * Loading_ST;
	Machine_T * Unloading_ST;
};



struct Part_T
{
	Part_Type_T * PT;

	Mac_list * Machine_Sequence;
	Machine_T * Mac_Temp;
	
	Machine_T ** Mac_Select; // machine selection 된 후 machine list
	int * Mac_Select_index; // machine selection 된 후 machine index list
	int * Select_Process_Time; // machine selection 된 후 processing time
	int Total_Processing_Time; // 선택된 machine의 총 가공시간
	char **Mac_Select_name;


	int All_processing_time; // 모든 대안들의 가공시간을 더한것

	int Current_Process_Completion_time;
	int Current_Process_Standard_Time;

	int completion_time;
	int release_time;

	int multiplier;
	int Part_No; // 몇 번 part인지 index
	int Job_No; // 어떤 job에 속한 것인지

	int Due_date; //part별로 due date 있다

	int Terminated; // ??
	
	int Pallet_type;
	int Fixture_type;

	int unloading_waiting;
	int loading_waiting;

	char * Current_Process;
	char * Current_Machine;

	int Current_Process_No;
	int Current_Alt_Mac_index;

	double ATWK; // ??
	

};

struct Job_T
{
	Part_T ** P;
	
	int Total_Number_Operation;
	int Num_parts; //몇개의 part가 올라갓는지
	int Dependent_part ; // dependent part의 첫번째 part가 하나라도 올라가 있으면 1 아니면 0

	Mac_list * Machine_Sequence;


	Machine_T ** Machine_Route; // 올라온 part들의 operation에 해당하는 machine
	Part_T ** Part_Route; //올라온 part들의 operation이 어떤 part인지
	int * OP_Route ; //올라온 part들의 Operation number를 가지고 있는다. Route 결정할때 필요!
	char ** Machine_name;
	int *Processing_time;
	//위 5가지가 하나로 같이 묶인다. 그 position에 그 part-operation-machine이다


	int Total_movement; // machie route의 총 movement


	int current_position; //이걸로 route들 하나씩 이동!
	int current_state ; // 프로세스 중인지 아닌지, 1이면 프로세스중, 0이면 buffer에 있음

	int * Machine_Route_index; // 아직 필요한지 모름

	int Current_Process_Completion_time;
	int Current_Process_Standard_Time;
	int Terminate;

	Pallet_T * Pallet_job; //어떤 pallet인지

	int Job_No ;
	int Empty; // pallet에 part들이 올라가는것이 없으면! 1
	int Completion_time;
	int Release_time;

	int TWKR;
	double avg_duedate; // 올라간 part들의 평균 due-date

};





// TODO: reference additional headers your program requires here
