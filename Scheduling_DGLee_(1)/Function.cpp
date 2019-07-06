#include "stdafx.h"
#include "Function.h"

using namespace std;

void initialize_Job_List(Job_List * JL)
{
	Cell_job * temp = new Cell_job;
	Cell_job* temp2 = new Cell_job;

	temp->next = temp->pre = temp2;
	temp2->next = temp2->pre = temp;

	JL->Head = temp;
	JL->Tail = temp2;

	JL->Length = 0;
};

int input_Last_to_Queue(Queue * Q, Part_T * P)
{
	Cell * temp = new Cell;
	Cell * temp2 = Q->Tail;

	
	temp->Part = P;

	temp->next = temp2;
	temp->pre = temp2->pre; //�ʱ�ȭ
	
	temp->pre->next = temp;
	temp2->pre = temp;
	
	Q->Length ++;

	return Q->Length;
}


int input_Last_to_Job_Queue(Queue_job * Q, Job_T * J)
{
	Cell_job * temp = new Cell_job;
	Cell_job * temp2 = Q->Tail;

	
	temp->Job = J;

	temp->next = temp2;
	temp->pre = temp2->pre; //�ʱ�ȭ
	
	temp->pre->next = temp;
	temp2->pre = temp;
	
	Q->Length ++;

	return Q->Length;
}


void initialize_Machine_List(ifstream * in, Mac_list * ML, int Num_Mac, Rmc_T * Rmc, int Num_Rmc, int Num_pallet, Pallet_T * Pallet_type)
{
	int * int_temp = new int[10000];

	Cell_machine * temp = new Cell_machine;
	Cell_machine * temp2 = new Cell_machine;
	ML->head = temp; 
	ML->tail = temp2;
	temp->next = temp->pre = temp2;  //����Ʈ �ʱ�ȭ
	temp2->next = temp2->pre = temp; // ����Ʈ �ʱ�ȭ
	ML->length = 0;
	Machine_T * temp_Mac;
	
	int i;
	int j;

	
	for(i=0;i<Num_Rmc;i++)
	{
		Rmc[i].Fixture = new Fixture_T;
		Rmc[i].Rmc_No = i+1;
		Rmc[i].RMC_Q = new Queue;
		//initialize_Machine_Queue(Rmc[i].RMC_Q);
		Rmc[i].Loading_ST = new Machine_T;
		Rmc[i].Unloading_ST = new Machine_T;

		Rmc[i].Loading_ST->Machine_Name = new char[30];
		//sprintf(Rmc[i].Loading_ST->Machine_Name, "RMC%d Loading", i+1);
		
		Rmc[i].Unloading_ST->Machine_Name = new char[30];
		//sprintf(Rmc[i].Unloading_ST->Machine_Name, "RMC%d UnLoading", i+1);

		Rmc[i].Loading_ST->Job_Sequence = new Job_List;
		//initialize_Job_List(Rmc[i].Loading_ST->Job_Sequence);

		Rmc[i].Unloading_ST->Job_Sequence = new Job_List;
		//initialize_Job_List(Rmc[i].Unloading_ST->Job_Sequence);
	}
	
	for(i=0;i<Num_Mac;i++)
	{	
		temp_Mac = new Machine_T; //Num_Mac ��ŭ ���� �Ҵ�
		temp_Mac->Current_Job_End_Time = -1;
		temp_Mac->Current_Job_Start_Time = -1;
		temp_Mac->Current_State = 0;
		temp_Mac->idle_time = 0;
		temp_Mac->Total_Working_Time = 0;

		temp_Mac->Job_Sequence = new Job_List;
		initialize_Job_List(temp_Mac->Job_Sequence);
		
		
		temp_Mac->Machine_Name = new char[100];
		*in >> temp_Mac->Machine_Name;
		input_Last_to_Machine_List(ML,temp_Mac);  // machine�� list�� �ϳ��� ����
	}

	temp = ML->head;

	for(i=0;i<Num_Mac;i++)
	{	
		temp = temp->next;
		temp->Mac->Machine_Queue = new Queue;
		initialize_Machine_Queue(temp->Mac->Machine_Queue);
		*in >>temp->Mac->release_time;
	}

	temp = ML->head;
	for(i=0;i<Num_Mac;i++)
	{
		temp = temp->next; // �ϳ��� machine�� ��ġ �ű��
		*in >> temp->Mac->Machine_No; 
	//	cout << temp->Mac->Rmc_No << endl;
	}
	
	int t1, t2;
	for(i=0;i<Num_pallet;i++)
	{
		*in >> t1;
		Pallet_type[i].Fixture = new Fixture_T *[t1];
		Pallet_type[i].Num_Fixt = t1; // pallet�� �� t1��ŭ�� fixture�� ����
		Pallet_type[i].Pallet_index = i ;
		Pallet_type[i].rest_Pallet = 1;
		Pallet_type[i].number_Pallet= 1;
		//Rmc[i].immedieat_working_time = 0;
		
		//	cout << t1 << endl;

		for(j=0;j<t1;j++)
		{
			*in >> t2;
			Pallet_type[i].Fixture[j] = new Fixture_T;

			Pallet_type[i].Fixture[j]->number_Fixture = 1; // fixture type�� ������ 1��
			Pallet_type[i].Fixture[j]->fixture_no = t2; // � fixture type���� 
			Pallet_type[i].Fixture[j]->rest_Fixture = Pallet_type[i].Fixture[j]->number_Fixture;
		//	cout << t2 << endl;
		}
	}

	/*for(i=0;i<Num_Rmc;i++)
	{
		
		int j,k;
		for(j=0;j<100000;j++)
		{
			*in >> int_temp[j];
			if(int_temp[j] == -1)
			{
				break;
			}
		}

		Rmc[i].Machine_Schedule = new int[j];
		for(k=0;k<j;k++)
		{
			Rmc[i].Machine_Schedule[k] = int_temp[k];
		}
		Rmc[i].number_schedule = k;
		
		if(j != 0)
		{
			Rmc[i].next_rest_time = Rmc[i].Machine_Schedule[0];
			Rmc[i].next_working_time = -1;
		}
		else
		{
			Rmc[i].next_rest_time = 31536000;
			Rmc[i].next_working_time = -1;
		}
		Rmc[i].current_state = 1;
		Rmc[i].current_schedule = 0;
	}*/

	temp = ML->head;

	for(i=0;i<Num_Mac;i++)
	{
		temp = temp->next;
		//*in >> temp->Mac->Machine_State;

		int j, k;
		for(j=0;j<100000;j++)
		{
			*in >> int_temp[j]; //����� ���޽ð� �ޱ�
			if(int_temp[j] == -1)
			{
				break;
			}
		}
		
		temp->Mac->Current_Schedule = 0;
		if(temp->Mac->release_time == 0) //����� �غ�ð��� 0 �� �ٷ� �۾�����
		{
			temp->Mac->Machine_Schedule = new int[j]; 
			for(k=0;k<j;k++)
			{
				temp->Mac->Machine_Schedule[k] = int_temp[k];  // machine �����ٿ� �Ҵ�
			}
			temp->Mac->Number_Schedule = j;
			
			if(temp->Mac->Number_Schedule != 0) 
			{
				temp->Mac->Next_Rest_Time = temp->Mac->Machine_Schedule[0]; // ���� ���� �ð��� ù��° �۾��� ������
				temp->Mac->Next_Working_time = -1; 
			}
			else
			{
				temp->Mac->Next_Rest_Time = 31536000;
				temp->Mac->Next_Working_time = -1;
			}
			temp->Mac->Working_or_Rest = 1; //���� �� �ִ� �ð��ȿ� ������ 1 �ƴϸ�0
		}
		else
		{
			temp->Mac->Machine_Schedule = new int[j+1]; //����� �غ�ð� ���ؼ� �迭 ����
			temp->Mac->Machine_Schedule[0] = temp->Mac->release_time; //ù��°�� ����� �غ�ð� ��
			
			for(k=1;k<j+1;k++)
			{
				temp->Mac->Machine_Schedule[k] = int_temp[k-1]; //�ι�°���� �۾��ð��� �������� ��
			}
			temp->Mac->Number_Schedule = j+1; 
						
			temp->Mac->Next_Rest_Time = -1;
			temp->Mac->Next_Working_time = temp->Mac->Machine_Schedule[0]; //���� �۾��ð��� �غ�ð��� �����ں���
		
			temp->Mac->Working_or_Rest = 0; //���� �� �ִ� �ð��ȿ� ������ 1 �ƴϸ�0
		}
		temp->Mac->Current_Schedule = 0;
	}

	delete [] int_temp;

	
}


void initialize_Job_List(ifstream * in, int  Num_parttype, int *Num_Parts, Part_Type_T * PT, Part_T * P, Mac_list * ML)
{
	int i, j, k;
	int NJ = 0;
	int Num_alter_Machine;
	int Tmp1;
	int * part_due2 ;
	

	for(i=0;i< Num_parttype;i++)
	{
		int Demand;
		int Num_Process;
		int Release;
		int Due_Date;
		int Fixture_Type;
		int Pre_part;
		
		*in >> Fixture_Type;
		*in >> Release;
		*in >> Demand;
		*in >> Due_Date;
		*in >> Num_Process;
		*in >> Pre_part;

		part_due2 = new int[Demand];

		for(j=0 ; j < Demand ; j++)
		{				
			*in >> part_due2[j] ;
		}

		NJ += Demand;

		PT[i].demand = Demand;
		PT[i].release_time = Release;
		PT[i].Num_Operation = Num_Process;
		PT[i].Job_ID = i; // Part ID�� Job ID �� �ʿ� ?
		PT[i].Due_Date = Due_Date;
		PT[i].Fixture_Type = Fixture_Type;
		PT[i].Pre_part = Pre_part;
		
		PT[i].part_due = new int [Demand];
		for(j=0 ; j < Demand ; j++)
		{
			PT[i].part_due[j] = part_due2[j];
		}
		
		PT[i].PID = new char*[Num_Process];

		for(j=0; j<Num_Process;j++)
		{
			PT[i].PID[j] = new char[100];
			*in >> PT[i].PID[j]; //Operation �̸� �ޱ�
		}

		PT[i].Process_Plan = new int*[Num_Process]; // ���� �Ҵ� x
		for(j=0;j<Num_Process;j++)
		{
			PT[i].Process_Plan[j] = new int[Num_Process]; //���� �Ҵ� y
			for(k=0;k<Num_Process;k++)
			{
				*in >> PT[i].Process_Plan[j][k];	 // ���μ��� �÷� ��� �ޱ�			
			}
		}
		
		PT[i].Num_Alternative_Machine = new int[Num_Process]; // ��� machine �� process ����ŭ �Ҵ�
		PT[i].Alterntive_Machine_Name = new char**[Num_Process];
		PT[i].Standard_Time = new int*[Num_Process];
		PT[i].Alternative_Mac = new Machine_T**[Num_Process];

		
		for(j=0;j<Num_Process;j++)
		{
			char * temp_char;
			char * temp_char2;

			*in >> Num_alter_Machine;  // Altenative machine �� �ޱ�

			PT[i].Num_Alternative_Machine[j] = Num_alter_Machine;
			PT[i].Alterntive_Machine_Name[j] = new char*[Num_alter_Machine];
			PT[i].Standard_Time[j] = new int[Num_alter_Machine];
			PT[i].Alternative_Mac[j] = new Machine_T*[Num_alter_Machine];

												
			for(k=0;k<PT[i].Num_Alternative_Machine[j];k++)
			{
				PT[i].Alterntive_Machine_Name[j][k] = new char[100];  //ù��° operation�� ������ machine ���� �Ҵ�
		        *in >> PT[i].Alterntive_Machine_Name[j][k]; //ù��° operation�� ������ machine �̸� �ޱ�
				*in >> PT[i].Standard_Time[j][k];
				
				
				temp_char = PT[i].Alterntive_Machine_Name[j][k];
			
				Cell_machine * Node = ML->head->next;  // cell machine�� ML list�� �д�
				while(Node != ML->tail) // ó������ list�� �������� �ݺ��ؼ� ML�� �ִ� machine�� ã�´�
				{
					temp_char2 = Node->Mac->Machine_Name;
					if(strcmp(temp_char, temp_char2)==0) // strcmp ���ڿ��� �Լ�, ������ ���ڿ��̸� 0 ��
					{
						break;
					}
					Node=Node->next; // ���� cell machine�� ����Ŵ
				}

				
				PT[i].Alternative_Mac[j][k] = Node->Mac; //  ML list���� ���� �̸��� machine�� ������ node�� machine�� PT[i].alternative machine�� �ȴ�
			} // �� ML�� ����Ʈ���� machine�� ã�°���????

		}
	}
	
	*Num_Parts = NJ;  //NJ�� Total number of part�� �ȴ�, NJ�� Demand��ŭ ��������


	cout << " NJ �� ? : " <<NJ << endl;

	int Type = 0;
	int r = 0;
	int Demand = 0;
	Cell_machine * T1;
	Cell_machine * T2;
	Mac_list * ML_T;
	
		
	for(i=0;i<NJ;i++)
	{

		P[i].PT = &PT[Type]; // P�� ���� � Part type���� ���� 
		P[i].Current_Process_No = 0;
		
		P[i].loading_waiting = 0;
		P[i].unloading_waiting = 0;
		P[i].Fixture_type = P[i].PT->Fixture_Type; //PT�� fixture type�� �޾ƿ´�
		P[i].Part_No = Demand; // P�� ��ȣ

		P[i].Due_date = P[i].PT->part_due[r]; //due date �迭 �ϳ��� �޴´�
		

		ML_T = new Mac_list;
		T1 = new Cell_machine;
		T2 = new Cell_machine;
		T1->next = T1->pre = T2;
		T2->next = T2->pre = T1;
		ML_T->head = T1;
		ML_T->tail = T2;

		P[i].Machine_Sequence = ML_T; // Part�� machine sequence�� ��Ÿ���� list

		P[i].release_time = P[i].PT->release_time; //PT�� release time�� �޾ƿ�

		
		Tmp1 = P[i].PT->Num_Operation;
		P[i].Select_Process_Time = new int[Tmp1]; // operation ���� ���õ� ���μ��� Ÿ��
		P[i].Mac_Select = new Machine_T* [Tmp1]; // operation���� ���õ� machine 
		P[i].Mac_Select_name = new char * [Tmp1];
		Tmp1 = P[i].PT->Num_Operation;
		P[i].Mac_Select_index = new int[Tmp1]; // operation ���� ���õ� machine �ε���

		P[i].multiplier = 1; //�� P�� ���� demand
		
		
		P[i].Terminated = 0; //?? 
		//P[i].ATWK = TWKR(&P[i], 0); // TWKR �� ��� processing time ���ѰͿ� �׸�ŭ�� process plan depth ������. p1�� 228/3 = 76�� ���� ����
		Demand ++;
		r++;
		
		if(Demand == P[i].PT->demand || P[i].multiplier > 1) // �Ǵ� 
		{
			Type ++;
			r=0;
			Demand = 0;
		}
	}


	
	//cout << PT[4].demand;
	//cout << P[3].Terminated;
	//cout << "00";
}

