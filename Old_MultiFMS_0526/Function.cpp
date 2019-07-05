//구현부=====================================================================================================
#include "stdafx.h"
#include "Function.h"

using namespace std;

void Initialize::InputData(int argc, _TCHAR* argv[])
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	fin >> Num_LU_Station;
	fin >> Num_Machine;
	fin >> Part_Info_Size;
	fin >> Num_Parttype;
	fin >> Num_Pallet;
	fin >> Num_Dependency;
	fin >> Num_Total_Part;
	fin >> Num_Dependency_Pre; //dependency선행 
	fin >> Num_Dependency_Suc; //dependency후행
	fin >> LU_Time;


	//Transportation time
	int Trans_temp;
	fin >> Trans_temp;
	TransTime = Trans_temp * 3; //머신간이동시간

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

	// pallets with fixture types at LU_Station1
	fin >> Num_Pallet_LU1;
	//cout << "LU1-";
	PALLET_LU1.resize(Num_Pallet_LU1);
	for (int i = 0; i < Num_Pallet_LU1; i++)
	{
		PALLET_LU1[i].Pallet_No = i + 1;
		PALLET_LU1[i].LU_Station = 1;
		PALLET_LU1[i].Current_Position = 0;
		PALLET_LU1[i].State = 0;
		PALLET_LU1[i].Complete = 0;
		//PALLET_LU1[i].LU_Timetable.resize(4);

	/*	PALLET_LU1[i].LU1.LD_Start_vec.resize(100);
		PALLET_LU1[i].LU2.LD_Start_vec.resize(100);
		PALLET_LU1[i].LU3.LD_Start_vec.resize(100);
		PALLET_LU1[i].LU4.LD_Start_vec.resize(100);

		PALLET_LU1[i].LU1.ULD_Start_vec.resize(100);
		PALLET_LU1[i].LU2.ULD_Start_vec.resize(100);
		PALLET_LU1[i].LU3.ULD_Start_vec.resize(100);
		PALLET_LU1[i].LU4.ULD_Start_vec.resize(100);*/

		PALLET_LU1[i].Fixture_vec.resize(NumFixIn_P);

		int FixNo_temp;
		for (int j = 0; j < NumFixIn_P; j++)
		{
			fin >> FixNo_temp;
			PALLET_LU1[i].Fixture_vec[j].Fixture_No = FixNo_temp;
			PALLET_LU1[i].Fixture_vec[j].Pallet_No = PALLET_LU1[i].Pallet_No;
			//cout << PALLET_LU1[i].Fixture_vec[j].Fixture_No << " ";
		}
	}
	/*for (int i = 0; i < Num_Pallet_LU1; i++)
	{
	   cout << PALLET_LU1[i].Pallet_No << " " << PALLET_LU1[i].LU_Station << endl;

	   for (int j = 0; j < PALLET_LU1[i].Fixture_vec.size(); j++)
	   {
		  cout << PALLET_LU1[i].Fixture_vec[j].Fixture_No << " ";
	   }
	   cout << endl;
	}*/


	// pallets with fixture types at LU_Station2
	fin >> Num_Pallet_LU2;
	//cout << "LU2-";
	PALLET_LU2.resize(Num_Pallet_LU2);
	for (int i = 0; i < Num_Pallet_LU2; i++)
	{
		PALLET_LU2[i].Pallet_No = i + 1;
		PALLET_LU2[i].LU_Station = 2;
		PALLET_LU2[i].Current_Position = 0;
		PALLET_LU2[i].State = 0;
		PALLET_LU2[i].Complete = 0;
		//PALLET_LU2[i].LU_Timetable.resize(4);

		/*PALLET_LU2[i].LU1.LD_Start_vec.resize(100);
		PALLET_LU2[i].LU2.LD_Start_vec.resize(100);
		PALLET_LU2[i].LU3.LD_Start_vec.resize(100);
		PALLET_LU2[i].LU4.LD_Start_vec.resize(100);

		PALLET_LU2[i].LU1.ULD_Start_vec.resize(100);
		PALLET_LU2[i].LU2.ULD_Start_vec.resize(100);
		PALLET_LU2[i].LU3.ULD_Start_vec.resize(100);
		PALLET_LU2[i].LU4.ULD_Start_vec.resize(100);*/

		PALLET_LU2[i].Fixture_vec.resize(NumFixIn_P);

		int FixNo_temp;
		for (int j = 0; j < NumFixIn_P; j++)
		{
			fin >> FixNo_temp;
			PALLET_LU2[i].Fixture_vec[j].Fixture_No = FixNo_temp;
			PALLET_LU2[i].Fixture_vec[j].Pallet_No = PALLET_LU2[i].Pallet_No;
			//cout << PALLET_LU2[i].Fixture_vec[j].Fixture_No << " ";

		}
	}


	// pallets with fixture types at LU_Station3
	fin >> Num_Pallet_LU3;
	//cout << "LU3-";
	PALLET_LU3.resize(Num_Pallet_LU3);
	for (int i = 0; i < Num_Pallet_LU3; i++)
	{
		PALLET_LU3[i].Pallet_No = i + 1;
		PALLET_LU3[i].LU_Station = 3;
		PALLET_LU3[i].Current_Position = 0;
		PALLET_LU3[i].State = 0;
		PALLET_LU3[i].Complete = 0;
		//PALLET_LU3[i].LU_Timetable.resize(4);
		/*PALLET_LU3[i].LU1.LD_Start_vec.resize(100);
		PALLET_LU3[i].LU2.LD_Start_vec.resize(100);
		PALLET_LU3[i].LU3.LD_Start_vec.resize(100);
		PALLET_LU3[i].LU4.LD_Start_vec.resize(100);

		PALLET_LU3[i].LU1.ULD_Start_vec.resize(100);
		PALLET_LU3[i].LU2.ULD_Start_vec.resize(100);
		PALLET_LU3[i].LU3.ULD_Start_vec.resize(100);
		PALLET_LU3[i].LU4.ULD_Start_vec.resize(100);*/

		PALLET_LU3[i].Fixture_vec.resize(NumFixIn_P);

		int FixNo_temp;
		for (int j = 0; j < NumFixIn_P; j++)
		{
			fin >> FixNo_temp;
			PALLET_LU3[i].Fixture_vec[j].Fixture_No = FixNo_temp;
			PALLET_LU3[i].Fixture_vec[j].Pallet_No = PALLET_LU3[i].Pallet_No;
			//cout << PALLET_LU3[i].Fixture_vec[j].Fixture_No << " ";

		}
	}


	// pallets with fixture types at LU_Station4
	fin >> Num_Pallet_LU4;
	//cout << "LU4-";
	PALLET_LU4.resize(Num_Pallet_LU4);
	for (int i = 0; i < Num_Pallet_LU4; i++)
	{
		PALLET_LU4[i].Pallet_No = i + 1;
		PALLET_LU4[i].LU_Station = 4;
		PALLET_LU4[i].Current_Position = 0;
		PALLET_LU4[i].State = 0;
		PALLET_LU4[i].Complete = 0;
		//PALLET_LU4[i].LU_Timetable.resize(4);
		/*PALLET_LU4[i].LU1.LD_Start_vec.resize(100);
		PALLET_LU4[i].LU2.LD_Start_vec.resize(100);
		PALLET_LU4[i].LU3.LD_Start_vec.resize(100);
		PALLET_LU4[i].LU4.LD_Start_vec.resize(100);

		PALLET_LU4[i].LU1.ULD_Start_vec.resize(100);
		PALLET_LU4[i].LU2.ULD_Start_vec.resize(100);
		PALLET_LU4[i].LU3.ULD_Start_vec.resize(100);
		PALLET_LU4[i].LU4.ULD_Start_vec.resize(100);*/

		PALLET_LU4[i].Fixture_vec.resize(NumFixIn_P);

		int FixNo_temp;
		for (int j = 0; j < NumFixIn_P; j++)
		{
			fin >> FixNo_temp;
			PALLET_LU4[i].Fixture_vec[j].Fixture_No = FixNo_temp;
			PALLET_LU4[i].Fixture_vec[j].Pallet_No = PALLET_LU4[i].Pallet_No;
			//cout << PALLET_LU4[i].Fixture_vec[j].Fixture_No << " ";

		}
	}
	cout << endl;

	//Machine available time(Machine schedule)
	int Mac_temp;
	for (int i = 0; i < 1000; i++)
	{
		fin >> Mac_temp;
		Machine_Schedule.push_back(Mac_temp);

		if (Mac_temp == -1)
		{
			break;
		}
	}


	//Information about "PART TYPE"
	Part_Type = new Parttype[Num_Parttype];
	for (int i = 0; i < Num_Parttype; i++)  //일반 + 선행 
	{
		fin >> Parttype_temp;
		Part_Type[i].PartType = Parttype_temp;

		fin >> NumOperaton_temp;
		Part_Type[i].NumOperation = NumOperaton_temp;

		fin >> Dependency_temp;
		Part_Type[i].Dependency = Dependency_temp;

		fin >> NumDemand_temp;
		Part_Type[i].NumDemand = NumDemand_temp;
		Part_Type[i].Demand = new Part[NumDemand_temp];
		for (int j = 0; j < NumDemand_temp; j++)
		{
			Pcount++;  //total part count
			fin >> DueDate_temp;
			Part_Type[i].Demand[j].Due_Date = DueDate_temp;
			Part_Type[i].Demand[j].Part_No = j + 1;
			Part_Type[i].Demand[j].Total_Part_No = Pcount;
		}
		Part_Type[i].Oper = new Operation[NumOperaton_temp];
		for (int j = 0; j < NumOperaton_temp; j++)
		{
			fin >> NumMac_temp;
			Part_Type[i].Oper[j].Num_AlterMac = NumMac_temp;
			Part_Type[i].Oper[j].Mac = new Alternative_MAC[Part_Type[i].Oper[j].Num_AlterMac];

			for (int k = 0; k < Part_Type[i].Oper[j].Num_AlterMac; k++)
			{
				fin >> MacName_temp;
				Part_Type[i].Oper[j].Mac[k].Mac_Name = MacName_temp;
				fin >> ProcessTime_temp;
				Part_Type[i].Oper[j].Mac[k].Processing_Time = ProcessTime_temp;
				Part_Type[i].Oper[j].Mac[k].Pre_PT = 0;
				fin >> MacNo_temp;
				Part_Type[i].Oper[j].Mac[k].Mac_No = MacNo_temp;

			}
		}
	}

	for (int i = 0; i < Num_Dependency_Suc; i++) //후행 
	{
		Part_Type[i].Dependency_Suc = new DependPart[1];
		for (int j = 0; j < 1; j++)
		{
			fin >> Parttype_temp;
			Part_Type[i].Dependency_Suc[j].PartType = Parttype_temp;

			fin >> NumOperaton_temp;
			Part_Type[i].Dependency_Suc[j].NumOperation = NumOperaton_temp;

			fin >> Dependency_temp;
			Part_Type[i].Dependency_Suc[j].Dependency = Dependency_temp;

			fin >> NumDemand_temp;
			Part_Type[i].Dependency_Suc[j].NumDemand = NumDemand_temp;
			Part_Type[i].Dependency_Suc[j].Demand = new Part[NumDemand_temp];
			for (int k = 0; k < NumDemand_temp; k++)
			{
				//Pcount++;  //total part count
				fin >> DueDate_temp;
				Part_Type[i].Dependency_Suc[j].Demand[k].Due_Date = DueDate_temp;
				Part_Type[i].Dependency_Suc[j].Demand[k].Part_No = j + 1;
				Part_Type[i].Dependency_Suc[j].Demand[k].Total_Part_No = Part_Type[i].Demand[k].Total_Part_No;
			}
			Part_Type[i].Dependency_Suc[j].Oper = new Operation[NumOperaton_temp];
			for (int h = 0; h < NumOperaton_temp; h++)
			{
				fin >> NumMac_temp;
				Part_Type[i].Dependency_Suc[j].Oper[h].Num_AlterMac = NumMac_temp;
				Part_Type[i].Dependency_Suc[j].Oper[h].Mac = new Alternative_MAC[NumMac_temp];
				for (int w = 0; w < NumMac_temp; w++)
				{
					fin >> MacName_temp;
					Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Mac_Name = MacName_temp;
					fin >> ProcessTime_temp;
					Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Processing_Time = ProcessTime_temp;
					Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Pre_PT = 0;
					fin >> MacNo_temp;
					Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Mac_No = MacNo_temp;
				}
			}
		}
	}

	//인풋데이터 출력 (일반+선행파트)
	/*for (int i = 0; i < Num_Parttype; i++)
	{
		cout << Part_Type[i].PartType << " " << Part_Type[i].NumOperation << " " << Part_Type[i].Dependency << endl;
		for (int j = 0; j < Part_Type[i].NumDemand; j++)
		{
			cout << Part_Type[i].Demand[j].Due_Date << " ";
		}
		cout << endl;
		for (int j = 0; j < Part_Type[i].NumOperation; j++)
		{
			cout << Part_Type[i].Oper[j].Num_AlterMac << " ";
			for (int k = 0; k < Part_Type[i].Oper[j].Num_AlterMac; k++)
			{
				cout << Part_Type[i].Oper[j].Mac[k].Mac_Name << " "
					<< Part_Type[i].Oper[j].Mac[k].Processing_Time << " "
					<< Part_Type[i].Oper[j].Mac[k].Mac_No << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;*/

	//인풋데이터 출력 (후행파트)
	/*for (int i = 0; i < Num_Dependency_Suc; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			cout << Part_Type[i].Dependency_Suc[j].PartType << " "
				<< Part_Type[i].Dependency_Suc[j].NumOperation << " "
				<< Part_Type[i].Dependency_Suc[j].Dependency << endl;
			cout << Part_Type[i].Dependency_Suc[j].NumDemand << endl;

			for (int k = 0; k < Part_Type[i].Dependency_Suc[j].NumDemand; k++)
			{
				cout << Part_Type[i].Dependency_Suc[j].Demand[k].Due_Date << " ";
			}
			cout << endl;
			for (int h = 0; h < Part_Type[i].Dependency_Suc[j].NumOperation; h++)
			{

				cout << Part_Type[i].Dependency_Suc[j].Oper[h].Num_AlterMac << " ";

				for (int w = 0; w < Part_Type[i].Dependency_Suc[j].Oper[h].Num_AlterMac; w++)
				{
					cout << Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Mac_Name << " "
						<< Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Processing_Time << " "
						<< Part_Type[i].Dependency_Suc[j].Oper[h].Mac[w].Mac_No << " ";
				}
				cout << endl;
			}
		}
	}*/


	/*cout << "일반 + 선행 + 후행 파트------- " << endl;
	for (int i = 0; i < Num_Parttype; i++) //일반+선행+후행
	{
		cout << Part_Type[i].PartType << " " << Part_Type[i].NumOperation << " " << Part_Type[i].Dependency << endl;
		cout << Part_Type[i].NumDemand << endl;
		if (Part_Type[i].Dependency == -1)
		{
			cout << Part_Type[i].Dependency_Suc[0].PartType << " " << Part_Type[i].Dependency_Suc[0].NumOperation << " "
				<< Part_Type[i].Dependency_Suc[0].Dependency <<  " (후행 파트타입넘버, 오퍼수, 디펜던시)" << endl;
			cout << Part_Type[i].Dependency_Suc[0].NumDemand << "(후행 파트수)" << endl;
		}
		for (int j = 0; j < Part_Type[i].NumDemand; j++)
		{
			cout << Part_Type[i].Demand[j].Due_Date << endl;
			if (Part_Type[i].Dependency == -1)
			{
				cout <<  Part_Type[i].Dependency_Suc[0].Demand[j].Due_Date << " (후행 납기)" << endl;
			}
		}
		for (int j = 0; j < Part_Type[i].NumOperation; j++)
		{
			cout << Part_Type[i].Oper[j].Num_AlterMac << endl;
			if (Part_Type[i].Dependency == -1)
			{
				cout << Part_Type[i].Dependency_Suc[0].Oper[j].Num_AlterMac << " (후행 머신수)" << endl ;
			}

			for (int k = 0; k < Part_Type[i].Oper[j].Num_AlterMac; k++)
			{
				cout << Part_Type[i].Oper[j].Mac[k].Mac_Name << " "
					<< Part_Type[i].Oper[j].Mac[k].Processing_Time << " "
					<< Part_Type[i].Oper[j].Mac[k].Mac_No << endl;
				if (Part_Type[i].Dependency == -1)
				{
					cout  << Part_Type[i].Dependency_Suc[0].Oper[j].Mac[k].Mac_Name << " "
						<< Part_Type[i].Dependency_Suc[0].Oper[j].Mac[k].Processing_Time << " "
						<< Part_Type[i].Dependency_Suc[0].Oper[j].Mac[k].Mac_No <<  "후행 머신이름, 가공시간, 머신번호" <<endl;
				}
			}
			cout << endl;
		}
	}*/



	//Information about "All PART"
	AllPart = new Part[Num_Total_Part - (Num_Dependency / 2)];
	iter = 0; //total part count
	for (int i = 0; i < Num_Parttype; i++)
	{
		for (int j = 0; j < Part_Type[i].NumDemand; j++)
		{
			AllPart[iter].Total_Part_No = iter + 1;  //전체파트번호 
			AllPart[iter].Part_Type = Part_Type[i].PartType; //파트타입번호 
			AllPart[iter].Part_No = Part_Type[i].Demand[j].Part_No;  //파트타입내에서 파트번호 
			AllPart[iter].Dependency = Part_Type[i].Dependency;
			AllPart[iter].Due_Date = Part_Type[i].Demand[j].Due_Date;
			AllPart[iter].Num_Operation = Part_Type[i].NumOperation;
			AllPart[iter].Complete = 0;  //작업아직안함0, 끝나면1
			AllPart[iter].State = 0; //1:가공중, 0:노는중 
			AllPart[iter].OP_idx = 0;

			AllPart[iter].Oper = new Operation[AllPart[iter].Num_Operation];
			for (int k = 0; k < Part_Type[i].NumOperation; k++)
			{
				AllPart[iter].Oper[k].Operation_No = k + 1;
				AllPart[iter].Oper[k].Complete = 0; //작업아직안함0, 끝나면1
				AllPart[iter].Oper[k].State = 0;  //1:가공중, 0:노는중 
				AllPart[iter].Oper[k].Num_AlterMac = Part_Type[i].Oper[k].Num_AlterMac;

				AllPart[iter].Oper[k].Mac = new Alternative_MAC[AllPart[iter].Oper[k].Num_AlterMac];
				AllPart[iter].Oper[k].SelectedMac = new Alternative_MAC[1];
				for (int h = 0; h < AllPart[iter].Oper[k].Num_AlterMac; h++)
				{
					AllPart[iter].Oper[k].Mac[h].Mac_Name = Part_Type[i].Oper[k].Mac[h].Mac_Name;
					AllPart[iter].Oper[k].Mac[h].Processing_Time = Part_Type[i].Oper[k].Mac[h].Processing_Time;
					AllPart[iter].Oper[k].Mac[h].Mac_No = Part_Type[i].Oper[k].Mac[h].Mac_No;
					if (AllPart[iter].Dependency == -1)
					{
						AllPart[iter].Oper[k].Mac[h].Depend = new Depend[1];
						AllPart[iter].Oper[k].Mac[h].Depend[0].Dependency = AllPart[iter].Dependency;
					}
				}
			}

			if (AllPart[iter].Dependency == -1) //dependency 후행파트의 정보  
			{
				AllPart[iter].Depend = new DependPart[1];

				AllPart[iter].Depend[0].Total_Part_No = iter + 1;  //전체파트번호 
				AllPart[iter].Depend[0].Part_Type = Part_Type[i].Dependency_Suc[0].PartType; //파트타입번호 
				AllPart[iter].Depend[0].Part_No = Part_Type[i].Dependency_Suc[0].Demand[j].Part_No;  //파트타입내에서 파트번호 
				AllPart[iter].Depend[0].Dependency = Part_Type[i].Dependency_Suc[0].Dependency;
				AllPart[iter].Depend[0].Due_Date = Part_Type[i].Dependency_Suc[0].Demand[j].Due_Date;
				AllPart[iter].Depend[0].Num_Operation = Part_Type[i].Dependency_Suc[0].NumOperation;
				AllPart[iter].Depend[0].state = 0;
				AllPart[iter].Depend[0].OP_idx = 0;

				AllPart[iter].Depend[0].Oper = new Operation[AllPart[iter].Depend[0].Num_Operation];
				for (int k = 0; k < AllPart[iter].Depend[0].Num_Operation; k++)
				{
					AllPart[iter].Depend[0].Oper[k].Operation_No = k + 1;
					AllPart[iter].Depend[0].Oper[k].Complete = 0;
					AllPart[iter].Depend[0].Oper[k].Num_AlterMac = Part_Type[i].Dependency_Suc[0].Oper[k].Num_AlterMac;

					AllPart[iter].Depend[0].Oper[k].Mac = new Alternative_MAC[Part_Type[i].Dependency_Suc[0].Oper[k].Num_AlterMac];
					AllPart[iter].Depend[0].Oper[k].SelectedMac = new Alternative_MAC[1];
					for (int h = 0; h < AllPart[iter].Depend[0].Oper[k].Num_AlterMac; h++)
					{
						AllPart[iter].Depend[0].Oper[k].Mac[h].Mac_Name = Part_Type[i].Dependency_Suc[0].Oper[k].Mac[h].Mac_Name;
						AllPart[iter].Depend[0].Oper[k].Mac[h].Processing_Time = Part_Type[i].Dependency_Suc[0].Oper[k].Mac[h].Processing_Time;
						AllPart[iter].Depend[0].Oper[k].Mac[h].Mac_No = Part_Type[i].Dependency_Suc[0].Oper[k].Mac[h].Mac_No;

						/*AllPart[iter].Depend[0].Oper[k].Mac[h].Depend = new Depend[1];
						AllPart[iter].Depend[0].Oper[k].Mac[h].Depend[0].Dependency = AllPart[iter].Depend[0].Dependency;
						cout << AllPart[iter].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << endl; */
					}
				}
			}
			iter++;
		}
	}

	//AllPart 출력 
	/*cout << "Information about All PART" << endl;
	for (int i = 0; i < Num_Total_Part - (Num_Dependency / 2); i++)
	{
		cout << "Part" << AllPart[i].Total_Part_No << " ";
		cout << "type" << AllPart[i].Part_Type << " ";
		cout << AllPart[i].Num_Operation << " ";
		cout << AllPart[i].Dependency << endl;
		cout << AllPart[i].Due_Date << " (";
		cout << AllPart[i].state << " ";
		cout << AllPart[i].OP_idx << ")" << endl;
		for (int k = 0; k < AllPart[i].Num_Operation; k++)
		{
			cout << AllPart[i].Oper[k].Operation_No << " " << AllPart[i].Oper[k].state
				<< " " << AllPart[i].Oper[k].Num_AlterMac << " ";
			for (int h = 0; h < AllPart[i].Oper[k].Num_AlterMac; h++)
			{
				cout << AllPart[i].Oper[k].Mac[h].Mac_Name << " " << AllPart[i].Oper[k].Mac[h].Processing_Time << " "
					<< AllPart[i].Oper[k].Mac[h].Mac_No << " ";
			}
			cout << endl;
		}
		if (AllPart[i].Dependency == -1)
		{
			cout << "(Dependency) Part" << AllPart[i].Depend[0].Total_Part_No << " ";
			cout << "type" << AllPart[i].Depend[0].Part_Type << " ";
			cout << AllPart[i].Depend[0].Part_No << " ";
			cout << AllPart[i].Depend[0].Dependency << endl;
			cout << AllPart[i].Depend[0].Due_Date << " (";
			cout << AllPart[i].Depend[0].state << " ";
			cout << AllPart[i].Depend[0].OP_idx << ")" << endl;
			for (int k = 0; k < AllPart[i].Depend[0].Num_Operation; k++)
			{
				cout << AllPart[i].Oper[k].Operation_No << " " << AllPart[i].Oper[k].state
					<< " " << AllPart[i].Oper[k].Num_AlterMac << " ";

				for (int h = 0; h < AllPart[i].Depend[0].Oper[k].Num_AlterMac; h++)
				{
					cout << AllPart[i].Depend[0].Oper[k].Mac[h].Mac_Name << " " << AllPart[i].Depend[0].Oper[k].Mac[h].Processing_Time << " "
						<< AllPart[i].Depend[0].Oper[k].Mac[h].Mac_No << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}*/




	/*AllPart[iter].Depend = new DependPart[];
		for (int d = 0; d < Num_Dependency; d++)
		{

		}*/
		//AllPart[iter].Depnedency = Part_Type[i].Depnedency;
	/*PALLET_temp[pallet][전체part][oper][mac][dependency]
	[dependency] 인덱스는 [0] 선행, [1] 후행 으로 size()는 2.
	[전체part]는
	1 2 -1
	1 2 -1
	1 2 -1
	1 2 0
	1 2 0
	1 2 0
	2 2 -2
	2 2 -2
	2 2 -2
	3 3 -2
	일 경우 올라간 파트 개수 7개. 1번 dependency파트타입의 정보는 묶음임*/

	//인풋데이터는 dependency 상관없이 중구난방하게 받았지만 PALLET_temp에서 위처럼 5차원 배열 or벡터로 가공되어야 함
	//dependency part는 하나의 파트를 두번 가공하는 경우이기 때문에 팔렛타이징되면 시스템안에서 dependency 선행작업인지, 후행작업인지 판단하여 가공된다. 
	//지금은 총 10개 파트가 올라갔지만 사실 7개가 올라간것임. 오퍼레이션처럼 디펜던시도 있는것임 


}

