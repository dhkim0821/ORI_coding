//������=====================================================================================================
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
	fin >> Num_Dependency_Pre; //dependency���� 
	fin >> Num_Dependency_Suc; //dependency����
	fin >> LU_Time;


	//Transportation time
	int Trans_temp;
	fin >> Trans_temp;
	TransTime = Trans_temp * 3; //�ӽŰ��̵��ð�

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
	for (int i = 0; i < Num_Parttype; i++)  //�Ϲ� + ���� 
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

	for (int i = 0; i < Num_Dependency_Suc; i++) //���� 
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

	//��ǲ������ ��� (�Ϲ�+������Ʈ)
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

	//��ǲ������ ��� (������Ʈ)
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


	/*cout << "�Ϲ� + ���� + ���� ��Ʈ------- " << endl;
	for (int i = 0; i < Num_Parttype; i++) //�Ϲ�+����+����
	{
		cout << Part_Type[i].PartType << " " << Part_Type[i].NumOperation << " " << Part_Type[i].Dependency << endl;
		cout << Part_Type[i].NumDemand << endl;
		if (Part_Type[i].Dependency == -1)
		{
			cout << Part_Type[i].Dependency_Suc[0].PartType << " " << Part_Type[i].Dependency_Suc[0].NumOperation << " "
				<< Part_Type[i].Dependency_Suc[0].Dependency <<  " (���� ��ƮŸ�Գѹ�, ���ۼ�, �������)" << endl;
			cout << Part_Type[i].Dependency_Suc[0].NumDemand << "(���� ��Ʈ��)" << endl;
		}
		for (int j = 0; j < Part_Type[i].NumDemand; j++)
		{
			cout << Part_Type[i].Demand[j].Due_Date << endl;
			if (Part_Type[i].Dependency == -1)
			{
				cout <<  Part_Type[i].Dependency_Suc[0].Demand[j].Due_Date << " (���� ����)" << endl;
			}
		}
		for (int j = 0; j < Part_Type[i].NumOperation; j++)
		{
			cout << Part_Type[i].Oper[j].Num_AlterMac << endl;
			if (Part_Type[i].Dependency == -1)
			{
				cout << Part_Type[i].Dependency_Suc[0].Oper[j].Num_AlterMac << " (���� �ӽż�)" << endl ;
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
						<< Part_Type[i].Dependency_Suc[0].Oper[j].Mac[k].Mac_No <<  "���� �ӽ��̸�, �����ð�, �ӽŹ�ȣ" <<endl;
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
			AllPart[iter].Total_Part_No = iter + 1;  //��ü��Ʈ��ȣ 
			AllPart[iter].Part_Type = Part_Type[i].PartType; //��ƮŸ�Թ�ȣ 
			AllPart[iter].Part_No = Part_Type[i].Demand[j].Part_No;  //��ƮŸ�Գ����� ��Ʈ��ȣ 
			AllPart[iter].Dependency = Part_Type[i].Dependency;
			AllPart[iter].Due_Date = Part_Type[i].Demand[j].Due_Date;
			AllPart[iter].Num_Operation = Part_Type[i].NumOperation;
			AllPart[iter].Complete = 0;  //�۾���������0, ������1
			AllPart[iter].State = 0; //1:������, 0:����� 
			AllPart[iter].OP_idx = 0;

			AllPart[iter].Oper = new Operation[AllPart[iter].Num_Operation];
			for (int k = 0; k < Part_Type[i].NumOperation; k++)
			{
				AllPart[iter].Oper[k].Operation_No = k + 1;
				AllPart[iter].Oper[k].Complete = 0; //�۾���������0, ������1
				AllPart[iter].Oper[k].State = 0;  //1:������, 0:����� 
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

			if (AllPart[iter].Dependency == -1) //dependency ������Ʈ�� ����  
			{
				AllPart[iter].Depend = new DependPart[1];

				AllPart[iter].Depend[0].Total_Part_No = iter + 1;  //��ü��Ʈ��ȣ 
				AllPart[iter].Depend[0].Part_Type = Part_Type[i].Dependency_Suc[0].PartType; //��ƮŸ�Թ�ȣ 
				AllPart[iter].Depend[0].Part_No = Part_Type[i].Dependency_Suc[0].Demand[j].Part_No;  //��ƮŸ�Գ����� ��Ʈ��ȣ 
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

	//AllPart ��� 
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
	/*PALLET_temp[pallet][��üpart][oper][mac][dependency]
	[dependency] �ε����� [0] ����, [1] ���� ���� size()�� 2.
	[��üpart]��
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
	�� ��� �ö� ��Ʈ ���� 7��. 1�� dependency��ƮŸ���� ������ ������*/

	//��ǲ�����ʹ� dependency ������� �߱������ϰ� �޾����� PALLET_temp���� ��ó�� 5���� �迭 or���ͷ� �����Ǿ�� ��
	//dependency part�� �ϳ��� ��Ʈ�� �ι� �����ϴ� ����̱� ������ �ȷ�Ÿ��¡�Ǹ� �ý��۾ȿ��� dependency �����۾�����, �����۾����� �Ǵ��Ͽ� �����ȴ�. 
	//������ �� 10�� ��Ʈ�� �ö����� ��� 7���� �ö󰣰���. ���۷��̼�ó�� ������õ� �ִ°��� 


}

bool Max_PT1(const mac &PT1, const mac &PT2) {//��Ʈ�����󿡼� �ִ� �����ð�  
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


auto FIND_MAX_PT(Initialize InitializeSystem, std::vector<Pallet> PALLET_temp, vector<MatrixMax> Matrix_For_Max, std::mutex& mux) //�Լ���Ȱ�� = �Ķ���� ���߱� �ڡڸӽſ��� ���� �ϳ� ������ PALLET, PALLET_temp�� �ٲﵥ���� ������Ʈ 
{
	mux.lock();
	cout << "------------Find Maximum Operation Processing Time --------------" << endl;
	mux.unlock();


	cout << "PALLET_temp size" << PALLET_temp.size() << endl;
	cout << "PALLET size " << PALLET.size() << endl;

	Matrix_For_Max.resize(PALLET_temp.size());  //�ٽ� ��Ʈ���� �θ��� �Ķ���ͷ� �׶��׶� ��Ȳ�� �´� PALLET,PALLET_temp( std::vector<Pallet> PALLET )���·� ������ �ٲ㼭 ����־�ߵ� �ڡ�

	mux.lock();
	cout << "Matrix �ȷ� size?" << Matrix_For_Max.size() << endl;
	mux.unlock();


	for (int i = 0; i < Matrix_For_Max.size(); i++)  // Matrix_For_Max (�׶��׶� �����Ǵ� ��Ʈ����) : PALLET_temp (��ǲ������)
	{
		//�̺κ��� B�� �ȷ� �ٽ� ����ִºκ� PALLET_temp[i].State ==1 �ΰ͵��� ���� �ȵȴ�.  
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

			int OP_index = Matrix_For_Max[i].part[j].op_index;   // ���⼭���� OP_index �ڡ� PALLET_temp[i].SelecPart[j].OP_idx  : ���۷��̼� �ϳ� ������ +1 �������������			

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
				for (int k = 0; k < OP_index + 1; k++)   // �ڡڡڿ��۷��̼� �ϳ� ������ �ش� ��Ʈ "PALLET[i].SelecPart[j].OP_idx+1" +1 ��������ԡڡڡ�
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

					//���� 3���� ��ŷ���̶��? -> ���۷��̼� �ϳ��� ������ ��Ʈ���������ǹǷ� �׷��Ͼ���
					//working���� 1�� �ӽ� ����� 
					for (vector<int>::size_type h = 0; h < temp_mac.size(); ) {
						if (temp_mac[h].mac_no == 1 && M1_State == 1) {
							temp_mac.erase(temp_mac.begin() + h);
						}
						else {
							h++;
						}
					}
					//working���� 2�� �ӽ� ����� 
					for (vector<int>::size_type h = 0; h < temp_mac.size(); ) {
						if (temp_mac[h].mac_no == 2 && M2_State == 1) {
							temp_mac.erase(temp_mac.begin() + h);
						}
						else {
							h++;
						}
					}
					//working���� 3�� �ӽ� ����� 
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
						cout << "�̰Űɸ��� ���۷��̼� ���� �ȳ����µ� ��Ʈ���� ���� �Ȱ���." << endl;
					}

					for (int h = 0; h < temp_mac.size(); h++)
					{
						//cout << "mac" << temp_mac[h].mac_no << " " << temp_mac[h].processing_time << " available" << endl;
					}
					sort(temp_mac.begin(), temp_mac.end(), Max_PT1);
					//cout << "                                (available mac�� max PT" << temp_mac[0].processing_time << " Mac" << temp_mac[0].mac_no << ") " << endl;
					temp_op[k] = temp_mac[0];
				}
				sort(temp_op.begin(), temp_op.end(), Max_PT1);
				//cout << "OP�� LPT" << temp_op[0].processing_time << endl;
				temp_part[j] = temp_op[0];
				if (temp_part.size() < 1)       //����ִ� �ȷ����� error���� 
					temp_part[j].processing_time = 0;
			}
			sort(temp_part.begin(), temp_part.end(), Max_PT1);
			//cout << "��Ʈ�� LPT:" << temp_part[0].processing_time << endl;
			temp_pallet[i] = temp_part[0];
		}

		else
		{
			temp_pallet[i].processing_time = 1;  //����ִ� �ȷ����� error���� 
		}
	}
	sort(temp_pallet.begin(), temp_pallet.end(), Max_PT1);

	mux.lock();
	cout << "�ȷ��� LPT:" << temp_pallet[0].processing_time << " [Pallet" << temp_pallet[0].pallet_no << "] Part" << temp_pallet[0].part_no
		<< " OP" << temp_pallet[0].op_no << " Mac" << temp_pallet[0].mac_no << endl;
	mux.unlock();

	struct Max_PT {
		Initialize InitializeSystem; std::vector<mac>temp_pallet; std::vector<Pallet> PALLET_temp; vector<MatrixMax> Matrix_For_Max;
	};
	return Max_PT{ InitializeSystem, temp_pallet, PALLET_temp, Matrix_For_Max };
};


