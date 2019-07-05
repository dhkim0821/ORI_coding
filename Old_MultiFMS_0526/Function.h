//�����=====================================================================================================
#ifndef Function_h
#define Function_h
#include "stdafx.h"


using namespace std;

static vector<Pallet> PALLET; //Pallets in Buffer after Loading
static vector<Pallet> PALLET_temp_public; //A
static vector<Pallet> B;

static int LU1_State;  //0�޽��� 1��ŷ��, LU ���� State 
static int LU2_State;
static int LU3_State;
static int LU4_State;
static int M1_State;
static int M2_State;
static int M3_State;
static int Go_F_State;

class Initialize { //input data ����������� ������ class��
public:
	int Num_LU_Station;
	int Num_Machine;
	int Num_Parttype;
	int Part_Info_Size;
	int Num_Pallet;
	int Num_Dependency;
	int Num_Total_Part;
	int Num_Dependency_Pre;  //dependency��Ʈ����
	int Num_Dependency_Suc;  //dependency��Ʈ����
	int General_Parttype;    //general��Ʈ
	int LU_Time;

	int NumFixIn_P = 3;
	//Trnasportation time
	int **Transportation_Time;
	int TransTime;

	//Fixture Information on Pallet at each LU Station 
	int Num_Pallet_LU1;
	int Num_Pallet_LU2;
	int Num_Pallet_LU3;
	int Num_Pallet_LU4;
	std::vector<Pallet> PALLET_LU1;
	std::vector<Pallet> PALLET_LU2;
	std::vector<Pallet> PALLET_LU3;
	std::vector<Pallet> PALLET_LU4;


	//Machine available time
	std::vector<int> Machine_Schedule;

	//Part type�� information 
	Parttype * Part_Type;
	int Pcount = 0;  //total part count
	int Parttype_temp;
	int NumOperaton_temp;
	int Dependency_temp;
	int NumDemand_temp;
	int DueDate_temp;
	int NumMac_temp;
	std::string MacName_temp;
	int ProcessTime_temp;
	int MacNo_temp;

	//Part�� information
	Part * AllPart;
	Part * PART;
	int iter;   //total part count


	void InputData(int argc, _TCHAR* argv[]);


};


class Algorithm {
public:

	int PalletInSys;  //�ý��� �ȿ� �ִ� �ȷ�, ����CAPA�� ������  

	vector <Part> SelecParts_vec;

	//===

	int Total_Part_No;
	int NumPartLU; //��ü��Ʈ�� �� �ε������̼� ���� NumPartLU���� �й��Ŵ
	int reminder;  //������������ LU1�� ���Ƴ���

	Part * Part_LU1; //�� LU�� ������� ��Ʈ
	Part * Part_LU2;
	Part * Part_LU3;
	Part * Part_LU4;
	int NumPart_LU1; //      "     ��Ʈ ���� 
	int NumPart_LU2;
	int NumPart_LU3;
	int NumPart_LU4;

	vector<Part> Part_LU1_vec; //���ͷοű�
	vector<Part> Part_LU2_vec;
	vector<Part> Part_LU3_vec;
	vector<Part> Part_LU4_vec;


	//vector<Pallet> PALLET_temp; �������� �ؾߵɱ�? 
	vector <MatrixMax> Matrix_For_Max;  	//Matrix for Max Procceing Time
	MatrixMin MATRIX_DUE;  	//Matrix for Min Due Date
	MatrixMin MATRIX;  	//Matrix for Min Procceing Time


	void Palletizing(Initialize InitializeSystem);

};



//Time measure convertor
inline uint64_t CurrentTime_milliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

inline uint64_t CurrentTime_microseconds()
{
	return std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

inline uint64_t CurrentTime_nanoseconds()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void MACHINE1(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux);
void MACHINE2(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux);
void MACHINE3(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux);
auto MIN_PT1(int MinPT_M2, vector<int> mac2, vector<mac> MAC2_temp, vector<Pallet> Matrix_p, std::mutex& mux);
auto MIN_PT2(int MinPT_M2, vector<int> mac2, vector<mac> MAC2_temp, vector<Pallet> Matrix_p, std::mutex& mux);
auto MIN_PT3(int MinPT_M3, vector<int> mac3, vector<mac> MAC3_temp, vector<Pallet> Matrix_p, std::mutex& mux);
auto FIND_MIN_PT(Initialize InitializeSystem, vector<Pallet> PALLET_temp, MatrixMin MATRIX, vector<Pallet> B, std::mutex& mux); //�Ķ����(PALLET, PALLET_temp) ��ü�� �ٲ��� ���;ߵ�  //PALLET_temp(��ǲ������)
void Compare_Trans_vs_MaxPT(Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max,
	MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux);
auto FIND_MAX_PT(Initialize InitializeSystem, std::vector<Pallet> PALLET_temp, vector<MatrixMax> Matrix_For_Max, std::mutex& mux);
auto FIND_MIN_DUE(Initialize InitializeSystem, vector<Pallet> PALLET_temp, MatrixMin MATRIX_DUE, vector<Pallet> B, std::mutex& mux);




#endif Function_h



//auto comp = [](const Pallet& p1, const Pallet& p2) {return p1.Total_Pallet_No < p2.Total_Pallet_No; };
//sort(PALLET_temp_temp.begin(), PALLET_temp_temp.end(), comp); ����ü���� ���� ���� ���� �ڵ� 