bool Max_PT1(const mac &PT1, const mac &PT2) {//매트릭스상에서 최대 가공시간  
	if (PT1.processing_time > PT2.processing_time)
	{
		return true;
	}
	else if (PT1.processing_time == PT2.processing_time)
	{
		return PT1.processing_time > PT2.processing_time;
	}
	else
	{
		return false;
	}
};


auto FIND_MAX_PT(Initialize InitializeSystem, std::vector<Pallet> PALLET_temp, vector<MatrixMax> Matrix_For_Max, std::mutex& mux) //함수재활용 = 파라미터 맞추기 ★★머신에서 가공 하나 끝나면 PALLET, PALLET_temp에 바뀐데이터 업데이트 
{
	mux.lock();
	cout << "------------Find Maximum Operation Processing Time --------------" << endl;
	mux.unlock();


	cout << "PALLET_temp size" << PALLET_temp.size() << endl;
	cout << "PALLET size " << PALLET.size() << endl;

	Matrix_For_Max.resize(PALLET_temp.size());  //다시 매트릭스 부를때 파라미터로 그때그때 상황에 맞는 PALLET,PALLET_temp( std::vector<Pallet> PALLET )형태로 무조건 바꿔서 집어넣어야되 ★★

	mux.lock();
	cout << "Matrix 팔렛 size?" << Matrix_For_Max.size() << endl;
	mux.unlock();


	for (int i = 0; i < Matrix_For_Max.size(); i++)  // Matrix_For_Max (그때그때 생성되는 매트릭스) : PALLET_temp (인풋데이터)
	{
		//이부분이 B에 팔렛 다시 집어넣는부분 PALLET_temp[i].State ==1 인것들은 들어가면 안된다.  
		Matrix_For_Max[i].pallet_no = PALLET_temp[i].Total_Pallet_No;
		Matrix_For_Max[i].part = new part[PALLET_temp[i].SelecPart.size()];
		mux.lock();
		cout << "[Pallet" << Matrix_For_Max[i].pallet_no << "]" << endl;
		mux.unlock();

		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			Matrix_For_Max[i].part[j].part_no = PALLET_temp[i].SelecPart[j].Total_Part_No;
			Matrix_For_Max[i].part[j].op_index = PALLET_temp[i].SelecPart[j].OP_idx;

			mux.lock();
			cout << "Part" << Matrix_For_Max[i].part[j].part_no << endl;
			mux.unlock();

			int OP_index = Matrix_For_Max[i].part[j].op_index;   // 여기서부터 OP_index ★★ PALLET_temp[i].SelecPart[j].OP_idx  : 오퍼레이션 하나 끝나면 +1 증가시켜줘야함			

			Matrix_For_Max[i].part[j].op.resize(OP_index + 1);
			for (int k = 0; k < OP_index + 1; k++)
			{
				Matrix_For_Max[i].part[j].op[OP_index].op_no = PALLET_temp[i].SelecPart[j].Oper[OP_index].Operation_No;
				mux.lock();
				cout << "OP" << Matrix_For_Max[i].part[j].op[OP_index].op_no << " ";
				mux.unlock();

				int temp_num_op_mac = PALLET_temp[i].SelecPart[j].Oper[OP_index].Num_AlterMac;
				Matrix_For_Max[i].part[j].op[OP_index].mac = new mac[temp_num_op_mac];
				for (int h = 0; h < temp_num_op_mac; h++)
				{
					Matrix_For_Max[i].part[j].op[OP_index].mac[h].mac_no = PALLET_temp[i].SelecPart[j].Oper[OP_index].Mac[h].Mac_No;
					Matrix_For_Max[i].part[j].op[OP_index].mac[h].processing_time = PALLET_temp[i].SelecPart[j].Oper[OP_index].Mac[h].Processing_Time;
					mux.lock();
					cout << "mac" << PALLET_temp[i].SelecPart[j].Oper[OP_index].Mac[h].Mac_No << " "
						<< PALLET_temp[i].SelecPart[j].Oper[OP_index].Mac[h].Processing_Time << " ";
					mux.unlock();

				}
				cout << endl;
			}
		}

	}


	//Find Maximum Operation Processing Time
	vector <mac> temp_pallet(Matrix_For_Max.size());
	for (int i = 0; i < Matrix_For_Max.size(); i++)
	{
		int temp_num_part = PALLET_temp[i].SelecPart.size();
		if (temp_num_part > 0)
		{
			//cout << "[Pallet" << Matrix_For_Max[i].pallet_no << "]" << endl;

			vector <mac> temp_part(temp_num_part);
			for (int j = 0; j < temp_num_part; j++)
			{
				//cout << "Part" << Matrix_For_Max[i].part[j].part_no << endl;
				int OP_index = PALLET_temp[i].SelecPart[j].OP_idx;
				vector <mac> temp_op(OP_index + 1);
				for (int k = 0; k < OP_index + 1; k++)   // ★★★오퍼레이션 하나 끝날때 해당 파트 "PALLET[i].SelecPart[j].OP_idx+1" +1 더해줘야함★★★
				{
					//cout << "OP" << Matrix_For_Max[i].part[j].op[OP_index].op_no << ", ";
					int temp_num_op_mac = PALLET_temp[i].SelecPart[j].Oper[OP_index].Num_AlterMac;
					vector <mac> temp_mac(temp_num_op_mac);
					for (int h = 0; h < temp_num_op_mac; h++)
					{
						temp_mac[h] = Matrix_For_Max[i].part[j].op[OP_index].mac[h];
						temp_mac[h].op_no = Matrix_For_Max[i].part[j].op[OP_index].op_no;
						temp_mac[h].mac_no = Matrix_For_Max[i].part[j].op[OP_index].mac[h].mac_no;
						temp_mac[h].part_no = Matrix_For_Max[i].part[j].part_no;
						temp_mac[h].pallet_no = Matrix_For_Max[i].pallet_no;
						//cout << "mac" << temp_mac[h].mac_no << " " << temp_mac[h].processing_time << endl;
					}

					//만일 3개다 워킹중이라면? -> 오퍼레이션 하나라도 끝나야 매트릭스생성되므로 그럴일없음
					//working중인 1번 머신 지우기 
					for (vector<int>::size_type h = 0; h < temp_mac.size(); ) {
						if (temp_mac[h].mac_no == 1 && M1_State == 1) {
							temp_mac.erase(temp_mac.begin() + h);
						}
						else {
							h++;
						}
					}
					//working중인 2번 머신 지우기 
					for (vector<int>::size_type h = 0; h < temp_mac.size(); ) {
						if (temp_mac[h].mac_no == 2 && M2_State == 1) {
							temp_mac.erase(temp_mac.begin() + h);
						}
						else {
							h++;
						}
					}
					//working중인 3번 머신 지우기 
					for (vector<int>::size_type h = 0; h < temp_mac.size(); ) {
						if (temp_mac[h].mac_no == 3 && M3_State == 1) {
							temp_mac.erase(temp_mac.begin() + h);
						}
						else {
							h++;
						}
					}
					if (M1_State == 1 && M2_State == 1 && M3_State == 1)
					{
						cout << "이거걸리면 오퍼레이션 아직 안끝났는데 매트릭스 생성 된거임." << endl;
					}

					for (int h = 0; h < temp_mac.size(); h++)
					{
						//cout << "mac" << temp_mac[h].mac_no << " " << temp_mac[h].processing_time << " available" << endl;
					}
					sort(temp_mac.begin(), temp_mac.end(), Max_PT1);
					//cout << "                                (available mac중 max PT" << temp_mac[0].processing_time << " Mac" << temp_mac[0].mac_no << ") " << endl;
					temp_op[k] = temp_mac[0];
				}
				sort(temp_op.begin(), temp_op.end(), Max_PT1);
				//cout << "OP중 LPT" << temp_op[0].processing_time << endl;
				temp_part[j] = temp_op[0];
				if (temp_part.size() < 1)       //비어있는 팔렛에서 error떠서 
					temp_part[j].processing_time = 0;
			}
			sort(temp_part.begin(), temp_part.end(), Max_PT1);
			//cout << "파트중 LPT:" << temp_part[0].processing_time << endl;
			temp_pallet[i] = temp_part[0];
		}

		else
		{
			temp_pallet[i].processing_time = 1;  //비어있는 팔렛에서 error떠서 
		}
	}
	sort(temp_pallet.begin(), temp_pallet.end(), Max_PT1);

	mux.lock();
	cout << "팔렛중 LPT:" << temp_pallet[0].processing_time << " [Pallet" << temp_pallet[0].pallet_no << "] Part" << temp_pallet[0].part_no
		<< " OP" << temp_pallet[0].op_no << " Mac" << temp_pallet[0].mac_no << endl;
	mux.unlock();

	struct Max_PT {
		Initialize InitializeSystem; std::vector<mac>temp_pallet; std::vector<Pallet> PALLET_temp; vector<MatrixMax> Matrix_For_Max;
	};
	return Max_PT{ InitializeSystem, temp_pallet, PALLET_temp, Matrix_For_Max };
};


bool CMP_DUE(const mac &DUE1, const mac &DUE2) {//due date 비교함수 
	if (DUE1.due < DUE2.due)
	{
		return true;
	}
	else if (DUE1.due == DUE2.due)
	{
		return DUE1.due < DUE2.due;
	}
	else
	{
		return false;
	}
};



auto MIN_DUE1(int MinDue_M1, vector<mac> MAC1_temp, vector<Pallet> Matrix_d, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 
	if (M1_State == 0)
	{
		sort(MAC1_temp.begin(), MAC1_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M1에서 최소값:" << MAC1_temp[0].due << "(" << MAC1_temp[0].processing_time << ", " << MAC1_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC1_temp[0].pallet_no << "], P"
			<< MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //최소 납기 선택되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_d[i].Total_Pallet_No == MAC1_temp[0].pallet_no)
			{
				Matrix_d[i].State = 1;
			}
		}
	}
	struct Result1 { int MinDue_M1; vector<mac> MAC1_temp; vector<Pallet> Matrix_d; };
	return Result1{ MinDue_M1, MAC1_temp, Matrix_d };
};


auto MIN_DUE2(int MinDue_M2, vector<mac> MAC2_temp, vector<Pallet> Matrix_d, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 
	if (M2_State == 0)
	{
		sort(MAC2_temp.begin(), MAC2_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M2에서 최소값:" << MAC2_temp[0].due << "(" << MAC2_temp[0].processing_time << ", " << MAC2_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC2_temp[0].pallet_no << "], P"
			<< MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //최소 납기 선택되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_d[i].Total_Pallet_No == MAC2_temp[0].pallet_no)
			{
				Matrix_d[i].State = 1;
			}
		}
	}
	struct Result1 { int MinDue_M2; vector<mac> MAC2_temp; vector<Pallet> Matrix_d; };
	return Result1{ MinDue_M2, MAC2_temp, Matrix_d };
};



auto MIN_DUE3(int MinDue_M3, vector<mac> MAC3_temp, vector<Pallet> Matrix_d, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 
	if (M3_State == 0)
	{
		sort(MAC3_temp.begin(), MAC3_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M3에서 최소값:" << MAC3_temp[0].due << "(" << MAC3_temp[0].processing_time << ", " << MAC3_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC3_temp[0].pallet_no << "], P"
			<< MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //최소 납기 선택되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_d[i].Total_Pallet_No == MAC3_temp[0].pallet_no)
			{
				Matrix_d[i].State = 1;
			}
		}
	}
	struct Result1 { int MinDue_M3; vector<mac> MAC3_temp; vector<Pallet> Matrix_d; };
	return Result1{ MinDue_M3, MAC3_temp, Matrix_d };
};