void initialize_Joblist_Queue(Queue_job * Q)
{
	Cell_job * temp = new Cell_job;
	Cell_job * temp2 = new Cell_job;

	temp->next = temp2;
	temp->pre = temp2;

	temp2->next = temp; //����Ʈ �ʱ�ȭ 
	temp2->pre = temp;

	Q->Head = temp;
	Q->Tail = temp2;
	Q->Length = 0;
}


void initialize_Machine_Queue(Queue * Q)
{
	Cell * temp = new Cell;
	Cell * temp2 = new Cell;

	temp->next = temp2;
	temp->pre = temp2;

	temp2->next = temp; //����Ʈ �ʱ�ȭ 
	temp2->pre = temp;

	Q->Head = temp;
	Q->Tail = temp2;
	Q->Length = 0;
}


double TWKR(Part_T * P, int Current_Process)
{
	int i;
	int total = 0;
	double sum = 0;
	double sum2 = 0;
	for(i=0;i<P->PT->Num_Operation;i++)
	{
		if(P->PT->Process_Plan[Current_Process][i] == 1)
		{
			sum += TWKR(P,i); // DFS (Ʈ�� �ִ� depth���ϱ�) - �������� ���processing time 
			total ++;
		}
	}
	if(total != 0)
	{
		sum /= total * 1.; //sum = ��� workload
	}
	else
	{
		sum = 0; 
	}

	for(i=0;i<P->PT->Num_Alternative_Machine[Current_Process];i++)
	{
		sum2 += P->PT->Standard_Time[Current_Process][i]; // ���� ���μ��� ������ ���μ��� Ÿ�� �� ���Ѱ� (��� ���õ�����)
	}
	if(i != 0)
	{
		sum2 /= i * 1.;
	}
	else
	{
		sum2 = 0;
	}
	

	return sum + sum2;
}

int TWKR2(Job_T * J)
{
	int i;

	int sum = 0;

	for(i=0;i<J->Total_Number_Operation;i++)
	{
		sum += J->Processing_time[i];
	}
	
	

	return sum;
}


int input_Last_to_Machine_List(Mac_list * ML, Machine_T * M)
{
	Cell_machine * temp = new Cell_machine;
	Cell_machine * temp2 = ML->tail;

	temp->Mac = M;

	temp->next = temp2;
	temp->pre = temp2->pre;  

	temp2->pre->next = temp;
	temp2->pre = temp;

	ML->length ++;
	return ML->length;
}



int initialize_Setting(int Num_parts, Part_T * P, Mac_list * ML, Queue * Dummy, Queue * System)
{
	int i;
	int k;
	int j;
	int temp=0;
	Cell * temp_part ;
	
	for(i=0;i<Num_parts;i++) //machine ������
	{
		P[i].All_processing_time = 0; //�ʱ�ȭ

		for(k=0;k<P[i].PT->Num_Operation;k++)
		{
			if (P[i].PT->Num_Alternative_Machine[k] == 0)  // ù��° �۾��� ������ �۾��� ���machine ����
			{
				temp = 0;
			}
			else
			{
				for(j=0; j<P[i].PT->Num_Alternative_Machine[k]; j++)
				{
					temp = P[i].PT->Standard_Time[k][j] ;	
					P[i].All_processing_time += temp;
				}
			}
		}

		//cout << "�� ��ȵ��� �ð��̴� : "<<P[i].All_processing_time << endl;

		input_Last_to_Queue(System,&(P[i])); //�ϴ� queue�� part�� ���Ƴִ´�
	}
	

	temp_part = System->Head->next;
	while( temp_part != System->Tail)
	{
		if(temp_part->Part->PT->Pre_part == -1 || temp_part->Part->PT->Pre_part == -2)
		{
			//cout<< "�ε� ���̷� ���� Part type : "  << temp_part->Part->PT->Job_ID << endl;
			//cout<< "�ε� ���̷� ���� Part ��ȣ : "  << temp_part->Part->Part_No << endl;
			input_Last_to_Queue(Dummy,temp_part->Part);
		}
		
		temp_part = temp_part->next;
	}

	

	return 1;
}

int Total_Proc_Time_in_Buffer(Queue_job * Q, Machine_T *T)
{
	int i;
	int proc = 0;
	Cell_job * temp = Q->Head->next;
	while(temp!= Q->Tail)
	{
		for(i=0 ; i< temp->Job->Total_Number_Operation ; i++)
		{
			if(temp->Job->Machine_Route[i] == T)
			{
				proc += temp->Job->Processing_time[i];
			}
		}

		temp = temp->next;
	}

	return proc;
}

