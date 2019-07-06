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
	
	int operation; //�׶��� operation
	int start_time;
	int ending_time;
	char * PID;
};

struct Config
{
	int Job_index;
	Machine_T ** machine_name; // ���μ��� Ÿ�ӵ� �޾Ƽ� ���� machine �����Ҷ� �������� machine ����Ѵ�
	int * machine_pro; // ���μ��� Ÿ�ӵ� �޾Ƽ� ���� machine �����Ҷ� �������� processing time�� ����Ѵ�

	int last_processing_time ; //�ùķ��̼ǿ��� Ÿ�� ���������ٰ� ������ processing time�� �����ش� makespan������
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
	
	int Current_State; //0 �̸� machine ���� 1�̸� �Ұ�
	int Current_Job_No;
	int Current_Part_ID;
	int Current_Part_No;
	int Current_Job_Start_Time;
	int Current_Job_End_Time;
	int Total_Working_Time;

	int End_time; // ����ؼ� End ������Ʈ�ؼ� ����ִ´�. �ֳĸ� dispacting �Ҵ� end time�� ���� time�� ������ ������ machine���� process�Ǵ��� üũ�ϱ�����
	
	Job_List * Job_Sequence;
	Queue * Machine_Queue; // ���� �ʿ����
	
	int release_time; //�ʿ����
	int idle_time; // �ʿ����
	
	int Machine_State; //Auto(1) or Manual(0) machine, ���� ������� 
	int * Machine_Schedule;
	int Working_or_Rest; //if time is at working hour, 1, otherwise 0; 1�̸� ����, 0�̸� �Ұ�
	int Next_Working_time;
	int Next_Rest_Time;
	int Number_Schedule;
	int Current_Schedule;
	int Machine_No;
};


struct Fixture_T
{

	int number_Fixture; // fixture�� ���Ѵ�
	int rest_Fixture; // ������̸� 1 �ƴϸ� 0
	int fixture_no;

};
struct Pallet_T
{

	Fixture_T ** Fixture;

	int Pallet_index;
	int Num_Fixt;

	int number_Pallet; // 1�� �д�
	int rest_Pallet; // 1 �Ǵ� ���� 0���� �ٲ�� 



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
	int Job_ID; //� part type���� !!
	//int Priority;
	int Due_Date;
	int Fixture_Type;
	int Pre_part;

	int * part_due ; // due_date ���� �ٸ��� �޴´� �����ص״ٰ�

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
	int next_working_time; //������° ���ϴ� �ð�(u/lu)
	int next_rest_time; //������° ���� �ð�(u/lu)
	int current_state;//���� l/ul �� ��� ��������
	int number_schedule;
	int current_schedule;//���° ����������..
	int immedieat_working_time;
	int * Machine_Schedule;
	int Rmc_No;
	Queue * RMC_Q;
	Fixture_T * Fixture; //pallet���� ���
	int Num_Fixt; //pallet���� ���
	Machine_T * Loading_ST;
	Machine_T * Unloading_ST;
};



struct Part_T
{
	Part_Type_T * PT;

	Mac_list * Machine_Sequence;
	Machine_T * Mac_Temp;
	
	Machine_T ** Mac_Select; // machine selection �� �� machine list
	int * Mac_Select_index; // machine selection �� �� machine index list
	int * Select_Process_Time; // machine selection �� �� processing time
	int Total_Processing_Time; // ���õ� machine�� �� �����ð�
	char **Mac_Select_name;


	int All_processing_time; // ��� ��ȵ��� �����ð��� ���Ѱ�

	int Current_Process_Completion_time;
	int Current_Process_Standard_Time;

	int completion_time;
	int release_time;

	int multiplier;
	int Part_No; // �� �� part���� index
	int Job_No; // � job�� ���� ������

	int Due_date; //part���� due date �ִ�

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
	int Num_parts; //��� part�� �ö󰫴���
	int Dependent_part ; // dependent part�� ù��° part�� �ϳ��� �ö� ������ 1 �ƴϸ� 0

	Mac_list * Machine_Sequence;


	Machine_T ** Machine_Route; // �ö�� part���� operation�� �ش��ϴ� machine
	Part_T ** Part_Route; //�ö�� part���� operation�� � part����
	int * OP_Route ; //�ö�� part���� Operation number�� ������ �ִ´�. Route �����Ҷ� �ʿ�!
	char ** Machine_name;
	int *Processing_time;
	//�� 5������ �ϳ��� ���� ���δ�. �� position�� �� part-operation-machine�̴�


	int Total_movement; // machie route�� �� movement


	int current_position; //�̰ɷ� route�� �ϳ��� �̵�!
	int current_state ; // ���μ��� ������ �ƴ���, 1�̸� ���μ�����, 0�̸� buffer�� ����

	int * Machine_Route_index; // ���� �ʿ����� ��

	int Current_Process_Completion_time;
	int Current_Process_Standard_Time;
	int Terminate;

	Pallet_T * Pallet_job; //� pallet����

	int Job_No ;
	int Empty; // pallet�� part���� �ö󰡴°��� ������! 1
	int Completion_time;
	int Release_time;

	int TWKR;
	double avg_duedate; // �ö� part���� ��� due-date

};





// TODO: reference additional headers your program requires here