auto FIND_MIN_DUE(Initialize InitializeSystem, vector<Pallet> PALLET_temp, MatrixMin MATRIX_DUE, std::mutex& mux)
{
	cout << "------------Find Earliest Due Date Part --------------" << endl;

	/*매트릭스조건
	PALLET_temp.size() => 실제들어오는 팔렛 개수
	SelecPart.size() => 실제 팔렛에 올라간 파트 개수
	NumMac => 시스템에서 총 머신개수

	가공시간에 이동시간 추가
	워킹중인 머신 제외시키기
	머신당 팔렛 하나씩만 선택
	파트 머신개수만큼 선택
	*/
	int NumMac = InitializeSystem.Num_Machine;   //머신개수
	int NumPallet; //팔렛개수 
	int MinDue_M1 = 0; //머신별 최소 납기 
	int MinDue_M2 = 0;
	int MinDue_M3 = 0;


	//인풋데이터 PALLET_temp 출력
	/*mux.lock();
	cout << "PALLET_temp 잘나오나 체크" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++) //PALLET_temp 잘나오나 체크
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]" << endl;
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "Part" << PALLET_temp[i].SelecPart[j].Total_Part_No << endl;
			cout << "Due Date" << PALLET_temp[i].SelecPart[j].Due_Date << endl;
			for (int k = 0; k < PALLET_temp[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "OP" << PALLET_temp[i].SelecPart[j].Oper[k].Operation_No << "-";
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "mac" << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " ";
					cout << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Processing_Time << " ";
				}cout << endl;
			}cout << endl;
		}
	}cout << endl << endl;
	mux.unlock();*/




	//1.인풋데이터 가공 
	int p = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {  // 사용중인(파트가 올라간) 팔렛 개수 세기
		if (PALLET_temp[i].SelecPart.size() > 0)
			p++;
	}

	NumPallet = p;   //사용중인 팔렛개수
	vector<Pallet> Matrix_d(p);  //사용중인 팔렛 개수만큼 벡터 선언후 인풋데이터 옮기고 

	int u = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {
		if (PALLET_temp[i].SelecPart.size() > 0)
		{
			Matrix_d[u] = PALLET_temp[i];
			u++;
		}
	}

	//2.매트릭스 생성 
	MATRIX_DUE.aryprocess = new int**[NumPallet];
	for (int x = 0; x < NumPallet; x++)
	{
		MATRIX_DUE.aryprocess[x] = new int *[NumPallet];
		for (int y = 0; y < Matrix_d[x].SelecPart.size(); y++)
		{
			MATRIX_DUE.aryprocess[x][y] = new int[NumMac];
		}
	}


	//3.매트릭스에 데이터 인풋 
	int part_count = 0; //파트개수 
	for (int i = 0; i < NumPallet; i++) {
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			part_count++;

			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
				MATRIX_DUE.aryprocess[i][j][v] = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
				//MATRIX_DUE.aryprocess[i][j][v] = Matrix_d[i].SelecPart[j].Due_Date;
				if (Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
				{
					MATRIX_DUE.aryprocess[i][j][v] = 0;
				}
			}
		}
	}


	//매트릭스 출력 (납기)
	cout << "(파트 별 납기)" << endl;
	for (int i = 0; i < NumPallet; i++) {
		cout << "[Pallet" << Matrix_d[i].Total_Pallet_No << "] ";
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			cout << "[P" << Matrix_d[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				for (int v = 0; v < Matrix_d[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; v++) {
					if (Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 1)
						cout << 0 << " ";
					else
						cout << Matrix_d[i].SelecPart[j].Due_Date << " ";
				}
			}
		}
		cout << endl;
	}


	//매트릭스 출력 (가공시간)
	mux.lock();
	cout << "(오퍼레이션 별 가공시간)" << endl;
	for (int i = 0; i < NumPallet; i++) {
		cout << "[Pallet" << Matrix_d[i].Total_Pallet_No << "] ";
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			cout << "[P" << Matrix_d[i].SelecPart[j].Total_Part_No << "] ";
			for (int v = 0; v < NumMac; v++) {
				cout << MATRIX_DUE.aryprocess[i][j][v] << " ";
				//cout << Matrix_d[i].SelecPart[j].Oper[0].Mac[v].Mac_No << " ";
			}
		}
		cout << endl;
	}
	mux.unlock();


	//4.이동시간 추가 
	mux.lock();
	cout << "Transportation time" << endl;
	for (int i = 0; i < NumMac + 1; i++) {
		for (int j = 0; j < NumMac + 1; j++)
			cout << InitializeSystem.Transportation_Time[i][j] << " ";
		cout << endl;
	}
	mux.unlock();

	mux.lock();
	cout << "(오퍼레이션 별 가공 + 이동시간)     ※비어있는 머신 999999" << endl;
	mux.unlock();

	int Trans;
	for (int i = 0; i < NumPallet; i++) {
		int Current_Position = Matrix_d[i].Current_Position; //현재 팔렛 위치. 오퍼레이션 하나 끝날때마다 팔렛 위치 (PALLET_temp[0].Current_Position) 바꿔줘야함★★

		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;  // OP index
				int Mac_Position = Matrix_d[i].SelecPart[j].Oper[0].Mac[v].Mac_No; //machine index

				//현재 포지션에서 각 머신의 포지션으로 가는 이동시간 계산 
				for (int i = 0; i < NumMac + 1; i++) {
					for (int j = 0; j < NumMac + 1; j++)
					{
						Trans = InitializeSystem.Transportation_Time[Current_Position][Mac_Position];  //현재 팔렛 위치 [i] , 각 머신들의 위치 [j]
					}
				}
				if (Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
					Trans = 999999;

				//가공시간 + 이동시간 
				mux.lock();
				cout << MATRIX_DUE.aryprocess[i][j][v] << " + ";
				cout << Trans << " = ";
				MATRIX_DUE.aryprocess[i][j][v] += Trans;
				cout << MATRIX_DUE.aryprocess[i][j][v] << " | ";
				mux.unlock();

			}
			cout << endl;
		}
	}


	vector <mac> MAC1_temp(part_count);
	vector <mac> MAC2_temp(part_count);
	vector <mac> MAC3_temp(part_count);

	vector <int> mac1;
	vector <int> mac2;
	vector <int> mac3;

	int a = 0;
	int b = 0;
	int c = 0;



	//working 중인 팔렛 test
	/*cout << "워킹중인 팔렛 888888" << endl;
	Matrix_p[0].State = 1;
	Matrix_p[2].State = 1;
	cout << "Pallet" << Matrix_p[0].Total_Pallet_No << "is working" << endl;
	cout << "Pallet" << Matrix_p[2].Total_Pallet_No << "is working" << endl;*/


	//5. working중인 팔렛 제외
	for (int i = 0; i < NumPallet; i++) {  //머신1 
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 0)
				{
					if (M1_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 1)  //머신이 놀고있고, 팔렛이 놀고 있고, 머신이 존재하면 데이터인풋 
					{
						int temp1 = MATRIX_DUE.aryprocess[i][j][v]; 	// 가공 + 이동시간 

						MAC1_temp[a].pallet_no = Matrix_d[i].Total_Pallet_No;  //최소납기가 어느 파트 어느오퍼레이션 인지 확인하기 위한거 
						MAC1_temp[a].part_no = Matrix_d[i].SelecPart[j].Total_Part_No;
						MAC1_temp[a].op_no = Matrix_d[i].SelecPart[j].OP_idx;
						MAC1_temp[a].mac_no = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;
						MAC1_temp[a].due = Matrix_d[i].SelecPart[j].Due_Date;
						MAC1_temp[a].processing_time = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC1_temp[a].PT_Trans_Time = temp1;
					}
					else if (M1_State == 1 || Matrix_d[i].State == 1 || Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == -1)
					{
						MAC1_temp[a].due = 888888;
						MAC1_temp[a].processing_time = 888888;
						MAC1_temp[a].PT_Trans_Time = 888888;  //머신이 일하고이썩나 팔렛이 일하고 있거나 머신이 비어있으면 Large number(888888) 넣어서 선택 되지 않도록 함
					}
					a++;
				}
			}
		}
	}

	//5. working중인 머신 제외 및 팔렛 중복선택 방지
	auto Result1 = MIN_DUE1(MinDue_M1, MAC1_temp, Matrix_d, mux);
	MinDue_M1 = Result1.MinDue_M1;
	MAC1_temp = Result1.MAC1_temp;  //MAC1_temp[0] : 선택된 팔렛,파트 및 납기 등 결과 저장되어 있음 
	Matrix_d = Result1.Matrix_d;
	mux.lock();
	//cout << "선택된 Part" << MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << " Due" << MAC1_temp[0].due << " (mac state" << M1_State << ")" << endl;
	cout << "(M1_State" << M1_State << ")" << endl;

	mux.unlock();



	for (int i = 0; i < NumPallet; i++) { //머신2
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 1)
				{
					if (M2_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 2)
					{

						int temp2 = MATRIX_DUE.aryprocess[i][j][v]; //가공시간 + 이동시간 들어있음 
						//mac2.push_back(temp2); //머신2 납기만 다 넣음

						MAC2_temp[b].pallet_no = Matrix_d[i].Total_Pallet_No; //최소가공시간이 어느 파트시간인지 확인하기 위한거 
						MAC2_temp[b].part_no = Matrix_d[i].SelecPart[j].Total_Part_No;
						MAC2_temp[b].op_no = Matrix_d[i].SelecPart[j].OP_idx;
						MAC2_temp[b].mac_no = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;
						MAC2_temp[b].due = Matrix_d[i].SelecPart[j].Due_Date;
						MAC2_temp[b].processing_time = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC2_temp[b].PT_Trans_Time = temp2;

					}
					else if (M2_State == 1 || Matrix_d[i].State == 1 || Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == -2)
					{
						MAC2_temp[b].due = 888888;
						MAC2_temp[b].processing_time = 888888;
						MAC2_temp[b].PT_Trans_Time = 888888;  //working중인 팔렛은 888888 
					}
					b++;
				}
			}
		}
	}
	auto Result2 = MIN_DUE2(MinDue_M2, MAC2_temp, Matrix_d, mux);
	MinDue_M2 = Result2.MinDue_M2;
	MAC2_temp = Result2.MAC2_temp;  //MAC1_temp[0] : 선택된 팔렛,파트 및 납기 등 결과 저장되어 있음 
	Matrix_d = Result2.Matrix_d;
	mux.lock();
	//cout << "선택된 Part" << MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << " Due" << MAC2_temp[0].due << " (mac state" << M2_State << ")" << endl;
	cout << "(M2_State" << M2_State << ")" << endl;
	mux.unlock();


	for (int i = 0; i < NumPallet; i++) {  //머신1 
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 2)
				{
					if (M3_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 3)
					{
						int temp3 = MATRIX_DUE.aryprocess[i][j][v]; 	//가공시간 + 이동시간 

						MAC3_temp[c].pallet_no = Matrix_d[i].Total_Pallet_No;  //최소납기가 어느 파트 어느오퍼레이션 인지 확인하기 위한거 
						MAC3_temp[c].part_no = Matrix_d[i].SelecPart[j].Total_Part_No;
						MAC3_temp[c].op_no = Matrix_d[i].SelecPart[j].OP_idx;
						MAC3_temp[c].mac_no = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;
						MAC3_temp[c].due = Matrix_d[i].SelecPart[j].Due_Date;
						MAC3_temp[c].processing_time = Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC3_temp[c].PT_Trans_Time = temp3;
					}
					else if (M3_State == 1 || Matrix_d[i].State == 1 || Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == -3)
					{
						MAC3_temp[c].due = 888888;
						MAC3_temp[c].processing_time = 888888;
						MAC3_temp[c].PT_Trans_Time = 888888;  //working중인 팔렛은 납기에 888888 넣어서 선택 되지 않도록 함
					}
					c++;
				}
			}
		}
	}

	//5. working중인 머신 제외 및 팔렛 중복선택 방지
	auto Result3 = MIN_DUE3(MinDue_M3, MAC3_temp, Matrix_d, mux);
	MinDue_M3 = Result3.MinDue_M3;
	MAC3_temp = Result3.MAC3_temp;  //MAC1_temp[0] : 선택된 팔렛,파트 및 납기 등 결과 저장되어 있음 
	Matrix_d = Result3.Matrix_d;  //Matrix_d : 팔렛 state
	mux.lock();
	//cout << "선택된 Part" << MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << " Due" << MAC3_temp[0].due << " (mac state" << M3_State << ")" << endl;
	cout << "(M3_State" << M3_State << ")" << endl;
	mux.unlock();



	/*PALLET_temp (A) 에서 선택된 팔렛만(state:1)  ->  (B) 로 이동
	PALLET_temp (A) 리스트에서 삭제
	 (B)는 머신에 투입후 오퍼레이션 하나 끝나면 끝난 팔렛 있는지, 있다면 몇개가 끝났는지 개수 확인후 (A)에 팔렛 들어온 순서대로 작업끝난팔렛 개수만큼 (B)로 끌고온다
														  , 없다면 오퍼레이션 끝난 팔렛을 (B) -> (A)가장 위로 이동 */

	mux.lock();
	if (B.size() == 0) //가장 초기에 B Matrix 생성 
	{
		//PALLET_temp (A) 에서 선택된 팔렛만(state:1)  ->  (B) 로 이동  ->  PALLET_temp (A) 리스트에서 삭제
		PALLET_temp = Matrix_d;
		cout << endl;
		cout << " PALLET_temp (A) 출력해보자 (size:" << PALLET_temp.size() << ")" << endl;
		for (int i = 0; i < PALLET_temp.size(); i++)
		{
			cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
			for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
			{
				cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			}
			cout << "(state:" << PALLET_temp[i].State << ") " << endl;

			if (PALLET_temp[i].State == 1)   //선택 팔렛은 (B)로 옮긴후 
			{
				B.push_back(PALLET_temp[i]);
			}
		}
		cout << endl;

		for (int i = 0; i < PALLET_temp.size(); i++)  // PALLET_temp (A) 에서 삭제 
		{
			if (PALLET_temp[i].State == 1)
			{
				PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
				i--;
			}
		}
	}

	else
		cout << "두번째부터 는 B안에서 min값만 찾아" << endl;

	mux.unlock();



	mux.lock();
	cout << " (B) 출력해보자 (size:" << B.size() << ")" << endl; // (B) 잘 옮겨졌는지 확인 
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << " (A) 삭제햇는데 지워졋나 (size:" << PALLET_temp.size() << ") - 함수 두번째 탈때부터는 B로 출력함" << endl; // (A) 잘 지워졌는지 확인 
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			/*for (int k = 0; PALLET_temp[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "O" << PALLET_temp[i].SelecPart[j].Oper[k].Operation_No << " ";
				for (int h = 0; PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "M" << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " ";
				}
			}*/
		}
		cout << "(state:" << PALLET_temp[i].State << ") " << endl;
	} cout << endl;
	mux.unlock();

	for (int i = 0; i < B.size(); i++) //Go_Func에서 팔렛에 가공할수 있는 작업 없을때 A <-> B이동시 사용
	{
		if (B[i].Total_Pallet_No == MAC1_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC1_temp[0].mac_no;
		}
		if (B[i].Total_Pallet_No == MAC2_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC2_temp[0].mac_no;
		}
		if (B[i].Total_Pallet_No == MAC3_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC3_temp[0].mac_no;
		}
	}
	cout << endl;

	Matrix_d.clear();


	//머신별 선택된 파트(오퍼레이션)
	/*cout << "머신" << MAC1_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC1_temp[0].pallet_no << "] P" << MAC1_temp[0].part_no
		<< " OP" << MAC1_temp[0].op_no + 1 << " 가공+이동시간" << MAC1_temp[0].PT_Trans_Time << endl;
	cout << "머신" << MAC2_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC2_temp[0].pallet_no << "] P" << MAC2_temp[0].part_no
		<< " OP" << MAC2_temp[0].op_no + 1 << " 가공+이동시간" << MAC2_temp[0].PT_Trans_Time << endl;
	cout << "머신" << MAC3_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC3_temp[0].pallet_no << "] P" << MAC3_temp[0].part_no
		<< " OP" << MAC3_temp[0].op_no + 1 << " 가공+이동시간" << MAC3_temp[0].PT_Trans_Time << endl;*/



	struct Min_Due {
		Initialize InitializeSystem; vector<Pallet> PALLET_temp; MatrixMin MATRIX_DUE;
		std::vector<mac> MAC1_temp; std::vector<mac> MAC2_temp; std::vector<mac> MAC3_temp;  vector<Pallet> B;
	};
	return Min_Due{ InitializeSystem, PALLET_temp, MATRIX_DUE, MAC1_temp, MAC2_temp, MAC3_temp, B };
};


bool CMP_PT(const mac &PT1, const mac &PT2) {//due date 비교함수 
	if (PT1.PT_Trans_Time < PT2.PT_Trans_Time)
	{
		return true;
	}
	else if (PT1.PT_Trans_Time == PT2.PT_Trans_Time)
	{
		return PT1.PT_Trans_Time < PT2.PT_Trans_Time;
	}
	else
	{
		return false;
	}
};


auto MIN_PT1(int MinPT_M1, vector<int> mac1, vector<mac> MAC1_temp, vector<Pallet> Matrix_p, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 
	if (M1_State == 0)
	{
		MinPT_M1 = *min_element(mac1.begin(), mac1.end());
		sort(MAC1_temp.begin(), MAC1_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M1에서 최소값:" << MAC1_temp[0].processing_time << "(" << MAC1_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC1_temp[0].pallet_no << "], P"
			<< MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << endl;
		//mux.unlock();

		for (int i = 0; i < Matrix_p.size(); i++) //최소 가공시간 선택되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_p[i].Total_Pallet_No == MAC1_temp[0].pallet_no)
			{
				Matrix_p[i].State = 1;
			}
		}
	}
	struct Result1 { int MinPT_M1; vector<int> mac1; vector<mac> MAC1_temp; vector<Pallet> Matrix_p; };
	return Result1{ MinPT_M1, mac1, MAC1_temp, Matrix_p };
};


auto MIN_PT2(int MinPT_M2, vector<int> mac2, vector<mac> MAC2_temp, vector<Pallet> Matrix_p, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 
	if (M2_State == 0)
	{
		MinPT_M2 = *min_element(mac2.begin(), mac2.end());
		sort(MAC2_temp.begin(), MAC2_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M2에서 최소값:" << MAC2_temp[0].processing_time << "(" << MAC2_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC2_temp[0].pallet_no << "], P"
			<< MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << endl;
		//mux.unlock();


		for (int i = 0; i < Matrix_p.size(); i++) //가공시간 최소값이 결정되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_p[i].Total_Pallet_No == MAC2_temp[0].pallet_no)
			{
				Matrix_p[i].State = 1;
			}
		}
	}
	struct Result2 { int MinPT_M2; vector<int> mac2; vector<mac> MAC2_temp; vector<Pallet> Matrix_p; };
	return Result2{ MinPT_M2, mac2, MAC2_temp, Matrix_p };
};


