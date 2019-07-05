//����ü====================================================================================================================
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <ctime> 
#include <time.h> 
#include <cstdint>

#include <thread>
#include <mutex>
#include <future>
#include <algorithm>
#include <functional>

#include <cmath>
#include <iomanip>  //setw()
#include <tuple>    //�Լ�����ü����

#pragma once



struct Transporation_Time;
struct Depend;
struct Alternative_MAC;
struct Operation;
struct Part;
struct Parttype;
struct Fixture;
struct Pallet;

struct mac;
struct op;
struct part;
struct MatrixMax;
struct MatrixMin;
struct MinPT;


struct Transporation_Time {
	std::vector<int> TransportationT;
};

struct Depend {
	int Dependency;
};

struct Alternative_MAC {
	std::string Mac_Name;
	int Mac_No;
	int Processing_Time;
	int Trans_PT; 
	int Trans_PT_New;
	int Pre_PT; //�����ð� ���� �� New_Matrix���� �� ?
	Depend * Depend;  /* -1:Dependency����/0:dependency���� */

	int TrasnPoint;

	std::vector<int> Mac_Schedule;
};

struct Operation {
	int Operation_No;
	int Num_AlterMac;

	int State; //1:������, 0:����� 
	int Complete;  //1:�����Ϸ�, 0:�����Ϸ�ȵ�.  �ӽż��õǸ� 1�� �ٲ�(�׷����ߺ�x)
	int Current_PT;

	std::vector<long long> MAC1_Start_vec;
	std::vector<long long> MAC1_End_vec;
	std::vector<long long> MAC2_Start_vec;
	std::vector<long long> MAC2_End_vec;
	std::vector<long long> MAC3_Start_vec;
	std::vector<long long> MAC3_End_vec;


	Alternative_MAC * Mac; //��ȸӽ�
	Alternative_MAC * SelectedMac; //��ȸӽ�
};

struct DependPart {    //Part����  dependency��Ʈ�� ���� �з� 
	//��ǲ������ ������ ���� �κ� 
	int PartType;
	int NumDemand;
	int NumOperation;
	Part * Demand;
	Operation * Oper;

	int Dependency;   /* -1:Dependency����/0:dependency����/-2:�Ϲ���Ʈ */

	//��ǲ������ ������ ���ºκ� 
	int Total_Part_No;
	int Part_Type;
	int Part_No;
	int Due_Date;
	int Num_Operation;
	int state;
	int OP_idx;
};

struct Parttype {
	int PartType;
	int NumDemand;
	int NumOperation;
	int Dependency;   /* -1:Dependency����/0:dependency����/-2:�Ϲ���Ʈ */
	DependPart * Dependency_Suc; /* -1:Dependency����/0:dependency����/-2:�Ϲ���Ʈ */
	Part * Demand;
	Operation * Oper;
};

struct Part {
	int Part_No;   //��ƮŸ�Ժ� ��Ʈ��ȣ 
	int Total_Part_No; //�����Ʈ�ټ��� �������� ��Ʈ��ȣ
	int Part_Type;
	int Dependency;
	DependPart * Depend; /* -1:Dependency����/0:dependency����/-2:�Ϲ���Ʈ */

	int Num_Operation;
	int Due_Date;
	int LD_Station;
	int ULD_Station;

	int State; //1:������, 0:����� 
	int Complete;  //1:�����Ϸ�, 0:�����Ϸ�ȵ�
	int OP_idx; //���� OP��� �۾����̰�, ���� OP������� �ĺ� 

	Operation * Oper;

	int LD_Time;
	int ULD_Time;
	int Trans_Time;
	int Process_Time;
	int Waiting_Time;

};
//�����Ʈ(�ȷ�Ÿ��¡��) -> ���õ���Ʈ(�ȷ�Ÿ��¡��)�� ��� 

struct Fixture {
	int Fixture_No;
	int Pallet_No;
};


//------------------------------ line 134~178 �Ⱦ��°� ���߿� ���� 
//for Maximum Processing Time : line 107~133
struct mac {
	int mac_no;
	int processing_time;
	int PT_Trans_Time; //����+�̵��ð�
	int Current_Position;

	int op_no;
	int part_no;
	int pallet_no;

	int due; //for finding min due 
};

struct op {
	int op_no;
	mac *mac;
};

struct part {
	int part_no;
	int op_index;
	std::vector<op> op;
};
struct MatrixMax { //=pallet
	int pallet_no;
	int Current_Position;
	part *part;
};

//for Minimm Processing Time : line 133~ 145
struct MatrixMin {
	int Mac_No;
	int ***aryprocess;
	int ***aryoper;
	int ***arydepend;

	//std::vector< std::vector< std::vector <std::vector <std::vector <int>>>>> arr;
};

struct MinPT {
	int Min_pt;
	int Min_mac;
	int Min_op;
	int Min_part;
	int Min_pallet;
};
//------------------------------------

struct LU_Time {
	std::vector<long long> LD_Start_vec;
	std::vector<long long> LD_End_vec;
	std::vector<long long> ULD_Start_vec;
	std::vector<long long> ULD_End_vec;
};

struct Pallet {
	int Pallet_No;
	int Total_Pallet_No;
	int LU_Station;

	int LD_Station;
	int ULD_Station;

	int Trans_Time;
	int Current_Position;
	int Current_Mac;

	int OP_idx;
	int State;  //1:���ϴ���, 0:�������
	int Complete;  //1:�����Ϸ�, 0:�����Ϸ�ȵ�


	std::vector<long long> LD_Start_vec;
	std::vector<long long> LD_End_vec;

	std::vector<long long> ULD_Start_vec;
	std::vector<long long> ULD_End_vec;
	std::vector<LU_Time> LU_Timetable;

	LU_Time LU1;
	LU_Time LU2;
	LU_Time LU3;
	LU_Time LU4;


	//std::vector<std::vector<long long>> LD_Start_Vec;  //�ȷ����� �� LU station(��)�� �ε����� �ð�(��) 
	//std::vector<std::vector<long long>> LD_End_Vec;  //���� ��ġ�� �ȷ����� �� LU station(��)�� �ε����� �ð�(��)

	//std::vector<std::vector<long long>> ULD_Start_Vec;  //�ȷ����� �� LU station(��)�� ��ε����� �ð�(��) 
	//std::vector<std::vector<long long>> ULD_End_Vec;  //���� ��ġ�� �ȷ����� �� LU station(��)�� ��ε����� �ð�(��)




	std::vector<Fixture> Fixture_vec;
	std::vector<Part> SelecPart; //���ȷ��� ���õ���Ʈ 


};