Machine_T * Machine_Selection_MNPB(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) // part���� ������Ʈ�ؼ� ���� machine selection
{
	
	int min = 9999999;
	int i;
	int j;
	int t;
	int a = 0 ;
	int b ;

	Cell_machine *temp2 = ML->head;
	//machine_name = new Machine_T * [Num_machine];



	int temp;
	int temp_i;
	int temp_j;
	//int Crt_Proc = P->Current_Process_No;
	Machine_T * temp_Mac = NULL;
	Machine_T * temp_previous = NULL; //������ ���õ� machine�� �׸�ŭ prosseing time �������� �ȴ�.
	Machine_T * Ret_Mac = NULL; 
	
	
	
	P->Total_Processing_Time = 0;

	for(i=0;i<P->PT->Num_Operation;i++)
	{
		P-> Mac_Select[i]= new Machine_T ;
		P-> Mac_Select_name[i] = new char [100];
		min = 999999;
		temp = 0;

		if (P->PT->Num_Alternative_Machine[i] == 0)  // ù��° �۾��� ������ �۾��� ���machine ����
		{
			P->Mac_Select[i] = NULL ;
			P->Mac_Select_name[i] = NULL;
			P->Mac_Select_index[i] = NULL;
			P->Select_Process_Time[i] = NULL;
		}
		else
		{
			for(j=0;j<P->PT->Num_Alternative_Machine[i];j++)
			{

				//cout << " a : " << a << endl;
				temp_Mac = P->PT->Alternative_Mac[i][j]; // �ٽ� ���� !!

				temp = Total_Proc_Time_in_Buffer(Job_list, temp_Mac);

				for(t=0 ; t< Num_machine ; t++)
				{
					if(temp_Mac == Job_IDNEX->machine_name[t])
					{
						temp = temp+ Job_IDNEX->machine_pro[t];
						//cout << " temp �� : " << temp  << endl;
					}
				}

				if(min > temp)
				{
						temp_i = i;
						temp_j = j;
						min = temp;
						Ret_Mac = temp_Mac;
				}
			}

			if(Ret_Mac != NULL)
			{
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T�� �ް�
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)�� �ް�
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // �׶��� processing time �ޱ�

				temp_previous = Ret_Mac; //���õ� machine�� �޾Ƽ� ���� ������ �˻�
				a = P->Select_Process_Time[i]; //���õ� prosessing time �޾Ƽ� ���� ������ �����ش�

				b=0;
				temp2 = ML->head->next;
				while(temp2 != ML->tail )
				{
					if(temp_previous == temp2->Mac)
					{
						Job_IDNEX->machine_pro[b] += a ;
						Job_IDNEX->machine_name[b] = temp_previous;
					}
					b++;
					temp2 = temp2->next;
				}		


				//cout << "a : " << a <<endl;
				//cout << " part type : " << P->PT->Job_ID << endl; 
				//cout << " part ��ȣ : " << P->Part_No << endl;
				//cout << " machine �̸� " << P->Mac_Select_name[i] << endl;

			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //�� processig time �ޱ�
	}
			
	/*for(t=0 ; t < Num_machine ; t++)
	{
		cout << Job_IDNEX->machine_pro[t] << " " ;
	}*/

	return Ret_Mac;
}


Machine_T * Machine_Selection_MNPB2(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) //pallet�� üũ�ؼ� machine selelction
{
	
	int min = 9999999;
	int i;
	int j;
	int t;
	int a = 0 ;




	int temp;
	int temp_i;
	int temp_j;
	//int Crt_Proc = P->Current_Process_No;
	Machine_T * temp_Mac = NULL;
	Machine_T * temp_previous = NULL; //������ ���õ� machine�� �׸�ŭ prosseing time �������� �ȴ�.
	Machine_T * Ret_Mac = NULL; 
	
	
	
	P->Total_Processing_Time = 0;

	for(i=0;i<P->PT->Num_Operation;i++)
	{
		P-> Mac_Select[i]= new Machine_T ;
		P-> Mac_Select_name[i] = new char [100];
		min = 999999;
		temp = 0;

		if (P->PT->Num_Alternative_Machine[i] == 0)  // ù��° �۾��� ������ �۾��� ���machine ����
		{
			P->Mac_Select[i] = NULL ;
			P->Mac_Select_name[i] = NULL;
			P->Mac_Select_index[i] = NULL;
			P->Select_Process_Time[i] = NULL;
		}
		else
		{
			for(j=0;j<P->PT->Num_Alternative_Machine[i];j++)
			{

				cout << " a : " << a << endl;
				temp_Mac = P->PT->Alternative_Mac[i][j]; // �ٽ� ���� !!

				temp = Total_Proc_Time_in_Buffer(Job_list, temp_Mac);

				if(min > temp)
				{
						temp_i = i;
						temp_j = j;
						min = temp;
						Ret_Mac = temp_Mac;
				}
			}

			if(Ret_Mac != NULL)
			{
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T�� �ް�
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)�� �ް�
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // �׶��� processing time �ޱ�

				temp_previous = Ret_Mac; //���õ� machine�� �޾Ƽ� ���� ������ �˻�
				a = P->Select_Process_Time[i]; //���õ� prosessing time �޾Ƽ� ���� ������ �����ش�

				//cout << "a : " << a <<endl;
				//cout << " part type : " << P->PT->Job_ID << endl; 
				//cout << " part ��ȣ : " << P->Part_No << endl;
				//cout << " machine �̸� " << P->Mac_Select_name[i] << endl;

			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //�� processig time �ޱ�
	}
			
	for(t=0 ; t < Num_machine ; t++)
	{
		cout << Job_IDNEX->machine_pro[t] << " " ;
	}
	cout << endl;
	return Ret_Mac;
}
Machine_T * Machine_Selection_SPT(Part_T * P)
{
	
	int min = 9999999;
	int i;
	int j;
	int t;
	
	int temp;
	int temp_i;
	int temp_j;
	//int Crt_Proc = P->Current_Process_No;
    Machine_T * temp_Mac;
	Machine_T * Ret_Mac = NULL; 
	
	
	t = 0;
	P->Total_Processing_Time = 0;

	for(i=0;i<P->PT->Num_Operation;i++)
	{
		P-> Mac_Select[i]= new Machine_T ;
		P-> Mac_Select_name[i] = new char [100] ;
		min = 999999;

		if (P->PT->Num_Alternative_Machine[i] == 0)  // ù��° �۾��� ������ �۾��� ���machine ����
		{
			P->Mac_Select[i] = NULL ;
			P->Mac_Select_name[i] = NULL;
			P->Mac_Select_index[i] = NULL;
			P->Select_Process_Time[i] = NULL;
		}
		else
		{
			for(j=0;j<P->PT->Num_Alternative_Machine[i];j++)
			{
				temp_Mac = P->PT->Alternative_Mac[i][j]; // �ٽ� ���� !!
				temp = P->PT->Standard_Time[i][j] ;
					if(min > temp)
					{
						temp_i = i;
						temp_j = j;
						min = temp;
						Ret_Mac = temp_Mac;
					}
			}

			if(Ret_Mac != NULL)
			{
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T�� �ް�
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)�� �ް�
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // �׶��� processing time �ޱ�

				//cout << " part type : " << P->PT->Job_ID << endl; 
			    //cout << " part ��ȣ : " << P->Part_No << endl;
				//cout << " machine �̸� " << P->Mac_Select_name[i] << endl;
			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //�� processig time �ޱ�
	}
			


	return Ret_Mac;
}

void Loading(Pallet_T * Pallet_type, Part_T * P, Job_T *J, int Num_pallet, Queue * Dummy, int Job_index, Queue_job * Job_list, Config * Job_IDNEX, int Machine_Selection_Option, int Num_machine, Mac_list * ML, int Input_Sequence_Option, int Job_route_Option)
{
	int k;
	int v;

	Job_T tem_Job;

	Job_index = Job_IDNEX->Job_index;
	
		for(k=0 ; k < Num_pallet ; k++)
		{
			if(Pallet_type[k].rest_Pallet == 1)
			{
				if( Input_Sequence_Option == 1)
				{
					tem_Job = Job_Define_SPPT(P, &(Pallet_type[k]), Dummy, Machine_Selection_Option, Job_list, Num_machine, ML, Job_IDNEX); // job define  rule��� ����� function �����
				}
				else if (Input_Sequence_Option == 2)
				{
					tem_Job = Job_Define_EDD(P, &(Pallet_type[k]), Dummy, Machine_Selection_Option, Job_list, Num_machine, ML , Job_IDNEX);
				}

				if(tem_Job.Empty == 0) //part�� �ö� pallet�� job���� define
				{
					Pallet_type[k].rest_Pallet = 0;
					
					//J[Job_index] = tem_Job ; //job index �ش�

					J[Job_index].P = new Part_T*[tem_Job.Pallet_job->Num_Fixt];
					//J[Job_index].Current_OP_Position = new int[tem_Job.Pallet_job->Num_Fixt]; //current operation �߿� �ϳ� ���� �� machine route �Ǵ� operation index�� ������.

					for(v=0 ; v < tem_Job.Pallet_job->Num_Fixt ; v++)
					{
						J[Job_index].P[v] = new Part_T;
						J[Job_index].P[v] = tem_Job.P[v];

						if(J[Job_index].P[v] != NULL)
						{
							J[Job_index].P[v]->Job_No = Job_index; //� job�� ���ϴ���
							//J[Job_index].Current_OP_Position[v] = J[Job_index].P[v]->Current_Process_No; // ù��° operation�� ����. v��° part�� operation ��ġ�� ��Ÿ��
						}
						else
						{
							//J[Job_index].Current_OP_Position[v] = NULL; //0�� operation�� ����.
						}
					}

					J[Job_index].Pallet_job = tem_Job.Pallet_job ;
					J[Job_index].Empty = tem_Job.Empty;
					J[Job_index].Total_Number_Operation = (tem_Job.Total_Number_Operation - (2*tem_Job.Num_parts)) ; //part type �� ���۰� �� operation ���� �� 1����ŭ �� �Ҵ�!

					J[Job_index].Job_No = Job_index;
					J[Job_index].Num_parts = tem_Job.Num_parts; // ��� part�� �ö󰬴���
					J[Job_index].current_position = 0; //Route�� ���ٴҶ� �ʿ���!
					J[Job_index].current_state=0; //1�̸� �۾����̴�
					J[Job_index].avg_duedate = tem_Job.avg_duedate/tem_Job.Num_parts;

				

					if(Job_route_Option == 1)
					{
						Job_route(&(J[Job_index])); //Job route greedy ������� ����
					}
					else if( Job_route_Option == 2 )
					{
						Job_IDNEX->total_movement = 99;
						Job_IDNEX->temp = 99;
						Job_route_HU(&(J[Job_index]), Job_IDNEX); //Job route DP ������� ����
					}
					else if( Job_route_Option == 3 )
					{
						Job_IDNEX->total_movement = 99;
						Job_IDNEX->temp = 99;
						Job_route_DP(&(J[Job_index]), Job_IDNEX);//Job route DP ������� ����
					}
		

					input_Last_to_Job_Queue(Job_list, &J[Job_index]); //part�� �ö� pallet�� buffer(job_list)�� ���� ����Ʈ�� �ڿ��� ���� ����
					Job_index ++;
					
					//cout << "Job�� �ö���� part�� �� : " << tem_Job.Num_parts << endl;
					//cout << " Job�� ��� due date : " << tem_Job.avg_duedate/tem_Job.Num_parts<< endl;
					
				}
				/*else
				{
					J[Job_index].Pallet_job = tem_Job.Pallet_job ;
					J[Job_index].P = new Part_T*[tem_Job.Pallet_job->Num_Fixt];
					for(v=0 ; v < tem_Job.Pallet_job->Num_Fixt ; v++)
					{
						J[Job_index].P[v] = new Part_T;
						J[Job_index].P[v] = tem_Job.P[v]; //NULL �� �޴´�
					}
					J[Job_index].Empty = tem_Job.Empty;
				
				}*/

			}

			else 
			{
				//cout << " No more pallet " << endl; // ���� ���� �ȷ��� ���ٸ�?? ��� ??
			}
			

		
			Job_IDNEX->Job_index = Job_index;

		}
	
}

Job_T Job_Define_FIFO(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy)
{
	int i =0 ;
	int j;
	int k =1;
	Job_T Temp_Job ;
	//Job_T No_Job ;

	int o = 0;

	Temp_Job.Total_Number_Operation = 0;

	Cell * temp;
	Cell * temp_a = NULL;
	
	Temp_Job.P = new Part_T *[Pallet_type->Num_Fixt];

	//cout << "���ο� pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		//cout << j << endl;
		temp = Dummy->Head->next ;
		k=1;
		

		//cout << "����fixture " << endl;
		while(temp != Dummy->Tail)
		{
			//cout << k << endl ;
			k++;
			
			if(temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1) // 
			{
				i++;
				Temp_Job.P[j] = new Part_T ;
				Temp_Job.P[j] = temp->Part; //� part�� ���Դ���	

				
				Temp_Job.Total_Number_Operation += temp->Part->PT->Num_Operation; //������ part���� operation ���� ��ġ��
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job�� � �ȷ��� �����Ǵ���
				Temp_Job.Empty = 0; // pallet�� part�� �ö󰡸� 0

				

				//cout <<"fixture�� �ɸ��� part : "<<  o << endl;
				o++;

				temp->next->pre = temp->pre;
				temp->pre->next = temp->next;//���õ� part�� queue���� ������� 
				temp_a = temp;
				temp = temp->next;

				delete temp_a;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // �׶� fixture�� ����
				
				break;
				
			}
			
			
				Temp_Job.P[j] = NULL;

				temp = temp->next;
		}
		


	}

		
	return Temp_Job ;

}

Job_T Job_Define_EDD(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy, int Machine_Selection_Option, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) 
{
	int i =0 ;
	int p;
	int j;
	int t;
	int total_duedate = 0;
	
	Machine_T *temp_Mac;
	Job_T Temp_Job ;
	//Job_T No_Job ;
	int min = 999999;

	int o = 0;

	Temp_Job.Total_Number_Operation = 0;

	Cell * temp;
	Cell * test = NULL;


	Job_IDNEX->machine_name = new Machine_T * [Num_machine]; // machine selection �Ҷ� name list �ޱ�
	Job_IDNEX->machine_pro = new int [Num_machine]; // machine selection �Ҷ� ���� machine�鿡 ���� processing time �ޱ�
	
	Temp_Job.P = new Part_T *[Pallet_type->Num_Fixt];

	for(t=0 ; t < Num_machine ; t++)
	{
		Job_IDNEX->machine_pro[t] = 0; //�ʱ�ȭ
		Job_IDNEX->machine_name[t] =  new Machine_T ; // �ʱ�ȭ
	}


	//cout << "���ο� pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		Temp_Job.P[j] = new Part_T ;
		//cout << j << endl;

		Cell * test = NULL;
		temp = Dummy->Head->next ;
	
		
		//cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;
		min = 99999;
		//cout << "����fixture " << endl;
		while(temp != Dummy->Tail)
		{

			
			//cout << " ddddddddddddddddddddd " << endl;
			if(temp->Part->Terminated==0 && temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1 && min > temp->Part->Due_date) // ��� ����� �����ð� �� min�� 
			{
					//cout << "aaaaaaaaaaaaaa " << endl;
					test = temp; //� part�� ���Դ���	
					min = temp->Part->Due_date; 
				
					//cout <<"fixture�� �ɸ��� part : "<<  temp->Part->Part_No << endl;
					//cout <<"fixture�� �ɸ��� part type : "<<  temp->Part->PT->Job_ID << endl;
					//cout << " Pocessing time aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa :" << temp->Part->PT->Due_Date << endl;
				  //  cout << endl;
					
				o++;
			}
			

			temp= temp->next;
		}

		if(test == NULL)
		{
			Temp_Job.P[j] = NULL;
		}
		else
		{
				Temp_Job.P[j] = test->Part;
				i++;
				Temp_Job.Total_Number_Operation += test->Part->PT->Num_Operation; //������ part���� operation ���� ��ġ��
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job�� � �ȷ��� �����Ǵ���
				Temp_Job.Empty = 0; // pallet�� part�� �ö󰡸� 0
				total_duedate += test->Part->Due_date;
				Temp_Job.avg_duedate = total_duedate;

				//cout<< "�ε� �Ǵ� Part type : "  << test->Part->PT->Job_ID << endl;
				//cout<< "�ε� �Ǵ� Part ��ȣ : "  << test->Part->Part_No << endl;
				//cout<< "�ε� �Ǵ� Pallet ��ȣ : "  << Pallet_type->Pallet_index << endl;
				//cout << " total duedate = : " << Temp_Job.avg_duedate<< endl;
				//cout << "�ö� ���� part�� �� : " << Temp_Job.Num_parts<< endl;
					
				if(Machine_Selection_Option == 1)
				{
					temp_Mac = Machine_Selection_SPT(test->Part);//opreation ���� machine ���� 
					//cout << "total processing time ===============: " << test->Part->Total_Processing_Time << endl;
				}
				else if(Machine_Selection_Option == 2)
				{
					if(Job_list->Length==0) // buffer�� �ƹ��͵� �������� SPT�� ����
					{
						temp_Mac = Machine_Selection_SPT(test->Part);
					}
					else // buffer�� job�� ������ machine�� �� processing time���� ���
					{
						temp_Mac = Machine_Selection_MNPB(test->Part, Job_list, Num_machine, ML, Job_IDNEX);
					}
				}


			//	cout << " �̶��� part ��ȣ : " << Temp_Job.P[j]->Part_No << endl;
			//  cout << " �̶��� PT type: " << Temp_Job.P[j]->PT->Job_ID<< endl;
			//	cout <<" �̰� ��Ż �ѹ� ���� ���۷��׼� : " << Temp_Job.Total_Number_Operation << endl;


				test->next->pre = test->pre;
				test->pre->next = test->next;//���õ� part�� queue���� ������� 

				delete test;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // �׶� fixture�� ����
		}
	
	}

		
	return Temp_Job ;

}

Job_T Job_Define_SPPT(Part_T *P, Pallet_T *Pallet_type, Queue * Dummy, int Machine_Selection_Option, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) 
{
	int i =0 ;
	int p;
	int j;
	int t;
	int total_duedate = 0;

	Machine_T *temp_Mac;
	Job_T Temp_Job ;
	//Job_T No_Job ;
	int min = 999999;

	int o = 0;

	Temp_Job.Total_Number_Operation = 0;

	Cell * temp;
	Cell * test = NULL;
	

	Job_IDNEX->machine_name = new Machine_T * [Num_machine]; // machine selection �Ҷ� name list �ޱ�
	Job_IDNEX->machine_pro = new int [Num_machine]; // machine selection �Ҷ� ���� machine�鿡 ���� processing time �ޱ�

	Temp_Job.P = new Part_T *[Pallet_type->Num_Fixt];


	for(t=0 ; t < Num_machine ; t++)
	{
		Job_IDNEX->machine_pro[t] = 0; //�ʱ�ȭ
		Job_IDNEX->machine_name[t] =  new Machine_T ; // �ʱ�ȭ
	}



	//cout << "���ο� pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		Temp_Job.P[j] = new Part_T ;
		//cout << j << endl;

		Cell * test = NULL;
		temp = Dummy->Head->next ;
	
		
		//cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;
		min = 99999;
		//cout << "����fixture " << endl;
		while(temp != Dummy->Tail)
		{

			
			//cout << " ddddddddddddddddddddd " << endl;
			if(temp->Part->Terminated ==0 && temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1 && min > temp->Part->All_processing_time) // ��� ����� �����ð� �� min�� 
			{
					//cout << "aaaaaaaaaaaaaa " << endl;
				test = temp; //� part�� ���Դ���	
				min = temp->Part->All_processing_time; 
				
					//cout << " Pocessing time aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa :" << temp->Part->Total_Processing_Time << endl;
					//cout <<"fixture�� �ɸ��� part : "<<  o << endl;
				o++;
			}
			

			temp= temp->next;
		}

		if(test ==NULL)
		{
			Temp_Job.P[j] = NULL;
		}
		else
		{
				Temp_Job.P[j] = test->Part;
				i++;
				Temp_Job.Total_Number_Operation += test->Part->PT->Num_Operation; //������ part���� operation ���� ��ġ��
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job�� � �ȷ��� �����Ǵ���
				Temp_Job.Empty = 0; // pallet�� part�� �ö󰡸� 0
				total_duedate += test->Part->Due_date;
				Temp_Job.avg_duedate = total_duedate;


				//cout<< "�ε� �Ǵ� Part type : "  << test->Part->PT->Job_ID << endl;
				//cout<< "�ε� �Ǵ� Part ��ȣ : "  << test->Part->Part_No << endl;
				//cout<< "�ε� �Ǵ� Pallet ��ȣ : "  << Pallet_type->Pallet_index << endl;
					
				if(Machine_Selection_Option == 1)
				{
					temp_Mac = Machine_Selection_SPT(test->Part);//opreation ���� machine ���� 
					//cout << "total processing time ===============: " << test->Part->Total_Processing_Time << endl;
				}
				else if(Machine_Selection_Option == 2)
				{
					if(Job_list->Length==0) // buffer�� �ƹ��͵� �������� SPT�� ����
					{
						temp_Mac = Machine_Selection_SPT(test->Part);
						//cout << " ���� ������ ? " << endl;
					}
					else // buffer�� job�� ������ machine�� �� processing time���� ���
					{
						//cout << " ���� ������ 2222222? " << endl;
						temp_Mac = Machine_Selection_MNPB(test->Part, Job_list, Num_machine, ML, Job_IDNEX);
						//cout << " ���� ������ 3333333333? " << endl;
					}
				}


			//	cout << " �̶��� part ��ȣ : " << Temp_Job.P[j]->Part_No << endl;
			//  cout << " �̶��� PT type: " << Temp_Job.P[j]->PT->Job_ID<< endl;
			//	cout <<" �̰� ��Ż �ѹ� ���� ���۷��׼� : " << Temp_Job.Total_Number_Operation << endl;


				test->next->pre = test->pre;
				test->pre->next = test->next;//���õ� part�� queue���� ������� 

				delete test;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // �׶� fixture�� ����
		}
	
	}

		
	return Temp_Job ;

}