auto MIN_PT3(int MinPT_M3, vector<int> mac3, vector<mac> MAC3_temp, vector<Pallet> Matrix_p, std::mutex& mux)
{
	//working중인 머신제외 하고 머신1->머신2->머신3 순서로 최소값 찾기 

	if (M3_State == 0)
	{
		MinPT_M3 = *min_element(mac3.begin(), mac3.end());
		sort(MAC3_temp.begin(), MAC3_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M3에서 최소값:" << MAC3_temp[0].processing_time << "(" << MAC3_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC3_temp[0].pallet_no << "], P"
			<< MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << endl;
		//mux.unlock();

		for (int i = 0; i < Matrix_p.size(); i++) //가공시간 최소값이 결정되면 해당 팔렛 state = 1 로 바꿈 
		{
			if (Matrix_p[i].Total_Pallet_No == MAC3_temp[0].pallet_no)
			{
				Matrix_p[i].State = 1;
			}
		}
	}
	struct Result3 { int MinPT_M3; vector<int> mac3; vector<mac> MAC3_temp; vector<Pallet> Matrix_p; };
	return Result3{ MinPT_M3, mac3, MAC3_temp, Matrix_p };
}



auto FIND_MIN_PT(Initialize InitializeSystem, vector<Pallet> PALLET_temp, MatrixMin MATRIX, std::mutex& mux) //파라미터(PALLET, PALLET_temp) 자체가 바껴서 들어와야됨  //PALLET_temp(인풋데이터)
{
	cout << "------Find Shortest Processing Time + Transportation Time-------" << endl;

	/*매트릭스조건
	PALLET_temp.size() => 실제들어오는 팔렛 개수 (O)
	SelecPart.size() => 실제 팔렛에 올라간 파트 개수 (O)
	NumMac => 시스템에서 총 머신개수 (O)

	가공시간에 이동시간 추가 (O)
	워킹중인 머신 제외시키기 (O)
	머신당 팔렛 하나씩만 선택 (O)
	파트 머신개수만큼 선택 (O)
	*/

	/*머신에서 가공 하나 끝나면
	1.머신 state=0으로 되돌려 놓기
	2.팔렛 state =0으로 되돌려 놓기
	3.팔렛 작업 다 끝났는지 체크
	4.오퍼레이션 인덱스 고치기
	5. dependency 파트인지 체크 (?)
	*/
	int NumMac = InitializeSystem.Num_Machine;   //머신개수
	int NumPallet; //팔렛개수 
	int MinPT_M1 = 0; //머신별 최소 가공시간+이동시간
	int MinPT_M2 = 0;
	int MinPT_M3 = 0;



	//오퍼레이션 바뀌는거 테스트 
	//cout << "Operation 바뀌는거 테스트 " << endl; 
	//cout << "Pallet " << PALLET_temp[3].Total_Pallet_No << " Part" << PALLET_temp[3].SelecPart[0].Total_Part_No <<
	//"  Operation" << PALLET_temp[3].SelecPart[0].Oper[0].Operation_No
	//<< "   M1 " << PALLET_temp[3].SelecPart[0].Oper[0].Mac[0].Processing_Time << "   M2 "
	//<< PALLET_temp[3].SelecPart[0].Oper[0].Mac[1].Processing_Time << "   M3 "
	//<< PALLET_temp[3].SelecPart[0].Oper[0].Mac[2].Processing_Time << "  ---> operation " << PALLET_temp[3].SelecPart[0].Oper[0].Operation_No <<"번 끝났음" <<  endl;
	//PALLET_temp[3].SelecPart[0].OP_idx = 1;


	//인풋데이터 PALLET_temp 출력
	/*cout << "PALLET_temp 잘나오나 체크" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++) //PALLET_temp 잘나오나 체크
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]" << endl;
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "Part" << PALLET_temp[i].SelecPart[j].Total_Part_No << endl;
			for (int k = 0; k < PALLET_temp[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "OP" << PALLET_temp[i].SelecPart[j].Oper[k].Operation_No << "-";
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "mac" << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " ";
					cout << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Processing_Time << " ";
				}cout << endl;
			}cout << endl;
		}
	}cout << endl << endl;*/


	//1. 인풋데이터 가공 
	int p = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {  // 사용중인(파트가 올라간) 팔렛 개수 세기
		if (PALLET_temp[i].SelecPart.size() > 0)
			p++;
	}

	NumPallet = p;   //사용중인 팔렛개수
	vector<Pallet> Matrix_p(p);  //사용중인 팔렛 개수만큼 벡터 선언후 인풋데이터 옮기고 ( PALLET_temp -> Matrix_p )

	int u = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {
		if (PALLET_temp[i].SelecPart.size() > 0)
		{
			Matrix_p[u] = PALLET_temp[i];
			u++;
		}
	}



	//Matrix_p 출력
	/*cout << "Matrix_p 잘 들어왔나 체크" << endl;
	for (int i = 0; i < Matrix_p.size(); i++) //temp_p 잘나오나 체크
	{
		cout << "[Pallet" << Matrix_p[i].Total_Pallet_No << "]" << endl;
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++)
		{
			cout << "Part" << Matrix_p[i].SelecPart[j].Total_Part_No << endl;
			for (int k = 0; k < Matrix_p[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "OP" << Matrix_p[i].SelecPart[j].Oper[k].Operation_No << "-";
				for (int h = 0; h < Matrix_p[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "mac" << Matrix_p[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " ";
					cout << Matrix_p[i].SelecPart[j].Oper[k].Mac[h].Processing_Time << " ";
				}cout << endl;
			}cout << endl;
		}
	}*/



	//2.매트릭스 생성 
	MATRIX.aryprocess = new int**[NumPallet];
	MATRIX.aryoper = new int**[NumPallet];             //@@@@@@@@@@@@@@@@MATRIX.aryTrans 
	MATRIX.arydepend = new int**[NumPallet];

	for (int x = 0; x < NumPallet; x++)
	{
		MATRIX.aryprocess[x] = new int *[NumPallet];
		MATRIX.aryoper[x] = new int *[Matrix_p[x].SelecPart.size()];
		MATRIX.arydepend[x] = new int *[Matrix_p[x].SelecPart.size()];
		for (int y = 0; y < Matrix_p[x].SelecPart.size(); y++)
		{
			MATRIX.aryprocess[x][y] = new int[NumMac];
			MATRIX.aryoper[x][y] = new int[NumMac];
			MATRIX.arydepend[x][y] = new int[NumMac];
		}
	}

	for (int i = 0; i < NumPallet; i++)
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++)
			for (int v = 0; v < NumMac; v++) {
				MATRIX.aryprocess[i][j][v] = 0;
				MATRIX.aryoper[i][j][v] = 0;
				MATRIX.arydepend[i][j][v] = 0;
			}


	//3.매트릭스에 데이터 인풋 
	int part_count = 0; //파트개수 
	for (int i = 0; i < NumPallet; i++) {
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			part_count++;

			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
				MATRIX.aryprocess[i][j][v] = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
				//MATRIX.aryoper[i][j][v] = Matrix_p[i].SelecPart[j].Num_Operation;
				//MATRIX.arydepend[i][j][v] = Matrix_p[i].SelecPart[j].Dependency; // depend -2 없는애 -1 선행 0 후행	

				if (Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
				{
					MATRIX.aryprocess[i][j][v] = 0;
				}
				//cout << MATRIX.aryoper[i][j][v] << " ";
				//cout << MATRIX.arydepend[i][j][v] << " ";
			}
		}
	}




	mutex mux2;
	mux2.lock();
	//매트릭스 출력 
	for (int i = 0; i < NumPallet; i++) {
		cout << "[Pallet" << Matrix_p[i].Total_Pallet_No << "]" << endl;
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			cout << "P" << Matrix_p[i].SelecPart[j].Total_Part_No << " ";
			cout << "O" << OP_idx + 1 << " ";
			for (int v = 0; v < NumMac; v++) {
				cout << MATRIX.aryprocess[i][j][v] << " ";

				//cout << Matrix_p[i].SelecPart[j].Oper[0].Mac[v].Mac_No << " ";
			}
			cout << "(가공시간)" << endl;
		}
	}

	//4.이동시간 추가 
	cout << "Transportation time" << endl;
	for (int i = 0; i < NumMac + 1; i++) {
		for (int j = 0; j < NumMac + 1; j++)
			cout << InitializeSystem.Transportation_Time[i][j] << " ";
		cout << endl;
	}

	cout << "비어있는 머신 999999" << endl;
	mux2.unlock();

	mux2.lock();
	int Trans;
	for (int i = 0; i < NumPallet; i++) {
		int Current_Position = Matrix_p[i].Current_Position; //현재 팔렛 위치. 오퍼레이션 하나 끝날때마다 팔렛 위치 (PALLET_temp[0].Current_Position) 바꿔줘야함★★

		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;  // OP index
				int Mac_Position = Matrix_p[i].SelecPart[j].Oper[0].Mac[v].Mac_No; //machine index

				//현재 포지션에서 각 머신의 포지션으로 가는 이동시간 계산 
				for (int i = 0; i < NumMac + 1; i++) {
					for (int j = 0; j < NumMac + 1; j++)
					{
						Trans = InitializeSystem.Transportation_Time[Current_Position][Mac_Position];  //현재 팔렛 위치 [i] , 각 머신들의 위치 [j]
					}
				}
				if (Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
					Trans = 999999;


				//가공시간 + 이동시간 
				cout << "Part" << Matrix_p[i].SelecPart[j].Total_Part_No << " ";
				cout << "O" << OP_idx + 1 << " ";
				cout << MATRIX.aryprocess[i][j][v] << " + ";
				cout << Trans << " = ";

				MATRIX.aryprocess[i][j][v] += Trans;
				cout << MATRIX.aryprocess[i][j][v] << " | ";
				Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Trans_PT = MATRIX.aryprocess[i][j][v];
			}
			cout << endl;

		}
	}
	mux2.unlock();


	vector <mac> MAC1_temp(part_count);
	vector <mac> MAC2_temp(part_count);
	vector <mac> MAC3_temp(part_count);

	vector <int> mac1;
	vector <int> mac2;
	vector <int> mac3;

	int a = 0;
	int b = 0;
	int c = 0;



	//working 중인 팔렛 test
	/*cout << "워킹중인 팔렛 888888" << endl;
	Matrix_p[0].State = 1;
	Matrix_p[2].State = 1;
	cout << "Pallet" << Matrix_p[0].Total_Pallet_No << "is working" << endl;
	cout << "Pallet" << Matrix_p[2].Total_Pallet_No << "is working" << endl;*/


	//5. working중인 팔렛 제외
	for (int i = 0; i < NumPallet; i++) {  //머신1 
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 0)  //머신1 
				{
					if (M1_State == 0 && Matrix_p[i].State == 0) //머신1이 놀고있고 해당 팔렛도 놀고있으면 데이터 인풋 
					{
						int temp1 = MATRIX.aryprocess[i][j][v];
						mac1.push_back(temp1);  //머신1 가공시간만 다 넣음 

						MAC1_temp[a].pallet_no = Matrix_p[i].Total_Pallet_No;  //최소가공시간이 어느 파트시간인지 확인하기 위한거 
						MAC1_temp[a].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC1_temp[a].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC1_temp[a].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC1_temp[a].PT_Trans_Time = temp1;
						MAC1_temp[a].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;
					}

					else if (M1_State == 1 || Matrix_p[i].State == 1) //머신이 일하고 있거나 팔렛이 일하고 있으면 
					{
						mac1.push_back(888888);
						MAC1_temp[a].processing_time = 0;
						MAC1_temp[a].PT_Trans_Time = 888888;  //가공시간+이동시간에 888888 넣어서 선택 되지 않도록 함
					}
					a++;
				}
			}
		}
	}
	//5. working중인 머신 제외 및 팔렛 중복선택 방지
	auto Result1 = MIN_PT1(MinPT_M1, mac1, MAC1_temp, Matrix_p, mux);
	MinPT_M1 = Result1.MinPT_M1;
	mac1 = Result1.mac1;
	MAC1_temp = Result1.MAC1_temp;  // ★MAC1_temp[0] : 선택된 팔렛,파트 및 가공시간
	Matrix_p = Result1.Matrix_p;  //Matrix_p[i].State : 팔렛 state



	for (int i = 0; i < NumPallet; i++) { //머신2
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 1)  //머신2 
				{
					if (M2_State == 0 && Matrix_p[i].State == 0) //머신2 놀고있고 팔렛도 놀고있으면 데이터인풋 
					{
						int temp2 = MATRIX.aryprocess[i][j][v];
						mac2.push_back(temp2); //머신2 가공시간만 다 넣음

						MAC2_temp[b].pallet_no = Matrix_p[i].Total_Pallet_No; //최소가공시간이 어느 파트시간인지 확인하기 위한거 
						MAC2_temp[b].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC2_temp[b].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC2_temp[b].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC2_temp[b].PT_Trans_Time = temp2;
						MAC2_temp[b].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;

					}

					else if (M2_State == 1 || Matrix_p[i].State == 1) //머신이 일하고 있거나 팔렛이 일하고 있으면 
					{
						mac2.push_back(888888);
						MAC2_temp[b].processing_time = 0;
						MAC2_temp[b].PT_Trans_Time = 888888;  //Large number(888888) 인풋해서 최소값으로 선택 안되게함 

					}
					b++;
				}
			}
		}
	}
	auto Result2 = MIN_PT2(MinPT_M2, mac2, MAC2_temp, Matrix_p, mux);
	MinPT_M2 = Result2.MinPT_M2;
	mac2 = Result2.mac2;
	MAC2_temp = Result2.MAC2_temp;  // ★MAC2_temp[0] : 선택된 팔렛,파트 및 가공시간
	Matrix_p = Result2.Matrix_p; //Matrix_p[i].State : 팔렛 state


	for (int i = 0; i < NumPallet; i++) { //머신2
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (머신1), v=1 (머신2), v=2(머신3)

				if (v == 2) //머신3
				{
					if (M3_State == 0 && Matrix_p[i].State == 0) //머신이 놀고있고, 팔렛도 놀고 있으면 데이터인풋 
					{
						int temp3 = MATRIX.aryprocess[i][j][v];
						mac3.push_back(temp3); //머신3 가공시간만 다 넣음

						MAC3_temp[c].pallet_no = Matrix_p[i].Total_Pallet_No; //최소가공시간이 어느 파트시간인지 확인하기 위한거 
						MAC3_temp[c].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC3_temp[c].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC3_temp[c].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC3_temp[c].PT_Trans_Time = temp3;
						MAC3_temp[c].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;

					}
					else if (M3_State == 1 || Matrix_p[i].State == 1) //머신이 일하고 있거나 팔렛이 일하고 있으면
					{
						mac3.push_back(888888);
						MAC3_temp[c].processing_time = 0;
						MAC3_temp[c].PT_Trans_Time = 888888;  //Large number(888888) 인풋해서 최소값으로 선택 안되게함 

					}
					c++;
				}
			}
		}
	}

	auto Result3 = MIN_PT3(MinPT_M3, mac3, MAC3_temp, Matrix_p, mux);
	MinPT_M3 = Result3.MinPT_M3;
	mac3 = Result3.mac3;
	MAC3_temp = Result3.MAC3_temp;  // ★MAC3_temp[0] : 선택된 팔렛,파트 및 가공시간
	Matrix_p = Result3.Matrix_p; //Matrix_p[i].State : 팔렛 state


	mux2.lock();
	if (B.size() == 0) //가장 초기에 B Matrix 생성 
	{
		//PALLET_temp (A) 에서 선택된 팔렛만(state:1)  ->  (B) 로 이동  ->  PALLET_temp (A) 리스트에서 삭제
		PALLET_temp = Matrix_p;
		cout << endl;
		cout << " PALLET_temp (A) 출력해보자 (size:" << PALLET_temp.size() << ")" << endl;
		for (int i = 0; i < PALLET_temp.size(); i++)
		{
			cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
			for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
			{
				cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			}
			cout << "(state:" << PALLET_temp[i].State << ") " << endl;

			if (PALLET_temp[i].State == 1)   //선택 팔렛은 (B)로 옮긴후 
			{
				B.push_back(PALLET_temp[i]);
			}
		}
		cout << endl;

		for (int i = 0; i < PALLET_temp.size(); i++)  // PALLET_temp (A) 에서 삭제 
		{
			if (PALLET_temp[i].State == 1)
			{
				PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
				i--;
			}
		}
	}

	else
		cout << "두번째부터 는 B안에서 min값만 찾아" << endl;

	mux2.unlock();


	cout << " (B) 출력해보자 (size:" << B.size() << ")" << endl; // (B) 잘 옮겨졌는지 확인 
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}
	cout << endl;

	mux2.lock();
	cout << " (A) 삭제햇는데 지워졋나 (size:" << PALLET_temp.size() << ") - 함수 두번째 탈때부터는 B로 출력함" << endl; // (A) 잘 지워졌는지 확인 
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			/*for (int k = 0; PALLET_temp[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "O" << PALLET_temp[i].SelecPart[j].Oper[k].Operation_No << " ";
				for (int h = 0; PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "M" << PALLET_temp[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " ";
				}
			}*/
		}
		cout << "(state:" << PALLET_temp[i].State << ") " << endl;
	} cout << endl;


	for (int i = 0; i < B.size(); i++) //Go_Func에서 팔렛에 가공할수 있는 작업 없을때 A <-> B이동시 사용
	{
		if (B[i].Total_Pallet_No == MAC1_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC1_temp[0].mac_no;
		}
		if (B[i].Total_Pallet_No == MAC2_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC2_temp[0].mac_no;
		}
		if (B[i].Total_Pallet_No == MAC3_temp[0].pallet_no)
		{
			B[i].Current_Mac = MAC3_temp[0].mac_no;
		}
	}
	cout << endl;
	mux2.unlock();




	//머신별 선택된 파트(오퍼레이션)
	/*cout << "머신" << MAC1_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC1_temp[0].pallet_no << "] P" << MAC1_temp[0].part_no
		<< " OP" << MAC1_temp[0].op_no + 1 << " 가공+이동시간" << MAC1_temp[0].PT_Trans_Time << endl;
	cout << "머신" << MAC2_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC2_temp[0].pallet_no << "] P" << MAC2_temp[0].part_no
		<< " OP" << MAC2_temp[0].op_no + 1 << " 가공+이동시간" << MAC2_temp[0].PT_Trans_Time << endl;
	cout << "머신" << MAC3_temp[0].mac_no << " 선택된 파트: [Pallet" << MAC3_temp[0].pallet_no << "] P" << MAC3_temp[0].part_no
		<< " OP" << MAC3_temp[0].op_no + 1 << " 가공+이동시간" << MAC3_temp[0].PT_Trans_Time << endl;*/



	Matrix_p.clear();
	mac1.clear();
	mac2.clear();
	mac3.clear();


	struct Min_PT_TT {
		Initialize InitializeSystem; vector<Pallet> PALLET_temp;
		MatrixMin MATRIX; std::vector<mac> MAC1_temp; std::vector<mac> MAC2_temp; std::vector<mac> MAC3_temp; vector<Pallet> B;
	};
	return Min_PT_TT{ InitializeSystem, PALLET_temp, MATRIX, MAC1_temp, MAC2_temp, MAC3_temp, B }; // temp_pallet, PALLET_temp
};