bool CMP_DUE(const mac &DUE1, const mac &DUE2) {//due date ���Լ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 
	if (M1_State == 0)
	{
		sort(MAC1_temp.begin(), MAC1_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M1���� �ּҰ�:" << MAC1_temp[0].due << "(" << MAC1_temp[0].processing_time << ", " << MAC1_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC1_temp[0].pallet_no << "], P"
			<< MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //�ּ� ���� ���õǸ� �ش� �ȷ� state = 1 �� �ٲ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 
	if (M2_State == 0)
	{
		sort(MAC2_temp.begin(), MAC2_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M2���� �ּҰ�:" << MAC2_temp[0].due << "(" << MAC2_temp[0].processing_time << ", " << MAC2_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC2_temp[0].pallet_no << "], P"
			<< MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //�ּ� ���� ���õǸ� �ش� �ȷ� state = 1 �� �ٲ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 
	if (M3_State == 0)
	{
		sort(MAC3_temp.begin(), MAC3_temp.end(), CMP_DUE);

		mux.lock();
		cout << "M3���� �ּҰ�:" << MAC3_temp[0].due << "(" << MAC3_temp[0].processing_time << ", " << MAC3_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC3_temp[0].pallet_no << "], P"
			<< MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << " ";
		mux.unlock();

		for (int i = 0; i < Matrix_d.size(); i++) //�ּ� ���� ���õǸ� �ش� �ȷ� state = 1 �� �ٲ� 
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

	/*��Ʈ��������
	PALLET_temp.size() => ���������� �ȷ� ����
	SelecPart.size() => ���� �ȷ��� �ö� ��Ʈ ����
	NumMac => �ý��ۿ��� �� �ӽŰ���

	�����ð��� �̵��ð� �߰�
	��ŷ���� �ӽ� ���ܽ�Ű��
	�ӽŴ� �ȷ� �ϳ����� ����
	��Ʈ �ӽŰ�����ŭ ����
	*/
	int NumMac = InitializeSystem.Num_Machine;   //�ӽŰ���
	int NumPallet; //�ȷ����� 
	int MinDue_M1 = 0; //�ӽź� �ּ� ���� 
	int MinDue_M2 = 0;
	int MinDue_M3 = 0;


	//��ǲ������ PALLET_temp ���
	/*mux.lock();
	cout << "PALLET_temp �߳����� üũ" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++) //PALLET_temp �߳����� üũ
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




	//1.��ǲ������ ���� 
	int p = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {  // �������(��Ʈ�� �ö�) �ȷ� ���� ����
		if (PALLET_temp[i].SelecPart.size() > 0)
			p++;
	}

	NumPallet = p;   //������� �ȷ�����
	vector<Pallet> Matrix_d(p);  //������� �ȷ� ������ŭ ���� ������ ��ǲ������ �ű�� 

	int u = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {
		if (PALLET_temp[i].SelecPart.size() > 0)
		{
			Matrix_d[u] = PALLET_temp[i];
			u++;
		}
	}

	//2.��Ʈ���� ���� 
	MATRIX_DUE.aryprocess = new int**[NumPallet];
	for (int x = 0; x < NumPallet; x++)
	{
		MATRIX_DUE.aryprocess[x] = new int *[NumPallet];
		for (int y = 0; y < Matrix_d[x].SelecPart.size(); y++)
		{
			MATRIX_DUE.aryprocess[x][y] = new int[NumMac];
		}
	}


	//3.��Ʈ������ ������ ��ǲ 
	int part_count = 0; //��Ʈ���� 
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


	//��Ʈ���� ��� (����)
	cout << "(��Ʈ �� ����)" << endl;
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


	//��Ʈ���� ��� (�����ð�)
	mux.lock();
	cout << "(���۷��̼� �� �����ð�)" << endl;
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


	//4.�̵��ð� �߰� 
	mux.lock();
	cout << "Transportation time" << endl;
	for (int i = 0; i < NumMac + 1; i++) {
		for (int j = 0; j < NumMac + 1; j++)
			cout << InitializeSystem.Transportation_Time[i][j] << " ";
		cout << endl;
	}
	mux.unlock();

	mux.lock();
	cout << "(���۷��̼� �� ���� + �̵��ð�)     �غ���ִ� �ӽ� 999999" << endl;
	mux.unlock();

	int Trans;
	for (int i = 0; i < NumPallet; i++) {
		int Current_Position = Matrix_d[i].Current_Position; //���� �ȷ� ��ġ. ���۷��̼� �ϳ� ���������� �ȷ� ��ġ (PALLET_temp[0].Current_Position) �ٲ�����ԡڡ�

		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;  // OP index
				int Mac_Position = Matrix_d[i].SelecPart[j].Oper[0].Mac[v].Mac_No; //machine index

				//���� �����ǿ��� �� �ӽ��� ���������� ���� �̵��ð� ��� 
				for (int i = 0; i < NumMac + 1; i++) {
					for (int j = 0; j < NumMac + 1; j++)
					{
						Trans = InitializeSystem.Transportation_Time[Current_Position][Mac_Position];  //���� �ȷ� ��ġ [i] , �� �ӽŵ��� ��ġ [j]
					}
				}
				if (Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
					Trans = 999999;

				//�����ð� + �̵��ð� 
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



	//working ���� �ȷ� test
	/*cout << "��ŷ���� �ȷ� 888888" << endl;
	Matrix_p[0].State = 1;
	Matrix_p[2].State = 1;
	cout << "Pallet" << Matrix_p[0].Total_Pallet_No << "is working" << endl;
	cout << "Pallet" << Matrix_p[2].Total_Pallet_No << "is working" << endl;*/


	//5. working���� �ȷ� ����
	for (int i = 0; i < NumPallet; i++) {  //�ӽ�1 
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 0)
				{
					if (M1_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 1)  //�ӽ��� ����ְ�, �ȷ��� ��� �ְ�, �ӽ��� �����ϸ� ��������ǲ 
					{
						int temp1 = MATRIX_DUE.aryprocess[i][j][v]; 	// ���� + �̵��ð� 

						MAC1_temp[a].pallet_no = Matrix_d[i].Total_Pallet_No;  //�ּҳ��Ⱑ ��� ��Ʈ ������۷��̼� ���� Ȯ���ϱ� ���Ѱ� 
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
						MAC1_temp[a].PT_Trans_Time = 888888;  //�ӽ��� ���ϰ��̽⳪ �ȷ��� ���ϰ� �ְų� �ӽ��� ��������� Large number(888888) �־ ���� ���� �ʵ��� ��
					}
					a++;
				}
			}
		}
	}

	//5. working���� �ӽ� ���� �� �ȷ� �ߺ����� ����
	auto Result1 = MIN_DUE1(MinDue_M1, MAC1_temp, Matrix_d, mux);
	MinDue_M1 = Result1.MinDue_M1;
	MAC1_temp = Result1.MAC1_temp;  //MAC1_temp[0] : ���õ� �ȷ�,��Ʈ �� ���� �� ��� ����Ǿ� ���� 
	Matrix_d = Result1.Matrix_d;
	mux.lock();
	//cout << "���õ� Part" << MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << " Due" << MAC1_temp[0].due << " (mac state" << M1_State << ")" << endl;
	cout << "(M1_State" << M1_State << ")" << endl;

	mux.unlock();



	for (int i = 0; i < NumPallet; i++) { //�ӽ�2
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 1)
				{
					if (M2_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 2)
					{

						int temp2 = MATRIX_DUE.aryprocess[i][j][v]; //�����ð� + �̵��ð� ������� 
						//mac2.push_back(temp2); //�ӽ�2 ���⸸ �� ����

						MAC2_temp[b].pallet_no = Matrix_d[i].Total_Pallet_No; //�ּҰ����ð��� ��� ��Ʈ�ð����� Ȯ���ϱ� ���Ѱ� 
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
						MAC2_temp[b].PT_Trans_Time = 888888;  //working���� �ȷ��� 888888 
					}
					b++;
				}
			}
		}
	}
	auto Result2 = MIN_DUE2(MinDue_M2, MAC2_temp, Matrix_d, mux);
	MinDue_M2 = Result2.MinDue_M2;
	MAC2_temp = Result2.MAC2_temp;  //MAC1_temp[0] : ���õ� �ȷ�,��Ʈ �� ���� �� ��� ����Ǿ� ���� 
	Matrix_d = Result2.Matrix_d;
	mux.lock();
	//cout << "���õ� Part" << MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << " Due" << MAC2_temp[0].due << " (mac state" << M2_State << ")" << endl;
	cout << "(M2_State" << M2_State << ")" << endl;
	mux.unlock();


	for (int i = 0; i < NumPallet; i++) {  //�ӽ�1 
		for (int j = 0; j < Matrix_d[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_d[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 2)
				{
					if (M3_State == 0 && Matrix_d[i].State == 0 && Matrix_d[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No == 3)
					{
						int temp3 = MATRIX_DUE.aryprocess[i][j][v]; 	//�����ð� + �̵��ð� 

						MAC3_temp[c].pallet_no = Matrix_d[i].Total_Pallet_No;  //�ּҳ��Ⱑ ��� ��Ʈ ������۷��̼� ���� Ȯ���ϱ� ���Ѱ� 
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
						MAC3_temp[c].PT_Trans_Time = 888888;  //working���� �ȷ��� ���⿡ 888888 �־ ���� ���� �ʵ��� ��
					}
					c++;
				}
			}
		}
	}

	//5. working���� �ӽ� ���� �� �ȷ� �ߺ����� ����
	auto Result3 = MIN_DUE3(MinDue_M3, MAC3_temp, Matrix_d, mux);
	MinDue_M3 = Result3.MinDue_M3;
	MAC3_temp = Result3.MAC3_temp;  //MAC1_temp[0] : ���õ� �ȷ�,��Ʈ �� ���� �� ��� ����Ǿ� ���� 
	Matrix_d = Result3.Matrix_d;  //Matrix_d : �ȷ� state
	mux.lock();
	//cout << "���õ� Part" << MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << " Due" << MAC3_temp[0].due << " (mac state" << M3_State << ")" << endl;
	cout << "(M3_State" << M3_State << ")" << endl;
	mux.unlock();



	/*PALLET_temp (A) ���� ���õ� �ȷ���(state:1)  ->  (B) �� �̵�
	PALLET_temp (A) ����Ʈ���� ����
	 (B)�� �ӽſ� ������ ���۷��̼� �ϳ� ������ ���� �ȷ� �ִ���, �ִٸ� ��� �������� ���� Ȯ���� (A)�� �ȷ� ���� ������� �۾������ȷ� ������ŭ (B)�� ����´�
														  , ���ٸ� ���۷��̼� ���� �ȷ��� (B) -> (A)���� ���� �̵� */

	mux.lock();
	if (B.size() == 0) //���� �ʱ⿡ B Matrix ���� 
	{
		//PALLET_temp (A) ���� ���õ� �ȷ���(state:1)  ->  (B) �� �̵�  ->  PALLET_temp (A) ����Ʈ���� ����
		PALLET_temp = Matrix_d;
		cout << endl;
		cout << " PALLET_temp (A) ����غ��� (size:" << PALLET_temp.size() << ")" << endl;
		for (int i = 0; i < PALLET_temp.size(); i++)
		{
			cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
			for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
			{
				cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			}
			cout << "(state:" << PALLET_temp[i].State << ") " << endl;

			if (PALLET_temp[i].State == 1)   //���� �ȷ��� (B)�� �ű��� 
			{
				B.push_back(PALLET_temp[i]);
			}
		}
		cout << endl;

		for (int i = 0; i < PALLET_temp.size(); i++)  // PALLET_temp (A) ���� ���� 
		{
			if (PALLET_temp[i].State == 1)
			{
				PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
				i--;
			}
		}
	}

	else
		cout << "�ι�°���� �� B�ȿ��� min���� ã��" << endl;

	mux.unlock();



	mux.lock();
	cout << " (B) ����غ��� (size:" << B.size() << ")" << endl; // (B) �� �Ű������� Ȯ�� 
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
	cout << " (A) �����޴µ� �������� (size:" << PALLET_temp.size() << ") - �Լ� �ι�° Ż�����ʹ� B�� �����" << endl; // (A) �� ���������� Ȯ�� 
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

	for (int i = 0; i < B.size(); i++) //Go_Func���� �ȷ��� �����Ҽ� �ִ� �۾� ������ A <-> B�̵��� ���
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


	//�ӽź� ���õ� ��Ʈ(���۷��̼�)
	/*cout << "�ӽ�" << MAC1_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC1_temp[0].pallet_no << "] P" << MAC1_temp[0].part_no
		<< " OP" << MAC1_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC1_temp[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << MAC2_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC2_temp[0].pallet_no << "] P" << MAC2_temp[0].part_no
		<< " OP" << MAC2_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC2_temp[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << MAC3_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC3_temp[0].pallet_no << "] P" << MAC3_temp[0].part_no
		<< " OP" << MAC3_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC3_temp[0].PT_Trans_Time << endl;*/



	struct Min_Due {
		Initialize InitializeSystem; vector<Pallet> PALLET_temp; MatrixMin MATRIX_DUE;
		std::vector<mac> MAC1_temp; std::vector<mac> MAC2_temp; std::vector<mac> MAC3_temp;  vector<Pallet> B;
	};
	return Min_Due{ InitializeSystem, PALLET_temp, MATRIX_DUE, MAC1_temp, MAC2_temp, MAC3_temp, B };
};