void Job_route(Job_T *J)
{
	int j;
	int k;
	int a;
	
	
	int part_number;
	int *machine_movement ;
	Part_T *current_part;
	int current_part_op;

	int *part_position_index; //Job�� P���� NULL�� �� part������ �ִ�. ���� ����ִ� P�� postion index�� �ʿ�
	int  *temp_op_index;
	//Part_T temp_part;
	//Machine_T temp_machine ;

	current_part = new Part_T;
	machine_movement = new int[J->Num_parts]; //J��P�� NULL������ ���� �޸𸮰��� ����� 
	part_position_index = new int[J->Num_parts];
	temp_op_index = new int [J->Num_parts];

	for(k=0 ; k<J->Num_parts ; k++)
	{
		temp_op_index[k] = 0; //index�� 0�̴�
	}

	
	J->OP_Route = new int[J->Total_Number_Operation+1]; //operation route
	J->Part_Route = new Part_T *[J->Total_Number_Operation+1]; // part route
	J->Machine_Route = new Machine_T *[J->Total_Number_Operation+1] ; //machine route
	J->Machine_name = new char * [J->Total_Number_Operation+1];
	J->Processing_time = new int[J->Total_Number_Operation+1]; 

	for(k=0 ; k<J->Total_Number_Operation+1; k++)
	{
		J->Part_Route[k] = new Part_T;
		J->Machine_Route[k] = new Machine_T;
		J->Machine_name[k] = new char[100];
	}


	for(k=0 ; J->Pallet_job->Num_Fixt ; k++)
	{
		if( J->P[k] != NULL)
		{
			part_number = k;
			break;
		}
	}

	

	j=0;
	k=0;

	if( J->P[k] != NULL)
	{
			part_position_index[j] = k;
			k++;

		for(j=1 ; j<J->Num_parts ; j++)
		{
	
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}

	else
	{   k++;
		for(j=0 ; j<J->Num_parts ; j++)
		{
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}
	
	for(a=0 ; a<J->Num_parts ; a++)
	{
		//cout <<"Partposition : "<< part_position_index[a] << endl;
	}
	
	for(a=0 ; a<J->Pallet_job->Num_Fixt ; a++)
	{
		if(J->P[a] != NULL)
		{	
			//cout << "J�� part type : " << J->P[a]->PT->Job_ID << "    " ;
			
		}
	}
	
	for(j=0 ; j < J->Num_parts ; j++)
	{
		//cout << J->P[part_position_index[j]]->PT->Job_ID << endl;
	}
	
	J->OP_Route[0] = J->P[part_number]->Current_Process_No+1 ; //rand���� �޾������� ��
	J->Part_Route[0] =  J->P[part_number] ;
	J->Machine_Route[0] = J->P[part_number]->Mac_Select[1];  //rand���� �ϳ� �޾ƿ´� //�����ϰ� ��ȣ���� �� �ϳ��� part�� ù��° operation���� ����
	J->Machine_name[0] = J->P[part_number]->Mac_Select_name[1]; // ù��° operation�̱� ������ 
	J->Processing_time[0] =  J->P[part_number]->Select_Process_Time[1];
	J->Total_movement = 0 ;

	temp_op_index[0] += 1; // ù��° �迭�� �� part�� operation ��ȣ 
	current_part = J->P[part_number]; // ���� part
	current_part_op = J->P[part_number]->Current_Process_No+1; // ���� part�� operation ��ȣ

	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //���������� 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // �Ǹ����� �ƹ����� ����
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //�Ǹ������� �ƹ����� ����
	J->Machine_name[J->Total_Number_Operation+1] = NULL ;
	J->Processing_time[J->Total_Number_Operation+1] = NULL; 

	machine_movement = movement_cal(current_part, current_part_op, temp_op_index, J, part_position_index); // movement ��� �� selection
	

	J->TWKR = TWKR2(J);

	//cout <<"Job�� ��ȣ : " << J->Job_No << endl;
	//cout <<"Job�� TWKR : " << J->TWKR << endl;


	/*for(j=1;j<J->Total_Number_Operation;j++)
	{
		for(k=0 ; k<J->Pallet_job->Num_Fixt ; k++)
		{
			if(J->Part_Route[0] == J->Part_Route[k] ~~~~)
			{
				temp_machine = J->P[k]->Mac_Select[0] ;// Machine movement �ּ�ȭ�� �Ǵ°� ! � ������ ���ؼ� �ϳ��� ���õ� �� temp machine�� �ȴ�
				temp_part = J->P[k]
				temp_op_index =
			{
		}

		J->Machine_Route[j] = temp_machine;
		J->Part_Route[j] = temp_part;
		J->OP_Route[j] = J->P[k]->Current_Process_No ;
		J->Machine_name[j] =
	}*/
	
}





void Job_route_HU(Job_T *J, Config * Job_IDNEX)
{
	
	int j;
	int k;
	int a;
	int r = 0; //temp

	int index;
	int p;
	int s;
	int total_machine_movement = 0;
	int v = 0;
	
	int i ;
	j=0;
	k=0;
	int min = 999;



	int *machine_movement;
	Part_T *current_part;
	int current_part_op;
	int *part_position_index; //Job�� P���� NULL�� �� part������ �ִ�. ���� ����ִ� P�� postion index�� �ʿ�
	int * part_position_index2;
	int  *temp_op_index;

	int part_number;
	int total_num_operation;
	int Num_part_on_pallet;
	


	total_num_operation = J->Total_Number_Operation; // �� operation����
	
	Num_part_on_pallet = J->Num_parts; //��� part�� �ö���ִ���


	current_part = new Part_T;
	machine_movement = new int[J->Num_parts]; //J��P�� NULL������ ���� �޸𸮰��� ����� 
	part_position_index = new int[J->Num_parts];
	part_position_index2 = new int[J->Num_parts];
	temp_op_index = new int [J->Num_parts];


	int  *temp_op_index2; // part���� operation index
	temp_op_index2 = new int [Num_part_on_pallet]; // part���� ���� operation index

	for(k=0 ; k<Num_part_on_pallet ; k++)
	{
		temp_op_index2[k] = 0; //index�� 0�̴�
		temp_op_index[k] = 0;
	}
	

	




	int *temp; // �ӽ� operation ����
	int *temp2;
	int *Job_route; //job route = final job route ����

	Job_route = new int [total_num_operation];
	temp2 = new int [total_num_operation];
	temp = new int [total_num_operation];

	for(j=0; j < total_num_operation ; j++)
	{
		Job_route[j] = 1;
		temp2[j] = 0;
		temp[j] = 0;
	}
	

	


	for(k=0 ; J->Pallet_job->Num_Fixt ; k++)
	{
		if( J->P[k] != NULL)
		{
			part_number = k;
			break;
		}
	}




	J->OP_Route = new int[J->Total_Number_Operation+1]; //operation route
	J->Part_Route = new Part_T *[J->Total_Number_Operation+1]; // part route
	J->Machine_Route = new Machine_T *[J->Total_Number_Operation+1] ; //machine route
	J->Machine_name = new char * [J->Total_Number_Operation+1];
	J->Processing_time = new int[J->Total_Number_Operation+1]; 

	for(k=0 ; k<J->Total_Number_Operation+1; k++)
	{
		J->Part_Route[k] = new Part_T;
		J->Machine_Route[k] = new Machine_T;
		J->Machine_name[k] = new char[100];
	}



	J->OP_Route[0] = J->P[part_number]->Current_Process_No+1 ; //rand���� �޾������� ��
	J->Part_Route[0] =  J->P[part_number] ;
	J->Machine_Route[0] = J->P[part_number]->Mac_Select[1];  //rand���� �ϳ� �޾ƿ´� //�����ϰ� ��ȣ���� �� �ϳ��� part�� ù��° operation���� ����
	J->Machine_name[0] = J->P[part_number]->Mac_Select_name[1]; // ù��° operation�̱� ������ 
	J->Processing_time[0] =  J->P[part_number]->Select_Process_Time[1];
	J->Total_movement = 0 ;


	temp_op_index[0] += 1; // ù��° �迭�� �� part�� operation ��ȣ 
	current_part = J->P[part_number]; // ���� part
	current_part_op = J->P[part_number]->Current_Process_No+1; // ���� part�� operation ��ȣ


	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //���������� 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // �Ǹ����� �ƹ����� ����
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //�Ǹ������� �ƹ����� ����
	J->Machine_name[J->Total_Number_Operation+1] = NULL ;
	J->Processing_time[J->Total_Number_Operation+1] = NULL; 

	


	j=0;
	k=0;


	if( J->P[k] != NULL)
	{
			part_position_index[j] = k;
			k++;

		for(j=1 ; j<J->Num_parts ; j++)
		{
	
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}

	else
	{   k++;
		for(j=0 ; j<J->Num_parts ; j++)
		{
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}




	/*
	for(a=0 ; a<total_num_operation ; a++) // route �˰��� ���� ���⼭ a�� ���� operation ���� �������̴�.
	{
		
				Job_IDNEX->temp = movement_cal2(temp, part_position_index, J, total_num_operation, temp_op_index2,Job_IDNEX);
			
				
				if( Job_IDNEX->temp < Job_IDNEX->total_movement )
				{
					Job_IDNEX->total_movement = Job_IDNEX->temp;
				

					for(k=0 ; k<total_num_operation ; k++)
					{
						//Job_route[k] = temp_route[k];
						Job_route[k] = temp[k];	
					  
					}
					
				}
	}
	*/


	


	for(a=1 ; a<total_num_operation ; a++) // route �˰��� ���� ���⼭ a�� ���� operation ���� �������̴�.
	{
		

		//num = new int [a];
		//temp = new int [a+1];


		// num�� Job_route �޴´�
		// temp �ʱ�ȭ 

		Job_IDNEX->total_movement = 99; //movement �ٽ� �ʱ�ȭ

		/*
		cout << "temp op index : " << temp_op_index[0] << endl;
		cout << "temp op index : " << temp_op_index[1] << endl;
		cout << "temp op index : " << temp_op_index[2] << endl;
		cout << "temp op index : " << temp_op_index[3] << endl;
		cout << "current part : " << current_part->PT->Job_ID << endl;
		cout << "part_position_index : " <<part_position_index[0] <<endl;
		*/

		for(i=0 ; i < J->Num_parts ; i++)
		{
			if(temp_op_index[i] != -1)
			{
				if(temp_op_index[i] < J->P[part_position_index[i]]->PT->Num_Operation-1) // J�� P�� operation ���ں��� ��������!
				{

					if(i==r) //ó���� current part�� position�� 0�̴�. �ѹ� iteration �� r�� ���� �ٲ� current part�� position ��ȭ �˱� ���� r�� ����
					{
						if(current_part->Mac_Select[current_part_op+1] != NULL)
						{
							if(current_part->Mac_Select[current_part_op] != current_part->Mac_Select[current_part_op+1])
							{
								v = 1;
								machine_movement[i] = v ;
							}
							else
							{
								v = 0;
								machine_movement[i] = v ;
							}
						}
						else
						{
							temp_op_index[i] = -1;
							machine_movement[i] = 99;
						}


					}
					else
					{
							if(current_part->Mac_Select[current_part_op] != J->P[part_position_index[i]]->Mac_Select[temp_op_index[i]+1])
							{
								v = 1 ;
								machine_movement[i] = v ;
							}
							else
							{
								v = 0;
								machine_movement[i] = v ;
							}
					}

				}
				else
				{
					temp_op_index[i] = -1;
					machine_movement[i] = 99;	//operation �Ҵ� �� �Ȱ��� �ǹ� !
				}
			}
		}
		


		/*for (a=0 ; a<J->Num_parts ; a++)
		{
			cout <<" machine movement : " << machine_movement[a] << endl ;
		}*/


		min=999;
		for(k=0 ; k < J->Num_parts ; k++) //�ּ� movementã�´� 
		{			
			if(machine_movement[k] <= min )
			{
				min = machine_movement[k];
				r = k; // current part�� position�� �ٲ�
				//cout << " r�� �� : " << r << endl;
			}
		}


		if(machine_movement[r] ==1)
		{
			total_machine_movement += 1;
		}
		current_part = J->P[part_position_index[r]];
		temp_op_index[r] += 1;
		current_part_op = temp_op_index[r];


		/*for(k=0 ; k < J->Num_parts ; k++) //�ּ� movementã�� ����غ���
		{	
			cout << " temp part op �� �� : " << temp_op_index[k] << endl ;
		}*/

		/*
		cout << "temp op index : " << temp_op_index[0] << endl;
		cout << "temp op index : " << temp_op_index[1] << endl;
		cout << "temp op index : " << temp_op_index[2] << endl;
		cout << "temp op index : " << temp_op_index[3] << endl;

		cout << "part_position_index : " <<part_position_index[r] <<endl;
		
		cout << "current part : " << current_part->PT->Job_ID << endl;
	

		cout<< " r�� �� : " << r << endl;
		cout << " ����~~~ " << endl;

		*/

	







		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ ���� for�� 2���� �߰��Ǵ� operation�� �ϳ��� ���̿� �־�鼭 route�� �����ϰ� �׶� route���� machine movement�� ����� �� ������Ʈ!
		for(p=0 ; p<a+1 ; p++) // operation 1�� �߰� �Ǹ鼭 operation ���� ����� �Ѱ� �þ
		{
			index = 0;
			

			for(s=0 ; s<a ; s++) // �ϳ��� �� �־��
			{

				if(p==s)
				{
					//temp[p] = part_position_index[r]+1;
					temp[p] = r+1;
					index ++;

					temp[p+1] = Job_route[s];
					index ++;
					
				}
				else
				{
					temp[index] = Job_route[s];
					index ++;

					if(p==a)
					{
						//temp[a] = part_position_index[r]+1;
						temp[a] = r+1;
					}


				}
				//part_position_index[r]�� ���ο� operation���� �߰��Ѵ� 


				//temp�� �����ϸ� ��. ��� �ٲ��ߵ� üũ!
				
				

			}
			
			/*
			cout << "temp route�� ? " ;
			for(int l=0; l < a+1 ; l++)
			{
				cout  <<  temp[l] << " " ;
			}
			cout << endl;
			*/

			//cout << " ��~~~~~~~~~~~~~~~~~ " << endl;
			Job_IDNEX->temp = movement_cal_HU(temp, part_position_index, J, a+1, temp_op_index2,Job_IDNEX); //������ route�� movement ���

			//cout << " ��������������������~~~~~~~~~~~~~~~~~ " << endl;

			//cout << " Job_Index�� movement �� " << Job_IDNEX->temp << endl;
			//cout << "Job_Index�� total movement �� " << Job_IDNEX->total_movement << endl;
			if( Job_IDNEX->temp < Job_IDNEX->total_movement ) // movement �� ���� route�� Job_route�� ������Ʈ
			{
				//cout << " ����222~~~ " << endl;	
				Job_IDNEX->total_movement = Job_IDNEX->temp;
				

				for(k=0 ; k<total_num_operation ; k++)
				{
					 temp2[k] = temp[k];
				}
					
			}
			


		}

		for(k=0 ; k<total_num_operation ; k++)
		{
			Job_route[k] = temp2[k];		
			//temp2[k] �ʱ�ȭ?
		}

		/*
		cout << "job route�� ? " ;
		for(int l=0; l < a+1 ; l++)
		{
				cout  <<  Job_route[l] << " " ;
		}
			cout << endl;
		cout << " machine movement�� ? " << Job_IDNEX->total_movement << endl;
		*/


	}

	for(j=0 ; j < Num_part_on_pallet ; j++)
	{
		temp_op_index2[j] = 0; 
	}

	
	
	for(j=0 ; j < total_num_operation ; j++) // ���� ���� job route�� J�� ������Ʈ!! 
	{
		

		/*	
		J->OP_Route[j] = (temp_op_index2[Job_route[j]])+1 ;
		J->Part_Route[j] = J->P[part_position_index[Job_route[j]]] ;
		J->Machine_Route[j] = J->P[part_position_index[Job_route[j]]]->Mac_Select[temp_op_index2[Job_route[j]]+1];  //rand���� �ϳ� �޾ƿ´� //�����ϰ� ��ȣ���� �� �ϳ��� part�� ù��° operation���� ����
		J->Machine_name[j] = J->P[part_position_index[Job_route[j]]]->Mac_Select_name[temp_op_index2[Job_route[j]]+1];
		J->Processing_time[j] =  J->P[part_position_index[Job_route[j]]]->Select_Process_Time[temp_op_index2[Job_route[j]]+1];
		*/



			J->OP_Route[j] = (temp_op_index2[Job_route[j]-1])+1 ;
			J->Part_Route[j] = J->P[part_position_index[Job_route[j]-1]] ;
			J->Machine_Route[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select[temp_op_index2[Job_route[j]-1]+1];  //rand���� �ϳ� �޾ƿ´� //�����ϰ� ��ȣ���� �� �ϳ��� part�� ù��° operation���� ����
			J->Machine_name[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select_name[temp_op_index2[Job_route[j]-1]+1];
			J->Processing_time[j] =  J->P[part_position_index[Job_route[j]-1]]->Select_Process_Time[temp_op_index2[Job_route[j]-1]+1];


			temp_op_index2[Job_route[j]-1] += 1;
			
			//cout << J->Part_Route[j]->PT->Job_ID << " " <<  J->Part_Route[j]->Part_No << endl;
			//cout << " op route : " << J->OP_Route[j] << " " ;
			//cout << " Machine_rotue : " << J->Machine_name[j] << " " ;
			//cout << " processing time : " << J->Processing_time[j] << " " ;
		
	}

	J->TWKR = TWKR2(J);
	J->Total_movement = Job_IDNEX->total_movement;
	
}


int movement_cal_HU(int * temp_route, int*part_position_index, Job_T *J , int total_num_operation, int  *temp_op_index2, Config * Job_IDNEX)
{
	int machine_movement;
	
	int v = 0;
	int i ;
	
	for( i=0 ; i<J->Num_parts ; i++)
	{ 
		temp_op_index2[i] =0;
	}

	
	

	for( i=0 ; i<total_num_operation-1 ; i++)
	{  
	  /*
	  cout << " temp route i+1 " << temp_route[i+1]-1 << endl;
	  cout <<" temp_route [i] : "<< temp_route[i] << endl;
	  cout <<" part_position_index [i] : " << part_position_index[temp_route[i+1]-1] << endl;
	  cout <<" part_position_index [i+1] : " << part_position_index[0] << endl;
	  cout <<" part_position_index [i+1] : " << part_position_index[1] << endl;
	  cout <<" part_position_index [i+1] : " << part_position_index[2] << endl;
	  cout <<" part_position_index [i+1] : " << part_position_index[3] << endl;
	  */

		//cout << " ���Ͷ� ~~~ " << endl;
		if( J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+1] != NULL )
		{
			//cout << " ���Ͷ�222 ~~~ " << endl;
			if(J->P[part_position_index[temp_route[i]-1]] == J->P[part_position_index[temp_route[i+1]-1]])
			{
				if(J->P[part_position_index[temp_route[i]-1]]->Mac_Select[temp_op_index2[temp_route[i]-1]+1] == J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+2])
				{

					//cout << " temp_op index 111 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v=v;
				}
				else
				{
					//cout << " temp_op index 222 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v++;
				}
				
			}
			else
			{
				if(J->P[part_position_index[temp_route[i]-1]]->Mac_Select[temp_op_index2[temp_route[i]-1]+1] == J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+1])
				{

					//cout << " temp_op index 333 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v=v;
				}
				else
				{
					//cout << " temp_op index 444 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v++;
				}
				//cout << " v�� �� : " << v << endl << endl;
			}
		}
		else
		{
			//cout << " ���Ͷ�333 ~~~ " << endl;
			v=v;
		}

		//cout << " ���Ͷ�444 ~~~ " << endl;
		temp_op_index2[temp_route[i]-1] +=1 ;

	}
	

	//cout << " ddddddddddddddddd " << endl;

	machine_movement = v;

	return machine_movement;
	
}




void Job_route_DP(Job_T *J, Config * Job_IDNEX)
{
	int j;
	int k;
	int a;
	int r; //temp

	int total_num_operation;
	int Num_part_on_pallet;

	total_num_operation = J->Total_Number_Operation; // �� operation����
	
	Num_part_on_pallet = J->Num_parts; //��� part�� �ö���ִ���
	


	int  *temp_op_index2;
	temp_op_index2 = new int [Num_part_on_pallet]; // part���� ���� operation index

	for(k=0 ; k<Num_part_on_pallet ; k++)
	{
		temp_op_index2[k] = 0; //index�� 0�̴�
	}
	

	int *part_position_index; //Job�� P���� NULL�� �� part������ �ִ�. ���� ����ִ� P�� postion index�� �ʿ�
	part_position_index = new int[Num_part_on_pallet];


	int *mat;
	int *num;
	int *Job_route; //job route 

	Job_route = new int [total_num_operation];

	for(j=0; j < total_num_operation ; j++)
	{
		Job_route[j] = 0;
	}
	
	num = new int [Num_part_on_pallet];
	mat = new int [total_num_operation];



	for(j=0 ; j < total_num_operation ; j++)
	{
		mat[j] = 0;
	}

	

	j=0;
	k=0;

	if( J->P[k] != NULL)
	{
			part_position_index[j] = k;
			k++;

		for(j=1 ; j<J->Num_parts ; j++)
		{
	
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}

	else
	{   k++;
		for(j=0 ; j<J->Num_parts ; j++)
		{
			while(k!=J->Pallet_job->Num_Fixt)
			{
				if( J->P[k] != NULL)
				{
					part_position_index[j] = k;
					k++;
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}


	for(j=0 ; j < Num_part_on_pallet ; j++)
	{
		num[j] = J->P[part_position_index[j]]->PT->Num_Operation-2;  //���⼭ ��ġ�� �˾ƾߵ�
	
	}

	
	int step =0;
	r = recursive(step, mat, num, Job_route, total_num_operation, Num_part_on_pallet, part_position_index, J, temp_op_index2, Job_IDNEX); //job route ����
	//recursive_temp(step, mat, num); //job route ����


	
	J->OP_Route = new int[J->Total_Number_Operation+1]; //operation route
	J->Part_Route = new Part_T *[J->Total_Number_Operation+1]; // part route
	J->Machine_Route = new Machine_T *[J->Total_Number_Operation+1] ; //machine route
	J->Machine_name = new char * [J->Total_Number_Operation+1];
	J->Processing_time = new int[J->Total_Number_Operation+1]; 


	for(k=0 ; k<J->Total_Number_Operation+1; k++)
	{
		J->Part_Route[k] = new Part_T;
		J->Machine_Route[k] = new Machine_T;
		J->Machine_name[k] = new char[100];
	}



	
	
	

	
	for(a=0 ; a<J->Num_parts ; a++)
	{
		//cout <<"Partposition : "<< part_position_index[a] << endl;
	}
	
	for(a=0 ; a<J->Pallet_job->Num_Fixt ; a++)
	{
		if(J->P[a] != NULL)
		{	
			//cout << "J�� part type : " << J->P[a]->PT->Job_ID << "    " ;
			cout <<endl;
		}
	}
	
	for(j=0 ; j < J->Num_parts ; j++)
	{
		//cout << J->P[part_position_index[j]]->PT->Job_ID << endl;
	}
	

	for(j=0 ; j < Num_part_on_pallet ; j++)
	{
		temp_op_index2[j] = 0; 
	}
	
	if (r!=0)
	{
		for(j=0 ; j < total_num_operation ; j++)
		{
			J->OP_Route[j] = (temp_op_index2[Job_route[j]-1])+1 ;
			J->Part_Route[j] = J->P[part_position_index[Job_route[j]-1]] ;
			J->Machine_Route[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select[temp_op_index2[Job_route[j]-1]+1];  //rand���� �ϳ� �޾ƿ´� //�����ϰ� ��ȣ���� �� �ϳ��� part�� ù��° operation���� ����
			J->Machine_name[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select_name[temp_op_index2[Job_route[j]-1]+1];
			J->Processing_time[j] =  J->P[part_position_index[Job_route[j]-1]]->Select_Process_Time[temp_op_index2[Job_route[j]-1]+1];

			temp_op_index2[Job_route[j]-1] += 1;

			//cout << J->Part_Route[j]->PT->Job_ID << " " <<  J->Part_Route[j]->Part_No << endl;
			//cout << " op route : " << J->OP_Route[j] << " " ;
			//cout << " Machine_rotue : " << J->Machine_name[j] << " " ;
			//cout << " processing time : " << J->Processing_time[j] << " " ;
		
		}
	}

	//J->Total_movement = total_machine_movement;

	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //���������� 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // �Ǹ����� �ƹ����� ����
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //�Ǹ������� �ƹ����� ����
	J->Machine_name[J->Total_Number_Operation+1] = NULL ;
	J->Processing_time[J->Total_Number_Operation+1] = NULL; 

	J->TWKR = TWKR2(J);

	//cout <<"Job�� ��ȣ : " << J->Job_No << endl;
	//cout <<"Job�� TWKR : " << J->TWKR << endl;


	/*for(j=1;j<J->Total_Number_Operation;j++)
	{
		for(k=0 ; k<J->Pallet_job->Num_Fixt ; k++)
		{
			if(J->Part_Route[0] == J->Part_Route[k] ~~~~)
			{
				temp_machine = J->P[k]->Mac_Select[0] ;// Machine movement �ּ�ȭ�� �Ǵ°� ! � ������ ���ؼ� �ϳ��� ���õ� �� temp machine�� �ȴ�
				temp_part = J->P[k]
				temp_op_index =
			{
		}

		J->Machine_Route[j] = temp_machine;
		J->Part_Route[j] = temp_part;
		J->OP_Route[j] = J->P[k]->Current_Process_No ;
		J->Machine_name[j] =
	}*/
	
}
void recursive_temp(int step, int * mat, int * num)
{
	int i;
	int j; 
	int k;

	cout << "���� 8 "<< endl;
	cout << " num 1 " << num[0];
	cout << endl << "num 2" << num[1];
	for( i = 0 ; i < 2 ; i++)
	{
		if(num[i] > 0)
		{ 
			num[i] --;
			mat[step] = i+1;

			cout<< "step : "  << step << endl;
			cout<< "mat :: " <<mat[step] << endl;
			
			cout <<" 1111 " << endl;

			if(step == 9) 
			{
				cout << " ���� ���� ? " << endl;
				for(j = 0 ; j <= step ; j++)
				{ 
					//cout << "��� ����? " <<endl;
					//temp_route[j] = mat[j];
					cout << "route ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ : " << mat[j];
				}

			}
			
			cout << " �߰����� �� " << endl;
			recursive_temp(step+1, mat, num);
			num[i] ++;

		}
	}
}


int recursive(int step, int * mat, int * num, int * Job_route, int total_num_operation, int Num_part_on_pallet, int *part_position_index, Job_T *J, int  *temp_op_index2, Config * Job_IDNEX)
{
	int i;
	int j; 
	int k;
	//int * temp_route ;
	//temp_route = new int[total_num_operation];
	int temp;


	/*for(j=0 ; j<total_num_operation ; j++)
	{
		
		temp_route[j] = 0;
	}*/


	for( i = 0 ; i < Num_part_on_pallet ; i++)
	{
		if(num[i] > 0)
		{
			num[i] --;
			mat[step] = i+1;


			


			if(step == total_num_operation-1)
			{

				
				Job_IDNEX->temp = movement_cal2(mat, part_position_index, J, total_num_operation, temp_op_index2,Job_IDNEX);
			
				
				if( Job_IDNEX->temp < Job_IDNEX->total_movement )
				{
					Job_IDNEX->total_movement = Job_IDNEX->temp;
				
	
					for(k=0 ; k<total_num_operation ; k++)
					{
						//Job_route[k] = temp_route[k];
						Job_route[k] = mat[k];	
					  
					}
					
				}

			}
			
			//cout << " recursive ���̴� " << endl;
			temp = recursive(step+1, mat, num, Job_route, total_num_operation, Num_part_on_pallet, part_position_index, J, temp_op_index2, Job_IDNEX);
			num[i] ++;

		}
	}
	if(temp = 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int movement_cal2(int * temp_route, int*part_position_index, Job_T *J , int total_num_operation, int  *temp_op_index2, Config * Job_IDNEX)
{
	int machine_movement;
	
	int v = 0;
	int i ;
	
	for( i=0 ; i<J->Num_parts ; i++)
	{ 
		temp_op_index2[i] =0;
	}




	for( i=0 ; i<total_num_operation-1 ; i++)
	{  
	 //  cout <<" temp_route [i] : "<< temp_route[i] << endl;
	  //cout <<" part_position_index [i] : " << part_position_index[temp_route[i]-1] << endl;
	  // cout <<" part_position_index [i+1] : " << part_position_index[temp_route[i+1]-1] << endl;

		if( J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+1] != NULL )
		{
			
			if(J->P[part_position_index[temp_route[i]-1]] == J->P[part_position_index[temp_route[i+1]-1]])
			{
				if(J->P[part_position_index[temp_route[i]-1]]->Mac_Select[temp_op_index2[temp_route[i]-1]+1] == J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+2])
				{

					//cout << " temp_op index 111 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v=v;
				}
				else
				{
					//cout << " temp_op index 222 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v++;
				}
				
			}
			else
			{
				if(J->P[part_position_index[temp_route[i]-1]]->Mac_Select[temp_op_index2[temp_route[i]-1]+1] == J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+1])
				{

					//cout << " temp_op index 333 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v=v;
				}
				else
				{
					//cout << " temp_op index 444 : " << temp_op_index2[temp_route[i]-1]  << endl;
					v++;
				}
				//cout << " v�� �� : " << v << endl << endl;
			}
		}
		else
		{
			v=v;
		}

	
		temp_op_index2[temp_route[i]-1] +=1 ;

	}
	
	machine_movement = v;

	return machine_movement;
	
}

int *movement_cal(Part_T * current_part, int current_part_op, int *temp_op_index, Job_T *J, int *part_position_index)
{
	int *machine_movement;
	int total_machine_movement = 0;
	int v = 0;
	int i ;
	int j ;
	int k ;
	int a;
	int r = 0; 
	int min = 999;

	//cout << "temp op index : " << temp_op_index[0];
	machine_movement = new int [J->Num_parts];

	for(j=1; j < J->Total_Number_Operation ; j++) // j=1���ʹ� 0���� ó�� ���õ� ������ ������. Total_Number_operation+1 ���� NULL������ ������
	{
		for(i=0 ; i < J->Num_parts ; i++)
		{
			if(temp_op_index[i] != -1)
			{
				if(temp_op_index[i] < J->P[part_position_index[i]]->PT->Num_Operation-1) // J�� P�� operation ���ں��� ��������!
				{

					if(i==r) //ó���� current part�� position�� 0�̴�. �ѹ� iteration �� r�� ���� �ٲ� current part�� position ��ȭ �˱� ���� r�� ����
					{
						if(current_part->Mac_Select[current_part_op+1] != NULL)
						{
							if(current_part->Mac_Select[current_part_op] != current_part->Mac_Select[current_part_op+1])
							{
								v = 1;
								machine_movement[i] = v ;
							}
							else
							{
								v = 0;
								machine_movement[i] = v ;
							}
						}
						else
						{
							temp_op_index[i] = -1;
							machine_movement[i] = 99;
						}


					}
					else
					{
							if(current_part->Mac_Select[current_part_op] != J->P[part_position_index[i]]->Mac_Select[temp_op_index[i]+1])
							{
								v = 1 ;
								machine_movement[i] = v ;
							}
							else
							{
								v = 0;
								machine_movement[i] = v ;
							}
					}

				}
				else
				{
					temp_op_index[i] = -1;
					machine_movement[i] = 99;	//operation �Ҵ� �� �Ȱ��� �ǹ� !
				}
			}
		}
		


		/*for (a=0 ; a<J->Num_parts ; a++)
		{
			cout <<" machine movement : " << machine_movement[a] << endl ;
		}*/


		min=999;
		for(k=0 ; k < J->Num_parts ; k++) //�ּ� movementã�´� 
		{			
			if(machine_movement[k] <= min )
			{
				min = machine_movement[k];
				r = k; // current part�� position�� �ٲ�
				//cout << " r�� �� : " << r << endl;
			}
		}


		if(machine_movement[r] ==1)
		{
			total_machine_movement += 1;
		}
		current_part = J->P[part_position_index[r]];
		temp_op_index[r] += 1;
		current_part_op = temp_op_index[r];


		/*for(k=0 ; k < J->Num_parts ; k++) //�ּ� movementã�� ����غ���
		{	
			cout << " temp part op �� �� : " << temp_op_index[k] << endl ;
		}*/

		J->Machine_Route[j]= current_part->Mac_Select[current_part_op];
		J->OP_Route[j]=current_part_op;
		J->Part_Route[j]=current_part;
		J->Machine_name[j]=current_part->Mac_Select_name[current_part_op];
		J->Processing_time[j] =current_part->Select_Process_Time[current_part_op];
		J->Total_movement = total_machine_movement;


		
		//cout << "text text part : " << current_part->PT->Job_ID << endl;
	}

	
	return machine_movement;
	
}

int Simulation_Start(Pallet_T * Pallet_type, int Num_pallet, int Num_Parts, int Num_parttype, int Num_RMC, Part_T * P,Job_T * J, Queue_job * Job_queue, Mac_list * ML, Rmc_T * RMC, Queue *Dummy, int Machine_Selection_Option, Config * Job_INDEX, int Job_index, Queue *System, int Num_machine, int Input_Sequence_Option, int Dispatching_Option, int Job_route_Option, int transportation_time)
{
	int i;
	int k=0;
	int b=0;
	int c= 1500;
	int Simulation_time = 0;
	int event;
	int Terminated = 0;
	Cell_job * temp_job_cell = Job_queue->Head->next;
	Cell * CJ_temp = Dummy->Head->next;

	Job_INDEX->last_processing_time =0;
		
	//cout << " ���� " << endl;
	do
	{
		event = 1;
		while(event != 0)
		{
			event = event_Excuter(Pallet_type, Num_pallet, Num_Parts,Num_parttype, Num_RMC, P, J, Job_queue, ML, RMC, Dummy, Simulation_time, Machine_Selection_Option, Job_INDEX, Job_index, System, Num_machine, Input_Sequence_Option, Dispatching_Option, Job_route_Option, transportation_time);
			//Main procedure
		
			if(event == -1) //error check
			{
				return -1; //return to main - terminated
			}

		}//while - checking event in the same time

		
		Simulation_time ++; // time increase => there is no event
		//cout << "�ùķ��̼� Ÿ�� : " << Simulation_time << endl;
		Terminated = 0;

		for(i=0;i<Num_Parts;i++)
		{
			Terminated += P[i].Terminated;
			
		}



		


		//cout << " Terminated ��� ? : " << Terminated << endl;
		//cout << Num_Parts << endl;
		//cout << Terminated << endl;
		//ShowQueue(RMC[1].RMC_Q);
	}while(Terminated != Num_Parts); //all jobs are terminate
		
	
		temp_job_cell = Job_queue->Head;
		k=0;
		while(temp_job_cell != Job_queue->Tail)
		{
			//k++;
			//cout << k << endl;
			if(temp_job_cell->next == Job_queue->Tail)
			{
				//cout << "zzzzzzzzzzz" <<endl; //�������
			}
			temp_job_cell = temp_job_cell->next;
		}
		
		CJ_temp = Dummy->Head;
		k=0;
		while(CJ_temp != Dummy->Tail) //��ε� üũ
		{
			k++;
			//cout << " ggggggggggggggggggggggggggggggg : " << k << endl;
			if(CJ_temp->next == Dummy->Tail)
			{	
				//cout << "yyyyyyyyyyyy" <<endl; //�������
			}			
			CJ_temp= CJ_temp->next;
	
		}

		//cout << " ggggggggggggggggggggggggggggggg : " << Dummy->Length << endl;


		/*for ( k=0; k < Num_pallet ; k++)
		{
			cout<< " pallet�� �����ִ°� ��� ?? "  << Pallet_type[k].rest_Pallet << endl;
		}*/

	return Simulation_time;
}

int event_Excuter(Pallet_T * Pallet_type, int Num_pallet, int Num_Parts, int Num_parttype, int Num_RMC,Part_T * P, Job_T * J, Queue_job * Job_queue, Mac_list * ML, Rmc_T * RMC, Queue * Dummy, int Time, int Machine_Selection_Option,  Config * Job_INDEX, int Job_index, Queue *System, int Num_machine, int Input_Sequence_Option, int Dispatching_Option, int Job_route_Option, int transportation_time)
{
	//in to the machine from queue
	int i;
	int a=0;
	int b=0;
	int check = 0;
	int EV = 0;
	Cell_job * temp_cell_job =  Job_queue-> Head->next;
	Cell_machine * CM_Temp = ML->head->next;
	Machine_T * Mac_Temp;
	Cell * CJ_Temp;
	Job_T * Job_temp;
	Job_T * Pre_Job; //���� job üũ�ؼ� transportation time �߰�

	int trans = transportation_time;
	

	//---------------------------------------------------------------
	CM_Temp = ML->head->next;
	
	while(CM_Temp != ML->tail) //event check machine by machine
	{
				
		Mac_Temp = CM_Temp->Mac;
		
		//end of the vacation time in calender
		if(Mac_Temp->Working_or_Rest == 0 && Mac_Temp->Next_Working_time == Time)
		{
			Mac_Temp->Current_Schedule ++;
			if(Mac_Temp->Current_Schedule == Mac_Temp->Number_Schedule) // Number_Schedule�� ������ ���̴� ���������� ���� ��� machine�� on ����
			{
				Mac_Temp->Next_Working_time = -1;
				Mac_Temp->Next_Rest_Time = 31536000; // == 1��
			}
			else
			{
				Mac_Temp->Next_Working_time = -1;
				Mac_Temp->Next_Rest_Time = Mac_Temp->Machine_Schedule[Mac_Temp->Current_Schedule];
			}
			Mac_Temp->Working_or_Rest = 1; //1�̸� machine ��밡��
			EV = 1;
		}
		
		//change a machine to vacate mode by calender
		if(Mac_Temp->Working_or_Rest == 1 && Mac_Temp->Next_Rest_Time == Time)
		{
			Mac_Temp->Current_Schedule ++;
			if(Mac_Temp->Current_Schedule == Mac_Temp->Number_Schedule) // Number_Schedule�� ������ ���̴� ���������� ���� ��� machine�� on ����
			{
				Mac_Temp->Next_Rest_Time = -1;
				Mac_Temp->Next_Working_time = 31536000;// == 1��
			}
			else
			{
				Mac_Temp->Next_Working_time = Mac_Temp->Machine_Schedule[Mac_Temp->Current_Schedule];
				Mac_Temp->Next_Rest_Time = -1;
			}
			Mac_Temp->Working_or_Rest = 0; //0�̸� machine ��� �Ұ�
			EV = 1;
		}
	
		//starting processing in available machine with dispatching rule
		if(Mac_Temp->Current_State == 0 && Mac_Temp->Working_or_Rest == 1 ) //current state�� 0�̸� �Ҽ��ִ�
		{
			
			Pre_Job = Find_last_job(Mac_Temp->Job_Sequence) ;
			
			if(Pre_Job == NULL)
			{
				Job_temp = Dispatching(Dispatching_Option, Mac_Temp, Job_queue, Time);
				if (Job_temp == NULL)
				{
					return -1;
				}
				/* 
				if(Dispatching_Option == 1)
				{
					Job_temp = Dispatching_FIFO(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 2)
				{
					Job_temp = Dispatching_SPT(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 3)
				{
					Job_temp = Dispatching_TWKR(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 4)
				{
					Job_temp = Dispatching_MST(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 5)
				{
					//cout << "���� ~~~~~~~~~~~~~~~~~��������� �ѹ�" << endl;
					Job_temp = Dispatching_MDD(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 6)
				{
					Job_temp = Dispatching_Dependent_SPT(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 7)
				{
					Job_temp = Dispatching_Dependent_TWKR(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 8)
				{
					Job_temp = Dispatching_Dependent_MST(Mac_Temp, Job_queue, Time);
				}
				else if(Dispatching_Option == 9)
				{
					Job_temp = Dispatching_Dependent_MDD(Mac_Temp, Job_queue, Time);
				}
				else
				{
					cout << "Dispatching Option Error" << endl;
					return -1;
				}
				*/
			}
			else
			{
				if(Pre_Job->Machine_Route[Pre_Job->current_position] == Mac_Temp)
				{
					//cout << " ó������ �ɸ��� pre job�� current position : " << Pre_Job->current_position <<endl;
					//cout << "���� ~~~~~~~~~~~~~~~~~333333333" << endl;
					if(Pre_Job->current_state == 0 ) //Job(pallet)�� process���� �ƴϾ�ߵǰ�
					{
						if(Mac_Temp->End_time == Time) // �׶��� machine�� ��� ������ �ȴ�. ������ ������ machine�� ���ٰ� �ٽ� �Ȱ��� job�� ���� ��쿡�� �̵��ð� �߰��Ǿ�ߵ�
						{
							Job_temp = Pre_Job;
						}
						else
						{
							Job_temp = Dispatching(Dispatching_Option, Mac_Temp, Job_queue, Time);
							if (Job_temp == NULL)
							{
								return -1;
							}
							/* 
							if(Dispatching_Option == 1)
							{
								Job_temp = Dispatching_FIFO(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 2)
							{
								Job_temp = Dispatching_SPT(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 3)
							{
								Job_temp = Dispatching_TWKR(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 4)
							{
								Job_temp = Dispatching_MST(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 5)
							{
								Job_temp = Dispatching_MDD(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 6)
							{
								Job_temp = Dispatching_Dependent_SPT(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 7)
							{
								Job_temp = Dispatching_Dependent_TWKR(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 8)
							{
								Job_temp = Dispatching_Dependent_MST(Mac_Temp, Job_queue, Time);
							}
							else if(Dispatching_Option == 9)
							{
								Job_temp = Dispatching_Dependent_MDD(Mac_Temp, Job_queue, Time);
							}
							else
							{
								cout << "Dispatching Option Error" << endl;
								return -1;
							}
							*/
						}
					}
					else
					{
						Job_temp = Dispatching(Dispatching_Option, Mac_Temp, Job_queue, Time);
						if (Job_temp == NULL)
						{
							return -1;
						}
						/* 
						if(Dispatching_Option == 1)
						{
							Job_temp = Dispatching_FIFO(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 2)
						{
							Job_temp = Dispatching_SPT(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 3)
						{
							Job_temp = Dispatching_TWKR(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 4)
						{
							Job_temp = Dispatching_MST(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 5)
						{
							Job_temp = Dispatching_MDD(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 6)
						{
							Job_temp = Dispatching_Dependent_SPT(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 7)
						{
							Job_temp = Dispatching_Dependent_TWKR(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 8)
						{
							Job_temp = Dispatching_Dependent_MST(Mac_Temp, Job_queue, Time);
						}
						else if(Dispatching_Option == 9)
						{
							Job_temp = Dispatching_Dependent_MDD(Mac_Temp, Job_queue, Time);
						}
						else
						{
						cout << "Dispatching Option Error" << endl;
						return -1;
						}
						*/
					}
				}
				else
				{
					Job_temp = Dispatching(Dispatching_Option, Mac_Temp, Job_queue, Time);
					if (Job_temp == NULL)
					{
						return -1;
					}
					/* 
					if(Dispatching_Option == 1)
					{
						Job_temp = Dispatching_FIFO(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 2)
					{
						Job_temp = Dispatching_SPT(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 3)
					{
						Job_temp = Dispatching_TWKR(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 4)
					{
						Job_temp = Dispatching_MST(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 5)
					{
						Job_temp = Dispatching_MDD(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 6)
					{
						Job_temp = Dispatching_Dependent_SPT(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 7)
					{
						Job_temp = Dispatching_Dependent_TWKR(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 8)
					{
						Job_temp = Dispatching_Dependent_MST(Mac_Temp, Job_queue, Time);
					}
					else if(Dispatching_Option == 9)
					{
						Job_temp = Dispatching_Dependent_MDD(Mac_Temp, Job_queue, Time);
					}
					else
					{
						cout << "Dispatching Option Error" << endl;
						return -1;
					}
					*/
				}
			}
				//job selected by dispatching rule..			
			if(Job_temp != NULL) //starting process
			{
				
				if(Pre_Job != NULL)
				{
					//cout << " =============================================== pre job : " << Pre_Job->Job_No  << endl << endl; 
				}

				//cout <<  " =============================================== temp job : "<< Job_temp->Job_No << endl << endl;
				if(Pre_Job == Job_temp)
				{
					if(Mac_Temp->End_time == Time) // �׶��� machine�� ��� ������ �ȴ�. ������ ������ machine�� ���ٰ� �ٽ� �Ȱ��� job�� ���� ��쿡�� �̵��ð� �߰��Ǿ�ߵ�
					{
						Job_temp->Current_Process_Completion_time = Time + Job_temp->Processing_time[Job_temp->current_position]; // �� machine�� ���� job�� ������ transporation time ���� !
					}
					else
					{
						Job_temp->Current_Process_Completion_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position]; //���� job�̶�� ������ ��� ���� �ð��Ŀ� ���� job�� �;ߵȴ�. ���� �ڿ� ���� job���� tran ������
					}
				}
				else
				{
					Job_temp->Current_Process_Completion_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position]; //machine�� �ٸ� job�� ������ transportation �����ش�
					//cout << " ============================ �̶��� time : " << Job_temp->Current_Process_Completion_time << " " << Time + trans + Job_temp->Processing_time[Job_temp->current_position]<<  endl << endl;
				}

				input_Last_to_Job_List(Mac_Temp->Job_Sequence,Job_temp, trans); // Machine ���� J�� part���� �Է�

				Mac_Temp->Current_State = 1; //machine�� process��
				Mac_Temp->Current_Job_Start_Time = Time;
				if(Pre_Job == Job_temp)
				{
					if(Mac_Temp->End_time == Time) // �׶��� machine�� ��� ������ �ȴ�. ������ ������ machine�� ���ٰ� �ٽ� �Ȱ��� job�� ���� ��쿡�� �̵��ð� �߰��Ǿ�ߵ�
					{
						Mac_Temp->Current_Job_End_Time = Time + Job_temp->Processing_time[Job_temp->current_position];
						Mac_Temp->End_time = Time + Job_temp->Processing_time[Job_temp->current_position];
					}
					else
					{
						Mac_Temp->Current_Job_End_Time = Time + trans + Job_temp->Processing_time[Job_temp->current_position];
						Mac_Temp->End_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position];
					}
				}
				else
				{
					Mac_Temp->Current_Job_End_Time = Time + trans + Job_temp->Processing_time[Job_temp->current_position];
					Mac_Temp->End_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position];
				}
				Mac_Temp->Current_Part_ID = Job_temp->Part_Route[Job_temp->current_position]->PT->Job_ID; // ���� machine process���� part type
				Mac_Temp->Current_Part_No = Job_temp->Part_Route[Job_temp->current_position]->Part_No; // ���� machine�� process���� part ��ȣ
				Mac_Temp->Current_Job_No = Job_temp->Job_No; //���� machine�� process���� Job

				Job_INDEX->last_processing_time =  Job_temp->Processing_time[Job_temp->current_position];

				//cout << " uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu last procesing_time : " << Job_INDEX->last_processing_time << endl << endl;

				input_Last_to_Machine_Sched_List(Job_temp->Part_Route[Job_temp->current_position]->Machine_Sequence , Mac_Temp, Mac_Temp->Current_Job_Start_Time, Mac_Temp->Current_Job_End_Time, Job_temp->Part_Route[Job_temp->current_position]->PT->PID[Job_temp->OP_Route[Job_temp->current_position]]);
				// part �������� machine�̶� �ð� �޴´�


				Cell_machine * temp = new Cell_machine;
				temp=Job_temp->Part_Route[Job_temp->current_position]->Machine_Sequence->tail->pre;
				/*
				cout << " Job ��ȣ : " << Job_temp->Job_No << endl;
				cout << " part type : " << Job_temp->Part_Route[Job_temp->current_position]->PT->Job_ID << endl;
				cout << " Part ��ȣ : " << Job_temp->Part_Route[Job_temp->current_position]->Part_No << endl;
				cout << " OP ��ȣ : " << Job_temp->OP_Route[Job_temp->current_position] << endl;
				cout << " machine : " << CM_Temp->Mac->Machine_Name << endl ;
				cout << " �̶��� TWKR : " << Job_temp->TWKR << endl << endl;

				cout <<"�� part�� �� �ð� : " << temp->End_time << endl;
				cout <<" �� part�� ���� �ð�: " << temp->Start_time << endl;
				*/
				Job_temp->TWKR = Job_temp->TWKR - Job_temp->Processing_time[Job_temp->current_position]; // TWKR ���õ� �� ��ŭ processing time ���� ������Ʈ �ȴ�
				Job_temp->current_position ++; //Ȯ�� �ʿ�
				Job_temp->current_state = 1 ; //���� process ���̴�d
				

				//cout << " �ٲ���� TWKR : " << Job_temp->TWKR << endl << endl;
				

				EV = 1;
			}
			
		}

		

		if(Mac_Temp->Current_Job_End_Time == Time)
		{
			Mac_Temp->Current_Part_ID = -1;
			Mac_Temp->Current_Part_No = -1;
			Mac_Temp->Current_Job_No = -1;
			Mac_Temp->Current_Job_End_Time = -1;
			Mac_Temp->Current_Job_Start_Time = -1;
			Mac_Temp->Current_State = 0; // machine ��� ����
			
			


			Job_temp = Mac_Temp->Job_Sequence->Tail->pre->Job;

			Job_temp->current_state = 0; //�ٽ� �� job�� ���� �� �� ����


			
			Cell_machine * Cell_Temp;
			if(Job_temp->Part_Route[(Job_temp->current_position)-1]->Terminated == 1)
			{
				Cell_Temp = Job_temp->Part_Route[(Job_temp->current_position)-1]->Machine_Sequence->head->next;
				while(Cell_Temp->next != Job_temp->Part_Route[(Job_temp->current_position)-1]->Machine_Sequence->tail)
				{
					Cell_Temp = Cell_Temp->next;
				}

				Job_temp->Part_Route[(Job_temp->current_position)-1]->completion_time = Cell_Temp->End_time; //�׶� part�� ����ð�
				Job_temp->Completion_time = Cell_Temp->End_time; //Job�� ����ð�. ����ؼ� update �� . part���� ����ð��߿� �ϳ��� job�� ����ð���

			}

			//cout <<" Job ��ȣ : " << Job_temp->Job_No << " " << "Job�� ���� �ð� : " << Job_temp->Completion_time<< endl ;
			//cout << " job�� part�� operation�� ������ �ð� : "<< Job_temp->Part_Route[(Job_temp->current_position)-1]->completion_time << endl ;

			EV = 1;
		}
		
		CM_Temp = CM_Temp->next;
		
	}
	
	
	
	int k=0;
	while(temp_cell_job != Job_queue->Tail)
	{
		k++;
		//cout << " ����������������������������������������������: " << k << endl;
		//cout << "job��ȣ �Դϴ� : " << temp_cell_job->Job->Job_No << endl;
		//cout << " current position �Դϴ� : " << temp_cell_job->Job->current_position << endl;	
		
			if(temp_cell_job->Job->Processing_time[(temp_cell_job->Job->current_position)+1]==NULL)
			{
				temp_cell_job->Job->Terminate = 1 ;
				EV=1;
			}
			
		temp_cell_job = temp_cell_job ->next;
	}

	//Dummy Processing - stack to as/rs station
	int j;
	temp_cell_job = Job_queue->Head->next;
	while(temp_cell_job != Job_queue->Tail) // job�� ������ job_queue buffer���� �������ش�.
	{
		if(temp_cell_job->Job->Terminate==1)
		{
			temp_cell_job->Job->Pallet_job->rest_Pallet = 1; //�� ���� pallet�� ��밡��

			for(j=0 ; j < temp_cell_job->Job->Pallet_job->Num_Fixt ; j++)
			{
				temp_cell_job->Job->Pallet_job->Fixture[j]->rest_Fixture = 1; // �׶� pallet�� fixture�� ��밡��
			}

			b++;
			//cout << " Job ����� b�� ��� ? : " << b << endl;
			//cout << " Job ����Ȱ� ��ų� ? : " << temp_cell_job->Job->Job_No << endl;
			for(i=0; i<temp_cell_job->Job->Pallet_job->Num_Fixt ; i++)
				{
					if(temp_cell_job->Job->P[i]!=NULL)
					{
						temp_cell_job->Job->P[i]->Terminated = 1;
						input_Last_to_Queue(Dummy,temp_cell_job->Job->P[i]);  //  job�� �� �����ٸ� �׶��� P�� dummy�� ����
					
					}
					
				}

			temp_cell_job->next->pre = temp_cell_job->pre;
			temp_cell_job->pre->next = temp_cell_job->next;

			delete temp_cell_job;
			Job_queue->Length --;

			temp_cell_job =Job_queue->Head->next;
			EV=1;
			continue;
		}

		temp_cell_job = temp_cell_job->next;
	}


	Cell * temp_loading;
	int next_part ;
	int due; //due date ������� ���� ��ȣ�� �;ߵ�


	//cout << "���� ������ ?? " << endl;

	CJ_Temp = Dummy->Head->next;



	while(CJ_Temp != Dummy->Tail) //��ε� üũ
	{
		next_part = 100000000; //�ƹ��� ����
		
		
		if(CJ_Temp->Part->Terminated == 1) //�������� ���� ������ ����
		{
			//cout << " CJ_Temp- > part �� ����ð� : " << CJ_Temp->Part->completion_time << endl << endl;
			if(J[CJ_Temp->Part->Job_No].Completion_time == Time)
			{
				if(CJ_Temp->Part->PT->Pre_part == -1)
				{
					next_part = CJ_Temp->Part->PT->Job_ID; //���� part�� part type���� ����
					due = CJ_Temp->Part->Due_date;

					//cout << "                                                                    1�� ���� part type? : " << CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "                                                                    1�� ���� part ��ȣ? : " << CJ_Temp->Part->Part_No << endl;

					//cout << "�������� Parttype : "<< CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "�������� Part ��ȣ : "<< CJ_Temp->Part->Part_No<< endl;
					//cout << "next Part�� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! : "<< next_part << endl;

					//cout << "1111111111111111111111111111111 Dummy length : " << Dummy->Length << endl;

					temp_loading = System->Head->next;
					while(temp_loading != System->Tail)
					{
						if(temp_loading->Part->PT->Pre_part == next_part && temp_loading->Part->Due_date == due) 
						{
							//cout << "������ Parttype : "<< temp_loading->Part->PT->Job_ID << endl;
							//cout << "������ Part ��ȣ : "<< temp_loading->Part->Part_No<< endl;
		
							input_Last_to_Queue(Dummy,temp_loading->Part); // �׋��� dependecy part�� laoding dummy�� �ִ´�
						
							temp_loading->next->pre = temp_loading->pre;
							temp_loading->pre->next = temp_loading->next;//���õ� part�� queue���� ������� 

							delete temp_loading;

							System->Length --;

						
							EV = 1;
							break;
						}
						temp_loading = temp_loading->next;
					}

				//cout << "22222222222222222222222222222222 Dummy length : " << Dummy->Length << endl;
			

					CJ_Temp->next->pre = CJ_Temp->pre;
					CJ_Temp->pre->next = CJ_Temp->next;
			

					delete CJ_Temp;
					Dummy->Length --;
				}

				else
				{
					//cout << "                                                                    2�� ���� part type? : " << CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "                                                                    2�� ���� part ��ȣ? : " << CJ_Temp->Part->Part_No << endl;
					//cout << "                                                                    2�� ���� Job ��ȣ? : " << CJ_Temp->Part->Job_No<< endl;
				
					//cout << " �Ϸ� ??????????????????" << endl; 
					CJ_Temp->next->pre = CJ_Temp->pre;
					CJ_Temp->pre->next = CJ_Temp->next;
			

					delete CJ_Temp;
					Dummy->Length --;
				}

			
			//cout << "3333333333333333333333333333 Dummy length : " << Dummy->Length << endl;

			a++;

			//cout <<"�ùķ��̼� �� dummy ���� : " << a << endl;
			CJ_Temp = Dummy->Head->next;

			//cout << "======================================================Dummy length : " << Dummy->Length << endl;

			EV = 1;
			continue;
			}
		}
		
		//cout << "next Part�� 222222222222222222 : "<< next_part << endl;

		//if(CJ_Temp->Part->release_time <= Time) //�ε� üũ ���� �ε� �� �͵��!
		


		CJ_Temp = CJ_Temp->next;
	}
	
	//cout << " dummy lenght�� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ : "  << Dummy->Length << endl; 
	check = Job_INDEX->Job_index;
	
	if(Dummy->Length != 0)
	{

		Loading(Pallet_type, P, J, Num_pallet, Dummy, Job_index, Job_queue, Job_INDEX, Machine_Selection_Option, Num_machine, ML, Input_Sequence_Option, Job_route_Option);	
		if(check != Job_INDEX->Job_index)
		{
			EV =1;
		}
		
	}
	
	//cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk = : " << Job_INDEX[0].Job_index ;


	return EV;
	
	
	//OUTPUT proccessing -- unloading

	
}

Job_T * Dispatching(int Opt, Machine_T * M, Queue_job * Job_queue, int Time)
{
	Job_T * Job_temp;

	if (Opt == 1)
	{
		Job_temp = Dispatching_FIFO(M, Job_queue, Time);
	}
	else if (Opt == 2)
	{
		Job_temp = Dispatching_SPT(M, Job_queue, Time);
	}
	else if (Opt == 3)
	{
		Job_temp = Dispatching_TWKR(M, Job_queue, Time);
	}
	else if (Opt == 4)
	{
		Job_temp = Dispatching_MST(M, Job_queue, Time);
	}
	else if (Opt == 5)
	{
		//cout << "���� ~~~~~~~~~~~~~~~~~��������� �ѹ�" << endl;
		Job_temp = Dispatching_MDD(M, Job_queue, Time);
	}
	else if (Opt == 6)
	{
		Job_temp = Dispatching_Dependent_SPT(M, Job_queue, Time);
	}
	else if (Opt == 7)
	{
		Job_temp = Dispatching_Dependent_TWKR(M, Job_queue, Time);
	}
	else if (Opt == 8)
	{
		Job_temp = Dispatching_Dependent_MST(M, Job_queue, Time);
	}
	else if (Opt == 9)
	{
		Job_temp = Dispatching_Dependent_MDD(M, Job_queue, Time);
	}
	else
	{
		cout << "Dispatching Option Error" << endl;
		Job_temp = NULL;
	}
	return Job_temp;
	//return nullptr;
}

Job_T * Dispatching_FIFO(Machine_T * M, Queue_job * Job_queue, int Time)
{
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	while(temp != Job_queue->Tail)
	{
		//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
		{
			temp_Job = temp->Job;	
			break;
		}
		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		return temp_Job;
	}
}

Job_T * Dispatching_SPT(Machine_T * M, Queue_job * Job_queue, int Time)
{
	int min = 9999999;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	while(temp != Job_queue->Tail)
	{
		//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
		{		
			if( min > temp->Job->Processing_time[temp->Job->current_position])
			{
				temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
				min = temp->Job->Processing_time[temp->Job->current_position]; // �׶��� job�� processing time�� min ���� �ȴ�
			}
		}
		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		return temp_Job;
	}
}

Job_T * Dispatching_Dependent_SPT(Machine_T * M, Queue_job * Job_queue, int Time)
{
	int min = 9999999;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	int count = 0;
	int i;

	while(temp != Job_queue->Tail) // ���⼭ dependent part�� �ִ��� ã�´� ������ 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job���� �ִ� queue���� ���μ��� ������ job�� �߿���
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // �� Job�� �ö� part���� �˻�
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part�� �߿� pre part�� -1 �̸� 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job�� prepart�� �ö� �ִٴ� ��
					}
				}


			}
			
		}
		temp = temp->next;
	}



	temp = Job_queue->Head->next;



	while(temp != Job_queue->Tail)
	{

		if( count == 1) // dependent part�� �ִ� job���� ���� SPT�� ��
		{
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > temp->Job->Processing_time[temp->Job->current_position])
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = temp->Job->Processing_time[temp->Job->current_position]; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}
		else // dependent part�� ���� job�鸸 SPT�� ��
		{
			//cout << " ����� ������ �ȵȴ� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > temp->Job->Processing_time[temp->Job->current_position])
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = temp->Job->Processing_time[temp->Job->current_position]; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}

		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}