void New_Matrix(vector<Pallet> PALLET_temp, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, Initialize InitializeSystem,
	int PalletInSys, vector<MatrixMax> Matrix_For_Max,
	MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //이 함수를 재사용 하고싶거든 파라미터를 통일 시키시오 반.드.시) 
{
	mux.lock();

	/*
	  -조건
	  1. (완료된 팔렛 있을경우) Machine1 -> Go_func -> New_Matrix 오퍼레이션 연결 되는지
	  2. (완료된 팔렛 없을경우) Machine1-> New_Matrix 오퍼레이션 연결되는지
	  3. (머신이 다 놀고있을경우)
	  4. (머신이 한개라도 일하고 있는경우)
	  -절차
	  1. 머신이 다 놀고 있을경우 (B매트릭스 팔렛이 동시에 다 끝났을경우)
	   1-1. 매트릭스 B에서 최대가공시간 VS 머신간이동시간
	   1-2. 머신별로 머신간이동시간이 크면 최소납기, 최대가공시간이 크면 최소이동+가공시간 인 오퍼레이션을 고른다.
	  2. 머신이 한개라도 일하고 있을 경우 (B매트릭스에 작업중인 팔렛이 하나라도 있을경우)
	   2-1. 매트릭스 B에서 최대가공시간 VS 머신간이동시간
	   2-2. 머신별로 머신간이동시간이 크면 최소납기, 최대가공시간이 크면 최소이동+가공시간 인 오퍼레이션을 고른다.
			(두개 머신이 동시에 빌 경우 오퍼레이션 하나씩 각 대안머신에서 가공될경우를 비교해본다)
	   2-3. 고른 오퍼레이션이 방금 작업이 끝난 놀고있는 머신에서 가공할 경우와 워킹중인 머신에서 기다렸다 가공할 경우를 비교/예측 해본다.
	   2.3  워킹중인 머신이 끝날때까지 기다렸다 투입되는경우 머신이 끝날때까지 sleep 으로 기다린다.
	   2-4. 워킹중인 머신을 기다리고 있는 도중에 New_Matrix가 생성될때 기다리고 있는 팔렛과 예약된 머신을 제외된다.
	   2-5. 머신 가공이 끝나면 Go_Func(끝난팔렛체크) 반복.


	   지금의 문제, 뉴매트릭스 ->LPT 함수 탈때 어떨때는 가공시간 최소값이 아닌최대값을 찾음
	   매트릭스 B를 탈때 머신1에서 가공된 결과 ->B 매트릭스에 저장, 머신3에서 가공된 결과 ->B 매트릭스에 저장이 안됨.

	  */

	cout << "-----------------------------New Matrix-------------------------" << endl;
	/*cout << "----[ B ] 가공시간" << endl;  //Matrix B
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
			cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
				}
			}
			cout << "(state:" << B[i].State << ")" << endl;
		}
	}*/


	//Matrix B 가공시간 + 이동시간 
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT = -1;
					}
					if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -2)
					{
						B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT = -2;
					}
					if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -3)
					{
						B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT = -3;
					}

					if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT < -10000)
					{
						B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT = 0;
					}
				}
			}
		}
	}

	//남은 가공시간 계산 (방금 끝난 작업 의 가공+이동시간을 현재 working중인 오퍼레이션들의 가공시간에서 뺌). 
	if (M1_State == 0)
	{
		cout << "방금끝난 작업 : [PALLET" << Mac1_Part[0].pallet_no << "] Part" << Mac1_Part[0].part_no << " O" << Mac1_Part[0].op_no + 1 << " " << Mac1_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] 현재 워킹중인 작업" << endl;
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac2_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac2_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac2_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M2가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac1_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
			if (B[i].Total_Pallet_No == Mac3_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac3_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac3_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M3가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac1_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
		}

	}
	if (M2_State == 0)
	{
		cout << "방금끝난 작업 : [PALLET" << Mac2_Part[0].pallet_no << "] Part" << Mac2_Part[0].part_no << " O" << Mac2_Part[0].op_no + 1 << " " << Mac2_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] 현재 워킹중인 작업" << endl;
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac1_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac1_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac1_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M1가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac2_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
			if (B[i].Total_Pallet_No == Mac3_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac3_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac3_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M3가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac2_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
		}

	}
	if (M3_State == 0)
	{
		cout << "방금끝난 작업 : [PALLET" << Mac3_Part[0].pallet_no << "] Part" << Mac3_Part[0].part_no << " O" << Mac3_Part[0].op_no + 1 << " " << Mac3_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] 현재 워킹중인 작업" << endl;
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac1_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac1_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac1_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M1가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac3_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
			if (B[i].Total_Pallet_No == Mac2_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac2_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < 1; k++)
						{
							if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac2_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(현재M2가공중인 작업):";
								for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
								{
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT -= Mac3_Part[0].PT_Trans_Time;
									B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
									cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
								}
							}
						}
						cout << "(state:" << B[i].State << ")" << endl;
					}
				}
			}
		}
	}
	if (M1_State == 0 && M2_State == 0 && M3_State == 0)
		cout << "머신 동시에 비었음" << endl;




	cout << "----[ B ] 현재 남은 가공시간" << endl;
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
			cout << "[P" << B[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
				}
			}
			cout << "(state:" << B[i].State << ")" << endl;
		}
	}


	/*cout << "----[ A ] PALLET" << endl; //B 에서 작업 끝난거 원본데이터로 옮겨
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "[PALLET" << PALLET[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			cout << "[P" << PALLET[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = PALLET[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << PALLET[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << "M" << PALLET[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
		}
		cout << "(state:" << PALLET[i].State << ")" << endl;
	}*/


	/*cout << "----[ A ] PALLET_temp" << endl; //지역 A
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[PALLET" << PALLET_temp[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "[P" << PALLET_temp[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << "M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
		}
		cout << "(state:" << PALLET_temp[i].State << ")" << endl;
	}*/

	PALLET_temp_public = PALLET_temp;

	cout << "----[ A ] PALLET_temp_public" << endl;//전역 A
	for (int i = 0; i < PALLET_temp_public.size(); i++)
	{
		for (int j = 0; j < PALLET_temp_public[i].SelecPart.size(); j++)
		{
			cout << "[PALLET" << PALLET_temp_public[i].Total_Pallet_No << "] ";
			cout << "[P" << PALLET_temp_public[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = PALLET_temp_public[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << PALLET_temp_public[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < PALLET_temp_public[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << PALLET_temp_public[i].SelecPart[j].Oper[OP_idx].Mac[h].Processing_Time << " ";
				}
			}
			cout << "(state:" << PALLET_temp_public[i].State << ")" << endl;
		}
	}


	PALLET_temp.clear();
	PALLET_temp = B;
	mux.unlock();


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!일단 TEST_DATA4_2로 하고 auto return 하는 방법 알면 4_1로 만들기 

	//B Matrix상의 최대 가공시간 VS 머신간이동시간 비교 
	auto Max_PT = FIND_MAX_PT(InitializeSystem, PALLET_temp, Matrix_For_Max, mux); //최대가공시간 : Max_PT.temp_pallet[0]                                                                               
	B = Max_PT.PALLET_temp;

	cout << "-> LPT:" << Max_PT.temp_pallet[0].processing_time << " [Pallet" << Max_PT.temp_pallet[0].pallet_no << "] Part" << Max_PT.temp_pallet[0].part_no
		<< " OP" << Max_PT.temp_pallet[0].op_no << " Mac" << Max_PT.temp_pallet[0].mac_no << endl;



	vector <mac> Mac1_Part_New; //최소납기, 최소 가공시간을 찾는 단계를 거쳐 선택된 파트 
	vector <mac> Mac2_Part_New;
	vector <mac> Mac3_Part_New;

	PALLET_temp.clear();
	PALLET_temp = B;

	if (M1_State == 0 && M2_State == 0 && M3_State == 0)
	{
		cout << "머신 모두 idle" << endl;
	}
	else
	{
		cout << "머신 일부 working중" << endl;
		if (InitializeSystem.TransTime > Max_PT.temp_pallet[0].processing_time)
		{
			cout << "이동시간이 더 큼 -> 놀고있는 가장 가까운 머신 부터 납기가장 짧은 파트(오퍼레이션) 탐색" << endl;

			auto Min_Due = FIND_MIN_DUE(InitializeSystem, PALLET_temp, MATRIX_DUE, mux);
			Mac1_Part_New = Min_Due.MAC1_temp;
			Mac2_Part_New = Min_Due.MAC2_temp;
			Mac3_Part_New = Min_Due.MAC3_temp;
			B = Min_Due.B;
			PALLET_temp = Min_Due.PALLET_temp;
		}
		else
		{
			cout << "최대가공시간이 더 큼 -> 놀고있는 가장 가까운 머신부터 가공+이동시간 가장 작은 파트(오퍼레이션) 탐색" << endl;

			auto Min_PT_TT = FIND_MIN_PT(InitializeSystem, PALLET_temp, MATRIX, mux);
			Mac1_Part_New = Min_PT_TT.MAC1_temp;
			Mac2_Part_New = Min_PT_TT.MAC2_temp;
			Mac3_Part_New = Min_PT_TT.MAC3_temp;
			B = Min_PT_TT.B;
			PALLET_temp = Min_PT_TT.PALLET_temp;
		}
	}

	mux.lock();

	//선택된 파트  ->  머신끼리 예측!!!!!!!!!!!!!!!!!!!!!!!!!

	//B Matrix에서 선택된 오퍼레이션이 idle 머신에서 작업하는것이 빨리 끝나는지, working중인 머신에서 작업하는것이 빨리 끝나는지 예측 
	cout << "----------------------------New Matrix-----------------------------" << endl;

	vector<mac> m1_op(3);
	vector<mac> m2_op(3);
	vector<mac> m3_op(3);
	vector<mac> Mac1_SeletedOP(3);
	vector<mac> Mac2_SeletedOP(3);
	vector<mac> Mac3_SeletedOP(3);

	int min_pt;
	if (M1_State == 0)
	{
		cout << "선택된 작업 : [PALLET" << Mac1_Part_New[0].pallet_no << "] Part" << Mac1_Part_New[0].part_no << " O" << Mac1_Part_New[0].op_no + 1 << " " << Mac1_Part_New[0].PT_Trans_Time << endl;
	}
	if (M2_State == 0)
	{
		cout << "선택된 작업 : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O" << Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << endl;
		//선택된 작업
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac2_Part_New[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac2_Part_New[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
						{
							if (B[i].SelecPart[j].Oper[k].Operation_No == Mac2_Part_New[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[k].Operation_No << " 의 가공시간들 ";
								for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
								{
									cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " ";  //M2에서 선택된 오퍼레이션 //New Matrix B에서 선택된 가공시간 
									m2_op[h].pallet_no = B[i].Total_Pallet_No;
									m2_op[h].part_no = B[i].SelecPart[j].Total_Part_No;
									m2_op[h].op_no = B[i].SelecPart[j].Oper[k].Operation_No;
									m2_op[h].mac_no = B[i].SelecPart[j].Oper[k].Mac[h].Mac_No;
									m2_op[h].PT_Trans_Time = B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT;

									if (B[i].SelecPart[j].Oper[k].Mac[h].Mac_No == Mac2_Part_New[0].mac_no)
									{
										/*m2_op[0].pallet_no = B[i].Total_Pallet_No;
										m2_op[0].part_no = B[i].SelecPart[j].Total_Part_No;
										m2_op[0].op_no = B[i].SelecPart[j].Oper[k].Operation_No;
										m2_op[0].mac_no = B[i].SelecPart[j].Oper[k].Mac[h].Mac_No;
										m2_op[0].PT_Trans_Time = B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT;*/
									}
								}
							}
						}
					}
				}
			}
		}
		cout << endl;

		//M1에서 작업중인 오퍼레이션 - 머신의 남은시간
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac1_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac1_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
						{
							if (B[i].SelecPart[j].Oper[k].Operation_No == Mac1_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[k].Operation_No << " ";
								for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
								{
									if (B[i].SelecPart[j].Oper[k].Mac[h].Mac_No == Mac1_Part[0].mac_no)
									{
										cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " (M1에서 작업중인 오퍼레이션-머신의 남은시간)" << endl;
										m1_op[0].pallet_no = B[i].Total_Pallet_No;
										m1_op[0].part_no = B[i].SelecPart[j].Total_Part_No;
										m1_op[0].op_no = B[i].SelecPart[j].Oper[k].Operation_No;
										m1_op[0].mac_no = B[i].SelecPart[j].Oper[k].Mac[h].Mac_No;
										m1_op[0].PT_Trans_Time = B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT;
									}
								}
							}
						}
					}
				}
			}
		}


		//M3에서 작업중인 오퍼레이션 - 머신의 남은시간
		for (int i = 0; i < B.size(); i++)
		{
			if (B[i].Total_Pallet_No == Mac3_Part[0].pallet_no)
			{
				for (int j = 0; j < B[i].SelecPart.size(); j++)
				{
					if (B[i].SelecPart[j].Total_Part_No == Mac3_Part[0].part_no)
					{
						cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
						cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] ";
						int OP_idx = B[i].SelecPart[j].OP_idx;
						for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
						{
							if (B[i].SelecPart[j].Oper[k].Operation_No == Mac3_Part[0].op_no + 1)
							{
								cout << "O" << B[i].SelecPart[j].Oper[k].Operation_No << " ";
								for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
								{
									if (B[i].SelecPart[j].Oper[k].Mac[h].Mac_No == Mac3_Part[0].mac_no)
									{
										cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " (M3에서 작업중인 오퍼레이션-머신의 남은시간)" << endl;
										m3_op[0].pallet_no = B[i].Total_Pallet_No;
										m3_op[0].part_no = B[i].SelecPart[j].Total_Part_No;
										m3_op[0].op_no = B[i].SelecPart[j].Oper[k].Operation_No;
										m3_op[0].mac_no = B[i].SelecPart[j].Oper[k].Mac[h].Mac_No;
										m3_op[0].PT_Trans_Time = B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT;
									}
								}
							}
						}
					}
				}
			}
		}
		//M1 -> M2
		cout << m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time << " (M1->M2) 선택된 작업 M1에서 작업했을때 " << endl; //m1_op[0] : M1에서 가공중인 OP의 가공시간  

		//M2
		cout << m2_op[0].PT_Trans_Time << "(M1)  " << m2_op[1].PT_Trans_Time << " (M2)   " << m2_op[2].PT_Trans_Time << " (M3) M2에서 작업했을때 " << endl; // 새로 선택된 OP 의 가공시간들  m2_op[0] : M1,  m2_op[1] : M2,  m2_op[2] : M3

		//M3 -> M2
		cout << m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time << " (M3->M2) 선택된 작업 M3에서 작업했을때 " << endl;  //m3_op[0] : M3에서 가공중인 OP의 가공시간 


		//제일 적게 걸리는 머신은? M1,M2,M3중에 예측해보기 
		if (m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time < m2_op[1].PT_Trans_Time && m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time < m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time)
		{
			//M1에서 가공하는것이 더 빠르면 

			cout << "선택된 작업 : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " 작업하려면 ";
			cout << "M1이 제일 빠름 " << m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time << endl;
		}
		if (m2_op[1].PT_Trans_Time < m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time && m2_op[1].PT_Trans_Time < m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time)
		{
			//M2에서 가공하는것이 더 빠르면

			cout << "선택된 작업 : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " 작업하려면 ";
			cout << "M2이 제일 빠름 " << m2_op[1].PT_Trans_Time << endl;

			for (int i = 0; i < B.size(); i++)
			{
				if (B[i].Total_Pallet_No == Mac2_Part_New[0].pallet_no)
				{
					for (int j = 0; j < B[i].SelecPart.size(); j++)
					{
						if (B[i].SelecPart[j].Total_Part_No == Mac2_Part_New[0].part_no)
						{
							cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
							cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] ";
							int OP_idx = B[i].SelecPart[j].OP_idx;
							for (int k = 0; k < 1; k++)
							{
								if (B[i].SelecPart[j].Oper[OP_idx].Operation_No == Mac2_Part_New[0].op_no + 1)
								{
									cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
									for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
									{
										if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 2)
										{
											B[i].SelecPart[j].Oper[OP_idx].SelectedMac[0] = B[i].SelecPart[j].Oper[OP_idx].Mac[h];
											Mac2_SeletedOP[0].pallet_no = B[i].Total_Pallet_No;
											Mac2_SeletedOP[0].part_no = B[i].SelecPart[j].Total_Part_No;
											Mac2_SeletedOP[0].op_no = B[i].SelecPart[j].Oper[OP_idx].Operation_No;
											Mac2_SeletedOP[0].mac_no = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No;
											Mac2_SeletedOP[0].PT_Trans_Time = B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT;
										}
									}
								}
							}
							cout << "(state:" << B[i].State << ")" << endl;
						}
					}
				}
			}
		}
		if (m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time < m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time && m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time < m2_op[1].PT_Trans_Time)
		{
			//M3에서 가공하는것이 더 빠르면 

			cout << "선택된 작업 : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " 작업하려면 ";
			cout << "M3이 제일 빠름 " << m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time << endl;
		}



	}
	if (M3_State == 0)
	{
		cout << "선택된 작업 : [PALLET" << Mac3_Part_New[0].pallet_no << "] Part" << Mac3_Part_New[0].part_no
			<< " O" << Mac3_Part_New[0].op_no + 1 << " " << Mac3_Part_New[0].PT_Trans_Time << endl;
	}


	cout << "New_Matrix OP-MAC PAIR : [PALLET" << Mac2_SeletedOP[0].pallet_no << "] [P" << Mac2_SeletedOP[0].part_no
		<< "] O" << Mac2_SeletedOP[0].op_no << " - M" << Mac2_SeletedOP[0].mac_no << " " << Mac2_SeletedOP[0].PT_Trans_Time << endl;













	cout << "[ B ]" << endl;
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "[PALLET" << B[i].Total_Pallet_No << "] ";
			cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] ";
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Trans_PT << " ";
				}
			}
			cout << "(state:" << B[i].State << ")" << endl;
		}
	}
	mux.unlock();




	//idle 머신에 바로 투입될때 




	//기다렸다가 working중인 머신에 투입될때
	

	//선택된 파트 가공처리  
	/*std::future<void> Thread1 = std::async(std::launch::async, MACHINE1,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread2 = std::async(std::launch::async, MACHINE2,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread3 = std::async(std::launch::async, MACHINE3,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));*/








	//함수 종료시 모든 임시벡터 clear 
	m1_op.clear();
	m2_op.clear();
	m3_op.clear();


	cout << "----------------------------------------------------------------" << endl;

};




void Move_A_to_B(int Pallet_count, vector<Pallet> PALLET_temp, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part,
	Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX,
	int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //이 함수를 재사용 하고싶거든 파라미터를 통일 시키시오 반.드.시

{
	cout << "----------------------Move Pallet A to_B----------------------" << endl;

	/* 팔렛pool PALLET에서 파트 안올라간 빈팔렛은 지워버리고 파트가 올라와있는 팔렛들 중에서 (로딩된 순서대로) 방금 작업이 끝난 머신에서 처리 가능한 팔렛을 찾아
	 끝난 팔렛 개수(Pallet_count) 만큼  A->B로 가져온다.  */

	 /*cout << "[PALLET] - 새로 로딩된 팔렛들 " << endl; //원본 인풋데이터
	 for (int i = 0; i < PALLET.size(); i++)
	 {
		 cout << "[Pallet" << PALLET[i].Total_Pallet_No << "] ";
		 for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		 {
			 cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " ";
		 }
		 cout << "(State:" << PALLET[i].State << ")" << endl;
	 }*/


	cout << "[ B ]  A->B 이동 전" << endl;  //Matrix B
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << "(State:" << B[i].State << ") ";
		if (B[i].Complete == 1)
			cout << "완료";

		cout << endl;
	}



	int p = 0;
	for (int i = 0; i < PALLET.size(); i++) {  // 사용중인(파트가 올라간) 팔렛 개수(p) 세서
		if (PALLET[i].SelecPart.size() > 0)
			p++;
	}

	PALLET_temp.clear();
	PALLET_temp.resize(p);  //사용중인 팔렛 개수만큼의 크기의 A Matrix 재생성

	int u = 0;
	for (int i = 0; i < PALLET.size(); i++) {
		if (PALLET[i].SelecPart.size() > 0)
		{
			PALLET_temp[u] = PALLET[i];
			u++;
		}
	}

	for (int i = 0; i < PALLET_temp.size(); i++)  // A (PALLET_temp) 에서 이미 working중인 팔렛(B Matrix) 삭제 
	{
		if (PALLET_temp[i].State == 1)
		{
			PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
			i--;
		}
	}

	cout << "[ A ]  A->B 이동 전" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++)  //Matrix A 완성
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]" << " ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "(P" << PALLET_temp[i].SelecPart[j].Total_Part_No << ") ";
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << "O" << OP_idx + 1 << " ";
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					cout << "M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
		}
		cout << "(State:" << PALLET_temp[i].State << ")" << endl;
	}
	cout << endl;


	//가공 후 바뀐 파트정보는 PALLET에 저장 후 B에서 끝난 팔렛 삭제 
	for (int i = 0; i < PALLET.size(); i++)
	{
		for (int a = 0; a < B.size(); a++)  //(현재는 머신1,2번 구현 안되어 아직 끝난 오퍼레이션 정보가 원본 데이터 PALLET에 연결 되지 않은 상태임) 
		{
			if (PALLET[i].Total_Pallet_No == B[a].Total_Pallet_No)
			{

				for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
				{
					for (int b = 0; b < B[a].SelecPart.size(); b++)
					{
						if (PALLET[i].SelecPart[j].Total_Part_No == B[a].SelecPart[b].Total_Part_No)
						{
							PALLET[i].SelecPart[j].Complete = B[a].SelecPart[b].Complete;  //완료된 파트 정보
							for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
							{
								for (int c = 0; c < B[a].SelecPart[b].Num_Operation; c++)
								{
									if (PALLET[i].SelecPart[j].Oper[k].Operation_No == B[a].SelecPart[b].Oper[c].Operation_No)
									{
										PALLET[i].SelecPart[j].OP_idx = B[a].SelecPart[b].OP_idx;  //완료된 오퍼레이션 인덱스
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//PALLET 출력
	/*cout << "B 정보 PALLET에 저장됬니" << endl;
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "[Pallet" << PALLET[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			cout << "P" << PALLET[i].SelecPart[j].Total_Part_No ;
			cout << "(" << PALLET[i].SelecPart[j].Complete << ") ";
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				cout << "OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No << " ";


				if (M1_State == 0)
				{
					for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec.size(); h++)
					{
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec[h] << " ";
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC1_End_vec[h] << " ";
					}
				}
				if (M2_State == 0)
				{
					for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec.size(); h++)
					{
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec[h] << " ";
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC2_End_vec[h] << " ";
					}
				}
			   if (M3_State == 0)
				{
					for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec.size(); h++)
					{
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec[h] << " ";
						cout << "start" << PALLET[i].SelecPart[j].Oper[k].MAC3_End_vec[h] << " ";
					}
				}
				cout << "idx" << PALLET[i].SelecPart[j].OP_idx << " ";
				cout << "(" << PALLET[i].SelecPart[j].Oper[k].Complete << ") ";
			}
		}
		cout << endl;
	}*/

	/*한가지 의문점 : 나는 B Matrix -> PALLET 로  Oper[k].Complete, Oper[k].MAC1_Start_vec 옮긴적이 없는데 어디서 옮겨졌지? */


   //B에서 완료된팔렛 언로딩 ★★★★★

   //B Matrix에서 완료된 팔렛 삭제 
	for (vector<int>::size_type i = 0; i < B.size(); )
	{
		if (B[i].Complete == 1)
		{
			B.erase(B.begin() + i);
		}
		else {
			i++;
		}
	}


	mux.lock();


	//A에서 로딩된 순서대로 방금 가공끝난 머신에서 처리할수 있는 오퍼레이션이 남아있는 팔렛인지 확인 
	cout << "A 팔렛들의 오퍼레이션별 대안머신     // M1_State:" << M1_State << " M2_State:" << M2_State << " M3_State:" << M3_State << " //" << endl;
	vector <Pallet> PALLET_temp_temp;
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					if (M1_State == 0 && PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 1)
					{
						PALLET_temp_temp.push_back(PALLET_temp[i]);
					}
					else if (M1_State == 1 || PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						cout << "M1에서 가공가능한 팔렛 없슴  ";
					}

					if (M2_State == 0 && PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 2)
					{
						PALLET_temp_temp.push_back(PALLET_temp[i]);
					}
					else if (M2_State == 1 || PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						cout << "M2에서 가공가능한 팔렛 없슴  ";
					}


					if (M3_State == 0 && PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 3)
					{
						PALLET_temp_temp.push_back(PALLET_temp[i]);

					}
					else if (M3_State == 1 || PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						cout << "M3에서 가공가능한 팔렛 없슴  ";
					}


				}
			}
		}
	}
	mux.unlock();


	auto comp1 = [](const Pallet& p1, const Pallet& p2) {return p1.Total_Pallet_No == p2.Total_Pallet_No; }; //구조체벡터 중복 삭제  
	auto last = std::unique(PALLET_temp_temp.begin(), PALLET_temp_temp.end(), comp1);
	PALLET_temp_temp.erase(last, PALLET_temp_temp.end());


	PALLET_temp.clear();
	PALLET_temp = PALLET_temp_temp;





	int P_count = Pallet_count;
	//끝난 팔렛개수 만큼 A -> B로 가져온다.  (First In First Out)
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		B.push_back(PALLET_temp[i]);
		P_count--;
		if (P_count == 0)
			break;
	}



	//A에서 이동된 팔렛 삭제
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		for (int b = 0; b < B.size(); b++)
		{
			if (PALLET_temp[i].Total_Pallet_No == B[b].Total_Pallet_No)
			{
				PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
			}
		}
	}



	cout << "----[ B ]  A->B 이동 후" << endl;  //Matrix B
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << "(State:" << B[i].State << ") ";
		if (B[i].Complete == 1)
			cout << "완료";

		cout << endl;
	}

	cout << "----[ A ]  A->B 이동 후 (가공끝난머신에서 가공할수 없는 팔렛은 제외함)" << endl;  //Matrix A 
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";

		}
		cout << "(State:" << PALLET_temp[i].State << ")" << endl;
	}

	//-------------------Matrix A, B 가공 완료-------------------------------

	Go_F_State == 0;
	New_Matrix(PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part, InitializeSystem, PalletInSys, Matrix_For_Max,
		MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));


};