bool CMP_PT(const mac &PT1, const mac &PT2) {//due date ���Լ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 
	if (M1_State == 0)
	{
		MinPT_M1 = *min_element(mac1.begin(), mac1.end());
		sort(MAC1_temp.begin(), MAC1_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M1���� �ּҰ�:" << MAC1_temp[0].processing_time << "(" << MAC1_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC1_temp[0].pallet_no << "], P"
			<< MAC1_temp[0].part_no << " OP" << MAC1_temp[0].op_no + 1 << endl;
		//mux.unlock();

		for (int i = 0; i < Matrix_p.size(); i++) //�ּ� �����ð� ���õǸ� �ش� �ȷ� state = 1 �� �ٲ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 
	if (M2_State == 0)
	{
		MinPT_M2 = *min_element(mac2.begin(), mac2.end());
		sort(MAC2_temp.begin(), MAC2_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M2���� �ּҰ�:" << MAC2_temp[0].processing_time << "(" << MAC2_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC2_temp[0].pallet_no << "], P"
			<< MAC2_temp[0].part_no << " OP" << MAC2_temp[0].op_no + 1 << endl;
		//mux.unlock();


		for (int i = 0; i < Matrix_p.size(); i++) //�����ð� �ּҰ��� �����Ǹ� �ش� �ȷ� state = 1 �� �ٲ� 
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
	//working���� �ӽ����� �ϰ� �ӽ�1->�ӽ�2->�ӽ�3 ������ �ּҰ� ã�� 

	if (M3_State == 0)
	{
		MinPT_M3 = *min_element(mac3.begin(), mac3.end());
		sort(MAC3_temp.begin(), MAC3_temp.end(), CMP_PT);

		//mux.lock();
		cout << "M3���� �ּҰ�:" << MAC3_temp[0].processing_time << "(" << MAC3_temp[0].PT_Trans_Time << ")" << " [Pallet" << MAC3_temp[0].pallet_no << "], P"
			<< MAC3_temp[0].part_no << " OP" << MAC3_temp[0].op_no + 1 << endl;
		//mux.unlock();

		for (int i = 0; i < Matrix_p.size(); i++) //�����ð� �ּҰ��� �����Ǹ� �ش� �ȷ� state = 1 �� �ٲ� 
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



auto FIND_MIN_PT(Initialize InitializeSystem, vector<Pallet> PALLET_temp, MatrixMin MATRIX, std::mutex& mux) //�Ķ����(PALLET, PALLET_temp) ��ü�� �ٲ��� ���;ߵ�  //PALLET_temp(��ǲ������)
{
	cout << "------Find Shortest Processing Time + Transportation Time-------" << endl;

	/*��Ʈ��������
	PALLET_temp.size() => ���������� �ȷ� ���� (O)
	SelecPart.size() => ���� �ȷ��� �ö� ��Ʈ ���� (O)
	NumMac => �ý��ۿ��� �� �ӽŰ��� (O)

	�����ð��� �̵��ð� �߰� (O)
	��ŷ���� �ӽ� ���ܽ�Ű�� (O)
	�ӽŴ� �ȷ� �ϳ����� ���� (O)
	��Ʈ �ӽŰ�����ŭ ���� (O)
	*/

	/*�ӽſ��� ���� �ϳ� ������
	1.�ӽ� state=0���� �ǵ��� ����
	2.�ȷ� state =0���� �ǵ��� ����
	3.�ȷ� �۾� �� �������� üũ
	4.���۷��̼� �ε��� ��ġ��
	5. dependency ��Ʈ���� üũ (?)
	*/
	int NumMac = InitializeSystem.Num_Machine;   //�ӽŰ���
	int NumPallet; //�ȷ����� 
	int MinPT_M1 = 0; //�ӽź� �ּ� �����ð�+�̵��ð�
	int MinPT_M2 = 0;
	int MinPT_M3 = 0;



	//���۷��̼� �ٲ�°� �׽�Ʈ 
	//cout << "Operation �ٲ�°� �׽�Ʈ " << endl; 
	//cout << "Pallet " << PALLET_temp[3].Total_Pallet_No << " Part" << PALLET_temp[3].SelecPart[0].Total_Part_No <<
	//"  Operation" << PALLET_temp[3].SelecPart[0].Oper[0].Operation_No
	//<< "   M1 " << PALLET_temp[3].SelecPart[0].Oper[0].Mac[0].Processing_Time << "   M2 "
	//<< PALLET_temp[3].SelecPart[0].Oper[0].Mac[1].Processing_Time << "   M3 "
	//<< PALLET_temp[3].SelecPart[0].Oper[0].Mac[2].Processing_Time << "  ---> operation " << PALLET_temp[3].SelecPart[0].Oper[0].Operation_No <<"�� ������" <<  endl;
	//PALLET_temp[3].SelecPart[0].OP_idx = 1;


	//��ǲ������ PALLET_temp ���
	/*cout << "PALLET_temp �߳����� üũ" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++) //PALLET_temp �߳����� üũ
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


	//1. ��ǲ������ ���� 
	int p = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {  // �������(��Ʈ�� �ö�) �ȷ� ���� ����
		if (PALLET_temp[i].SelecPart.size() > 0)
			p++;
	}

	NumPallet = p;   //������� �ȷ�����
	vector<Pallet> Matrix_p(p);  //������� �ȷ� ������ŭ ���� ������ ��ǲ������ �ű�� ( PALLET_temp -> Matrix_p )

	int u = 0;
	for (int i = 0; i < PALLET_temp.size(); i++) {
		if (PALLET_temp[i].SelecPart.size() > 0)
		{
			Matrix_p[u] = PALLET_temp[i];
			u++;
		}
	}



	//Matrix_p ���
	/*cout << "Matrix_p �� ���Գ� üũ" << endl;
	for (int i = 0; i < Matrix_p.size(); i++) //temp_p �߳����� üũ
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



	//2.��Ʈ���� ���� 
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


	//3.��Ʈ������ ������ ��ǲ 
	int part_count = 0; //��Ʈ���� 
	for (int i = 0; i < NumPallet; i++) {
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			part_count++;

			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
				MATRIX.aryprocess[i][j][v] = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
				//MATRIX.aryoper[i][j][v] = Matrix_p[i].SelecPart[j].Num_Operation;
				//MATRIX.arydepend[i][j][v] = Matrix_p[i].SelecPart[j].Dependency; // depend -2 ���¾� -1 ���� 0 ����	

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
	//��Ʈ���� ��� 
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
			cout << "(�����ð�)" << endl;
		}
	}

	//4.�̵��ð� �߰� 
	cout << "Transportation time" << endl;
	for (int i = 0; i < NumMac + 1; i++) {
		for (int j = 0; j < NumMac + 1; j++)
			cout << InitializeSystem.Transportation_Time[i][j] << " ";
		cout << endl;
	}

	cout << "����ִ� �ӽ� 999999" << endl;
	mux2.unlock();

	mux2.lock();
	int Trans;
	for (int i = 0; i < NumPallet; i++) {
		int Current_Position = Matrix_p[i].Current_Position; //���� �ȷ� ��ġ. ���۷��̼� �ϳ� ���������� �ȷ� ��ġ (PALLET_temp[0].Current_Position) �ٲ�����ԡڡ�

		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			for (int v = 0; v < NumMac; v++) {
				int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;  // OP index
				int Mac_Position = Matrix_p[i].SelecPart[j].Oper[0].Mac[v].Mac_No; //machine index

				//���� �����ǿ��� �� �ӽ��� ���������� ���� �̵��ð� ��� 
				for (int i = 0; i < NumMac + 1; i++) {
					for (int j = 0; j < NumMac + 1; j++)
					{
						Trans = InitializeSystem.Transportation_Time[Current_Position][Mac_Position];  //���� �ȷ� ��ġ [i] , �� �ӽŵ��� ��ġ [j]
					}
				}
				if (Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No < 0)
					Trans = 999999;


				//�����ð� + �̵��ð� 
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



	//working ���� �ȷ� test
	/*cout << "��ŷ���� �ȷ� 888888" << endl;
	Matrix_p[0].State = 1;
	Matrix_p[2].State = 1;
	cout << "Pallet" << Matrix_p[0].Total_Pallet_No << "is working" << endl;
	cout << "Pallet" << Matrix_p[2].Total_Pallet_No << "is working" << endl;*/


	//5. working���� �ȷ� ����
	for (int i = 0; i < NumPallet; i++) {  //�ӽ�1 
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {    // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 0)  //�ӽ�1 
				{
					if (M1_State == 0 && Matrix_p[i].State == 0) //�ӽ�1�� ����ְ� �ش� �ȷ��� ��������� ������ ��ǲ 
					{
						int temp1 = MATRIX.aryprocess[i][j][v];
						mac1.push_back(temp1);  //�ӽ�1 �����ð��� �� ���� 

						MAC1_temp[a].pallet_no = Matrix_p[i].Total_Pallet_No;  //�ּҰ����ð��� ��� ��Ʈ�ð����� Ȯ���ϱ� ���Ѱ� 
						MAC1_temp[a].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC1_temp[a].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC1_temp[a].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC1_temp[a].PT_Trans_Time = temp1;
						MAC1_temp[a].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;
					}

					else if (M1_State == 1 || Matrix_p[i].State == 1) //�ӽ��� ���ϰ� �ְų� �ȷ��� ���ϰ� ������ 
					{
						mac1.push_back(888888);
						MAC1_temp[a].processing_time = 0;
						MAC1_temp[a].PT_Trans_Time = 888888;  //�����ð�+�̵��ð��� 888888 �־ ���� ���� �ʵ��� ��
					}
					a++;
				}
			}
		}
	}
	//5. working���� �ӽ� ���� �� �ȷ� �ߺ����� ����
	auto Result1 = MIN_PT1(MinPT_M1, mac1, MAC1_temp, Matrix_p, mux);
	MinPT_M1 = Result1.MinPT_M1;
	mac1 = Result1.mac1;
	MAC1_temp = Result1.MAC1_temp;  // ��MAC1_temp[0] : ���õ� �ȷ�,��Ʈ �� �����ð�
	Matrix_p = Result1.Matrix_p;  //Matrix_p[i].State : �ȷ� state



	for (int i = 0; i < NumPallet; i++) { //�ӽ�2
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 1)  //�ӽ�2 
				{
					if (M2_State == 0 && Matrix_p[i].State == 0) //�ӽ�2 ����ְ� �ȷ��� ��������� ��������ǲ 
					{
						int temp2 = MATRIX.aryprocess[i][j][v];
						mac2.push_back(temp2); //�ӽ�2 �����ð��� �� ����

						MAC2_temp[b].pallet_no = Matrix_p[i].Total_Pallet_No; //�ּҰ����ð��� ��� ��Ʈ�ð����� Ȯ���ϱ� ���Ѱ� 
						MAC2_temp[b].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC2_temp[b].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC2_temp[b].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC2_temp[b].PT_Trans_Time = temp2;
						MAC2_temp[b].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;

					}

					else if (M2_State == 1 || Matrix_p[i].State == 1) //�ӽ��� ���ϰ� �ְų� �ȷ��� ���ϰ� ������ 
					{
						mac2.push_back(888888);
						MAC2_temp[b].processing_time = 0;
						MAC2_temp[b].PT_Trans_Time = 888888;  //Large number(888888) ��ǲ�ؼ� �ּҰ����� ���� �ȵǰ��� 

					}
					b++;
				}
			}
		}
	}
	auto Result2 = MIN_PT2(MinPT_M2, mac2, MAC2_temp, Matrix_p, mux);
	MinPT_M2 = Result2.MinPT_M2;
	mac2 = Result2.mac2;
	MAC2_temp = Result2.MAC2_temp;  // ��MAC2_temp[0] : ���õ� �ȷ�,��Ʈ �� �����ð�
	Matrix_p = Result2.Matrix_p; //Matrix_p[i].State : �ȷ� state


	for (int i = 0; i < NumPallet; i++) { //�ӽ�2
		for (int j = 0; j < Matrix_p[i].SelecPart.size(); j++) {
			int OP_idx = Matrix_p[i].SelecPart[j].OP_idx;
			for (int v = 0; v < NumMac; v++) {   // v=0 (�ӽ�1), v=1 (�ӽ�2), v=2(�ӽ�3)

				if (v == 2) //�ӽ�3
				{
					if (M3_State == 0 && Matrix_p[i].State == 0) //�ӽ��� ����ְ�, �ȷ��� ��� ������ ��������ǲ 
					{
						int temp3 = MATRIX.aryprocess[i][j][v];
						mac3.push_back(temp3); //�ӽ�3 �����ð��� �� ����

						MAC3_temp[c].pallet_no = Matrix_p[i].Total_Pallet_No; //�ּҰ����ð��� ��� ��Ʈ�ð����� Ȯ���ϱ� ���Ѱ� 
						MAC3_temp[c].part_no = Matrix_p[i].SelecPart[j].Total_Part_No;
						MAC3_temp[c].op_no = Matrix_p[i].SelecPart[j].OP_idx;
						MAC3_temp[c].processing_time = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Processing_Time;
						MAC3_temp[c].PT_Trans_Time = temp3;
						MAC3_temp[c].mac_no = Matrix_p[i].SelecPart[j].Oper[OP_idx].Mac[v].Mac_No;

					}
					else if (M3_State == 1 || Matrix_p[i].State == 1) //�ӽ��� ���ϰ� �ְų� �ȷ��� ���ϰ� ������
					{
						mac3.push_back(888888);
						MAC3_temp[c].processing_time = 0;
						MAC3_temp[c].PT_Trans_Time = 888888;  //Large number(888888) ��ǲ�ؼ� �ּҰ����� ���� �ȵǰ��� 

					}
					c++;
				}
			}
		}
	}

	auto Result3 = MIN_PT3(MinPT_M3, mac3, MAC3_temp, Matrix_p, mux);
	MinPT_M3 = Result3.MinPT_M3;
	mac3 = Result3.mac3;
	MAC3_temp = Result3.MAC3_temp;  // ��MAC3_temp[0] : ���õ� �ȷ�,��Ʈ �� �����ð�
	Matrix_p = Result3.Matrix_p; //Matrix_p[i].State : �ȷ� state


	mux2.lock();
	if (B.size() == 0) //���� �ʱ⿡ B Matrix ���� 
	{
		//PALLET_temp (A) ���� ���õ� �ȷ���(state:1)  ->  (B) �� �̵�  ->  PALLET_temp (A) ����Ʈ���� ����
		PALLET_temp = Matrix_p;
		cout << endl;
		cout << " PALLET_temp (A) ����غ��� (size:" << PALLET_temp.size() << ")" << endl;
		for (int i = 0; i < PALLET_temp.size(); i++)
		{
			cout << "[" << PALLET_temp[i].Total_Pallet_No << "] ";
			for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
			{
				cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";
			}
			cout << "(state:" << PALLET_temp[i].State << ") " << endl;

			if (PALLET_temp[i].State == 1)   //���� �ȷ��� (B)�� �ű��� 
			{
				B.push_back(PALLET_temp[i]);
			}
		}
		cout << endl;

		for (int i = 0; i < PALLET_temp.size(); i++)  // PALLET_temp (A) ���� ���� 
		{
			if (PALLET_temp[i].State == 1)
			{
				PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
				i--;
			}
		}
	}

	else
		cout << "�ι�°���� �� B�ȿ��� min���� ã��" << endl;

	mux2.unlock();


	cout << " (B) ����غ��� (size:" << B.size() << ")" << endl; // (B) �� �Ű������� Ȯ�� 
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
	cout << " (A) �����޴µ� �������� (size:" << PALLET_temp.size() << ") - �Լ� �ι�° Ż�����ʹ� B�� �����" << endl; // (A) �� ���������� Ȯ�� 
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


	for (int i = 0; i < B.size(); i++) //Go_Func���� �ȷ��� �����Ҽ� �ִ� �۾� ������ A <-> B�̵��� ���
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




	//�ӽź� ���õ� ��Ʈ(���۷��̼�)
	/*cout << "�ӽ�" << MAC1_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC1_temp[0].pallet_no << "] P" << MAC1_temp[0].part_no
		<< " OP" << MAC1_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC1_temp[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << MAC2_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC2_temp[0].pallet_no << "] P" << MAC2_temp[0].part_no
		<< " OP" << MAC2_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC2_temp[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << MAC3_temp[0].mac_no << " ���õ� ��Ʈ: [Pallet" << MAC3_temp[0].pallet_no << "] P" << MAC3_temp[0].part_no
		<< " OP" << MAC3_temp[0].op_no + 1 << " ����+�̵��ð�" << MAC3_temp[0].PT_Trans_Time << endl;*/



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
	MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //�� �Լ��� ���� �ϰ�Ͱŵ� �Ķ���͸� ���� ��Ű�ÿ� ��.��.��) 
{
	mux.lock();

	/*
	  -����
	  1. (�Ϸ�� �ȷ� �������) Machine1 -> Go_func -> New_Matrix ���۷��̼� ���� �Ǵ���
	  2. (�Ϸ�� �ȷ� �������) Machine1-> New_Matrix ���۷��̼� ����Ǵ���
	  3. (�ӽ��� �� ����������)
	  4. (�ӽ��� �Ѱ��� ���ϰ� �ִ°��)
	  -����
	  1. �ӽ��� �� ��� ������� (B��Ʈ���� �ȷ��� ���ÿ� �� ���������)
	   1-1. ��Ʈ���� B���� �ִ밡���ð� VS �ӽŰ��̵��ð�
	   1-2. �ӽź��� �ӽŰ��̵��ð��� ũ�� �ּҳ���, �ִ밡���ð��� ũ�� �ּ��̵�+�����ð� �� ���۷��̼��� ����.
	  2. �ӽ��� �Ѱ��� ���ϰ� ���� ��� (B��Ʈ������ �۾����� �ȷ��� �ϳ��� �������)
	   2-1. ��Ʈ���� B���� �ִ밡���ð� VS �ӽŰ��̵��ð�
	   2-2. �ӽź��� �ӽŰ��̵��ð��� ũ�� �ּҳ���, �ִ밡���ð��� ũ�� �ּ��̵�+�����ð� �� ���۷��̼��� ����.
			(�ΰ� �ӽ��� ���ÿ� �� ��� ���۷��̼� �ϳ��� �� ��ȸӽſ��� �����ɰ�츦 ���غ���)
	   2-3. �� ���۷��̼��� ��� �۾��� ���� ����ִ� �ӽſ��� ������ ���� ��ŷ���� �ӽſ��� ��ٷȴ� ������ ��츦 ��/���� �غ���.
	   2.3  ��ŷ���� �ӽ��� ���������� ��ٷȴ� ���ԵǴ°�� �ӽ��� ���������� sleep ���� ��ٸ���.
	   2-4. ��ŷ���� �ӽ��� ��ٸ��� �ִ� ���߿� New_Matrix�� �����ɶ� ��ٸ��� �ִ� �ȷ��� ����� �ӽ��� ���ܵȴ�.
	   2-5. �ӽ� ������ ������ Go_Func(�����ȷ�üũ) �ݺ�.


	   ������ ����, ����Ʈ���� ->LPT �Լ� Ż�� ����� �����ð� �ּҰ��� �ƴ��ִ밪�� ã��
	   ��Ʈ���� B�� Ż�� �ӽ�1���� ������ ��� ->B ��Ʈ������ ����, �ӽ�3���� ������ ��� ->B ��Ʈ������ ������ �ȵ�.

	  */

	cout << "-----------------------------New Matrix-------------------------" << endl;
	/*cout << "----[ B ] �����ð�" << endl;  //Matrix B
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


	//Matrix B �����ð� + �̵��ð� 
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

	//���� �����ð� ��� (��� ���� �۾� �� ����+�̵��ð��� ���� working���� ���۷��̼ǵ��� �����ð����� ��). 
	if (M1_State == 0)
	{
		cout << "��ݳ��� �۾� : [PALLET" << Mac1_Part[0].pallet_no << "] Part" << Mac1_Part[0].part_no << " O" << Mac1_Part[0].op_no + 1 << " " << Mac1_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] ���� ��ŷ���� �۾�" << endl;
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M2�������� �۾�):";
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M3�������� �۾�):";
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
		cout << "��ݳ��� �۾� : [PALLET" << Mac2_Part[0].pallet_no << "] Part" << Mac2_Part[0].part_no << " O" << Mac2_Part[0].op_no + 1 << " " << Mac2_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] ���� ��ŷ���� �۾�" << endl;
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M1�������� �۾�):";
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M3�������� �۾�):";
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
		cout << "��ݳ��� �۾� : [PALLET" << Mac3_Part[0].pallet_no << "] Part" << Mac3_Part[0].part_no << " O" << Mac3_Part[0].op_no + 1 << " " << Mac3_Part[0].PT_Trans_Time << endl;
		cout << "----[ B ] ���� ��ŷ���� �۾�" << endl;
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M1�������� �۾�):";
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
								cout << "O" << B[i].SelecPart[j].Oper[OP_idx].Operation_No << "(����M2�������� �۾�):";
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
		cout << "�ӽ� ���ÿ� �����" << endl;




	cout << "----[ B ] ���� ���� �����ð�" << endl;
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


	/*cout << "----[ A ] PALLET" << endl; //B ���� �۾� ������ ���������ͷ� �Ű�
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


	/*cout << "----[ A ] PALLET_temp" << endl; //���� A
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

	cout << "----[ A ] PALLET_temp_public" << endl;//���� A
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


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�ϴ� TEST_DATA4_2�� �ϰ� auto return �ϴ� ��� �˸� 4_1�� ����� 

	//B Matrix���� �ִ� �����ð� VS �ӽŰ��̵��ð� �� 
	auto Max_PT = FIND_MAX_PT(InitializeSystem, PALLET_temp, Matrix_For_Max, mux); //�ִ밡���ð� : Max_PT.temp_pallet[0]                                                                               
	B = Max_PT.PALLET_temp;

	cout << "-> LPT:" << Max_PT.temp_pallet[0].processing_time << " [Pallet" << Max_PT.temp_pallet[0].pallet_no << "] Part" << Max_PT.temp_pallet[0].part_no
		<< " OP" << Max_PT.temp_pallet[0].op_no << " Mac" << Max_PT.temp_pallet[0].mac_no << endl;



	vector <mac> Mac1_Part_New; //�ּҳ���, �ּ� �����ð��� ã�� �ܰ踦 ���� ���õ� ��Ʈ 
	vector <mac> Mac2_Part_New;
	vector <mac> Mac3_Part_New;

	PALLET_temp.clear();
	PALLET_temp = B;

	if (M1_State == 0 && M2_State == 0 && M3_State == 0)
	{
		cout << "�ӽ� ��� idle" << endl;
	}
	else
	{
		cout << "�ӽ� �Ϻ� working��" << endl;
		if (InitializeSystem.TransTime > Max_PT.temp_pallet[0].processing_time)
		{
			cout << "�̵��ð��� �� ŭ -> ����ִ� ���� ����� �ӽ� ���� ���Ⱑ�� ª�� ��Ʈ(���۷��̼�) Ž��" << endl;

			auto Min_Due = FIND_MIN_DUE(InitializeSystem, PALLET_temp, MATRIX_DUE, mux);
			Mac1_Part_New = Min_Due.MAC1_temp;
			Mac2_Part_New = Min_Due.MAC2_temp;
			Mac3_Part_New = Min_Due.MAC3_temp;
			B = Min_Due.B;
			PALLET_temp = Min_Due.PALLET_temp;
		}
		else
		{
			cout << "�ִ밡���ð��� �� ŭ -> ����ִ� ���� ����� �ӽź��� ����+�̵��ð� ���� ���� ��Ʈ(���۷��̼�) Ž��" << endl;

			auto Min_PT_TT = FIND_MIN_PT(InitializeSystem, PALLET_temp, MATRIX, mux);
			Mac1_Part_New = Min_PT_TT.MAC1_temp;
			Mac2_Part_New = Min_PT_TT.MAC2_temp;
			Mac3_Part_New = Min_PT_TT.MAC3_temp;
			B = Min_PT_TT.B;
			PALLET_temp = Min_PT_TT.PALLET_temp;
		}
	}

	mux.lock();

	//���õ� ��Ʈ  ->  �ӽų��� ����!!!!!!!!!!!!!!!!!!!!!!!!!

	//B Matrix���� ���õ� ���۷��̼��� idle �ӽſ��� �۾��ϴ°��� ���� ��������, working���� �ӽſ��� �۾��ϴ°��� ���� �������� ���� 
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
		cout << "���õ� �۾� : [PALLET" << Mac1_Part_New[0].pallet_no << "] Part" << Mac1_Part_New[0].part_no << " O" << Mac1_Part_New[0].op_no + 1 << " " << Mac1_Part_New[0].PT_Trans_Time << endl;
	}
	if (M2_State == 0)
	{
		cout << "���õ� �۾� : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O" << Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << endl;
		//���õ� �۾�
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
								cout << "O" << B[i].SelecPart[j].Oper[k].Operation_No << " �� �����ð��� ";
								for (int h = 0; h < B[i].SelecPart[j].Oper[k].Num_AlterMac; h++)
								{
									cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " ";  //M2���� ���õ� ���۷��̼� //New Matrix B���� ���õ� �����ð� 
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

		//M1���� �۾����� ���۷��̼� - �ӽ��� �����ð�
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
										cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " (M1���� �۾����� ���۷��̼�-�ӽ��� �����ð�)" << endl;
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


		//M3���� �۾����� ���۷��̼� - �ӽ��� �����ð�
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
										cout << B[i].SelecPart[j].Oper[k].Mac[h].Trans_PT << " (M3���� �۾����� ���۷��̼�-�ӽ��� �����ð�)" << endl;
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
		cout << m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time << " (M1->M2) ���õ� �۾� M1���� �۾������� " << endl; //m1_op[0] : M1���� �������� OP�� �����ð�  

		//M2
		cout << m2_op[0].PT_Trans_Time << "(M1)  " << m2_op[1].PT_Trans_Time << " (M2)   " << m2_op[2].PT_Trans_Time << " (M3) M2���� �۾������� " << endl; // ���� ���õ� OP �� �����ð���  m2_op[0] : M1,  m2_op[1] : M2,  m2_op[2] : M3

		//M3 -> M2
		cout << m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time << " (M3->M2) ���õ� �۾� M3���� �۾������� " << endl;  //m3_op[0] : M3���� �������� OP�� �����ð� 


		//���� ���� �ɸ��� �ӽ���? M1,M2,M3�߿� �����غ��� 
		if (m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time < m2_op[1].PT_Trans_Time && m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time < m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time)
		{
			//M1���� �����ϴ°��� �� ������ 

			cout << "���õ� �۾� : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " �۾��Ϸ��� ";
			cout << "M1�� ���� ���� " << m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time << endl;
		}
		if (m2_op[1].PT_Trans_Time < m1_op[0].PT_Trans_Time + m2_op[0].PT_Trans_Time && m2_op[1].PT_Trans_Time < m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time)
		{
			//M2���� �����ϴ°��� �� ������

			cout << "���õ� �۾� : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " �۾��Ϸ��� ";
			cout << "M2�� ���� ���� " << m2_op[1].PT_Trans_Time << endl;

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
			//M3���� �����ϴ°��� �� ������ 

			cout << "���õ� �۾� : [PALLET" << Mac2_Part_New[0].pallet_no << "] Part" << Mac2_Part_New[0].part_no << " O"
				<< Mac2_Part_New[0].op_no + 1 << " " << Mac2_Part_New[0].PT_Trans_Time << " �۾��Ϸ��� ";
			cout << "M3�� ���� ���� " << m3_op[0].PT_Trans_Time + m2_op[2].PT_Trans_Time << endl;
		}



	}
	if (M3_State == 0)
	{
		cout << "���õ� �۾� : [PALLET" << Mac3_Part_New[0].pallet_no << "] Part" << Mac3_Part_New[0].part_no
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




	//idle �ӽſ� �ٷ� ���Եɶ� 




	//��ٷȴٰ� working���� �ӽſ� ���Եɶ�
	

	//���õ� ��Ʈ ����ó��  
	/*std::future<void> Thread1 = std::async(std::launch::async, MACHINE1,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread2 = std::async(std::launch::async, MACHINE2,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	std::future<void> Thread3 = std::async(std::launch::async, MACHINE3,
		PalletInSys, Mac1_Part, Mac2_Part, Mac3_Part, PALLET_temp,
		InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));*/








	//�Լ� ����� ��� �ӽú��� clear 
	m1_op.clear();
	m2_op.clear();
	m3_op.clear();


	cout << "----------------------------------------------------------------" << endl;

};




void Move_A_to_B(int Pallet_count, vector<Pallet> PALLET_temp, vector<mac> Mac1_Part, vector<mac> Mac2_Part, vector<mac> Mac3_Part,
	Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX,
	int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //�� �Լ��� ���� �ϰ�Ͱŵ� �Ķ���͸� ���� ��Ű�ÿ� ��.��.��

{
	cout << "----------------------Move Pallet A to_B----------------------" << endl;

	/* �ȷ�pool PALLET���� ��Ʈ �ȿö� ���ȷ��� ���������� ��Ʈ�� �ö���ִ� �ȷ��� �߿��� (�ε��� �������) ��� �۾��� ���� �ӽſ��� ó�� ������ �ȷ��� ã��
	 ���� �ȷ� ����(Pallet_count) ��ŭ  A->B�� �����´�.  */

	 /*cout << "[PALLET] - ���� �ε��� �ȷ��� " << endl; //���� ��ǲ������
	 for (int i = 0; i < PALLET.size(); i++)
	 {
		 cout << "[Pallet" << PALLET[i].Total_Pallet_No << "] ";
		 for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
		 {
			 cout << "P" << PALLET[i].SelecPart[j].Total_Part_No << " ";
		 }
		 cout << "(State:" << PALLET[i].State << ")" << endl;
	 }*/


	cout << "[ B ]  A->B �̵� ��" << endl;  //Matrix B
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << "(State:" << B[i].State << ") ";
		if (B[i].Complete == 1)
			cout << "�Ϸ�";

		cout << endl;
	}



	int p = 0;
	for (int i = 0; i < PALLET.size(); i++) {  // �������(��Ʈ�� �ö�) �ȷ� ����(p) ����
		if (PALLET[i].SelecPart.size() > 0)
			p++;
	}

	PALLET_temp.clear();
	PALLET_temp.resize(p);  //������� �ȷ� ������ŭ�� ũ���� A Matrix �����

	int u = 0;
	for (int i = 0; i < PALLET.size(); i++) {
		if (PALLET[i].SelecPart.size() > 0)
		{
			PALLET_temp[u] = PALLET[i];
			u++;
		}
	}

	for (int i = 0; i < PALLET_temp.size(); i++)  // A (PALLET_temp) ���� �̹� working���� �ȷ�(B Matrix) ���� 
	{
		if (PALLET_temp[i].State == 1)
		{
			PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
			i--;
		}
	}

	cout << "[ A ]  A->B �̵� ��" << endl;
	for (int i = 0; i < PALLET_temp.size(); i++)  //Matrix A �ϼ�
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


	//���� �� �ٲ� ��Ʈ������ PALLET�� ���� �� B���� ���� �ȷ� ���� 
	for (int i = 0; i < PALLET.size(); i++)
	{
		for (int a = 0; a < B.size(); a++)  //(����� �ӽ�1,2�� ���� �ȵǾ� ���� ���� ���۷��̼� ������ ���� ������ PALLET�� ���� ���� ���� ������) 
		{
			if (PALLET[i].Total_Pallet_No == B[a].Total_Pallet_No)
			{

				for (int j = 0; j < PALLET[i].SelecPart.size(); j++)
				{
					for (int b = 0; b < B[a].SelecPart.size(); b++)
					{
						if (PALLET[i].SelecPart[j].Total_Part_No == B[a].SelecPart[b].Total_Part_No)
						{
							PALLET[i].SelecPart[j].Complete = B[a].SelecPart[b].Complete;  //�Ϸ�� ��Ʈ ����
							for (int k = 0; k < PALLET[i].SelecPart[j].Num_Operation; k++)
							{
								for (int c = 0; c < B[a].SelecPart[b].Num_Operation; c++)
								{
									if (PALLET[i].SelecPart[j].Oper[k].Operation_No == B[a].SelecPart[b].Oper[c].Operation_No)
									{
										PALLET[i].SelecPart[j].OP_idx = B[a].SelecPart[b].OP_idx;  //�Ϸ�� ���۷��̼� �ε���
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//PALLET ���
	/*cout << "B ���� PALLET�� ������" << endl;
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

	/*�Ѱ��� �ǹ��� : ���� B Matrix -> PALLET ��  Oper[k].Complete, Oper[k].MAC1_Start_vec �ű����� ���µ� ��� �Ű�����? */


   //B���� �Ϸ���ȷ� ��ε� �ڡڡڡڡ�

   //B Matrix���� �Ϸ�� �ȷ� ���� 
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


	//A���� �ε��� ������� ��� �������� �ӽſ��� ó���Ҽ� �ִ� ���۷��̼��� �����ִ� �ȷ����� Ȯ�� 
	cout << "A �ȷ����� ���۷��̼Ǻ� ��ȸӽ�     // M1_State:" << M1_State << " M2_State:" << M2_State << " M3_State:" << M3_State << " //" << endl;
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
						cout << "M1���� ���������� �ȷ� ����  ";
					}

					if (M2_State == 0 && PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 2)
					{
						PALLET_temp_temp.push_back(PALLET_temp[i]);
					}
					else if (M2_State == 1 || PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						cout << "M2���� ���������� �ȷ� ����  ";
					}


					if (M3_State == 0 && PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == 3)
					{
						PALLET_temp_temp.push_back(PALLET_temp[i]);

					}
					else if (M3_State == 1 || PALLET_temp[i].SelecPart[j].Oper[OP_idx].Mac[h].Mac_No == -1)
					{
						cout << "M3���� ���������� �ȷ� ����  ";
					}


				}
			}
		}
	}
	mux.unlock();


	auto comp1 = [](const Pallet& p1, const Pallet& p2) {return p1.Total_Pallet_No == p2.Total_Pallet_No; }; //����ü���� �ߺ� ����  
	auto last = std::unique(PALLET_temp_temp.begin(), PALLET_temp_temp.end(), comp1);
	PALLET_temp_temp.erase(last, PALLET_temp_temp.end());


	PALLET_temp.clear();
	PALLET_temp = PALLET_temp_temp;





	int P_count = Pallet_count;
	//���� �ȷ����� ��ŭ A -> B�� �����´�.  (First In First Out)
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		B.push_back(PALLET_temp[i]);
		P_count--;
		if (P_count == 0)
			break;
	}



	//A���� �̵��� �ȷ� ����
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



	cout << "----[ B ]  A->B �̵� ��" << endl;  //Matrix B
	for (int i = 0; i < B.size(); i++)
	{
		cout << "[Pallet" << B[i].Total_Pallet_No << "] ";
		for (int j = 0; j < B[i].SelecPart.size(); j++)
		{
			cout << "P" << B[i].SelecPart[j].Total_Part_No << " ";
		}
		cout << "(State:" << B[i].State << ") ";
		if (B[i].Complete == 1)
			cout << "�Ϸ�";

		cout << endl;
	}

	cout << "----[ A ]  A->B �̵� �� (���������ӽſ��� �����Ҽ� ���� �ȷ��� ������)" << endl;  //Matrix A 
	for (int i = 0; i < PALLET_temp.size(); i++)
	{
		cout << "[Pallet" << PALLET_temp[i].Total_Pallet_No << "] ";
		for (int j = 0; j < PALLET_temp[i].SelecPart.size(); j++)
		{
			cout << "P" << PALLET_temp[i].SelecPart[j].Total_Part_No << " ";

		}
		cout << "(State:" << PALLET_temp[i].State << ")" << endl;
	}

	//-------------------Matrix A, B ���� �Ϸ�-------------------------------

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







	//A (�ε��� �ȷ� pool) ����
	int p = 0;
	for (int i = 0; i < PALLET.size(); i++) {  // �������(��Ʈ�� �ö�) �ȷ� ����(p) ����
		if (PALLET[i].SelecPart.size() > 0)
			p++;
	}

	PALLET_temp.clear();
	PALLET_temp.resize(p);  //������� �ȷ� ������ŭ�� ũ���� A Matrix �����
	int u = 0;
	for (int i = 0; i < PALLET.size(); i++) {
		if (PALLET[i].SelecPart.size() > 0)
		{
			PALLET_temp[u] = PALLET[i];
			u++;
		}
	}

	for (int i = 0; i < PALLET_temp.size(); i++)  // A (PALLET_temp) ���� �̹� working���� �ȷ�(B Matrix) ���� 
	{
		if (PALLET_temp[i].State == 1)
		{
			PALLET_temp.erase(PALLET_temp.begin() + i, PALLET_temp.begin() + i + 1);
			i--;
		}
	}

	mux.lock();
	cout << "A (�̵� ��)" << endl;
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

	cout << "B (�̵� ��)" << endl;
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

	//B -> A front�� insert �� B���� ���� 
	for (int i = 0; i < B.size(); i++)
	{
		if (B[i].Total_Pallet_No == Mac_P) //Mac2_P : A Matrix�� �������� �ȷ�. ��� ���� �ӽſ��� �����Ҽ� �ִ� �۾� ���� 
		{
			cout << "(B Matrix) M" << Mac << "���� ó�� �Ұ����� �ȷ�: [PALLET" << B[i].Total_Pallet_No << "]" << endl;
			//	B[i].State = 0; //A�� �ű�鼭 state ����
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

	//A���� ��� front�� insert�� �ȷ��� �����ϰ� idle�ӽſ��� �۾� ������ �ȷ��� FIFO�� ã�´�. -> ������ �������۷��̼� ������Ʈ �ɶ����� ������� �ڡڳ��߿�üũ 
	cout << "(A Matrix) M" << Mac << "���� ó�� ������ ù��° �ȷ� ";
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
						cout << endl << "M" << Mac << " ���� �۾� ������ ���۷��̼� ���� (�ӽ� �۾� ����)" << endl;
						/*	!!!!!!!!!!!!!!!!!!!!!!!!!!!MAC���� �۾������� �ȷ��� A���� ������ �Լ� return. �ش� �ӽ� ����.
							=>auto �� �Լ��� ����ü�� return�Ұ��, �Լ� �߰��� �Լ��� ��ȯ�ϴ� ��� �˾Ƽ� ������� (�ϴ� stackoverflow�� ����)
						 �ƴϴ� ��ε� ����鼭 �����غ�!!!!!!!!!!!!!!!!!!!!!!!!!! ����� �ӽ� ��� �Ұſ�     */
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


	cout << "A (�̵� ��)" << endl;
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



	cout << "B (�̵� ��)" << endl;
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
	/* B���� ���� �ȷ� �ִ��� Check -> �������� �? -> (��� ���� �Ϸ�� �ӽſ��� ó�������� �ȷ��� �ε��� ������� ã�Ƽ�) �����ȷ� ���� ��ŭ A->B�� �ȷ� �߰� -> New Matrix
								  -> �����ȷ� ������? -> New Matrix */
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

	cout << "�����ȷ� ��ΰ���?" << Pallet_count << endl;


	//Go_F_State = 0;


	mux.lock();

	if (Pallet_count > 0)  //�Ϸ�� �ȷ��� �ϳ� �̻��̸� 
	{
		cout << "���� �ȷ��� " << Pallet_count << "�� �׿�" << endl;

		Move_A_to_B(Pallet_count, PALLET_temp, Mac1_Part, Mac3_Part, Mac3_Part,
			InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
	}
	else //�Ϸ�� �ȷ� ������ 
	{
		cout << "���� �ȷ��� ���׿�" << endl;

		//�ȷ��� �ȳ������� ��ݸӽſ��� ���������� ���۷��̼��� ���°�� (B����)  -> B���� �ش��ȷ� A�� �̵�, A���� ������� �ȷ��� ù��° �ȷ� ������ 
		cout << "B �ȷ����� ���۷��̼Ǻ� ��ȸӽ� (���� �� OP update)    // M1_State:" << M1_State << " M2_State:" << M2_State << " M3_State:" << M3_State << " //" << endl;
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
			/*  �ӽ����忡�� ��� ������ ���� �ȷ����� ó���Ҽ� �ִ� �۾��� �������,
				A ��Ʈ������ ���� ù��°�� �ε��� ������� �������ִ� �ӽſ��� ���������� �ȷ��� ã�� B ��Ʈ������ �߰��Ѵ�. (A-> B)
				��ݳ����ȷ��� ������ �ȷ��� �ڸ���(B ��Ʈ���� ù��°�ڸ�) �д�  (B-> A)*/


			if (M1_State == 0 && m1_empty == B[i].SelecPart.size() && B[i].Current_Mac == 1)
			{
				cout << "M1 ������ �� �ִ� �۾� ���� " << endl;
				int Mac = 1;
				auto After_Move = Incomplete_Move_B_To_A(PALLET_temp, Mac, B[i].Total_Pallet_No);

				PALLET_temp = After_Move.PALLET_temp;
			}
			else if (M2_State == 0 && m2_empty == B[i].SelecPart.size() && B[i].Current_Mac == 2)
			{
				int Mac = 2;
				cout << "M2 ������ �� �ִ� �۾� ���� " << endl;
				auto After_Move = Incomplete_Move_B_To_A(PALLET_temp, Mac, B[i].Total_Pallet_No);

				PALLET_temp = After_Move.PALLET_temp;
			}
			else if (M3_State == 0 && m3_empty == B[i].SelecPart.size() && B[i].Current_Mac == 3)
			{
				cout << "M3 ������ �� �ִ� �۾� ���� " << endl;
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


		/*cout << "M1 �ȷ� �����ٰ� �������� " << endl;
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

		/*���۷��̼� �ϳ� ������. -> ���� ���� ���۷��̼��� ���� �ð�,�� �ð� ��� -> ���۷��̼��� �ε��� �÷��ش�. -> ��Ʈ �����ٸ� �Ϸ�ó��
		( B ��Ʈ���� ���ַ� ���ư��� ���� ��Ʈ���� �ݺ������� A(PALLET_temp), ������ǲ������ (PALLET) �� ������ �Ű������) */
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
						B[i].SelecPart[j].Oper[k].MAC1_Start_vec.push_back(start); //���� �ð�, �� �ð� ���
						B[i].SelecPart[j].Oper[k].MAC1_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						B[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						B[i].State = 0;

						//��� 
						/*mux.lock();
						cout << "M1 ��ݰ����� ���۷��̼� [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ")" << ") �ȷ�state:" << B[i].State << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC1_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M1 ���� " << B[i].SelecPart[j].Oper[k].MAC1_Start_vec[h] << " "
								<< " M1 �� " << B[i].SelecPart[j].Oper[k].MAC1_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}

		//A ���� �۾� ������ ���������Ϳ� ���
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
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						PALLET[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						PALLET[i].State = 0;

						//��� 
						mux.lock();
						cout << "M1 ��ݰ����� ���۷��̼� [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") �ȷ�state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M1 ���� " << PALLET[i].SelecPart[j].Oper[k].MAC1_Start_vec[h] << " "
								<< " M1 �� " << PALLET[i].SelecPart[j].Oper[k].MAC1_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}

		//M1_State = 0;



		//���� �ȷ� üũ
		if (Go_F_State == 0)
		{
			M1_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//cout << "Go_f ������" << endl; 
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
		cout <<"M2 �ȷ� �����ٰ� ���� << endl;
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

		/*���۷��̼� �ϳ� ������. -> ���� ���� ���۷��̼��� ���� �ð�,�� �ð� ��� -> ���۷��̼��� �ε��� �÷��ش�. -> ��Ʈ �����ٸ� �Ϸ�ó��
		( B ��Ʈ���� ���ַ� ���ư��� ���� ��Ʈ���� �ݺ������� A(PALLET_temp), ������ǲ������ (PALLET) �� ������ �Ű������) */
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
						B[i].SelecPart[j].Oper[k].MAC2_Start_vec.push_back(start); //���� �ð�, �� �ð� ���
						B[i].SelecPart[j].Oper[k].MAC2_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						B[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						B[i].State = 0;  // ���۷��̼� �����ϳ� �������Ƿ� �ȷ� State �ٲ���


						//��� 
						/*mux.lock();
						cout << "M2 ��ݰ����� ���۷��̼� [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ") �ȷ�state:" << B[i].State << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC2_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M2 ���� " << B[i].SelecPart[j].Oper[k].MAC2_Start_vec[h] << " "
								<< " M2 �� " << B[i].SelecPart[j].Oper[k].MAC2_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}




		//A ���� �۾� ������ ���������Ϳ� ���
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
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						PALLET[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						//PALLET[i].State = 0;

						//��� 
						mux.lock();
						cout << "M2 ��ݰ����� ���۷��̼� [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") �ȷ�state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M2 ���� " << PALLET[i].SelecPart[j].Oper[k].MAC2_Start_vec[h] << " "
								<< " M2 �� " << PALLET[i].SelecPart[j].Oper[k].MAC2_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}

		//M2_State = 0;





		//���� �ȷ� üũ
		if (Go_F_State == 0)
		{
			M2_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//cout << "Go_f ������" << endl;
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
		cout <<"M3 �ȷ� �����ٰ� ���� << endl;
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

		/*���۷��̼� �ϳ� ������. -> ���� ���� ���۷��̼��� ���� �ð�,�� �ð� ��� -> ���۷��̼��� �ε��� �÷��ش�. -> ��Ʈ �����ٸ� �Ϸ�ó��
		( B ��Ʈ���� ���ַ� ���ư��� ���� ��Ʈ���� �ݺ������� A(PALLET_temp), ������ǲ������ (PALLET) �� ������ �Ű������) */
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
						B[i].SelecPart[j].Oper[k].MAC3_Start_vec.push_back(start); //���� �ð�, �� �ð� ���
						B[i].SelecPart[j].Oper[k].MAC3_End_vec.push_back(end);
						B[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						B[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						B[i].State = 0;  // ���۷��̼� �����ϳ� �������Ƿ� �ȷ� State �ٲ���


						//��� 
						/*mux.lock();
						cout << "M3 ��ݰ����� ���۷��̼� [Pallet" << B[i].Total_Pallet_No << "] P" <<
							B[i].SelecPart[j].Total_Part_No << " OP" << B[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << B[i].SelecPart[j].OP_idx << ")" << endl;
						mux.unlock();

						for (int h = 0; h < B[i].SelecPart[j].Oper[k].MAC3_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M3 ���� " << B[i].SelecPart[j].Oper[k].MAC3_Start_vec[h] << " "
								<< " M3 �� " << B[i].SelecPart[j].Oper[k].MAC3_End_vec[h] << endl;
							mux.unlock();

						}*/
					}
					if (B[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count++;
				}
				if (OP_count == B[i].SelecPart[j].Num_Operation)
				{
					B[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count++;
				}
			}
			if (Part_count == B[i].SelecPart.size())
				B[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}

		//A ���� �۾� ������ ���������Ϳ� ���
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
						PALLET[i].SelecPart[j].Oper[k].Complete = 1; //��� ���� ���۷��̼� �Ϸ� ó�� �� 
						PALLET[i].SelecPart[j].OP_idx++;  //�ε��� �÷��ش�.
						PALLET[i].State = 0;

						//��� 
						mux.lock();
						cout << "M3 ��ݰ����� ���۷��̼� [Pallet" << PALLET[i].Total_Pallet_No << "] P" <<
							PALLET[i].SelecPart[j].Total_Part_No << " OP" << PALLET[i].SelecPart[j].Oper[k].Operation_No <<
							"(idx" << PALLET[i].SelecPart[j].OP_idx << ") �ȷ�state:" << PALLET[i].State << endl;
						mux.unlock();

						for (int h = 0; h < PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec.size(); h++)
						{
							mux.lock();
							cout << " M3 ���� " << PALLET[i].SelecPart[j].Oper[k].MAC3_Start_vec[h] << " "
								<< " M3 �� " << PALLET[i].SelecPart[j].Oper[k].MAC3_End_vec[h] << endl;
							mux.unlock();
						}
					}
					if (PALLET[i].SelecPart[j].Oper[k].Complete == 1)
						OP_count1++;
				}
				if (OP_count1 == PALLET[i].SelecPart[j].Num_Operation)
				{
					PALLET[i].SelecPart[j].Complete = 1; //�Ϸ�� ��Ʈ ��� 
					Part_count1++;
				}
			}
			if (Part_count1 == PALLET[i].SelecPart.size())
				PALLET[i].Complete = 1; //B Matrix���� ��� ���� �ȷ��� �����ϱ� ���� ǥ��. �ش� �ȷ��� B Matrix���� �������� "B[i].Complete = 0;" ���� �ǵ������´�. 
		}


		//M3_State = 0;



		//���� �ȷ� üũ
		if (Go_F_State == 0)
		{
			M3_State = 0;
			Go_Func(PalletInSys, PALLET_temp, Mac1_Part, Mac2_Part, Mac3_Part,
				InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux));
		}
		else
		{
			//	cout << "Go_f ������" << endl;
		}

	}
	else
		cout << "M3 is already working" << endl;
};



void Compare_Trans_vs_MaxPT(Initialize InitializeSystem, int PalletInSys, vector<MatrixMax> Matrix_For_Max,
	MatrixMin MATRIX_DUE, MatrixMin MATRIX, int Num_P, int P1, int P2, int P3, int P4, std::mutex& mux) //�� �Լ��� ���� �ϰ�Ͱŵ� �Ķ���͸� ���� ��Ű�ÿ� ��.��.��
{
	/*	�ε��Ǵ� �ȷ� ���������� -> PALLET
	FIND_MAX_PT, FIND_MIN_DUE, FIND_MIN_PT ���� ���Ǵ� �ȷ� A Matrix -> PALLET_temp
	�������� �ȷ� B Matrix -> B   */




	time_t comptime;
	comptime = CurrentTime_milliseconds();
	cout << "Compare Trans Time VS Max PT�� ���� �ð�  " << comptime << endl;
	cout << "-----------------Compare Trans Time VS Max PT-------------------" << endl;


	//InitializeSystem.TransTime = 10; //�ӽŰ� �̵��ð� 
	cout << "�ӽŰ��̵��ð�:" << InitializeSystem.TransTime << endl;

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

	vector<Pallet> PALLET_temp(PALLET.size());  //PALLET ��ǲ�����Ϳ��� , PALLET_temp �ӽ� ��ǲ������
	//vector<Pallet> B;

	PALLET_temp = PALLET;
	vector <mac> Mac1_Part; //�ּҳ���, �ּ� �����ð��� ã�� �ܰ踦 ���� ���õ� ��Ʈ 
	vector <mac> Mac2_Part;
	vector <mac> Mac3_Part;



	//���۷��̼� �ٲ㺸�� ������ ���⼭ �׽�Ʈ
	//cout << "PALLET_temp" << PALLET_temp[0].Total_Pallet_No << " " << "PART" << PALLET_temp[0].SelecPart[0].Total_Part_No << " OP" << PALLET_temp[0].SelecPart[0].OP_idx << endl;
	//cout << "PALLET" << PALLET[0].Total_Pallet_No << " " << "PART" << PALLET[0].SelecPart[0].Total_Part_No << " OP" << PALLET[0].SelecPart[0].OP_idx << endl;
	//PALLET_temp[0].SelecPart[0].OP_idx += 1;  //�ӽ� ���� ������ PALLET_temp[i].SelecPart[j].OP_idx ���� ���Ѿ��� 
	//PALLET[0].SelecPart[0].OP_idx += 1;	



	//�۾����� �ȷ�, �۾����� �ȷ�, �۾����� �ӽ� , �ӽŰ��� �̻����ȷ��� ����� �������� Pallet ��Ʈ���� ���·� ����־�� �Ѵ�.�ڡڡ�

	auto Max_PT = FIND_MAX_PT(InitializeSystem, PALLET_temp, Matrix_For_Max, mux); //�ִ밡���ð� : Max_PT.temp_pallet[0]                                                                               
	PALLET_temp = Max_PT.PALLET_temp;


	if (InitializeSystem.TransTime > Max_PT.temp_pallet[0].processing_time)
	{
		mux.lock();
		cout << "�̵��ð��� �� ŭ -> ����ִ� ���� ����� �ӽ� ���� ���Ⱑ�� ª�� ��Ʈ(���۷��̼�) Ž��" << endl;
		mux.unlock();

		auto Min_Due = FIND_MIN_DUE(InitializeSystem, PALLET_temp, MATRIX_DUE, mux);
		Mac1_Part = Min_Due.MAC1_temp;  	//�ӽú��Ϳ��� ���õ� ��Ʈ �ű� 
		Mac2_Part = Min_Due.MAC2_temp;
		Mac3_Part = Min_Due.MAC3_temp;
		//B = Min_Due.B;
		PALLET_temp = Min_Due.PALLET_temp;
	}


	else
	{
		mux.lock();
		cout << "�ִ밡���ð��� �� ŭ -> ����ִ� ���� ����� �ӽź��� ����+�̵��ð� ���� ���� ��Ʈ(���۷��̼�) Ž��" << endl;
		auto Min_PT_TT = FIND_MIN_PT(InitializeSystem, PALLET_temp, MATRIX, mux);
		mux.unlock();

		Mac1_Part = Min_PT_TT.MAC1_temp;
		Mac2_Part = Min_PT_TT.MAC2_temp;
		Mac3_Part = Min_PT_TT.MAC3_temp;
		//B = Min_PT_TT.B;
		PALLET_temp = Min_PT_TT.PALLET_temp;

	}




	//���õ� ��Ʈ 
	mux.lock();
	cout << "�ӽ�" << Mac1_Part[0].mac_no << " ���õ� ��Ʈ: [Pallet" << Mac1_Part[0].pallet_no << "] P" << Mac1_Part[0].part_no
		<< " OP" << Mac1_Part[0].op_no + 1 << " ����+�̵��ð�" << Mac1_Part[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << Mac2_Part[0].mac_no << " ���õ� ��Ʈ: [Pallet" << Mac2_Part[0].pallet_no << "] P" << Mac2_Part[0].part_no
		<< " OP" << Mac2_Part[0].op_no + 1 << " ����+�̵��ð�" << Mac2_Part[0].PT_Trans_Time << endl;
	cout << "�ӽ�" << Mac3_Part[0].mac_no << " ���õ� ��Ʈ: [Pallet" << Mac3_Part[0].pallet_no << "] P" << Mac3_Part[0].part_no
		<< " OP" << Mac3_Part[0].op_no + 1 << " ����+�̵��ð�" << Mac3_Part[0].PT_Trans_Time << endl;
	mux.unlock();




	for (int i = 0; i < PALLET.size(); i++) //��� ���� �ε��Ǵ� �ȷ�pool PALLET���� woring���� �ȷ� ǥ��  -> �۾������� 	PALLET[i].State = 0; ���� �ǵ����� 
	{
		if (PALLET[i].Total_Pallet_No == Mac1_Part[0].pallet_no || PALLET[i].Total_Pallet_No == Mac2_Part[0].pallet_no || PALLET[i].Total_Pallet_No == Mac3_Part[0].pallet_no)
			PALLET[i].State = 1;
	}



	//���õ� ��Ʈ ����ó��  
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
	printf("�ѻѻѻѻѻѻѻ�\n");
	printf("Compare_Trans_vs_MaxPT���� �ε��� �ȷ� ���� %d (�ð�%d) \n", PALLET.size(), comptime2);
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





	/*(B)�� �ӽſ� ������ ���۷��̼� �ϳ� ������ ���� �ȷ� �ִ���, �ִٸ� ��� �������� ���� Ȯ����(A)�� �ȷ� ���� ������� �۾������ȷ� ������ŭ(B)�� ����´�
	, ���ٸ� ���۷��̼� ���� �ȷ���(B) -> (A)���� ���� �̵� */


	//�ӽ� ���� ������ PALLET_temp, PALLET �� OP_idx �ϳ��� ������Ű��  ex) PALLET[0].SelecPart[0].OP_idx += 1;


	//��������

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
				cout << "                          �ڷε��߻���  [Pallet" << InitializeSystem.PALLET_LU1[P1].Total_Pallet_No << "]" << endl;
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
				cout << "                          �ڷε��߻���  [Pallet" << InitializeSystem.PALLET_LU2[P2].Total_Pallet_No << "]" << endl;
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
				cout << "                          �ڷε��߻���  [Pallet" << InitializeSystem.PALLET_LU3[P3].Total_Pallet_No << "]" << endl;
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
				cout << "                          �ڷε��߻���  [Pallet" << InitializeSystem.PALLET_LU4[P4].Total_Pallet_No << "]" << endl;
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
	cout << "                          �ڷε��߻���  ���� �ȷ� ����? " << PALLET.size() << endl; //���� �ȷ� ���� 
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
	cout << "                          �ڷε��߻���  PALLET.size() : " << PALLET.size() << endl;
	cout << "                          �ڷε��߻���  �ȷ�������Ӵ�?" << endl;
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
	cout << "Buffer�� ���� �ȷ� ����. �׿��� A �θ��� �־�  " << PALLET.size() << endl; //���� �ȷ� ����
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "���� �ȷ� ��ȣ " << PALLET[i].Total_Pallet_No << endl;
	}
	mux.unlock();
	*/


	/*PALLET[i].SelecPart[j].Oper[h].Mac[h].Depend ���·�. Depend[0] ����,
	  PALLET[i].SelecPart[j].Depend[0].Oper[h].Mac[h].Depend ���·�. Depend[1] ����  ���� ����*/
	  //cout << "----------------���� general ��Ʈ �׽�Ʈ " << endl;
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
	//cout << "----------------���� dependency ��Ʈ ���� �۾� �׽�Ʈ " << endl;

	//Dependency ���� ��Ʈ�� ���� ���
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

	//cout << "----------------���� dependency ��Ʈ ���� �۾� �׽�Ʈ " << endl;

	//Dependency ���� ��Ʈ�� ���� ���
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
		<< " Oper1�� �ӽŰ���" << PALLET[0].SelecPart[0].Oper[0].Num_AlterMac << " " << " Dependency" << PALLET[0].SelecPart[0].Dependency << endl;
	cout << "�����۾�" << PALLET[0].SelecPart[0].Depend[0].Total_Part_No << " type" << PALLET[0].SelecPart[0].Part_Type
		<< " Oper1�� �ӽŰ���" << PALLET[0].SelecPart[0].Oper[0].Num_AlterMac <<" Dependency" << PALLET[0].SelecPart[0].Depend[0].Dependency<<endl;*/


	Compare_Trans_vs_MaxPT(InitializeSystem, PalletInSys,
		Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, mux);   //���� 


};

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!InputThePallet �Լ� PALLET ������ �׽�Ʈ�� ���� . �ӽ�2�� �������°� ��ǲ������ ���� �־ ����°��� !!!!!!!!!!!!
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






	if (Num_P == (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1)  //ù��° ����Լ� �ٷ� ���۷�
	{
		std::future<void> Buff = std::async(std::launch::async, Buffer, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4, std::ref(mux)); 	//���� �񵿱�   

		if (LU1_State == 0 && LU2_State == 0 && LU3_State == 0 && LU4_State == 0)
			std::future<void> After_Load2 = std::async(std::launch::async, InputThePallet, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P - 1, P1, P2, P3, P4);

	}
	else if (Num_P > 0 && Num_P < (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1) //�ι�° ����Լ�����
	{

		if (LU1_State == 0 && LU2_State == 0 && LU3_State == 0 && LU4_State == 0)
			std::future<void> After_Load2 = std::async(std::launch::async, InputThePallet, InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P - 1, P1, P2, P3, P4);
	}
	else if (Num_P == 0) //�ȷ� �� �ö󰥶����� ���Ž 
		return;


	mux.lock();
	cout << "InputThePallet���� ���� �ȷ� ���� " << PALLET.size() << endl; //���� �ȷ� ����
	for (int i = 0; i < PALLET.size(); i++)
	{
		cout << "���� �ȷ� ��ȣ " << PALLET[i].Total_Pallet_No << endl;
	}cout << endl;
	mux.unlock();



};





void Loading(Initialize InitializeSystem, vector<MatrixMax> Matrix_For_Max, MatrixMin MATRIX_DUE, MatrixMin MATRIX, int PalletInSys)
{
	//���߿� �ε�Ÿ�� ��� ��Ƴ��� �׾ȿ��� ��ü(�ӽ�����) sleep���� �ð� üũ�س����� ������� ū�׸� !!!!!!!!!!!!!!

	//std::vector<Pallet> PALLET; //���� �ȷ� (A)
	/* InitializeSystem.PALLET_LU3[P3].LD_Start_vec(st), InitializeSystem.PALLET_LU3[P3].LD_End_vec(end) �ð����� ��
	   => PALLET[idx] = InitializeSystem.PALLET_LU3[P3]; */

	int	P1 = 0;   //LU1�� ������� �ȷ� PALLET ���� �ű�� �ε��� 
	int	P2 = 0;
	int	P3 = 0;
	int	P4 = 0;



	int Num_P = (InitializeSystem.Num_Pallet / InitializeSystem.Num_LU_Station) + 1;
	cout << "Num_P" << Num_P << endl;





	InputThePallet(InitializeSystem, PalletInSys, Matrix_For_Max, MATRIX_DUE, MATRIX, Num_P, P1, P2, P3, P4);



};


bool CMP(const Part &Order1, const Part &Order2) {//due date ���Լ� 
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
	/*���� Min�� ã�¹��
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
	std::cout << "<�ڡ�Phase1_Palletizing-EDD�ڡ�>" << endl;
	//1. Palletizing
	//1-1. ���� ��ü��Ʈ(����) ���� ���������� ����(����ü���� ����������� sorting) 
	Total_Part_No = InitializeSystem.Num_Total_Part - (InitializeSystem.Num_Dependency / 2);
	cout << "Total_Part_No " << Total_Part_No << endl;
	sort(InitializeSystem.AllPart, InitializeSystem.AllPart + Total_Part_No, CMP);

	//�� ��Ʈ�� �ε������̼� ������ŭ ���� ->�ε������̼� ���� ��Ʈ�� �����
	NumPartLU = Total_Part_No / InitializeSystem.Num_LU_Station;
	reminder = Total_Part_No % InitializeSystem.Num_LU_Station;
	cout << "��Ʈ ��" << NumPartLU << "���� �� LU�����.������ " << reminder << "���� LU1�ΰ�" << endl;

	NumPart_LU1 = NumPartLU + reminder;
	NumPart_LU2 = NumPartLU;
	NumPart_LU3 = NumPartLU;
	NumPart_LU4 = NumPartLU;

	Part_LU1 = new Part[NumPartLU + reminder];
	Part_LU2 = new Part[NumPartLU];
	Part_LU3 = new Part[NumPartLU];
	Part_LU4 = new Part[NumPartLU];


	//Part �ε������̼����� �й��ϴºκ� line 588~595 (�����ϰ���V�� sort(EDD)�Լ��� �й��� ����)
	Copy_Arr(InitializeSystem.AllPart, Part_LU1, NumPartLU + reminder);  //��ü��Ʈ �� �ε������̼Ǻ��� �й� ex)��Ʈ 10�� -> LU1 4��,LU2 2��,LU3 2��,LU4 2��
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder, Part_LU2, NumPartLU);
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder + NumPartLU, Part_LU3, NumPartLU);
	Copy_Arr(InitializeSystem.AllPart + NumPartLU + reminder + NumPartLU + NumPartLU, Part_LU4, NumPartLU);


	Part_LU1_vec.insert(Part_LU1_vec.end(), &Part_LU1[0], &Part_LU1[NumPart_LU1]);  //�迭 "Part_LU1" -> ���� "Part_LU1_vec" copy
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
	//1-2. �� �ȷ��� �Ƚ���Ÿ�԰� ������ƮŸ���� ã�´�(fixture_type�� ���� �ø� Part ��Ī ��Ű��)
	std::cout << "<LUSTATION1>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU1.size(); i++)
	{
		InitializeSystem.PALLET_LU1[i].Total_Pallet_No = i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU1[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU1[i].Fixture_vec.size(); j++)
		{
			cout << "-----���� Fixture type : " << InitializeSystem.PALLET_LU1[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU1_temp;
			for (int k = 0; k < Part_LU1_vec.size(); k++)  //Part_LU1_vec �ε������̼Ǻ� ������� ��Ʈ 
			{
				cout << "���� ������� ��Ʈ " << Part_LU1_vec[k].Total_Part_No << "�� type" << Part_LU1_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU1[i].Fixture_vec[j].Fixture_No == Part_LU1_vec[k].Part_Type) //fixtureŸ�԰� ���� part�� �߿��� duedate���� ª���ͳ��� �ȷ����̷� ���� �ε���ų����.
				{

					//cout << "���� ������� ��Ʈ�� �Ƚ���Ÿ�� �´���Ʈ" << Part_LU1_vec[k].Total_Part_No << "�� type" << Part_LU1_vec[k].Part_Type <<endl;
					cout << "���� Part Type:" << Part_LU1_vec[k].Part_Type << endl;
					//cout << "���� Part Due Date:" << Part_LU1_vec[k].Due_Date << endl;

					//1-3. fixture_type�� ���� Part_Type�� ��Ʈ�߿��� ���� Due_Date�� ª�� Part_No�� ����  
					Part_LU1_temp.push_back(Part_LU1_vec[k]);
					cout << "�ĺ���ƮNo :" << Part_LU1_temp[count].Total_Part_No << endl;
					cout << "�װ���Type :" << Part_LU1_temp[count].Part_Type << endl;
					cout << "�װ���DueDate:" << Part_LU1_temp[count].Due_Date << endl;

					cout << "==> �װ��� ����ª����: " << Part_LU1_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!���� �̻���

					InitializeSystem.PALLET_LU1[i].SelecPart.push_back(Part_LU1_temp[0]);   //���õ���Ʈ �ȷ�(����ü)�� ����               

					//1-4. ���õ� ��Ʈ�� ��Ʈpool(Part_LU1_vec)���� �����.
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

	//Phase1. LU Station1 �ȷ�Ÿ��¡ �Ϸ�
	cout << "Phase1. LU Station1 �ȷ�Ÿ��¡ �Ϸ�  " << endl;
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
	//1-2. �� �ȷ��� �Ƚ���Ÿ�԰� ������ƮŸ���� ã�´�(fixture_type�� ���� �ø� Part ��Ī ��Ű��)
	std::cout << "<LUSTATION2>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU2.size(); i++)
	{
		InitializeSystem.PALLET_LU2[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU2[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU2[i].Fixture_vec.size(); j++)
		{
			cout << "-----���� Fixture type : " << InitializeSystem.PALLET_LU2[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU2_temp;
			for (int k = 0; k < Part_LU2_vec.size(); k++)  //Part_LU2_vec �ε������̼Ǻ� ������� ��Ʈ 
			{
				cout << "���� ������� ��Ʈ " << Part_LU2_vec[k].Total_Part_No << "�� type" << Part_LU2_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU2[i].Fixture_vec[j].Fixture_No == Part_LU2_vec[k].Part_Type) //fixtureŸ�԰� ���� part�� �߿��� duedate���� ª���ͳ��� �ȷ����̷� ���� �ε���ų����.
				{

					//cout << "���� ������� ��Ʈ�� �Ƚ���Ÿ�� �´���Ʈ" << Part_LU2_vec[k].Total_Part_No << "�� type" << Part_LU2_vec[k].Part_Type <<endl;
					cout << "���� Part Type:" << Part_LU2_vec[k].Part_Type << endl;
					//cout << "���� Part Due Date:" << Part_LU2_vec[k].Due_Date << endl;

					//1-3. fixture_type�� ���� Part_Type�� ��Ʈ�߿��� ���� Due_Date�� ª�� Part_No�� ����  
					Part_LU2_temp.push_back(Part_LU2_vec[k]);
					cout << "�ĺ���ƮNo :" << Part_LU2_temp[count].Total_Part_No << endl;
					cout << "�װ���Type :" << Part_LU2_temp[count].Part_Type << endl;
					cout << "�װ���DueDate:" << Part_LU2_temp[count].Due_Date << endl;

					cout << "==> �װ��� ����ª����: " << Part_LU2_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!���� �̻���

					InitializeSystem.PALLET_LU2[i].SelecPart.push_back(Part_LU2_temp[0]);   //���õ���Ʈ �ȷ�(����ü)�� ����               

					//1-4. ���õ� ��Ʈ�� ��Ʈpool(Part_LU2_vec)���� �����.
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

	//Phase1. LU Station1 �ȷ�Ÿ��¡ �Ϸ�
	cout << "Phase1. LU Station2 �ȷ�Ÿ��¡ �Ϸ�  " << endl;
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
	//1-2. �� �ȷ��� �Ƚ���Ÿ�԰� ������ƮŸ���� ã�´�(fixture_type�� ���� �ø� Part ��Ī ��Ű��)
	std::cout << "<LUSTATION3>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU3.size(); i++)
	{
		InitializeSystem.PALLET_LU3[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + InitializeSystem.PALLET_LU2.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU3[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU3[i].Fixture_vec.size(); j++)
		{
			cout << "-----���� Fixture type : " << InitializeSystem.PALLET_LU3[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU3_temp;
			for (int k = 0; k < Part_LU3_vec.size(); k++)  //Part_LU3_vec �ε������̼Ǻ� ������� ��Ʈ 
			{
				cout << "���� ������� ��Ʈ " << Part_LU3_vec[k].Total_Part_No << "�� type" << Part_LU3_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU3[i].Fixture_vec[j].Fixture_No == Part_LU3_vec[k].Part_Type) //fixtureŸ�԰� ���� part�� �߿��� duedate���� ª���ͳ��� �ȷ����̷� ���� �ε���ų����.
				{

					//cout << "���� ������� ��Ʈ�� �Ƚ���Ÿ�� �´���Ʈ" << Part_LU3_vec[k].Total_Part_No << "�� type" << Part_LU3_vec[k].Part_Type <<endl;
					cout << "���� Part Type:" << Part_LU3_vec[k].Part_Type << endl;
					//cout << "���� Part Due Date:" << Part_LU3_vec[k].Due_Date << endl;

					//1-3. fixture_type�� ���� Part_Type�� ��Ʈ�߿��� ���� Due_Date�� ª�� Part_No�� ����  
					Part_LU3_temp.push_back(Part_LU3_vec[k]);
					cout << "�ĺ���ƮNo :" << Part_LU3_temp[count].Total_Part_No << endl;
					cout << "�װ���Type :" << Part_LU3_temp[count].Part_Type << endl;
					cout << "�װ���DueDate:" << Part_LU3_temp[count].Due_Date << endl;

					cout << "==> �װ��� ����ª����: " << Part_LU3_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!���� �̻���

					InitializeSystem.PALLET_LU3[i].SelecPart.push_back(Part_LU3_temp[0]);   //���õ���Ʈ �ȷ�(����ü)�� ����               

					//1-4. ���õ� ��Ʈ�� ��Ʈpool(Part_LU3_vec)���� �����.
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

	//Phase1. LU Station3 �ȷ�Ÿ��¡ �Ϸ�
	cout << "Phase1. LU Station3 �ȷ�Ÿ��¡ �Ϸ�  " << endl;
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
//1-2. �� �ȷ��� �Ƚ���Ÿ�԰� ������ƮŸ���� ã�´�(fixture_type�� ���� �ø� Part ��Ī ��Ű��)
	std::cout << "<LUSTATION4>" << endl;
	for (int i = 0; i < InitializeSystem.PALLET_LU4.size(); i++)
	{
		InitializeSystem.PALLET_LU4[i].Total_Pallet_No = InitializeSystem.PALLET_LU1.size() + InitializeSystem.PALLET_LU2.size() + InitializeSystem.PALLET_LU3.size() + i + 1;
		cout << "[Pallet" << InitializeSystem.PALLET_LU4[i].Total_Pallet_No << "]" << endl;

		for (int j = 0; j < InitializeSystem.PALLET_LU4[i].Fixture_vec.size(); j++)
		{
			cout << "-----���� Fixture type : " << InitializeSystem.PALLET_LU4[i].Fixture_vec[j].Fixture_No << endl;
			int count = 0;
			vector<Part> Part_LU4_temp;
			for (int k = 0; k < Part_LU4_vec.size(); k++)  //Part_LU1_vec �ε������̼Ǻ� ������� ��Ʈ 
			{
				cout << "���� ������� ��Ʈ " << Part_LU4_vec[k].Total_Part_No << "�� type" << Part_LU4_vec[k].Part_Type << endl;
				if (InitializeSystem.PALLET_LU4[i].Fixture_vec[j].Fixture_No == Part_LU4_vec[k].Part_Type) //fixtureŸ�԰� ���� part�� �߿��� duedate���� ª���ͳ��� �ȷ����̷� ���� �ε���ų����.
				{

					//cout << "���� ������� ��Ʈ�� �Ƚ���Ÿ�� �´���Ʈ" << Part_LU1_vec[k].Total_Part_No << "�� type" << Part_LU1_vec[k].Part_Type <<endl;
					cout << "���� Part Type:" << Part_LU4_vec[k].Part_Type << endl;
					//cout << "���� Part Due Date:" << Part_LU1_vec[k].Due_Date << endl;

					//1-3. fixture_type�� ���� Part_Type�� ��Ʈ�߿��� ���� Due_Date�� ª�� Part_No�� ����  
					Part_LU4_temp.push_back(Part_LU4_vec[k]);
					cout << "�ĺ���ƮNo :" << Part_LU4_temp[count].Total_Part_No << endl;
					cout << "�װ���Type :" << Part_LU4_temp[count].Part_Type << endl;
					cout << "�װ���DueDate:" << Part_LU4_temp[count].Due_Date << endl;

					cout << "==> �װ��� ����ª����: " << Part_LU4_temp[0].Total_Part_No << endl;        //!!!!!!!!!!!���� �̻���

					InitializeSystem.PALLET_LU4[i].SelecPart.push_back(Part_LU4_temp[0]);   //���õ���Ʈ �ȷ�(����ü)�� ����               

					//1-4. ���õ� ��Ʈ�� ��Ʈpool(Part_LU1_vec)���� �����.
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

	//Phase1. LU Station1 �ȷ�Ÿ��¡ �Ϸ�
	cout << "Phase1. LU Station4 �ȷ�Ÿ��¡ �Ϸ�  " << endl;
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

	cout << "----------�ȷ�Ÿ��¡ �Ϸ�--------------" << endl << endl;






	/*auto LUSTATION = Loading(InitializeSystem, LU1_State, LU2_State, LU3_State,
	M1_State, M2_State, M3_State, Matrix_For_Max, MATRIX_DUE, MATRIX);//�������� �ùķ��̼� ��ŸƮ ����Ʈ. ���⼭�����ؼ� ���⼭���� */

	Loading(InitializeSystem, Matrix_For_Max, MATRIX_DUE, MATRIX, PalletInSys);



	//�ڡ����� �ε������̼� ������ �ȷ� ��ü�� �� ����ȭ���ѹ���. �̺κ� �ε������̼� �Լ� Ż�� LU_State =1 �̸� 
	//�տ� �ȷ� �ε� �����ð� ��ŭ ��ٷȴ� ������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! �� �� ���۵� �ȷ�������ŭ �񵿱�� ó���Ǵ��� üũ�غ��ߵ�
};


