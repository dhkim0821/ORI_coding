//구조체====================================================================================================================
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
#include <tuple>    //함수구조체리턴

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
	int Pre_PT; //남은시간 저장 후 New_Matrix에서 비교 ?
	Depend * Depend;  /* -1:Dependency선행/0:dependency후행 */

	int TrasnPoint;

	std::vector<int> Mac_Schedule;
};

struct Operation {
	int Operation_No;
	int Num_AlterMac;

	int State; //1:가공중, 0:노는중 
	int Complete;  //1:가공완료, 0:아직완료안됨.  머신선택되면 1로 바뀜(그래야중복x)
	int Current_PT;

	std::vector<long long> MAC1_Start_vec;
	std::vector<long long> MAC1_End_vec;
	std::vector<long long> MAC2_Start_vec;
	std::vector<long long> MAC2_End_vec;
	std::vector<long long> MAC3_Start_vec;
	std::vector<long long> MAC3_End_vec;


	Alternative_MAC * Mac; //대안머신
	Alternative_MAC * SelectedMac; //대안머신
};

struct DependPart {    //Part에서  dependency파트만 따로 분류 
	//인풋데이터 받을때 쓰는 부분 
	int PartType;
	int NumDemand;
	int NumOperation;
	Part * Demand;
	Operation * Oper;

	int Dependency;   /* -1:Dependency선행/0:dependency후행/-2:일반파트 */

	//인풋데이터 가공후 쓰는부분 
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
	int Dependency;   /* -1:Dependency선행/0:dependency후행/-2:일반파트 */
	DependPart * Dependency_Suc; /* -1:Dependency선행/0:dependency후행/-2:일반파트 */
	Part * Demand;
	Operation * Oper;
};

struct Part {
	int Part_No;   //파트타입별 파트번호 
	int Total_Part_No; //모든파트줄세워 놨을때의 파트번호
	int Part_Type;
	int Dependency;
	DependPart * Depend; /* -1:Dependency선행/0:dependency후행/-2:일반파트 */

	int Num_Operation;
	int Due_Date;
	int LD_Station;
	int ULD_Station;

	int State; //1:가공중, 0:노는중 
	int Complete;  //1:가공완료, 0:아직완료안됨
	int OP_idx; //현재 OP몇번 작업중이고, 다음 OP몇번인지 식별 

	Operation * Oper;

	int LD_Time;
	int ULD_Time;
	int Trans_Time;
	int Process_Time;
	int Waiting_Time;

};
//모든파트(팔렛타이징전) -> 선택된파트(팔렛타이징후)에 사용 

struct Fixture {
	int Fixture_No;
	int Pallet_No;
};


//------------------------------ line 134~178 안쓰는거 나중에 정리 
//for Maximum Processing Time : line 107~133
struct mac {
	int mac_no;
	int processing_time;
	int PT_Trans_Time; //가공+이동시간
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
	int State;  //1:일하는중, 0:놀고있음
	int Complete;  //1:가공완료, 0:아직완료안됨


	std::vector<long long> LD_Start_vec;
	std::vector<long long> LD_End_vec;

	std::vector<long long> ULD_Start_vec;
	std::vector<long long> ULD_End_vec;
	std::vector<LU_Time> LU_Timetable;

	LU_Time LU1;
	LU_Time LU2;
	LU_Time LU3;
	LU_Time LU4;


	//std::vector<std::vector<long long>> LD_Start_Vec;  //팔렛별로 각 LU station(행)에 로딩시작 시간(열) 
	//std::vector<std::vector<long long>> LD_End_Vec;  //같은 위치에 팔렛별로 각 LU station(행)에 로딩끝난 시간(열)

	//std::vector<std::vector<long long>> ULD_Start_Vec;  //팔렛별로 각 LU station(행)에 언로딩시작 시간(열) 
	//std::vector<std::vector<long long>> ULD_End_Vec;  //같은 위치에 팔렛별로 각 LU station(행)에 언로딩끝난 시간(열)




	std::vector<Fixture> Fixture_vec;
	std::vector<Part> SelecPart; //각팔렛에 선택된파트 


};