Job_T * Dispatching_TWKR(Machine_T * M, Queue_job * Job_queue, int Time)
{
	int max = 0;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	while(temp != Job_queue->Tail)
	{
		//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
		{		
			if( max < temp->Job->TWKR)
			{
				temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
				max = temp->Job->TWKR; // �׶��� job�� processing time�� min ���� �ȴ�
			}
		}
		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}

Job_T * Dispatching_Dependent_TWKR(Machine_T * M, Queue_job * Job_queue, int Time)
{
	int max = 0;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;


	int count = 0;
	int i;

	while(temp != Job_queue->Tail) // ���⼭ dependent part�� �ִ��� ã�´� ������ 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job���� �ִ� queue���� ���μ��� ������ job�� �߿���
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // �� Job�� �ö� part���� �˻�
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part�� �߿� pre part�� -1 �̸� 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job�� prepart�� �ö� �ִٴ� ��
					}
				}


			}
			
		}
		temp = temp->next;
	}


	temp = Job_queue->Head->next;

		
	while(temp != Job_queue->Tail)
	{

		if( count == 1) // dependent part�� �ִ� job���� ���� SPT�� ��
		{
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( max < temp->Job->TWKR)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					max = temp->Job->TWKR; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}
		else // dependent part�� ���� job�鸸 SPT�� ��
		{
			//cout << " ����� ������ �ȵȴ� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( max < temp->Job->TWKR)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					max = temp->Job->TWKR; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}
		temp = temp->next;
	}
	

	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}