auto Incomplete_Move_B_To_A(vector<Pallet> PALLET_temp, int Mac, int Mac_P) {

	struct After_Move { vector<Pallet> PALLET_temp; int Mac_P; };

	cout << "-----------------Incomplete_Move_B_To_A-----------------" << endl;
	mutex mux;
	mux.lock();

	cout << " PALLET " << endl;
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "[Pallet" << PALLET[i].Total_Pallet_No << "]";
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			cout << " P" << PALLET[i].SelecPart[j].Total_Part_No;
			int OP_idx = PALLET[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << PALLET[i].SelecPart[j].Oper[OP_idx].Operation_No;
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << " M" << PALLET[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << PALLET[i].State << ")" << endl;
	}cout << endl;

	/*cout << " PALLET_temp " << endl;
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << " P" << PALLET_temp[i].SelecPart[j].Total_Part_No;
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Operation_No;
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << " M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << PALLET_temp[i].State << ")" << endl;
	}cout << endl;*/

	mux.unlock();







	//A (로딩된 팔렛 pool) 가공
	int p = 0;
	for (int i = 0; i < PALLET.size(); i++) {  // 사용중인(파트가 올라간) 팔렛 개수(p) 세서
		if (PALLET[i].SelecPart.size() > 0)
			p++;
	}

	PALLET_temp.clear();
	PALLET_temp.resize(p);  //사용중인 팔렛 개수만큼의 크기의 A Matrix 재생성
	int u = 0;
	for (int i = 0; i < PALLET.size(); i++) {
		if (PALLET[i].SelecPart.size() > 0)
		{
			PALLET_temp[u] = PALLET[i];
			u++;
		}
	}

	for (int i = 0; i < PALLET_temp.size(); i++)  // A (PALLET_temp) 에서 이미 working중인 팔렛(B Matrix) 삭제 
	{
		if (PALLET_temp[i].State == 1)
		{
			PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
			i--;
		}
	}

	mux.lock();
	cout << "A (이동 전)" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << " P" << PALLET_temp[i].SelecPart[j].Total_Part_No;
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Operation_No;
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << " M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << PALLET_temp[i].State << ")" << endl;
	}cout << endl;

	cout << "B (이동 전)" << endl;
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "]";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << " P" << B[i].SelecPart[j].Total_Part_No;
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "M" << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << B[i].State << ")" << endl;
	}cout << endl;
	mux.unlock();


	mux.lock();

	//B -> A front에 insert 후 B에서 삭제 
	for (int i = 0; i < B.size(); i++)
	{
		if (B[i].Total_Pallet_No == Mac_P) //Mac2_P : A Matrix로 보내야할 팔렛. 방금 끝난 머신에서 가공할수 있는 작업 없음 
		{
			cout << "(B Matrix) M" << Mac << "에서 처리 불가능한 팔렛: [PALLET" << B[i].Total_Pallet_No << "]" << endl;
			//	B[i].State = 0; //A로 옮기면서 state 변경
			PALLET_temp.insert(PALLET_temp.begin(), B[i]);
		}
	}

	for (int i = 0; i < B.size(); i++)
	{
		if (B[i].Total_Pallet_No == Mac_P)
		{
			B.erase(B.begin() + i, B.begin() + i + 1);
			i--;
		}
	}

	//A에서 방금 front에 insert된 팔렛을 제외하고 idle머신에서 작업 가능한 팔렛을 FIFO로 찾는다. -> 없으면 다음오퍼레이션 업데이트 될때까지 비어있음 ★★나중에체크 
	cout << "(A Matrix) M" << Mac << "에서 처리 가능한 첫번째 팔렛 ";
	for (int i = 1; i < PALLET_temp.size(); i++)
	{
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
				{
					if (PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == Mac)
					{
						cout << "[PALLET" << PALLET_temp[i].Total_Pallet_No << "]";
						cout << " Part" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
						cout << "OP" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
						cout << "M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << "  Mac" << Mac;
						B.push_back(PALLET_temp[i]);
						PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
						i--;
						break;
					}
					else
					{
						cout << endl << "M" << Mac << " 에서 작업 가능한 오퍼레이션 없음 (머신 작업 끝남)" << endl;
						/*	!!!!!!!!!!!!!!!!!!!!!!!!!!!MAC에서 작업가능한 팔렛이 A에도 없으면 함수 return. 해당 머신 종료.
							=>auto 형 함수를 구조체로 return할경우, 함수 중간에 함수를 반환하는 방법 알아서 적용시켜 (일단 stackoverflow에 질문)
						 아니다 언로딩 만들면서 생각해봐!!!!!!!!!!!!!!!!!!!!!!!!!! 종료된 머신 어떻게 할거여     */
					}
				}
				if (B.size() == 3)
					break;
			}
			cout << " ";
			if (B.size() == 3)
				break;
		}
		cout << endl;

		if (B.size() == 3)
			break;
		cout << endl;
	}


	cout << "A (이동 후)" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "]";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << " P" << PALLET_temp[i].SelecPart[j].Total_Part_No;
			int OP_idx = PALLET_temp[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < PALLET_temp[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "M" << PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << PALLET_temp[i].State << ")" << endl;
	}cout << endl;



	cout << "B (이동 후)" << endl;
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "]";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << " P" << B[i].SelecPart[j].Total_Part_No;
			int OP_idx = B[i].SelecPart[j].OP_idx;
			for (int k = 0; k < 1; k++)
			{
				cout << " OP" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
				for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					cout << "M" << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";
				}
			}
			cout << " ";
		}
		cout << "(state:" << B[i].State << ")" << endl;
	}cout << endl;
	mux.unlock();

	cout << "----------------------------------------------------------" << endl;

	return After_Move{ PALLET_temp, Mac_P };

};

void Go_Func(int PalletInSys, vector<Pallet> PALLET_temp, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	/* B에서 끝난 팔렛 있는지 Check -> 끝났으면 몇개? -> (방금 가공 완료된 머신에서 처리가능한 팔렛을 로딩된 순서대로 찾아서) 끝난팔렛 개수 만큼 A->B로 팔렛 추가 -> New Matrix
								  -> 끝난팔렛 없으면? -> New Matrix */
	Go_F_State = 1;

	int Pallet_count = 0;
	for (int i = 0; i < B.size(); i++)
	{
		int Part_count = 0;
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			int OP_count = 0;
			for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
			{
				if (B[i].SelecPart[j].Oper[k].Complete == 1)
					OP_count++;
			}
			if (OP_count == B[i].SelecPart[j].Num_Operation)
				Part_count++;
		}
		if (Part_count == B[i].SelecPart.size())
			Pallet_count++;
	}

	cout << "끝난팔렛 몇개인가요?" << Pallet_count << endl;


	//Go_F_State = 0;


	mux.lock();

	if (Pallet_count > 0)  //완료된 팔렛이 하나 이상이면 
	{
		cout << "끝난 팔렛이 " << Pallet_count << "개 네욤" << endl;

		Move_A_to_B(Pallet_count, PALLET_temp, Mac1_Part, Mac3_Part, Mac3_Part,
			InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	}
	else //완료된 팔렛 없으면 
	{
		cout << "끝난 팔렛이 없네욤" << endl;

		//팔렛은 안끝났지만 방금머신에서 가공가능한 오퍼레이션이 없는경우 (B시점)  -> B에서 해당팔렛 A로 이동, A에서 대기중인 팔렛중 첫번째 팔렛 가져옴 
		cout << "B 팔렛들의 오퍼레이션별 대안머신 (가공 후 OP update)    // M1_State:" << M1_State << " M2_State:" << M2_State << " M3_State:" << M3_State << " //" << endl;
		for (int i = 0; i < B.size(); i++)
		{
			cout << "[PALLET" << B[i].Total_Pallet_No << "] state:" << B[i].State << " ";
			int m1_empty = 0;
			int m2_empty = 0;
			int m3_empty = 0;

			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				int OP_idx = B[i].SelecPart[j].OP_idx;

				cout << " [P" << B[i].SelecPart[j].Total_Part_No << "] (OP_idx" << OP_idx + 1 << ") ";
				for (int k = 0; k < 1; k++)
				{
					cout << "OP" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << " ";
					for (int h = 0; h < B[i].SelecPart[j].Oper[OP_idx].Num_AlterMac; h++)
					{
						cout << "M" << B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No << " ";

						if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1 && M1_State == 0)
						{
							m1_empty++;
						}
						else if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -2 && M2_State == 0)
						{
							m2_empty++;
						}
						else if (B[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -3 && M3_State == 0)
						{
							m3_empty++;
						}
					}
				}
			}
			/*  머신입장에서 방금 가공이 끝난 팔렛에서 처리할수 있는 작업이 없을경우,
				A 매트릭스에 가장 첫번째로 로딩된 순서대로 현재비어있는 머신에서 가공가능한 팔렛을 찾아 B 매트릭스에 추가한다. (A-> B)
				방금끝난팔렛은 가져온 팔렛의 자리에(B 매트릭스 첫번째자리) 둔다  (B-> A)*/


			if (M1_State == 0 && m1_empty == B[i].SelecPart.size() && B[i].Current_Mac == 1)
			{
				cout << "M1 가공할 수 있는 작업 없음 " << endl;
				int Mac = 1;
				auto After_Move = Incomplete_Move_B_To_A(PALLET_temp, Mac, B[i].Total_Pallet_No);

				PALLET_temp = After_Move.PALLET_temp;
			}
			else if (M2_State == 0 && m2_empty == B[i].SelecPart.size() && B[i].Current_Mac == 2)
			{
				int Mac = 2;
				cout << "M2 가공할 수 있는 작업 없음 " << endl;
				auto After_Move = Incomplete_Move_B_To_A(PALLET_temp, Mac, B[i].Total_Pallet_No);

				PALLET_temp = After_Move.PALLET_temp;
			}
			else if (M3_State == 0 && m3_empty == B[i].SelecPart.size() && B[i].Current_Mac == 3)
			{
				cout << "M3 가공할 수 있는 작업 없음 " << endl;
				int Mac = 3;
				auto After_Move = Incomplete_Move_B_To_A(PALLET_temp, Mac, B[i].Total_Pallet_No);

				PALLET_temp = After_Move.PALLET_temp;
			}
			cout << endl;
		}

		cout << "B (Go_Func)" << endl;
		for (int i = 0; i < B.size(); i++)
		{
			cout << "[P" << B[i].Total_Pallet_No << "]" << endl;
		}

		mux.unlock();


		New_Matrix(PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	}
};