Job_T * Dispatching_MST(Machine_T * M, Queue_job * Job_queue, int Time)
{
	double min = 9999999;
	double v;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	while(temp != Job_queue->Tail)
	{
		//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

		v = temp->Job->avg_duedate - Time - temp->Job->TWKR;

		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
		{		
			if( min > v)
			{
				temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
				min = v; // �׶��� job�� processing time�� min ���� �ȴ�
			}
		}
		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}

Job_T * Dispatching_Dependent_MST(Machine_T * M, Queue_job * Job_queue, int Time)
{
	double min = 9999999;
	double v;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;


	int count = 0;
	int i;

	while(temp != Job_queue->Tail) // ���⼭ dependent part�� �ִ��� ã�´� ������ 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job���� �ִ� queue���� ���μ��� ������ job�� �߿���
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // �� Job�� �ö� part���� �˻�
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part�� �߿� pre part�� -1 �̸� 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job�� prepart�� �ö� �ִٴ� ��
					}
				}


			}
			
		}
		temp = temp->next;
	}


	temp = Job_queue->Head->next;


		
	while(temp != Job_queue->Tail)
	{
		//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

		if( count == 1) // dependent part�� �ִ� job���� ���� SPT�� ��
		{
			v = temp->Job->avg_duedate - Time - temp->Job->TWKR;

			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = v; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}
		else // dependent part�� ���� job�鸸 SPT�� ��
		{
			//cout << " ����� ������ �ȵȴ� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			v = temp->Job->avg_duedate - Time - temp->Job->TWKR;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = v; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}

		temp = temp->next;

	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}

Job_T * Dispatching_MDD(Machine_T * M, Queue_job * Job_queue, int Time)
{
	double min = 9999999;
	double v;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		
	while(temp != Job_queue->Tail)
	{
		
		v = max((int)temp->Job->avg_duedate, Time + temp->Job->TWKR);
		//cout << " �̶��� Time + temp �� : " << Time + temp->Job->TWKR << endl << endl;

		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
		{		
			if( min > v)
			{
				temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
				min = v; // �׶��� job�� processing time�� min ���� �ȴ�
			}
		}
		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " �̶��� mdd �� : " << min << endl << endl;
		
		return temp_Job;
	}
}

Job_T * Dispatching_Dependent_MDD(Machine_T * M, Queue_job * Job_queue, int Time)
{
	double min = 9999999;
	double v;
	Cell_job * temp = Job_queue->Head->next;

	Job_T * temp_Job = NULL;
	int Next_Rest_Time = M->Next_Rest_Time;
		

	int count = 0;
	int i;

	while(temp != Job_queue->Tail) // ���⼭ dependent part�� �ִ��� ã�´� ������ 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job���� �ִ� queue���� ���μ��� ������ job�� �߿���
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // �� Job�� �ö� part���� �˻�
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part�� �߿� pre part�� -1 �̸� 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job�� prepart�� �ö� �ִٴ� ��
					}
				}


			}
			
		}
		temp = temp->next;
	}


	temp = Job_queue->Head->next;


	while(temp != Job_queue->Tail)
	{
		
		if( count == 1) // dependent part�� �ִ� job���� ���� SPT�� ��
		{
			v = max((int)temp->Job->avg_duedate, Time + temp->Job->TWKR);

			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = v; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}
		else // dependent part�� ���� job�鸸 SPT�� ��
		{
			//cout << " ����� ������ �ȵȴ� ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			v = max((int)temp->Job->avg_duedate, Time + temp->Job->TWKR);

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state�� 0�̰� ���� �� operation�� processing time�� machine�� next_rest_time�� �ȳ����� �׶��� route�� machine�� M machine�� ������
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // �׶��� job�� temp_job�� �ȴ�
					min = v; // �׶��� job�� processing time�� min ���� �ȴ�
				}
			}
		}

		temp = temp->next;
	}
	
	if(temp_Job==NULL)
	{
		return NULL;
	}
	else
	{
		//cout << " dispatching �Ǵ� job�� ��ȣ : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching �Ǵ� job�� pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
		return temp_Job;
	}
}

int max(int a, int b)
{
	if(a> b)
		return a;
	else
		return b;
}

int input_Last_to_Machine_Sched_List(Mac_list * ML, Machine_T * M, int St, int Ed, char * Str)
{
	Cell_machine * temp = new Cell_machine;
	Cell_machine * temp2 = ML->tail;
	
	temp->Start_time = St;
	temp->End_time = Ed;
	temp->PID = Str;

	temp->Mac = M;
	
	temp->next = temp2;
	temp->pre = temp2->pre;
	
	temp2->pre->next = temp;
	temp2->pre = temp;
	
	ML->length ++;
	return ML->length;
}

int input_Last_to_Job_List(Job_List * JL, Job_T * J, int trans)
{
	Cell_job * temp = new Cell_job;
	Cell_job * temp2 = JL->Tail;
	
	temp->Job = J; //�׶��� job
	temp->Part = J->Part_Route[J->current_position]; // �״��� part
	
	temp->next = temp2;
	temp->pre = temp2->pre;
	
	temp->pre->next = temp;
	temp2->pre = temp;
	
	JL->Length ++;

	//cout << " machine list�� ���� job part�� completion time : " << J->Current_Process_Completion_time << endl ;

	temp->operation = J->OP_Route[J->current_position] ; // �׶��� operation�� ���� 
	temp->start_time = J->Current_Process_Completion_time - J->Processing_time[J->current_position]; //�׶��� ���۽ð�
	temp->ending_time = J->Current_Process_Completion_time; //�׶��� ������ �ð�
	temp->PID = J->Part_Route[J->current_position]->PT->PID[J->OP_Route[J->current_position]]; //Ȯ�� �ʿ�!  �׶��� process �̸�!
	
	return JL->Length;
}


Job_T * Find_last_job (Job_List * JL)
{
	Cell_job * temp = new Cell_job;
	Job_T * temp_Job;
	
	
	temp = JL->Tail->pre ;

	if (temp == JL->Head)
	{
		temp_Job = NULL;
	}
	else
	{
		temp_Job = temp->Job;
	}

	
	return temp_Job;
}


void initialize_Job_INDEX(Config * Job_INDEX)
{
	Job_INDEX->Job_index=0;
	Job_INDEX->last_processing_time=0;
	
}