void MACHINE1(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	time_t start, end;

	if (M1_State == 0)
	{
		cout << "------------------Machine1 Processing Start------------------" << endl;

		//Go_F_State = 0;
		M1_State = 1;
		start = CurrentTime_milliseconds();
		std::this_thread::sleep_for(std::chrono::milliseconds(Mac1_Part[0].PT_Trans_Time * 10));
		end = CurrentTime_milliseconds();


		/*cout << "M1 팔렛 끝났다고 가정하자 " << endl;
		for (int i = 0; i < 1; i++)
		{
			cout << "Pallet" << B[i].Total_Pallet_No << " ";
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					B[i].SelecPart[j].Oper[k].Complete = 1;
					B[i].SelecPart[j].OP_idx += 1;
					cout << "OP" << B[i].SelecPart[j].Oper[k].Operation_No << " (" << B[i].SelecPart[j].Oper[k].Complete << ") | ";
				}
			}
			cout << endl;
		}*/

		/*오퍼레이션 하나 끝났다. -> 가공 끝난 오퍼레이션은 가공 시간,끝 시간 기록 -> 오퍼레이션은 인덱스 올려준다. -> 파트 끝났다면 완료처리
		( B 매트릭스 위주로 돌아가고 다음 매트릭스 반복직전에 A(PALLET_temp), 원본인풋데이터 (PALLET) 로 데이터 옮겨줘야함) */
		for (int i = 0; i < B.size(); i++)
		{
			int Part_count = 0;
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				int OP_count = 0;
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					if (B[i].Total_Pallet_No == Mac1_Part[0].pallet_no &&
						B[i].SelecPart[j].Total_Part_No == Mac1_Part[0].part_no &&
						B[i].SelecPart[j].Oper[k].Operation_No == Mac1_Part[0].op_no + 1)
					{
						B[i].SelecPart[j].Oper[k].MAC1_Start_vec.push_back(start); //가공 시간, 끝 시간 기록
						B[i].SelecPart[j].Oper[k].MAC1_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						B[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						B[i].State = 0;

						//출력 
						/*mux.lock();
						cout << "M1 방금가공된 오퍼레이션 [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ")" << ") 팔렛state:" << B[i].State << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC1_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M1 시작 " << B[i].SelecPart[j].Oper[k].MAC1_Start_vec[h] << " "
								<< " M1 끝 " << B[i].SelecPart[j].Oper[k].MAC1_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}

		//A 에서 작업 끝난거 원본데이터에 기록
		for (int i = 0; i < PALLET.size(); i++)
		{
			int Part_count1 = 0;
			for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
			{
				int OP_count1 = 0;
				for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
				{
					if (PALLET[i].Total_Pallet_No == Mac1_Part[0].pallet_no &&
						PALLET[i].SelecPart[j].Total_Part_No == Mac1_Part[0].part_no &&
						PALLET[i].SelecPart[j].Oper[k].Operation_No == Mac1_Part[0].op_no + 1)
					{
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						PALLET[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						PALLET[i].State = 0;

						//출력 
						mux.lock();
						cout << "M1 방금가공된 오퍼레이션 [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") 팔렛state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M1 시작 " << PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec[h] << " "
								<< " M1 끝 " << PALLET[i].SelecPart[j].Oper[k].MAC1_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}

		//M1_State = 0;



		//끝난 팔렛 체크
		if (Go_F_State == 0)
		{
			M1_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//cout << "Go_f 실행중" << endl; 
		}


	}
	else
		cout << "M1 is already working" << endl;

};



/*void MACHINE2(int Go_F_State, int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part,
	vector<Pallet> PALLET_temp, vector<Pallet> B, std::mutex& mux)*/
void MACHINE2(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	time_t start, end;
	if (M2_State == 0)
	{
		cout << "------------------Machine2 Processing Start------------------" << endl;

		//Go_F_State = 0;
		M2_State = 1;
		start = CurrentTime_milliseconds();
		std::this_thread::sleep_for(std::chrono::milliseconds(Mac2_Part[0].PT_Trans_Time * 10));
		end = CurrentTime_milliseconds();

		/*
		cout <<"M2 팔렛 끝났다고 가정 << endl;
		for (int i = 1; i < 2; i++)
		{
			cout << "Pallet" << B[i].Total_Pallet_No << " ";
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					B[i].SelecPart[j].Oper[k].Complete = 1;
					B[i].SelecPart[j].OP_idx += 1;
					cout << "OP" << B[i].SelecPart[j].Oper[k].Operation_No << " (" << B[i].SelecPart[j].Oper[k].Complete << ") | ";
				}
			}
			cout << endl;
		}*/

		/*오퍼레이션 하나 끝났다. -> 가공 끝난 오퍼레이션은 가공 시간,끝 시간 기록 -> 오퍼레이션은 인덱스 올려준다. -> 파트 끝났다면 완료처리
		( B 매트릭스 위주로 돌아가고 다음 매트릭스 반복직전에 A(PALLET_temp), 원본인풋데이터 (PALLET) 로 데이터 옮겨줘야함) */
		int Pallet_count = 0;
		for (int i = 0; i < B.size(); i++)
		{
			int Part_count = 0;
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				int OP_count = 0;
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					if (B[i].Total_Pallet_No == Mac2_Part[0].pallet_no &&
						B[i].SelecPart[j].Total_Part_No == Mac2_Part[0].part_no &&
						B[i].SelecPart[j].Oper[k].Operation_No == Mac2_Part[0].op_no + 1)
					{
						B[i].SelecPart[j].Oper[k].MAC2_Start_vec.push_back(start); //가공 시간, 끝 시간 기록
						B[i].SelecPart[j].Oper[k].MAC2_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						B[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						B[i].State = 0;  // 오퍼레이션 가공하나 끝났으므로 팔렛 State 바꿔줌


						//출력 
						/*mux.lock();
						cout << "M2 방금가공된 오퍼레이션 [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ") 팔렛state:" << B[i].State << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC2_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M2 시작 " << B[i].SelecPart[j].Oper[k].MAC2_Start_vec[h] << " "
								<< " M2 끝 " << B[i].SelecPart[j].Oper[k].MAC2_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}




		//A 에서 작업 끝난거 원본데이터에 기록
		for (int i = 0; i < PALLET.size(); i++)
		{
			int Part_count1 = 0;
			for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
			{
				int OP_count1 = 0;
				for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
				{
					if (PALLET[i].Total_Pallet_No == Mac2_Part[0].pallet_no &&
						PALLET[i].SelecPart[j].Total_Part_No == Mac2_Part[0].part_no &&
						PALLET[i].SelecPart[j].Oper[k].Operation_No == Mac2_Part[0].op_no + 1)
					{
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						PALLET[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						//PALLET[i].State = 0;

						//출력 
						mux.lock();
						cout << "M2 방금가공된 오퍼레이션 [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") 팔렛state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M2 시작 " << PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec[h] << " "
								<< " M2 끝 " << PALLET[i].SelecPart[j].Oper[k].MAC2_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}

		//M2_State = 0;





		//끝난 팔렛 체크
		if (Go_F_State == 0)
		{
			M2_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//cout << "Go_f 실행중" << endl;
		}

	}
	else
		cout << "M2 is already working" << endl;
};

/*void MACHINE3(int Go_F_State, int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part,
	vector<Pallet> PALLET_temp, vector<Pallet> B, std::mutex& mux)*/
void MACHINE3(int PalletInSys, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part, vector<Pallet> PALLET_temp,
	Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	time_t start, end;
	if (M3_State == 0)
	{
		cout << "------------------Machine3 Processing Start------------------" << endl;

		//Go_F_State = 0;
		M3_State = 1;
		start = CurrentTime_milliseconds();
		std::this_thread::sleep_for(std::chrono::milliseconds(Mac3_Part[0].PT_Trans_Time * 10));
		end = CurrentTime_milliseconds();

		/*
		cout <<"M3 팔렛 끝났다고 가정 << endl;
		for (int i = 2; i < 3; i++)
		{
			cout << "Pallet" << B[i].Total_Pallet_No << " ";
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					B[i].SelecPart[j].Oper[k].Complete = 1;
					B[i].SelecPart[j].OP_idx += 1;
					cout << "OP" << B[i].SelecPart[j].Oper[k].Operation_No << " (" << B[i].SelecPart[j].Oper[k].Complete << ") | ";
				}
			}
			cout << endl;
		}*/

		/*오퍼레이션 하나 끝났다. -> 가공 끝난 오퍼레이션은 가공 시간,끝 시간 기록 -> 오퍼레이션은 인덱스 올려준다. -> 파트 끝났다면 완료처리
		( B 매트릭스 위주로 돌아가고 다음 매트릭스 반복직전에 A(PALLET_temp), 원본인풋데이터 (PALLET) 로 데이터 옮겨줘야함) */
		int Pallet_count = 0;
		for (int i = 0; i < B.size(); i++)
		{
			int Part_count = 0;
			for (int j = 0; j < B[i].SelecPart.size(); j++)
			{
				int OP_count = 0;
				for (int k = 0; k < B[i].SelecPart[j].Num_Operation; k++)
				{
					if (B[i].Total_Pallet_No == Mac3_Part[0].pallet_no &&
						B[i].SelecPart[j].Total_Part_No == Mac3_Part[0].part_no &&
						B[i].SelecPart[j].Oper[k].Operation_No == Mac3_Part[0].op_no + 1)
					{
						B[i].SelecPart[j].Oper[k].MAC3_Start_vec.push_back(start); //가공 시간, 끝 시간 기록
						B[i].SelecPart[j].Oper[k].MAC3_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						B[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						B[i].State = 0;  // 오퍼레이션 가공하나 끝났으므로 팔렛 State 바꿔줌


						//출력 
						/*mux.lock();
						cout << "M3 방금가공된 오퍼레이션 [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ")" << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC3_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M3 시작 " << B[i].SelecPart[j].Oper[k].MAC3_Start_vec[h] << " "
								<< " M3 끝 " << B[i].SelecPart[j].Oper[k].MAC3_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}

		//A 에서 작업 끝난거 원본데이터에 기록
		for (int i = 0; i < PALLET.size(); i++)
		{
			int Part_count1 = 0;
			for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
			{
				int OP_count1 = 0;
				for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
				{
					if (PALLET[i].Total_Pallet_No == Mac3_Part[0].pallet_no &&
						PALLET[i].SelecPart[j].Total_Part_No == Mac3_Part[0].part_no &&
						PALLET[i].SelecPart[j].Oper[k].Operation_No == Mac3_Part[0].op_no + 1)
					{
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //방금 끝난 오퍼레이션 완료 처리 후 
						PALLET[i].SelecPart[j].OP_idx++;  //인덱스 올려준다.
						PALLET[i].State = 0;

						//출력 
						mux.lock();
						cout << "M3 방금가공된 오퍼레이션 [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") 팔렛state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M3 시작 " << PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec[h] << " "
								<< " M3 끝 " << PALLET[i].SelecPart[j].Oper[k].MAC3_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //완료된 파트 기록 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix에서 방금 끝난 팔렛을 구분하기 위한 표시. 해당 팔렛이 B Matrix에서 지워질때 "B[i].Complete = 0;" 으로 되돌려놓는다. 
		}


		//M3_State = 0;



		//끝난 팔렛 체크
		if (Go_F_State == 0)
		{
			M3_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//	cout << "Go_f 실행중" << endl;
		}

	}
	else
		cout << "M3 is already working" << endl;
};



void Compare_Trans_vs_MaxPT(Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max,
	MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //이 함수를 재사용 하고싶거든 파라미터를 통일 시키시오 반.드.시
{
	/*	로딩되는 팔렛 원본데이터 -> PALLET
	FIND_MAX_PT, FIND_MIN_DUE, FIND_MIN_PT 에서 사용되는 팔렛 A Matrix -> PALLET_temp
	가공중인 팔렛 B Matrix -> B   */




	time_t comptime;
	comptime = CurrentTime_milliseconds();
	cout << "Compare Trans Time VS Max PT로 들어온 시간  " << comptime << endl;
	cout << "-----------------Compare Trans Time VS Max PT-------------------" << endl;


	//InitializeSystem.TransTime = 10; //머신간 이동시간 
	cout << "머신간이동시간:" << InitializeSystem.TransTime << endl;

	//M1_State = 1; 
	//M3_State = 1; //test
	//M2_State = 1;
	if (M1_State == 0)
	{
		cout << "M1 is available" << endl;
	}
	if (M2_State == 0)
	{
		cout << "M2 is available" << endl;
	}
	if (M3_State == 0)
	{
		cout << "M3 is available" << endl;
	}

	vector<Pallet> PALLET_temp(PALLET.size());  //PALLET 인풋데이터원본 , PALLET_temp 임시 인풋데이터
	//vector<Pallet> B;

	PALLET_temp = PALLET;
	vector <mac> Mac1_Part; //최소납기, 최소 가공시간을 찾는 단계를 거쳐 선택된 파트 
	vector <mac> Mac2_Part;
	vector <mac> Mac3_Part;



	//오퍼레이션 바꿔보고 싶으면 여기서 테스트
	//cout << "PALLET_temp" << PALLET_temp[0].Total_Pallet_No << " " << "PART" << PALLET_temp[0].SelecPart[0].Total_Part_No << " OP" << PALLET_temp[0].SelecPart[0].OP_idx << endl;
	//cout << "PALLET" << PALLET[0].Total_Pallet_No << " " << "PART" << PALLET[0].SelecPart[0].Total_Part_No << " OP" << PALLET[0].SelecPart[0].OP_idx << endl;
	//PALLET_temp[0].SelecPart[0].OP_idx += 1;  //머신 가공 끝나고 PALLET_temp[i].SelecPart[j].OP_idx 증가 시켜야함 
	//PALLET[0].SelecPart[0].OP_idx += 1;	



	//작업끝난 팔렛, 작업중인 팔렛, 작업중인 머신 , 머신개수 이상의팔렛을 지운뒤 나머지만 Pallet 매트릭스 형태로 집어넣어야 한다.★★★

	auto Max_PT = FIND_MAX_PT(InitializeSystem, PALLET_temp, Matrix_For_Max, mux); //최대가공시간 : Max_PT.temp_pallet[0]                                                                               
	PALLET_temp = Max_PT.PALLET_temp;


	if (InitializeSystem.TransTime > Max_PT.temp_pallet[0].processing_time)
	{
		mux.lock();
		cout << "이동시간이 더 큼 -> 놀고있는 가장 가까운 머신 부터 납기가장 짧은 파트(오퍼레이션) 탐색" << endl;
		mux.unlock();

		auto Min_Due = FIND_MIN_DUE(InitializeSystem, PALLET_temp, MATRIX_DUE, mux);
		Mac1_Part = Min_Due.MAC1_temp;  	//임시벡터에서 선택된 파트 옮김 
		Mac2_Part = Min_Due.MAC2_temp;
		Mac3_Part = Min_Due.MAC3_temp;
		//B = Min_Due.B;
		PALLET_temp = Min_Due.PALLET_temp;
	}


	else
	{
		mux.lock();
		cout << "최대가공시간이 더 큼 -> 놀고있는 가장 가까운 머신부터 가공+이동시간 가장 작은 파트(오퍼레이션) 탐색" << endl;
		auto Min_PT_TT = FIND_MIN_PT(InitializeSystem, PALLET_temp, MATRIX, mux);
		mux.unlock();

		Mac1_Part = Min_PT_TT.MAC1_temp;
		Mac2_Part = Min_PT_TT.MAC2_temp;
		Mac3_Part = Min_PT_TT.MAC3_temp;
		//B = Min_PT_TT.B;
		PALLET_temp = Min_PT_TT.PALLET_temp;

	}




	//선택된 파트 
	mux.lock();
	cout << "머신" << Mac1_Part[0].mac_no << " 선택된 파트: [Pallet" << Mac1_Part[0].pallet_no << "] P" << Mac1_Part[0].part_no
		<< " OP" << Mac1_Part[0].op_no + 1 << " 가공+이동시간" << Mac1_Part[0].PT_Trans_Time << endl;
	cout << "머신" << Mac2_Part[0].mac_no << " 선택된 파트: [Pallet" << Mac2_Part[0].pallet_no << "] P" << Mac2_Part[0].part_no
		<< " OP" << Mac2_Part[0].op_no + 1 << " 가공+이동시간" << Mac2_Part[0].PT_Trans_Time << endl;
	cout << "머신" << Mac3_Part[0].mac_no << " 선택된 파트: [Pallet" << Mac3_Part[0].pallet_no << "] P" << Mac3_Part[0].part_no
		<< " OP" << Mac3_Part[0].op_no + 1 << " 가공+이동시간" << Mac3_Part[0].PT_Trans_Time << endl;
	mux.unlock();




	for (int i = 0; i < PALLET.size(); i++) //계속 새로 로딩되는 팔렛pool PALLET에서 woring중인 팔렛 표시  -> 작업끝나면 	PALLET[i].State = 0; 으로 되돌리기 
	{
		if (PALLET[i].Total_Pallet_No == Mac1_Part[0].pallet_no || PALLET[i].Total_Pallet_No == Mac2_Part[0].pallet_no || PALLET[i].Total_Pallet_No == Mac3_Part[0].pallet_no)
			PALLET[i].State = 1;
	}



	//선택된 파트 가공처리  
	std::future<void> Thread1 = std::async(std::launch::async, MACHINE1,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread2 = std::async(std::launch::async, MACHINE2,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread3 = std::async(std::launch::async, MACHINE3,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));






	time_t comptime2;
	comptime2 = CurrentTime_milliseconds();

	mux.lock();
	printf("뿌뿌뿌뿌뿌뿌뿌뿌\n");
	printf("Compare_Trans_vs_MaxPT에서 로딩된 팔렛 개수 %d (시간%d) \n", PALLET.size(), comptime2);
	for (int i = 0; i < PALLET.size(); i++)
	{
		printf("[%d] ", PALLET[i].Total_Pallet_No);
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			printf("P%d ", PALLET[i].SelecPart[j].Total_Part_No);
		}
		if (PALLET[i].SelecPart.size() > 0)
			printf("(state:%d) ", PALLET[i].State);
		else
			printf(" ");

		printf("\n");
	}
	mux.unlock();





	/*(B)는 머신에 투입후 오퍼레이션 하나 끝나면 끝난 팔렛 있는지, 있다면 몇개가 끝났는지 개수 확인후(A)에 팔렛 들어온 순서대로 작업끝난팔렛 개수만큼(B)로 끌고온다
	, 없다면 오퍼레이션 끝난 팔렛을(B) -> (A)가장 위로 이동 */


	//머신 가공 끝나고 PALLET_temp, PALLET 의 OP_idx 하나씩 증가시키기  ex) PALLET[0].SelecPart[0].OP_idx += 1;


	//종료조건

	//for (int i = 0; i < PALLET.size(); i++)
	//{
	//	for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
	//	{
	//		for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
	//		{
	//			if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
	//			{
	//				p_count++;
	//				if (p_count == 2)
	//				{
	//					//return ;
	//					exit(0);
	//				}
	//			}
	//		}
	//	}
	//}
}




auto AsyncLoading(Initialize InitializeSystem,
	vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX,
	int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	std::mutex mux2;

	time_t LU1_start, LU2_start, LU3_start, LU4_start;
	time_t LU1_end, LU2_end, LU3_end, LU4_end;


	std::thread LUSTATION1([&]() {
		auto LU1 = std::async(std::launch::async, [&]() {

			if (P1 < InitializeSystem.PALLET_LU1.size())
			{
				LU1_start = CurrentTime_milliseconds();
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				LU1_end = CurrentTime_milliseconds();

				InitializeSystem.PALLET_LU1[P1].LU1.LD_Start_vec.push_back(LU1_start);
				InitializeSystem.PALLET_LU1[P1].LU1.LD_End_vec.push_back(LU1_end);

				mux.lock();
				PALLET.push_back(InitializeSystem.PALLET_LU1[P1]);
				cout << "                          ★로딩발생★  [Pallet" << InitializeSystem.PALLET_LU1[P1].Total_Pallet_No << "]" << endl;
				mux.unlock();

				P1++;
			}
			return 0;
		});
	});


	std::thread LUSTATION2([&]() {
		auto LU2 = std::async(std::launch::async, [&]() {

			if (P2 < InitializeSystem.PALLET_LU2.size())
			{
				LU2_start = CurrentTime_milliseconds();
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				LU2_end = CurrentTime_milliseconds();

				InitializeSystem.PALLET_LU2[P2].LU2.LD_Start_vec.push_back(LU2_start);
				InitializeSystem.PALLET_LU2[P2].LU2.LD_End_vec.push_back(LU2_end);

				mux.lock();
				PALLET.push_back(InitializeSystem.PALLET_LU2[P2]);
				cout << "                          ★로딩발생★  [Pallet" << InitializeSystem.PALLET_LU2[P2].Total_Pallet_No << "]" << endl;
				mux.unlock();

				P2++;
			}
			return 0;
		});
	});


	std::thread LUSTATION3([&]() {
		auto LU3 = std::async(std::launch::async, [&]() {

			if (P3 < InitializeSystem.PALLET_LU3.size())
			{
				LU3_start = CurrentTime_milliseconds();
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				LU3_end = CurrentTime_milliseconds();

				InitializeSystem.PALLET_LU3[P3].LU3.LD_Start_vec.push_back(LU3_start);
				InitializeSystem.PALLET_LU3[P3].LU3.LD_End_vec.push_back(LU3_end);

				mux.lock();
				PALLET.push_back(InitializeSystem.PALLET_LU3[P3]);
				cout << "                          ★로딩발생★  [Pallet" << InitializeSystem.PALLET_LU3[P3].Total_Pallet_No << "]" << endl;
				mux.unlock();

				P3++;
			}
			return 0;
		});
	});


	std::thread LUSTATION4([&]() {
		auto LU4 = std::async(std::launch::async, [&]() {

			if (P4 < InitializeSystem.PALLET_LU4.size())
			{
				LU4_start = CurrentTime_milliseconds();
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				LU4_end = CurrentTime_milliseconds();

				InitializeSystem.PALLET_LU4[P4].LU4.LD_Start_vec.push_back(LU4_start);
				InitializeSystem.PALLET_LU4[P4].LU4.LD_End_vec.push_back(LU4_end);

				mux.lock();
				PALLET.push_back(InitializeSystem.PALLET_LU4[P4]);
				cout << "                          ★로딩발생★  [Pallet" << InitializeSystem.PALLET_LU4[P4].Total_Pallet_No << "]" << endl;
				mux.unlock();

				P4++;
			}
			return 0;
		});
	});


	LUSTATION1.join();
	LUSTATION2.join();
	LUSTATION3.join();
	LUSTATION4.join();


	mux.lock();
	cout << "                          ★로딩발생★  들어온 팔렛 개수? " << PALLET.size() << endl; //들어온 팔렛 개수 
	mux.unlock();

	struct After_Load {
		Initialize InitializeSystem;
		vector<MatrixMax> Matrix_For_Max; MatrixMin MATRIX_DUE; MatrixMin MATRIX;
		int Num_P; int P1; int P2; int P3; int P4; std::mutex& mux;
	};
	return After_Load{ InitializeSystem,
		Matrix_For_Max, MATRIX_DUE, MATRIX,
		Num_P, P1, P2, P3, P4, mux };
}



void Buffer(Initialize InitializeSystem,
	int PalletInSys, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE,
	MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux)
{
	time_t st;
	st = CurrentTime_milliseconds();
	mux.lock();
	cout << "                          ★로딩발생★  PALLET.size() : " << PALLET.size() << endl;
	cout << "                          ★로딩발생★  팔렛몇번들어왓니?" << endl;
	mux.unlock();

	for (int i = 0; i < PALLET.size(); i++)
	{
		mux.lock();
		cout << "                             ====[" << PALLET[i].Total_Pallet_No << "]";
		for (int j = 0; j < PALLET[i].LU1.LD_Start_vec.size(); j++)
			cout << "LD start : " << PALLET[i].LU1.LD_Start_vec[j] << " LD end:" << PALLET[i].LU1.LD_End_vec[j] << endl;
		for (int j = 0; j < PALLET[i].LU2.LD_Start_vec.size(); j++)
			cout << "LD start : " << PALLET[i].LU2.LD_Start_vec[j] << " LD end:" << PALLET[i].LU2.LD_End_vec[j] << endl;
		for (int j = 0; j < PALLET[i].LU3.LD_Start_vec.size(); j++)
			cout << "LD start : " << PALLET[i].LU3.LD_Start_vec[j] << " LD end:" << PALLET[i].LU3.LD_End_vec[j] << endl;
		for (int j = 0; j < PALLET[i].LU4.LD_Start_vec.size(); j++)
			cout << "LD start : " << PALLET[i].LU4.LD_Start_vec[j] << " LD end:" << PALLET[i].LU4.LD_End_vec[j] << endl;
		mux.unlock();
	}

	/*mux.lock();
	cout << "Buffer에 쌓인 팔렛 개수. 쌓여야 A 부를수 있어  " << PALLET.size() << endl; //들어온 팔렛 개수
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "쌓인 팔렛 번호 " << PALLET[i].Total_Pallet_No << endl;
	}
	mux.unlock();
	*/


	/*PALLET[i].SelecPart[j].Oper[h].Mac[h].Depend 형태로. Depend[0] 선행,
	  PALLET[i].SelecPart[j].Depend[0].Oper[h].Mac[h].Depend 형태로. Depend[1] 후행  으로 가공*/
	  //cout << "----------------들어온 general 파트 테스트 " << endl;
	for (int i = 0; i < PALLET.size(); i++)
	{
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					if (PALLET[i].SelecPart[j].Dependency == -2)
					{
						//cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " ";
						//cout << "(general:" << PALLET[i].SelecPart[j].Dependency << ")" << endl;
					}
					if (PALLET[i].SelecPart[j].Dependency == -1)
					{
						//cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " ";
						//cout << "(Depend:" << PALLET[i].SelecPart[j].Oper[k].Mac[h].Depend[0].Dependency << ")" << endl;

						if (PALLET[i].SelecPart[j].Depend[0].Dependency == 0)
						{
							PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend = new Depend[1];
							PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency = PALLET[i].SelecPart[j].Depend[0].Dependency;
							/*cout << "P" << PALLET[i].SelecPart[j].Depend[0].Total_Part_No << " ";
							cout << "(Depend:" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << ")" << endl;
							cout << "P" << PALLET[i].SelecPart[j].Total_Part_No <<  " OP" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Operation_No << " "
								<< "Mac" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Mac_No << " "
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Processing_Time <<" ("
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << ") " <<endl;*/
						}
					}
				}
			}
		}
	}
	//cout << "----------------들어온 dependency 파트 선행 작업 테스트 " << endl;

	//Dependency 선행 파트만 따로 출력
	/*for (int i = 0; i < PALLET.size(); i++)
	{
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{

					if (PALLET[i].SelecPart[j].Dependency == -1)
					{
						cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No << " "
							<< "Mac" << PALLET[i].SelecPart[j].Oper[k].Mac[h].Mac_No << " "
							<< PALLET[i].SelecPart[j].Oper[k].Mac[h].Processing_Time << " ("
							<< PALLET[i].SelecPart[j].Dependency << ") " << endl;
					}

				}
			}
		}
	}*/

	//cout << "----------------들어온 dependency 파트 후행 작업 테스트 " << endl;

	//Dependency 후행 파트만 따로 출력
	/*for (int i = 0; i < PALLET.size(); i++)
	{
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					if (PALLET[i].SelecPart[j].Dependency == -1)
					{

						if (PALLET[i].SelecPart[j].Depend[0].Dependency == 0)
						{

							cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Operation_No << " "
								<< "Mac" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Mac_No << " "
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Processing_Time << " ("
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << ") " << endl;
						}
					}
				}
			}
		}
	}*/
	/*for (int i = 0; i < PALLET.size(); i++)
	{
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					if (PALLET[i].SelecPart[j].Dependency == -1)
					{

						if (PALLET[i].SelecPart[j].Depend[0].Dependency == 0)
						{

							cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Operation_No << " "
								<< "Mac" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Mac_No << " "
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Processing_Time << " ("
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << ") " << endl;
						}
					}
				}
			}
		}
	}*/
	/*for (int i = 0; i < PALLET.size(); i++)
	{
		for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		{
			for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
			{
				for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
				{
					if (PALLET[i].SelecPart[j].Dependency == -1)
					{

						if (PALLET[i].SelecPart[j].Depend[0].Dependency == 0)
						{

							cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Operation_No << " "
								<< "Mac" << PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Mac_No << " "
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Processing_Time << " ("
								<< PALLET[i].SelecPart[j].Depend[0].Oper[k].Mac[h].Depend[0].Dependency << ") " << endl;
						}
					}
				}
			}
		}
	}*/

	/*cout << "Pallet[" << PALLET[0].Total_Pallet_No << "]" << endl;
	cout << " Part" << PALLET[0].SelecPart[0].Total_Part_No << " type" << PALLET[0].SelecPart[0].Part_Type
		<< " Oper1의 머신개수" << PALLET[0].SelecPart[0].Oper[0].Num_AlterMac << " " << " Dependency" << PALLET[0].SelecPart[0].Dependency << endl;
	cout << "후행작업" << PALLET[0].SelecPart[0].Depend[0].Total_Part_No << " type" << PALLET[0].SelecPart[0].Part_Type
		<< " Oper1의 머신개수" << PALLET[0].SelecPart[0].Oper[0].Num_AlterMac <<" Dependency" << PALLET[0].SelecPart[0].Depend[0].Dependency<<endl;*/


	Compare_Trans_vs_MaxPT(InitializeSystem, PalletInSys,
		Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, mux);   //동기 


};

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!InputThePallet 함수 PALLET 찍히나 테스트할 차례 . 머신2번 안찍히는거 인풋데이터 문제 있어서 생기는거임 !!!!!!!!!!!!
void InputThePallet(Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX,
	int Num_P, int P1, int P2, int P3, int P4)
{
	static std::mutex mux;
	time_t c, cc, ccc;

	LU1_State = 1;
	LU2_State = 1;
	LU3_State = 1;
	LU4_State = 1;

	auto After_Load = AsyncLoading(InitializeSystem,
		Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));

	InitializeSystem = After_Load.InitializeSystem;
	Matrix_For_Max = After_Load.Matrix_For_Max;
	MATRIX_DUE = After_Load.MATRIX_DUE;
	MATRIX = After_Load.MATRIX;
	Num_P = After_Load.Num_P;
	P1 = After_Load.P1;
	P2 = After_Load.P2;
	P3 = After_Load.P3;
	P4 = After_Load.P4;


	LU1_State = 0;
	LU2_State = 0;
	LU3_State = 0;
	LU4_State = 0;






	if (Num_P == (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1)  //첫번째 재귀함수 바로 버퍼로
	{
		std::future<void> Buff = std::async(std::launch::async, Buffer, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux)); 	//버퍼 비동기   

		if (LU1_State == 0 && LU2_State == 0 && LU3_State == 0 && LU4_State == 0)
			std::future<void> After_Load2 = std::async(std::launch::async, InputThePallet, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P - 1, P1, P2, P3, P4);

	}
	else if (Num_P > 0 && Num_P < (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1) //두번째 재귀함수부터
	{

		if (LU1_State == 0 && LU2_State == 0 && LU3_State == 0 && LU4_State == 0)
			std::future<void> After_Load2 = std::async(std::launch::async, InputThePallet, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P - 1, P1, P2, P3, P4);
	}
	else if (Num_P == 0) //팔렛 다 올라갈때까지 재귀탐 
		return;


	mux.lock();
	cout << "InputThePallet에서 쌓인 팔렛 개수 " << PALLET.size() << endl; //들어온 팔렛 개수
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "쌓인 팔렛 번호 " << PALLET[i].Total_Pallet_No << endl;
	}cout << endl;
	mux.unlock();



};





void Loading(Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int PalletInSys)
{
	//나중에 로딩타임 길게 잡아놓고 그안에서 전체(머신포함) sleep으로 시간 체크해나가는 방식으로 큰그림 !!!!!!!!!!!!!!

	//std::vector<Pallet> PALLET; //들어온 팔렛 (A)
	/* InitializeSystem.PALLET_LU3[P3].LD_Start_vec(st), InitializeSystem.PALLET_LU3[P3].LD_End_vec(end) 시간저장 후
	   => PALLET[idx] = InitializeSystem.PALLET_LU3[P3]; */

	int	P1 = 0;   //LU1에 대기중인 팔렛 PALLET 으로 옮기는 인덱스 
	int	P2 = 0;
	int	P3 = 0;
	int	P4 = 0;



	int Num_P = (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1;
	cout << "Num_P" << Num_P << endl;





	InputThePallet(InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4);



};


bool CMP(const Part &Order1, const Part &Order2) {//due date 비교함수 
	if (Order1.Due_Date < Order2.Due_Date)
	{
		return true;
	}
	else if (Order1.Due_Date == Order2.Due_Date)
	{
		return Order1.Due_Date < Order2.Due_Date;
	}
	else
	{
		return false;
	}
	/*변수 Min값 찾는방법
	int MinDue;
	MinDue = *min_element(InitializeSystem.Part_Duedate.begin(),
	InitializeSystem.Part_Duedate.end());*/
};



void Copy_Arr(Part From[], Part To[], int n) {
	int i = 0;
	for (i = 0; i < n; i++)
	{
		To[i] = From[i];
	};
};



void Algorithm::Palletizing(Initialize InitializeSystem)
{
	std::cout << "<★★Phase1_Palletizing-EDD★★>" << endl;
	//1. Palletizing
	//1-1. 먼저 전체파트(오더) 납기 작은순으로 정렬(구조체벡터 납기기준으로 sorting) 
	Total_Part_No = InitializeSystem.Num_Total_Part - (InitializeSystem.Num_Dependency / 2);
	cout << "Total_Part_No " << Total_Part_No << endl;
	sort(InitializeSystem.AllPart, InitializeSystem.AllPart + Total_Part_No, CMP);

	//총 파트를 로딩스테이션 개수만큼 나눔 ->로딩스테이션 별로 파트가 대기중
	NumPartLU = Total_Part_No / InitializeSystem.Num_LU_Station;
	reminder = Total_Part_No % InitializeSystem.Num_LU_Station;
	cout << "파트 각" << NumPartLU << "개씩 각 LU에대기.나머지 " << reminder << "개는 LU1로가" << endl;

	NumPart_LU1 = NumPartLU + reminder;
	NumPart_LU2 = NumPartLU;
	NumPart_LU3 = NumPartLU;
	NumPart_LU4 = NumPartLU;

	Part_LU1 = new Part[NumPartLU + reminder];
	Part_LU2 = new Part[NumPartLU];
	Part_LU3 = new Part[NumPartLU];
	Part_LU4 = new Part[NumPartLU];


	//Part 로딩스테이션으로 분배하는부분 line 588~595 (수정하고시픙면 sort(EDD)함수를 분배후 실행)
	Copy_Arr(InitializeSystem.AllPart, Part_LU1, NumPartLU + reminder);  //전체파트 각 로딩스테이션별로 분배 ex)파트 10개 -> LU1 4개,LU2 2개,LU3 2개,LU4 2개
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder, Part_LU2, NumPartLU);
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder + NumPartLU, Part_LU3, NumPartLU);
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder + NumPartLU + NumPartLU, Part_LU4, NumPartLU);


	Part_LU1_vec.insert(Part_LU1_vec.end(), &Part_LU1[0], &Part_LU1[NumPart_LU1]);  //배열 "Part_LU1" -> 벡터 "Part_LU1_vec" copy
	Part_LU2_vec.insert(Part_LU2_vec.end(), &Part_LU2[0], &Part_LU2[NumPart_LU2]);
	Part_LU3_vec.insert(Part_LU3_vec.end(), &Part_LU3[0], &Part_LU3[NumPart_LU3]);
	Part_LU4_vec.insert(Part_LU4_vec.end(), &Part_LU4[0], &Part_LU4[NumPart_LU4]);


	cout << "No." << setw(5) << "Type." << setw(5) << "Due." << setw(5) << "LUstation." << setw(5) << "  (Part_LU1_vec)" << endl;
	for (int i = 0; i < Part_LU1_vec.size(); i++)
	{
		Part_LU1_vec[i].LD_Station = 1;
		cout << setw(2) << Part_LU1_vec[i].Total_Part_No << setw(4) << Part_LU1_vec[i].Part_Type << setw(7)
			<< Part_LU1_vec[i].Due_Date << setw(7) << Part_LU1_vec[i].LD_Station << endl;
	}
	for (int i = 0; i < Part_LU2_vec.size(); i++)
	{
		Part_LU2_vec[i].LD_Station = 2;
		cout << setw(2) << Part_LU2_vec[i].Total_Part_No << setw(4) << Part_LU2_vec[i].Part_Type << setw(7)
			<< Part_LU2_vec[i].Due_Date << setw(7) << Part_LU2_vec[i].LD_Station << endl;
	}
	for (int i = 0; i < Part_LU3_vec.size(); i++)
	{
		Part_LU3_vec[i].LD_Station = 3;
		cout << setw(2) << Part_LU3_vec[i].Total_Part_No << setw(4) << Part_LU3_vec[i].Part_Type << setw(7)
			<< Part_LU3_vec[i].Due_Date << setw(7) << Part_LU3_vec[i].LD_Station << endl;
	}
	for (int i = 0; i < Part_LU4_vec.size(); i++)
	{
		Part_LU4_vec[i].LD_Station = 4;
		cout << setw(2) << Part_LU4_vec[i].Total_Part_No << setw(4) << Part_LU4_vec[i].Part_Type << setw(7)
			<< Part_LU4_vec[i].Due_Date << setw(7) << Part_LU4_vec[i].LD_Station << endl;
	}

	//===================================LU_STATION1=================================================
	//1-2. 각 팔렛의 픽스쳐타입과 같은파트타입을 찾는다(fixture_type에 따라 올릴 Part 매칭 시키기)
	std::cout << "<LUSTATION1>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU1.size(); i++)
	{
		InitializeSystem.PALLET_LU1[i].Total_Pallet_No = i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU1[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU1[i].Fixture_vec.size(); j++)
		{
			cout << "-----현재 Fixture type : " << InitializeSystem.PALLET_LU1[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU1_temp;
			for (int k = 0; k < Part_LU1_vec.size(); k++)  //Part_LU1_vec 로딩스테이션별 대기중인 파트 
			{
				cout << "현재 대기중인 파트 " << Part_LU1_vec[k].Total_Part_No << "의 type" << Part_LU1_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU1[i].Fixture_vec[j].Fixture_No == Part_LU1_vec[k].Part_Type) //fixture타입과 같은 part들 중에서 duedate가장 짧은것끼리 팔렛단이로 묶어 로딩시킬것임.
				{

					//cout << "현재 대기중인 파트중 픽스쳐타입 맞는파트" << Part_LU1_vec[k].Total_Part_No << "의 type" << Part_LU1_vec[k].Part_Type <<endl;
					cout << "현재 Part Type:" << Part_LU1_vec[k].Part_Type << endl;
					//cout << "현재 Part Due Date:" << Part_LU1_vec[k].Due_Date << endl;

					//1-3. fixture_type과 같은 Part_Type인 파트중에서 가장 Due_Date이 짧은 Part_No를 선택  
					Part_LU1_temp.push_back(Part_LU1_vec[k]);
					cout << "후보파트No :" << Part_LU1_temp[count].Total_Part_No << endl;
					cout << "그것의Type :" << Part_LU1_temp[count].Part_Type << endl;
					cout << "그것의DueDate:" << Part_LU1_temp[count].Due_Date << endl;

					cout << "==> 그것중 납기짧은거: " << Part_LU1_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!여기 이상함

					InitializeSystem.PALLET_LU1[i].SelecPart.push_back(Part_LU1_temp[0]);   //선택된파트 팔렛(구조체)에 장착               

					//1-4. 선택된 파트는 파트pool(Part_LU1_vec)에서 지운다.
					Part_LU1_vec.erase(Part_LU1_vec.begin() + k, Part_LU1_vec.begin() + k + 1);
					count++;
					break;
				}
				else
				{
					//	//cout << "No matching" << endl; 
				}
			}
		}
	}

	//Phase1. LU Station1 팔렛타이징 완료
	cout << "Phase1. LU Station1 팔렛타이징 완료  " << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU1.size(); i++)
	{
		cout << "[pallet" << InitializeSystem.PALLET_LU1[i].Total_Pallet_No << "]- "
			<< "(size:" << InitializeSystem.PALLET_LU1[i].SelecPart.size() << ") ";
		for (int j = 0; j < InitializeSystem.PALLET_LU1[i].SelecPart.size(); j++)
		{
			cout << InitializeSystem.PALLET_LU1[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}
	//===================================LU_STATION2=================================================
	//1-2. 각 팔렛의 픽스쳐타입과 같은파트타입을 찾는다(fixture_type에 따라 올릴 Part 매칭 시키기)
	std::cout << "<LUSTATION2>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU2.size(); i++)
	{
		InitializeSystem.PALLET_LU2[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU2[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU2[i].Fixture_vec.size(); j++)
		{
			cout << "-----현재 Fixture type : " << InitializeSystem.PALLET_LU2[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU2_temp;
			for (int k = 0; k < Part_LU2_vec.size(); k++)  //Part_LU2_vec 로딩스테이션별 대기중인 파트 
			{
				cout << "현재 대기중인 파트 " << Part_LU2_vec[k].Total_Part_No << "의 type" << Part_LU2_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU2[i].Fixture_vec[j].Fixture_No == Part_LU2_vec[k].Part_Type) //fixture타입과 같은 part들 중에서 duedate가장 짧은것끼리 팔렛단이로 묶어 로딩시킬것임.
				{

					//cout << "현재 대기중인 파트중 픽스쳐타입 맞는파트" << Part_LU2_vec[k].Total_Part_No << "의 type" << Part_LU2_vec[k].Part_Type <<endl;
					cout << "현재 Part Type:" << Part_LU2_vec[k].Part_Type << endl;
					//cout << "현재 Part Due Date:" << Part_LU2_vec[k].Due_Date << endl;

					//1-3. fixture_type과 같은 Part_Type인 파트중에서 가장 Due_Date이 짧은 Part_No를 선택  
					Part_LU2_temp.push_back(Part_LU2_vec[k]);
					cout << "후보파트No :" << Part_LU2_temp[count].Total_Part_No << endl;
					cout << "그것의Type :" << Part_LU2_temp[count].Part_Type << endl;
					cout << "그것의DueDate:" << Part_LU2_temp[count].Due_Date << endl;

					cout << "==> 그것중 납기짧은거: " << Part_LU2_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!여기 이상함

					InitializeSystem.PALLET_LU2[i].SelecPart.push_back(Part_LU2_temp[0]);   //선택된파트 팔렛(구조체)에 장착               

					//1-4. 선택된 파트는 파트pool(Part_LU2_vec)에서 지운다.
					Part_LU2_vec.erase(Part_LU2_vec.begin() + k, Part_LU2_vec.begin() + k + 1);
					count++;
					break;
				}
				else
				{
					//	//cout << "No matching" << endl; 
				}
			}
		}
	}

	//Phase1. LU Station1 팔렛타이징 완료
	cout << "Phase1. LU Station2 팔렛타이징 완료  " << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU2.size(); i++)
	{
		cout << "[pallet" << InitializeSystem.PALLET_LU2[i].Total_Pallet_No << "]- "
			<< "(size:" << InitializeSystem.PALLET_LU2[i].SelecPart.size() << ") ";
		for (int j = 0; j < InitializeSystem.PALLET_LU2[i].SelecPart.size(); j++)
		{
			cout << InitializeSystem.PALLET_LU2[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}

	//===================================LU_STATION3=================================================
	//1-2. 각 팔렛의 픽스쳐타입과 같은파트타입을 찾는다(fixture_type에 따라 올릴 Part 매칭 시키기)
	std::cout << "<LUSTATION3>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU3.size(); i++)
	{
		InitializeSystem.PALLET_LU3[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + InitializeSystem.PALLET_LU2.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU3[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU3[i].Fixture_vec.size(); j++)
		{
			cout << "-----현재 Fixture type : " << InitializeSystem.PALLET_LU3[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU3_temp;
			for (int k = 0; k < Part_LU3_vec.size(); k++)  //Part_LU3_vec 로딩스테이션별 대기중인 파트 
			{
				cout << "현재 대기중인 파트 " << Part_LU3_vec[k].Total_Part_No << "의 type" << Part_LU3_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU3[i].Fixture_vec[j].Fixture_No == Part_LU3_vec[k].Part_Type) //fixture타입과 같은 part들 중에서 duedate가장 짧은것끼리 팔렛단이로 묶어 로딩시킬것임.
				{

					//cout << "현재 대기중인 파트중 픽스쳐타입 맞는파트" << Part_LU3_vec[k].Total_Part_No << "의 type" << Part_LU3_vec[k].Part_Type <<endl;
					cout << "현재 Part Type:" << Part_LU3_vec[k].Part_Type << endl;
					//cout << "현재 Part Due Date:" << Part_LU3_vec[k].Due_Date << endl;

					//1-3. fixture_type과 같은 Part_Type인 파트중에서 가장 Due_Date이 짧은 Part_No를 선택  
					Part_LU3_temp.push_back(Part_LU3_vec[k]);
					cout << "후보파트No :" << Part_LU3_temp[count].Total_Part_No << endl;
					cout << "그것의Type :" << Part_LU3_temp[count].Part_Type << endl;
					cout << "그것의DueDate:" << Part_LU3_temp[count].Due_Date << endl;

					cout << "==> 그것중 납기짧은거: " << Part_LU3_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!여기 이상함

					InitializeSystem.PALLET_LU3[i].SelecPart.push_back(Part_LU3_temp[0]);   //선택된파트 팔렛(구조체)에 장착               

					//1-4. 선택된 파트는 파트pool(Part_LU3_vec)에서 지운다.
					Part_LU3_vec.erase(Part_LU3_vec.begin() + k, Part_LU3_vec.begin() + k + 1);
					count++;
					break;
				}
				else
				{
					//	//cout << "No matching" << endl; 
				}
			}
		}
	}

	//Phase1. LU Station3 팔렛타이징 완료
	cout << "Phase1. LU Station3 팔렛타이징 완료  " << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU3.size(); i++)
	{
		cout << "[pallet" << InitializeSystem.PALLET_LU3[i].Total_Pallet_No << "]- "
			<< "(size:" << InitializeSystem.PALLET_LU3[i].SelecPart.size() << ") ";
		for (int j = 0; j < InitializeSystem.PALLET_LU3[i].SelecPart.size(); j++)
		{
			cout << InitializeSystem.PALLET_LU3[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}



	//===================================LU_STATION4=================================================
//1-2. 각 팔렛의 픽스쳐타입과 같은파트타입을 찾는다(fixture_type에 따라 올릴 Part 매칭 시키기)
	std::cout << "<LUSTATION4>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU4.size(); i++)
	{
		InitializeSystem.PALLET_LU4[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + InitializeSystem.PALLET_LU2.size() + InitializeSystem.PALLET_LU3.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU4[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU4[i].Fixture_vec.size(); j++)
		{
			cout << "-----현재 Fixture type : " << InitializeSystem.PALLET_LU4[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU4_temp;
			for (int k = 0; k < Part_LU4_vec.size(); k++)  //Part_LU1_vec 로딩스테이션별 대기중인 파트 
			{
				cout << "현재 대기중인 파트 " << Part_LU4_vec[k].Total_Part_No << "의 type" << Part_LU4_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU4[i].Fixture_vec[j].Fixture_No == Part_LU4_vec[k].Part_Type) //fixture타입과 같은 part들 중에서 duedate가장 짧은것끼리 팔렛단이로 묶어 로딩시킬것임.
				{

					//cout << "현재 대기중인 파트중 픽스쳐타입 맞는파트" << Part_LU1_vec[k].Total_Part_No << "의 type" << Part_LU1_vec[k].Part_Type <<endl;
					cout << "현재 Part Type:" << Part_LU4_vec[k].Part_Type << endl;
					//cout << "현재 Part Due Date:" << Part_LU1_vec[k].Due_Date << endl;

					//1-3. fixture_type과 같은 Part_Type인 파트중에서 가장 Due_Date이 짧은 Part_No를 선택  
					Part_LU4_temp.push_back(Part_LU4_vec[k]);
					cout << "후보파트No :" << Part_LU4_temp[count].Total_Part_No << endl;
					cout << "그것의Type :" << Part_LU4_temp[count].Part_Type << endl;
					cout << "그것의DueDate:" << Part_LU4_temp[count].Due_Date << endl;

					cout << "==> 그것중 납기짧은거: " << Part_LU4_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!여기 이상함

					InitializeSystem.PALLET_LU4[i].SelecPart.push_back(Part_LU4_temp[0]);   //선택된파트 팔렛(구조체)에 장착               

					//1-4. 선택된 파트는 파트pool(Part_LU1_vec)에서 지운다.
					Part_LU4_vec.erase(Part_LU4_vec.begin() + k, Part_LU4_vec.begin() + k + 1);
					count++;
					break;
				}
				else
				{
					//	//cout << "No matching" << endl; 
				}
			}
		}
	}

	//Phase1. LU Station1 팔렛타이징 완료
	cout << "Phase1. LU Station4 팔렛타이징 완료  " << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU4.size(); i++)
	{
		cout << "[pallet" << InitializeSystem.PALLET_LU4[i].Total_Pallet_No << "]- "
			<< "(size:" << InitializeSystem.PALLET_LU4[i].SelecPart.size() << ") ";
		for (int j = 0; j < InitializeSystem.PALLET_LU4[i].SelecPart.size(); j++)
		{
			cout << InitializeSystem.PALLET_LU4[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << endl;
	}

	cout << "----------팔렛타이징 완료--------------" << endl << endl;






	/*auto LUSTATION = Loading(InitializeSystem, LU1_State, LU2_State, LU3_State,
	M1_State, M2_State, M3_State, Matrix_For_Max, MATRIX_DUE, MATRIX);//실질적인 시뮬레이션 스타트 포인트. 여기서시작해서 여기서끝남 */

	Loading(InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, PalletInSys);



	//★★지금 로딩스테이션 문제가 팔렛 전체를 다 동기화시켜버림. 이부분 로딩스테이션 함수 탈때 LU_State =1 이면 
	//앞에 팔렛 로딩 남은시간 만큼 기다렸다 들어가야함!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 그 후 버퍼도 팔랫개수만큼 비동기로 처리되는지 체크해봐야됨
};


