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
	temp->pre = temp2->pre; //초기화
	
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
	temp->pre = temp2->pre; //초기화
	
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
	temp->next = temp->pre = temp2;  //리스트 초기화
	temp2->next = temp2->pre = temp; // 리스트 초기화
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
		temp_Mac = new Machine_T; //Num_Mac 만큼 동적 할당
		temp_Mac->Current_Job_End_Time = -1;
		temp_Mac->Current_Job_Start_Time = -1;
		temp_Mac->Current_State = 0;
		temp_Mac->idle_time = 0;
		temp_Mac->Total_Working_Time = 0;

		temp_Mac->Job_Sequence = new Job_List;
		initialize_Job_List(temp_Mac->Job_Sequence);
		
		
		temp_Mac->Machine_Name = new char[100];
		*in >> temp_Mac->Machine_Name;
		input_Last_to_Machine_List(ML,temp_Mac);  // machine을 list에 하나씩 삽입
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
		temp = temp->next; // 하나씩 machine의 위치 옮기기
		*in >> temp->Mac->Machine_No; 
	//	cout << temp->Mac->Rmc_No << endl;
	}
	
	int t1, t2;
	for(i=0;i<Num_pallet;i++)
	{
		*in >> t1;
		Pallet_type[i].Fixture = new Fixture_T *[t1];
		Pallet_type[i].Num_Fixt = t1; // pallet에 총 t1만큼의 fixture가 있음
		Pallet_type[i].Pallet_index = i ;
		Pallet_type[i].rest_Pallet = 1;
		Pallet_type[i].number_Pallet= 1;
		//Rmc[i].immedieat_working_time = 0;
		
		//	cout << t1 << endl;

		for(j=0;j<t1;j++)
		{
			*in >> t2;
			Pallet_type[i].Fixture[j] = new Fixture_T;

			Pallet_type[i].Fixture[j]->number_Fixture = 1; // fixture type의 갯수가 1개
			Pallet_type[i].Fixture[j]->fixture_no = t2; // 어떤 fixture type인지 
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
			*in >> int_temp[j]; //기계의 유휴시간 받기
			if(int_temp[j] == -1)
			{
				break;
			}
		}
		
		temp->Mac->Current_Schedule = 0;
		if(temp->Mac->release_time == 0) //기계의 준비시간이 0 면 바로 작업가능
		{
			temp->Mac->Machine_Schedule = new int[j]; 
			for(k=0;k<j;k++)
			{
				temp->Mac->Machine_Schedule[k] = int_temp[k];  // machine 스케줄에 할당
			}
			temp->Mac->Number_Schedule = j;
			
			if(temp->Mac->Number_Schedule != 0) 
			{
				temp->Mac->Next_Rest_Time = temp->Mac->Machine_Schedule[0]; // 다음 쉬는 시간은 첫번째 작업이 끝난후
				temp->Mac->Next_Working_time = -1; 
			}
			else
			{
				temp->Mac->Next_Rest_Time = 31536000;
				temp->Mac->Next_Working_time = -1;
			}
			temp->Mac->Working_or_Rest = 1; //일할 수 있는 시간안에 있으면 1 아니면0
		}
		else
		{
			temp->Mac->Machine_Schedule = new int[j+1]; //기계의 준비시간 더해서 배열 생성
			temp->Mac->Machine_Schedule[0] = temp->Mac->release_time; //첫번째는 기계의 준비시간 들어감
			
			for(k=1;k<j+1;k++)
			{
				temp->Mac->Machine_Schedule[k] = int_temp[k-1]; //두번째부터 작업시간이 스케줄이 들어감
			}
			temp->Mac->Number_Schedule = j+1; 
						
			temp->Mac->Next_Rest_Time = -1;
			temp->Mac->Next_Working_time = temp->Mac->Machine_Schedule[0]; //다음 작업시간은 준비시간이 끝난뒤부터
		
			temp->Mac->Working_or_Rest = 0; //일할 수 있는 시간안에 있으면 1 아니면0
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
		PT[i].Job_ID = i; // Part ID랑 Job ID 다 필요 ?
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
			*in >> PT[i].PID[j]; //Operation 이름 받기
		}

		PT[i].Process_Plan = new int*[Num_Process]; // 동적 할당 x
		for(j=0;j<Num_Process;j++)
		{
			PT[i].Process_Plan[j] = new int[Num_Process]; //동적 할당 y
			for(k=0;k<Num_Process;k++)
			{
				*in >> PT[i].Process_Plan[j][k];	 // 프로세스 플랜 행렬 받기			
			}
		}
		
		PT[i].Num_Alternative_Machine = new int[Num_Process]; // 대안 machine 수 process 수만큼 할당
		PT[i].Alterntive_Machine_Name = new char**[Num_Process];
		PT[i].Standard_Time = new int*[Num_Process];
		PT[i].Alternative_Mac = new Machine_T**[Num_Process];

		
		for(j=0;j<Num_Process;j++)
		{
			char * temp_char;
			char * temp_char2;

			*in >> Num_alter_Machine;  // Altenative machine 수 받기

			PT[i].Num_Alternative_Machine[j] = Num_alter_Machine;
			PT[i].Alterntive_Machine_Name[j] = new char*[Num_alter_Machine];
			PT[i].Standard_Time[j] = new int[Num_alter_Machine];
			PT[i].Alternative_Mac[j] = new Machine_T*[Num_alter_Machine];

												
			for(k=0;k<PT[i].Num_Alternative_Machine[j];k++)
			{
				PT[i].Alterntive_Machine_Name[j][k] = new char[100];  //첫번째 operation의 가능한 machine 동적 할당
		        *in >> PT[i].Alterntive_Machine_Name[j][k]; //첫번째 operation의 가능한 machine 이름 받기
				*in >> PT[i].Standard_Time[j][k];
				
				
				temp_char = PT[i].Alterntive_Machine_Name[j][k];
			
				Cell_machine * Node = ML->head->next;  // cell machine을 ML list에 둔다
				while(Node != ML->tail) // 처음부터 list의 꼬리까지 반복해서 ML에 있는 machine을 찾는다
				{
					temp_char2 = Node->Mac->Machine_Name;
					if(strcmp(temp_char, temp_char2)==0) // strcmp 문자열비교 함수, 동일한 문자열이면 0 값
					{
						break;
					}
					Node=Node->next; // 다음 cell machine을 가리킴
				}

				
				PT[i].Alternative_Mac[j][k] = Node->Mac; //  ML list에서 같은 이름의 machine을 가지는 node의 machine이 PT[i].alternative machine이 된다
			} // 왜 ML의 리스트에서 machine을 찾는건지????

		}
	}
	
	*Num_Parts = NJ;  //NJ가 Total number of part이 된다, NJ는 Demand만큼 더해진다


	cout << " NJ 는 ? : " <<NJ << endl;

	int Type = 0;
	int r = 0;
	int Demand = 0;
	Cell_machine * T1;
	Cell_machine * T2;
	Mac_list * ML_T;
	
		
	for(i=0;i<NJ;i++)
	{

		P[i].PT = &PT[Type]; // P에 대해 어떤 Part type인지 지정 
		P[i].Current_Process_No = 0;
		
		P[i].loading_waiting = 0;
		P[i].unloading_waiting = 0;
		P[i].Fixture_type = P[i].PT->Fixture_Type; //PT의 fixture type을 받아온다
		P[i].Part_No = Demand; // P에 번호

		P[i].Due_date = P[i].PT->part_due[r]; //due date 배열 하나씩 받는다
		

		ML_T = new Mac_list;
		T1 = new Cell_machine;
		T2 = new Cell_machine;
		T1->next = T1->pre = T2;
		T2->next = T2->pre = T1;
		ML_T->head = T1;
		ML_T->tail = T2;

		P[i].Machine_Sequence = ML_T; // Part의 machine sequence를 나타내는 list

		P[i].release_time = P[i].PT->release_time; //PT의 release time을 받아옴

		
		Tmp1 = P[i].PT->Num_Operation;
		P[i].Select_Process_Time = new int[Tmp1]; // operation 별로 선택된 프로세싱 타임
		P[i].Mac_Select = new Machine_T* [Tmp1]; // operation별로 선택된 machine 
		P[i].Mac_Select_name = new char * [Tmp1];
		Tmp1 = P[i].PT->Num_Operation;
		P[i].Mac_Select_index = new int[Tmp1]; // operation 별로 선택된 machine 인덱스

		P[i].multiplier = 1; //각 P에 대한 demand
		
		
		P[i].Terminated = 0; //?? 
		//P[i].ATWK = TWKR(&P[i], 0); // TWKR 총 대안 processing time 합한것에 그만큼의 process plan depth 나눈것. p1은 228/3 = 76의 값을 가짐
		Demand ++;
		r++;
		
		if(Demand == P[i].PT->demand || P[i].multiplier > 1) // 또는 
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

	temp2->next = temp; //리스트 초기화 
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

	temp2->next = temp; //리스트 초기화 
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
			sum += TWKR(P,i); // DFS (트리 최대 depth구하기) - 이전까지 평균processing time 
			total ++;
		}
	}
	if(total != 0)
	{
		sum /= total * 1.; //sum = 평균 workload
	}
	else
	{
		sum = 0; 
	}

	for(i=0;i<P->PT->Num_Alternative_Machine[Current_Process];i++)
	{
		sum2 += P->PT->Standard_Time[Current_Process][i]; // 현재 프로세스 까지의 프로세싱 타임 다 더한것 (어떤게 선택될지모름)
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
	
	for(i=0;i<Num_parts;i++) //machine 셀렉션
	{
		P[i].All_processing_time = 0; //초기화

		for(k=0;k<P[i].PT->Num_Operation;k++)
		{
			if (P[i].PT->Num_Alternative_Machine[k] == 0)  // 첫번째 작업과 마지막 작업은 대안machine 없음
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

		//cout << "총 대안들의 시간이다 : "<<P[i].All_processing_time << endl;

		input_Last_to_Queue(System,&(P[i])); //일단 queue에 part들 몰아넣는다
	}
	

	temp_part = System->Head->next;
	while( temp_part != System->Tail)
	{
		if(temp_part->Part->PT->Pre_part == -1 || temp_part->Part->PT->Pre_part == -2)
		{
			//cout<< "로딩 더미로 들어가는 Part type : "  << temp_part->Part->PT->Job_ID << endl;
			//cout<< "로딩 더미로 들어가는 Part 번호 : "  << temp_part->Part->Part_No << endl;
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

Machine_T * Machine_Selection_MNPB(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) // part별로 업데이트해서 다음 machine selection
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
	Machine_T * temp_previous = NULL; //이전에 선택된 machine은 그만큼 prosseing time 더해져야 된다.
	Machine_T * Ret_Mac = NULL; 
	
	
	
	P->Total_Processing_Time = 0;

	for(i=0;i<P->PT->Num_Operation;i++)
	{
		P-> Mac_Select[i]= new Machine_T ;
		P-> Mac_Select_name[i] = new char [100];
		min = 999999;
		temp = 0;

		if (P->PT->Num_Alternative_Machine[i] == 0)  // 첫번째 작업과 마지막 작업은 대안machine 없음
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
				temp_Mac = P->PT->Alternative_Mac[i][j]; // 다시 이해 !!

				temp = Total_Proc_Time_in_Buffer(Job_list, temp_Mac);

				for(t=0 ; t< Num_machine ; t++)
				{
					if(temp_Mac == Job_IDNEX->machine_name[t])
					{
						temp = temp+ Job_IDNEX->machine_pro[t];
						//cout << " temp 다 : " << temp  << endl;
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
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T로 받고
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)로 받고
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // 그때의 processing time 받기

				temp_previous = Ret_Mac; //선택된 machine을 받아서 다음 결정때 검사
				a = P->Select_Process_Time[i]; //선택된 prosessing time 받아서 다음 결정때 더해준다

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
				//cout << " part 번호 : " << P->Part_No << endl;
				//cout << " machine 이름 " << P->Mac_Select_name[i] << endl;

			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //총 processig time 받기
	}
			
	/*for(t=0 ; t < Num_machine ; t++)
	{
		cout << Job_IDNEX->machine_pro[t] << " " ;
	}*/

	return Ret_Mac;
}


Machine_T * Machine_Selection_MNPB2(Part_T * P, Queue_job * Job_list, int Num_machine, Mac_list * ML, Config * Job_IDNEX) //pallet만 체크해서 machine selelction
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
	Machine_T * temp_previous = NULL; //이전에 선택된 machine은 그만큼 prosseing time 더해져야 된다.
	Machine_T * Ret_Mac = NULL; 
	
	
	
	P->Total_Processing_Time = 0;

	for(i=0;i<P->PT->Num_Operation;i++)
	{
		P-> Mac_Select[i]= new Machine_T ;
		P-> Mac_Select_name[i] = new char [100];
		min = 999999;
		temp = 0;

		if (P->PT->Num_Alternative_Machine[i] == 0)  // 첫번째 작업과 마지막 작업은 대안machine 없음
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
				temp_Mac = P->PT->Alternative_Mac[i][j]; // 다시 이해 !!

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
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T로 받고
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)로 받고
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // 그때의 processing time 받기

				temp_previous = Ret_Mac; //선택된 machine을 받아서 다음 결정때 검사
				a = P->Select_Process_Time[i]; //선택된 prosessing time 받아서 다음 결정때 더해준다

				//cout << "a : " << a <<endl;
				//cout << " part type : " << P->PT->Job_ID << endl; 
				//cout << " part 번호 : " << P->Part_No << endl;
				//cout << " machine 이름 " << P->Mac_Select_name[i] << endl;

			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //총 processig time 받기
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

		if (P->PT->Num_Alternative_Machine[i] == 0)  // 첫번째 작업과 마지막 작업은 대안machine 없음
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
				temp_Mac = P->PT->Alternative_Mac[i][j]; // 다시 이해 !!
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
				P->Mac_Select[i] = P->PT->Alternative_Mac[temp_i][temp_j]; // Machine_T로 받고
				P->Mac_Select_name[i] = P->PT->Alterntive_Machine_Name[temp_i][temp_j];
				P->Mac_Select_index[i] = temp_j;//Machie number(index)로 받고
				P->Select_Process_Time[i] = P->PT->Standard_Time[temp_i][temp_j]; // 그때의 processing time 받기

				//cout << " part type : " << P->PT->Job_ID << endl; 
			    //cout << " part 번호 : " << P->Part_No << endl;
				//cout << " machine 이름 " << P->Mac_Select_name[i] << endl;
			}
		}
		
		P->Total_Processing_Time += P->Select_Process_Time[i]; //총 processig time 받기
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
					tem_Job = Job_Define_SPPT(P, &(Pallet_type[k]), Dummy, Machine_Selection_Option, Job_list, Num_machine, ML, Job_IDNEX); // job define  rule들로 나누어서 function 만든다
				}
				else if (Input_Sequence_Option == 2)
				{
					tem_Job = Job_Define_EDD(P, &(Pallet_type[k]), Dummy, Machine_Selection_Option, Job_list, Num_machine, ML , Job_IDNEX);
				}

				if(tem_Job.Empty == 0) //part가 올라간 pallet만 job으로 define
				{
					Pallet_type[k].rest_Pallet = 0;
					
					//J[Job_index] = tem_Job ; //job index 준다

					J[Job_index].P = new Part_T*[tem_Job.Pallet_job->Num_Fixt];
					//J[Job_index].Current_OP_Position = new int[tem_Job.Pallet_job->Num_Fixt]; //current operation 중에 하나 선택 후 machine route 또는 operation index로 보낸다.

					for(v=0 ; v < tem_Job.Pallet_job->Num_Fixt ; v++)
					{
						J[Job_index].P[v] = new Part_T;
						J[Job_index].P[v] = tem_Job.P[v];

						if(J[Job_index].P[v] != NULL)
						{
							J[Job_index].P[v]->Job_No = Job_index; //어떤 job에 속하는지
							//J[Job_index].Current_OP_Position[v] = J[Job_index].P[v]->Current_Process_No; // 첫번째 operation을 뜻함. v번째 part의 operation 위치를 나타냄
						}
						else
						{
							//J[Job_index].Current_OP_Position[v] = NULL; //0은 operation이 없음.
						}
					}

					J[Job_index].Pallet_job = tem_Job.Pallet_job ;
					J[Job_index].Empty = tem_Job.Empty;
					J[Job_index].Total_Number_Operation = (tem_Job.Total_Number_Operation - (2*tem_Job.Num_parts)) ; //part type 별 시작과 끝 operation 제거 후 1개만큼 더 할당!

					J[Job_index].Job_No = Job_index;
					J[Job_index].Num_parts = tem_Job.Num_parts; // 몇개의 part가 올라갔는지
					J[Job_index].current_position = 0; //Route들 들고다닐때 필요함!
					J[Job_index].current_state=0; //1이면 작업중이다
					J[Job_index].avg_duedate = tem_Job.avg_duedate/tem_Job.Num_parts;

				

					if(Job_route_Option == 1)
					{
						Job_route(&(J[Job_index])); //Job route greedy 방법으로 결정
					}
					else if( Job_route_Option == 2 )
					{
						Job_IDNEX->total_movement = 99;
						Job_IDNEX->temp = 99;
						Job_route_HU(&(J[Job_index]), Job_IDNEX); //Job route DP 밥어으로 결정
					}
					else if( Job_route_Option == 3 )
					{
						Job_IDNEX->total_movement = 99;
						Job_IDNEX->temp = 99;
						Job_route_DP(&(J[Job_index]), Job_IDNEX);//Job route DP 밥어으로 결정
					}
		

					input_Last_to_Job_Queue(Job_list, &J[Job_index]); //part가 올라간 pallet만 buffer(job_list)로 간다 리스트에 뒤에서 부터 삽입
					Job_index ++;
					
					//cout << "Job에 올라오는 part의 수 : " << tem_Job.Num_parts << endl;
					//cout << " Job의 평균 due date : " << tem_Job.avg_duedate/tem_Job.Num_parts<< endl;
					
				}
				/*else
				{
					J[Job_index].Pallet_job = tem_Job.Pallet_job ;
					J[Job_index].P = new Part_T*[tem_Job.Pallet_job->Num_Fixt];
					for(v=0 ; v < tem_Job.Pallet_job->Num_Fixt ; v++)
					{
						J[Job_index].P[v] = new Part_T;
						J[Job_index].P[v] = tem_Job.P[v]; //NULL 값 받는다
					}
					J[Job_index].Empty = tem_Job.Empty;
				
				}*/

			}

			else 
			{
				//cout << " No more pallet " << endl; // 만약 남는 팔렛이 없다면?? 어떻게 ??
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

	//cout << "새로운 pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		//cout << j << endl;
		temp = Dummy->Head->next ;
		k=1;
		

		//cout << "다음fixture " << endl;
		while(temp != Dummy->Tail)
		{
			//cout << k << endl ;
			k++;
			
			if(temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1) // 
			{
				i++;
				Temp_Job.P[j] = new Part_T ;
				Temp_Job.P[j] = temp->Part; //어떤 part가 들어왔는지	

				
				Temp_Job.Total_Number_Operation += temp->Part->PT->Num_Operation; //들어오는 part들의 operation 개수 합치기
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job에 어떤 팔렛이 대응되는지
				Temp_Job.Empty = 0; // pallet에 part가 올라가면 0

				

				//cout <<"fixture에 걸리는 part : "<<  o << endl;
				o++;

				temp->next->pre = temp->pre;
				temp->pre->next = temp->next;//선택된 part는 queue에서 사라진다 
				temp_a = temp;
				temp = temp->next;

				delete temp_a;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // 그때 fixture는 사용됨
				
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


	Job_IDNEX->machine_name = new Machine_T * [Num_machine]; // machine selection 할때 name list 받기
	Job_IDNEX->machine_pro = new int [Num_machine]; // machine selection 할때 이전 machine들에 대한 processing time 받기
	
	Temp_Job.P = new Part_T *[Pallet_type->Num_Fixt];

	for(t=0 ; t < Num_machine ; t++)
	{
		Job_IDNEX->machine_pro[t] = 0; //초기화
		Job_IDNEX->machine_name[t] =  new Machine_T ; // 초기화
	}


	//cout << "새로운 pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		Temp_Job.P[j] = new Part_T ;
		//cout << j << endl;

		Cell * test = NULL;
		temp = Dummy->Head->next ;
	
		
		//cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;
		min = 99999;
		//cout << "다음fixture " << endl;
		while(temp != Dummy->Tail)
		{

			
			//cout << " ddddddddddddddddddddd " << endl;
			if(temp->Part->Terminated==0 && temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1 && min > temp->Part->Due_date) // 모든 대안의 가공시간 중 min값 
			{
					//cout << "aaaaaaaaaaaaaa " << endl;
					test = temp; //어떤 part가 들어왔는지	
					min = temp->Part->Due_date; 
				
					//cout <<"fixture에 걸리는 part : "<<  temp->Part->Part_No << endl;
					//cout <<"fixture에 걸리는 part type : "<<  temp->Part->PT->Job_ID << endl;
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
				Temp_Job.Total_Number_Operation += test->Part->PT->Num_Operation; //들어오는 part들의 operation 개수 합치기
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job에 어떤 팔렛이 대응되는지
				Temp_Job.Empty = 0; // pallet에 part가 올라가면 0
				total_duedate += test->Part->Due_date;
				Temp_Job.avg_duedate = total_duedate;

				//cout<< "로딩 되는 Part type : "  << test->Part->PT->Job_ID << endl;
				//cout<< "로딩 되는 Part 번호 : "  << test->Part->Part_No << endl;
				//cout<< "로딩 되는 Pallet 번호 : "  << Pallet_type->Pallet_index << endl;
				//cout << " total duedate = : " << Temp_Job.avg_duedate<< endl;
				//cout << "올라 오는 part의 수 : " << Temp_Job.Num_parts<< endl;
					
				if(Machine_Selection_Option == 1)
				{
					temp_Mac = Machine_Selection_SPT(test->Part);//opreation 마다 machine 선택 
					//cout << "total processing time ===============: " << test->Part->Total_Processing_Time << endl;
				}
				else if(Machine_Selection_Option == 2)
				{
					if(Job_list->Length==0) // buffer에 아무것도 없을때는 SPT로 들어간다
					{
						temp_Mac = Machine_Selection_SPT(test->Part);
					}
					else // buffer에 job이 있으면 machine의 총 processing time들을 계산
					{
						temp_Mac = Machine_Selection_MNPB(test->Part, Job_list, Num_machine, ML, Job_IDNEX);
					}
				}


			//	cout << " 이때의 part 번호 : " << Temp_Job.P[j]->Part_No << endl;
			//  cout << " 이때의 PT type: " << Temp_Job.P[j]->PT->Job_ID<< endl;
			//	cout <<" 이게 토탈 넘버 오브 오퍼레잉션 : " << Temp_Job.Total_Number_Operation << endl;


				test->next->pre = test->pre;
				test->pre->next = test->next;//선택된 part는 queue에서 사라진다 

				delete test;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // 그때 fixture는 사용됨
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
	

	Job_IDNEX->machine_name = new Machine_T * [Num_machine]; // machine selection 할때 name list 받기
	Job_IDNEX->machine_pro = new int [Num_machine]; // machine selection 할때 이전 machine들에 대한 processing time 받기

	Temp_Job.P = new Part_T *[Pallet_type->Num_Fixt];


	for(t=0 ; t < Num_machine ; t++)
	{
		Job_IDNEX->machine_pro[t] = 0; //초기화
		Job_IDNEX->machine_name[t] =  new Machine_T ; // 초기화
	}



	//cout << "새로운 pallet " << endl; 
	for(j=0 ; j < Pallet_type->Num_Fixt ; j++)
	{
		Temp_Job.P[j] = new Part_T ;
		//cout << j << endl;

		Cell * test = NULL;
		temp = Dummy->Head->next ;
	
		
		//cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;
		min = 99999;
		//cout << "다음fixture " << endl;
		while(temp != Dummy->Tail)
		{

			
			//cout << " ddddddddddddddddddddd " << endl;
			if(temp->Part->Terminated ==0 && temp->Part->Fixture_type == Pallet_type->Fixture[j]->fixture_no && Pallet_type->Fixture[j]->rest_Fixture == 1 && min > temp->Part->All_processing_time) // 모든 대안의 가공시간 중 min값 
			{
					//cout << "aaaaaaaaaaaaaa " << endl;
				test = temp; //어떤 part가 들어왔는지	
				min = temp->Part->All_processing_time; 
				
					//cout << " Pocessing time aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa :" << temp->Part->Total_Processing_Time << endl;
					//cout <<"fixture에 걸리는 part : "<<  o << endl;
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
				Temp_Job.Total_Number_Operation += test->Part->PT->Num_Operation; //들어오는 part들의 operation 개수 합치기
				Temp_Job.Num_parts = i ;
				Temp_Job.Pallet_job = Pallet_type; // Job에 어떤 팔렛이 대응되는지
				Temp_Job.Empty = 0; // pallet에 part가 올라가면 0
				total_duedate += test->Part->Due_date;
				Temp_Job.avg_duedate = total_duedate;


				//cout<< "로딩 되는 Part type : "  << test->Part->PT->Job_ID << endl;
				//cout<< "로딩 되는 Part 번호 : "  << test->Part->Part_No << endl;
				//cout<< "로딩 되는 Pallet 번호 : "  << Pallet_type->Pallet_index << endl;
					
				if(Machine_Selection_Option == 1)
				{
					temp_Mac = Machine_Selection_SPT(test->Part);//opreation 마다 machine 선택 
					//cout << "total processing time ===============: " << test->Part->Total_Processing_Time << endl;
				}
				else if(Machine_Selection_Option == 2)
				{
					if(Job_list->Length==0) // buffer에 아무것도 없을때는 SPT로 들어간다
					{
						temp_Mac = Machine_Selection_SPT(test->Part);
						//cout << " 여기 찍히냐 ? " << endl;
					}
					else // buffer에 job이 있으면 machine의 총 processing time들을 계산
					{
						//cout << " 여기 찍히냐 2222222? " << endl;
						temp_Mac = Machine_Selection_MNPB(test->Part, Job_list, Num_machine, ML, Job_IDNEX);
						//cout << " 여기 찍히냐 3333333333? " << endl;
					}
				}


			//	cout << " 이때의 part 번호 : " << Temp_Job.P[j]->Part_No << endl;
			//  cout << " 이때의 PT type: " << Temp_Job.P[j]->PT->Job_ID<< endl;
			//	cout <<" 이게 토탈 넘버 오브 오퍼레잉션 : " << Temp_Job.Total_Number_Operation << endl;


				test->next->pre = test->pre;
				test->pre->next = test->next;//선택된 part는 queue에서 사라진다 

				delete test;

				Dummy->Length --;
				Pallet_type->Fixture[j]->rest_Fixture=0; // 그때 fixture는 사용됨
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

	int *part_position_index; //Job의 P에는 NULL로 된 part공간이 있다. 따라서 들어있는 P의 postion index가 필요
	int  *temp_op_index;
	//Part_T temp_part;
	//Machine_T temp_machine ;

	current_part = new Part_T;
	machine_movement = new int[J->Num_parts]; //J의P에 NULL값들을 빼고 메모리공간 만든다 
	part_position_index = new int[J->Num_parts];
	temp_op_index = new int [J->Num_parts];

	for(k=0 ; k<J->Num_parts ; k++)
	{
		temp_op_index[k] = 0; //index는 0이다
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
			//cout << "J의 part type : " << J->P[a]->PT->Job_ID << "    " ;
			
		}
	}
	
	for(j=0 ; j < J->Num_parts ; j++)
	{
		//cout << J->P[part_position_index[j]]->PT->Job_ID << endl;
	}
	
	J->OP_Route[0] = J->P[part_number]->Current_Process_No+1 ; //rand으로 받았을때의 값
	J->Part_Route[0] =  J->P[part_number] ;
	J->Machine_Route[0] = J->P[part_number]->Mac_Select[1];  //rand으로 하나 받아온다 //랜덤하게 번호생성 후 하나의 part의 첫번째 operation으로 들어간다
	J->Machine_name[0] = J->P[part_number]->Mac_Select_name[1]; // 첫번째 operation이기 때문에 
	J->Processing_time[0] =  J->P[part_number]->Select_Process_Time[1];
	J->Total_movement = 0 ;

	temp_op_index[0] += 1; // 첫번째 배열에 들어간 part의 operation 번호 
	current_part = J->P[part_number]; // 현재 part
	current_part_op = J->P[part_number]->Current_Process_No+1; // 현재 part의 operation 번호

	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //마지막값은 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // 맨마직은 아무값도 없다
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //맨마지막은 아무값도 없다
	J->Machine_name[J->Total_Number_Operation+1] = NULL ;
	J->Processing_time[J->Total_Number_Operation+1] = NULL; 

	machine_movement = movement_cal(current_part, current_part_op, temp_op_index, J, part_position_index); // movement 계산 및 selection
	

	J->TWKR = TWKR2(J);

	//cout <<"Job의 번호 : " << J->Job_No << endl;
	//cout <<"Job의 TWKR : " << J->TWKR << endl;


	/*for(j=1;j<J->Total_Number_Operation;j++)
	{
		for(k=0 ; k<J->Pallet_job->Num_Fixt ; k++)
		{
			if(J->Part_Route[0] == J->Part_Route[k] ~~~~)
			{
				temp_machine = J->P[k]->Mac_Select[0] ;// Machine movement 최소화가 되는것 ! 어떤 로직에 의해서 하나가 선택된 후 temp machine이 된다
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
	int *part_position_index; //Job의 P에는 NULL로 된 part공간이 있다. 따라서 들어있는 P의 postion index가 필요
	int * part_position_index2;
	int  *temp_op_index;

	int part_number;
	int total_num_operation;
	int Num_part_on_pallet;
	


	total_num_operation = J->Total_Number_Operation; // 총 operation개수
	
	Num_part_on_pallet = J->Num_parts; //몇개의 part가 올라와있는지


	current_part = new Part_T;
	machine_movement = new int[J->Num_parts]; //J의P에 NULL값들을 빼고 메모리공간 만든다 
	part_position_index = new int[J->Num_parts];
	part_position_index2 = new int[J->Num_parts];
	temp_op_index = new int [J->Num_parts];


	int  *temp_op_index2; // part들의 operation index
	temp_op_index2 = new int [Num_part_on_pallet]; // part들의 현재 operation index

	for(k=0 ; k<Num_part_on_pallet ; k++)
	{
		temp_op_index2[k] = 0; //index는 0이다
		temp_op_index[k] = 0;
	}
	

	




	int *temp; // 임시 operation 순서
	int *temp2;
	int *Job_route; //job route = final job route 순서

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



	J->OP_Route[0] = J->P[part_number]->Current_Process_No+1 ; //rand으로 받았을때의 값
	J->Part_Route[0] =  J->P[part_number] ;
	J->Machine_Route[0] = J->P[part_number]->Mac_Select[1];  //rand으로 하나 받아온다 //랜덤하게 번호생성 후 하나의 part의 첫번째 operation으로 들어간다
	J->Machine_name[0] = J->P[part_number]->Mac_Select_name[1]; // 첫번째 operation이기 때문에 
	J->Processing_time[0] =  J->P[part_number]->Select_Process_Time[1];
	J->Total_movement = 0 ;


	temp_op_index[0] += 1; // 첫번째 배열에 들어간 part의 operation 번호 
	current_part = J->P[part_number]; // 현재 part
	current_part_op = J->P[part_number]->Current_Process_No+1; // 현재 part의 operation 번호


	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //마지막값은 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // 맨마직은 아무값도 없다
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //맨마지막은 아무값도 없다
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
	for(a=0 ; a<total_num_operation ; a++) // route 알고리즘 결정 여기서 a는 현재 operation 길이 사이즈이다.
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


	


	for(a=1 ; a<total_num_operation ; a++) // route 알고리즘 결정 여기서 a는 현재 operation 길이 사이즈이다.
	{
		

		//num = new int [a];
		//temp = new int [a+1];


		// num은 Job_route 받는다
		// temp 초기화 

		Job_IDNEX->total_movement = 99; //movement 다시 초기화

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
				if(temp_op_index[i] < J->P[part_position_index[i]]->PT->Num_Operation-1) // J의 P의 operation 숫자보다 작을때만!
				{

					if(i==r) //처음에 current part의 position은 0이다. 한번 iteration 후 r의 값은 바뀜 current part의 position 변화 알기 위해 r에 저장
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
					machine_movement[i] = 99;	//operation 할당 다 된것을 의미 !
				}
			}
		}
		


		/*for (a=0 ; a<J->Num_parts ; a++)
		{
			cout <<" machine movement : " << machine_movement[a] << endl ;
		}*/


		min=999;
		for(k=0 ; k < J->Num_parts ; k++) //최소 movement찾는다 
		{			
			if(machine_movement[k] <= min )
			{
				min = machine_movement[k];
				r = k; // current part의 position이 바뀜
				//cout << " r의 값 : " << r << endl;
			}
		}


		if(machine_movement[r] ==1)
		{
			total_machine_movement += 1;
		}
		current_part = J->P[part_position_index[r]];
		temp_op_index[r] += 1;
		current_part_op = temp_op_index[r];


		/*for(k=0 ; k < J->Num_parts ; k++) //최소 movement찾아 출력해본다
		{	
			cout << " temp part op 의 값 : " << temp_op_index[k] << endl ;
		}*/

		/*
		cout << "temp op index : " << temp_op_index[0] << endl;
		cout << "temp op index : " << temp_op_index[1] << endl;
		cout << "temp op index : " << temp_op_index[2] << endl;
		cout << "temp op index : " << temp_op_index[3] << endl;

		cout << "part_position_index : " <<part_position_index[r] <<endl;
		
		cout << "current part : " << current_part->PT->Job_ID << endl;
	

		cout<< " r의 값 : " << r << endl;
		cout << " 여기~~~ " << endl;

		*/

	







		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ 여기 for문 2개는 추가되는 operation을 하나씩 사이에 넣어보면서 route들 생성하고 그때 route들의 machine movement를 계산한 후 업데이트!
		for(p=0 ; p<a+1 ; p++) // operation 1개 추가 되면서 operation 길이 사이즈가 한개 늘어남
		{
			index = 0;
			

			for(s=0 ; s<a ; s++) // 하나씩 다 넣어본다
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
				//part_position_index[r]을 새로운 operation으로 추가한다 


				//temp를 결정하면 됨. 계속 바껴야됨 체크!
				
				

			}
			
			/*
			cout << "temp route는 ? " ;
			for(int l=0; l < a+1 ; l++)
			{
				cout  <<  temp[l] << " " ;
			}
			cout << endl;
			*/

			//cout << " 왜~~~~~~~~~~~~~~~~~ " << endl;
			Job_IDNEX->temp = movement_cal_HU(temp, part_position_index, J, a+1, temp_op_index2,Job_IDNEX); //생성된 route의 movement 계산

			//cout << " 응응응으으으으으으으~~~~~~~~~~~~~~~~~ " << endl;

			//cout << " Job_Index의 movement 값 " << Job_IDNEX->temp << endl;
			//cout << "Job_Index의 total movement 값 " << Job_IDNEX->total_movement << endl;
			if( Job_IDNEX->temp < Job_IDNEX->total_movement ) // movement 더 작은 route면 Job_route로 업데이트
			{
				//cout << " 여기222~~~ " << endl;	
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
			//temp2[k] 초기화?
		}

		/*
		cout << "job route는 ? " ;
		for(int l=0; l < a+1 ; l++)
		{
				cout  <<  Job_route[l] << " " ;
		}
			cout << endl;
		cout << " machine movement는 ? " << Job_IDNEX->total_movement << endl;
		*/


	}

	for(j=0 ; j < Num_part_on_pallet ; j++)
	{
		temp_op_index2[j] = 0; 
	}

	
	
	for(j=0 ; j < total_num_operation ; j++) // 가장 좋은 job route를 J에 업데이트!! 
	{
		

		/*	
		J->OP_Route[j] = (temp_op_index2[Job_route[j]])+1 ;
		J->Part_Route[j] = J->P[part_position_index[Job_route[j]]] ;
		J->Machine_Route[j] = J->P[part_position_index[Job_route[j]]]->Mac_Select[temp_op_index2[Job_route[j]]+1];  //rand으로 하나 받아온다 //랜덤하게 번호생성 후 하나의 part의 첫번째 operation으로 들어간다
		J->Machine_name[j] = J->P[part_position_index[Job_route[j]]]->Mac_Select_name[temp_op_index2[Job_route[j]]+1];
		J->Processing_time[j] =  J->P[part_position_index[Job_route[j]]]->Select_Process_Time[temp_op_index2[Job_route[j]]+1];
		*/



			J->OP_Route[j] = (temp_op_index2[Job_route[j]-1])+1 ;
			J->Part_Route[j] = J->P[part_position_index[Job_route[j]-1]] ;
			J->Machine_Route[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select[temp_op_index2[Job_route[j]-1]+1];  //rand으로 하나 받아온다 //랜덤하게 번호생성 후 하나의 part의 첫번째 operation으로 들어간다
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

		//cout << " 들어와라 ~~~ " << endl;
		if( J->P[part_position_index[temp_route[i+1]-1]]->Mac_Select[temp_op_index2[temp_route[i+1]-1]+1] != NULL )
		{
			//cout << " 들어와라222 ~~~ " << endl;
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
				//cout << " v의 값 : " << v << endl << endl;
			}
		}
		else
		{
			//cout << " 들어와라333 ~~~ " << endl;
			v=v;
		}

		//cout << " 들어와라444 ~~~ " << endl;
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

	total_num_operation = J->Total_Number_Operation; // 총 operation개수
	
	Num_part_on_pallet = J->Num_parts; //몇개의 part가 올라와있는지
	


	int  *temp_op_index2;
	temp_op_index2 = new int [Num_part_on_pallet]; // part들의 현재 operation index

	for(k=0 ; k<Num_part_on_pallet ; k++)
	{
		temp_op_index2[k] = 0; //index는 0이다
	}
	

	int *part_position_index; //Job의 P에는 NULL로 된 part공간이 있다. 따라서 들어있는 P의 postion index가 필요
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
		num[j] = J->P[part_position_index[j]]->PT->Num_Operation-2;  //여기서 위치도 알아야됨
	
	}

	
	int step =0;
	r = recursive(step, mat, num, Job_route, total_num_operation, Num_part_on_pallet, part_position_index, J, temp_op_index2, Job_IDNEX); //job route 결정
	//recursive_temp(step, mat, num); //job route 결정


	
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
			//cout << "J의 part type : " << J->P[a]->PT->Job_ID << "    " ;
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
			J->Machine_Route[j] = J->P[part_position_index[Job_route[j]-1]]->Mac_Select[temp_op_index2[Job_route[j]-1]+1];  //rand으로 하나 받아온다 //랜덤하게 번호생성 후 하나의 part의 첫번째 operation으로 들어간다
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

	J->OP_Route[J->Total_Number_Operation+1] = NULL ; //마지막값은 0
	J->Part_Route[J->Total_Number_Operation+1] = NULL ; // 맨마직은 아무값도 없다
	J->Machine_Route[J->Total_Number_Operation+1] = NULL ; //맨마지막은 아무값도 없다
	J->Machine_name[J->Total_Number_Operation+1] = NULL ;
	J->Processing_time[J->Total_Number_Operation+1] = NULL; 

	J->TWKR = TWKR2(J);

	//cout <<"Job의 번호 : " << J->Job_No << endl;
	//cout <<"Job의 TWKR : " << J->TWKR << endl;


	/*for(j=1;j<J->Total_Number_Operation;j++)
	{
		for(k=0 ; k<J->Pallet_job->Num_Fixt ; k++)
		{
			if(J->Part_Route[0] == J->Part_Route[k] ~~~~)
			{
				temp_machine = J->P[k]->Mac_Select[0] ;// Machine movement 최소화가 되는것 ! 어떤 로직에 의해서 하나가 선택된 후 temp machine이 된다
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

	cout << "여기 8 "<< endl;
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
				cout << " 여기 들어와 ? " << endl;
				for(j = 0 ; j <= step ; j++)
				{ 
					//cout << "어디서 문제? " <<endl;
					//temp_route[j] = mat[j];
					cout << "route ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ : " << mat[j];
				}

			}
			
			cout << " 추가적인 곳 " << endl;
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
			
			//cout << " recursive 속이다 " << endl;
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
				//cout << " v의 값 : " << v << endl << endl;
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

	for(j=1; j < J->Total_Number_Operation ; j++) // j=1부터다 0에는 처음 선택된 값들이 들어가있음. Total_Number_operation+1 에는 NULL값들이 들어가있음
	{
		for(i=0 ; i < J->Num_parts ; i++)
		{
			if(temp_op_index[i] != -1)
			{
				if(temp_op_index[i] < J->P[part_position_index[i]]->PT->Num_Operation-1) // J의 P의 operation 숫자보다 작을때만!
				{

					if(i==r) //처음에 current part의 position은 0이다. 한번 iteration 후 r의 값은 바뀜 current part의 position 변화 알기 위해 r에 저장
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
					machine_movement[i] = 99;	//operation 할당 다 된것을 의미 !
				}
			}
		}
		


		/*for (a=0 ; a<J->Num_parts ; a++)
		{
			cout <<" machine movement : " << machine_movement[a] << endl ;
		}*/


		min=999;
		for(k=0 ; k < J->Num_parts ; k++) //최소 movement찾는다 
		{			
			if(machine_movement[k] <= min )
			{
				min = machine_movement[k];
				r = k; // current part의 position이 바뀜
				//cout << " r의 값 : " << r << endl;
			}
		}


		if(machine_movement[r] ==1)
		{
			total_machine_movement += 1;
		}
		current_part = J->P[part_position_index[r]];
		temp_op_index[r] += 1;
		current_part_op = temp_op_index[r];


		/*for(k=0 ; k < J->Num_parts ; k++) //최소 movement찾아 출력해본다
		{	
			cout << " temp part op 의 값 : " << temp_op_index[k] << endl ;
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
		
	//cout << " 여기 " << endl;
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
		//cout << "시뮬레이션 타임 : " << Simulation_time << endl;
		Terminated = 0;

		for(i=0;i<Num_Parts;i++)
		{
			Terminated += P[i].Terminated;
			
		}



		


		//cout << " Terminated 몇개냐 ? : " << Terminated << endl;
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
				//cout << "zzzzzzzzzzz" <<endl; //비어있음
			}
			temp_job_cell = temp_job_cell->next;
		}
		
		CJ_temp = Dummy->Head;
		k=0;
		while(CJ_temp != Dummy->Tail) //언로딩 체크
		{
			k++;
			//cout << " ggggggggggggggggggggggggggggggg : " << k << endl;
			if(CJ_temp->next == Dummy->Tail)
			{	
				//cout << "yyyyyyyyyyyy" <<endl; //비어있음
			}			
			CJ_temp= CJ_temp->next;
	
		}

		//cout << " ggggggggggggggggggggggggggggggg : " << Dummy->Length << endl;


		/*for ( k=0; k < Num_pallet ; k++)
		{
			cout<< " pallet이 여유있는게 몇개냐 ?? "  << Pallet_type[k].rest_Pallet << endl;
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
	Job_T * Pre_Job; //이전 job 체크해서 transportation time 추가

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
			if(Mac_Temp->Current_Schedule == Mac_Temp->Number_Schedule) // Number_Schedule은 스케줄 수이다 마지막까지 오면 계속 machine은 on 상태
			{
				Mac_Temp->Next_Working_time = -1;
				Mac_Temp->Next_Rest_Time = 31536000; // == 1년
			}
			else
			{
				Mac_Temp->Next_Working_time = -1;
				Mac_Temp->Next_Rest_Time = Mac_Temp->Machine_Schedule[Mac_Temp->Current_Schedule];
			}
			Mac_Temp->Working_or_Rest = 1; //1이면 machine 사용가능
			EV = 1;
		}
		
		//change a machine to vacate mode by calender
		if(Mac_Temp->Working_or_Rest == 1 && Mac_Temp->Next_Rest_Time == Time)
		{
			Mac_Temp->Current_Schedule ++;
			if(Mac_Temp->Current_Schedule == Mac_Temp->Number_Schedule) // Number_Schedule은 스케줄 수이다 마지막까지 오면 계속 machine은 on 상태
			{
				Mac_Temp->Next_Rest_Time = -1;
				Mac_Temp->Next_Working_time = 31536000;// == 1년
			}
			else
			{
				Mac_Temp->Next_Working_time = Mac_Temp->Machine_Schedule[Mac_Temp->Current_Schedule];
				Mac_Temp->Next_Rest_Time = -1;
			}
			Mac_Temp->Working_or_Rest = 0; //0이면 machine 사용 불가
			EV = 1;
		}
	
		//starting processing in available machine with dispatching rule
		if(Mac_Temp->Current_State == 0 && Mac_Temp->Working_or_Rest == 1 ) //current state가 0이면 할수있다
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
					//cout << "여기 ~~~~~~~~~~~~~~~~~비어있을때 한번" << endl;
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
					//cout << " 처음으로 걸리는 pre job의 current position : " << Pre_Job->current_position <<endl;
					//cout << "여기 ~~~~~~~~~~~~~~~~~333333333" << endl;
					if(Pre_Job->current_state == 0 ) //Job(pallet)이 process중이 아니어야되고
					{
						if(Mac_Temp->End_time == Time) // 그때의 machine이 방금 끝나야 된다. 이전에 끝났던 machine이 쉬다가 다시 똑같은 job을 받을 경우에는 이동시간 추가되어야됨
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
					if(Mac_Temp->End_time == Time) // 그때의 machine이 방금 끝나야 된다. 이전에 끝났던 machine이 쉬다가 다시 똑같은 job을 받을 경우에는 이동시간 추가되어야됨
					{
						Job_temp->Current_Process_Completion_time = Time + Job_temp->Processing_time[Job_temp->current_position]; // 한 machine에 같은 job이 들어오면 transporation time 제외 !
					}
					else
					{
						Job_temp->Current_Process_Completion_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position]; //같은 job이라고 할지라도 방금 끝난 시간후에 같은 job이 와야된다. 한참 뒤에 같은 job오면 tran 더해줌
					}
				}
				else
				{
					Job_temp->Current_Process_Completion_time = Time + trans + Job_temp->Processing_time[Job_temp->current_position]; //machine에 다른 job이 들어오면 transportation 더해준다
					//cout << " ============================ 이때의 time : " << Job_temp->Current_Process_Completion_time << " " << Time + trans + Job_temp->Processing_time[Job_temp->current_position]<<  endl << endl;
				}

				input_Last_to_Job_List(Mac_Temp->Job_Sequence,Job_temp, trans); // Machine 기준 J의 part까지 입력

				Mac_Temp->Current_State = 1; //machine이 process중
				Mac_Temp->Current_Job_Start_Time = Time;
				if(Pre_Job == Job_temp)
				{
					if(Mac_Temp->End_time == Time) // 그때의 machine이 방금 끝나야 된다. 이전에 끝났던 machine이 쉬다가 다시 똑같은 job을 받을 경우에는 이동시간 추가되어야됨
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
				Mac_Temp->Current_Part_ID = Job_temp->Part_Route[Job_temp->current_position]->PT->Job_ID; // 현재 machine process중인 part type
				Mac_Temp->Current_Part_No = Job_temp->Part_Route[Job_temp->current_position]->Part_No; // 현재 machine이 process중인 part 번호
				Mac_Temp->Current_Job_No = Job_temp->Job_No; //현재 machine이 process중인 Job

				Job_INDEX->last_processing_time =  Job_temp->Processing_time[Job_temp->current_position];

				//cout << " uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu last procesing_time : " << Job_INDEX->last_processing_time << endl << endl;

				input_Last_to_Machine_Sched_List(Job_temp->Part_Route[Job_temp->current_position]->Machine_Sequence , Mac_Temp, Mac_Temp->Current_Job_Start_Time, Mac_Temp->Current_Job_End_Time, Job_temp->Part_Route[Job_temp->current_position]->PT->PID[Job_temp->OP_Route[Job_temp->current_position]]);
				// part 기준으로 machine이랑 시간 받는다


				Cell_machine * temp = new Cell_machine;
				temp=Job_temp->Part_Route[Job_temp->current_position]->Machine_Sequence->tail->pre;
				/*
				cout << " Job 번호 : " << Job_temp->Job_No << endl;
				cout << " part type : " << Job_temp->Part_Route[Job_temp->current_position]->PT->Job_ID << endl;
				cout << " Part 번호 : " << Job_temp->Part_Route[Job_temp->current_position]->Part_No << endl;
				cout << " OP 번호 : " << Job_temp->OP_Route[Job_temp->current_position] << endl;
				cout << " machine : " << CM_Temp->Mac->Machine_Name << endl ;
				cout << " 이때의 TWKR : " << Job_temp->TWKR << endl << endl;

				cout <<"들어간 part의 끝 시간 : " << temp->End_time << endl;
				cout <<" 들어간 part의 시작 시간: " << temp->Start_time << endl;
				*/
				Job_temp->TWKR = Job_temp->TWKR - Job_temp->Processing_time[Job_temp->current_position]; // TWKR 선택된 거 만큼 processing time 빼고 업데이트 된다
				Job_temp->current_position ++; //확인 필요
				Job_temp->current_state = 1 ; //지금 process 중이다d
				

				//cout << " 바뀌고나서 TWKR : " << Job_temp->TWKR << endl << endl;
				

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
			Mac_Temp->Current_State = 0; // machine 사용 가능
			
			


			Job_temp = Mac_Temp->Job_Sequence->Tail->pre->Job;

			Job_temp->current_state = 0; //다시 이 job은 선택 될 수 있음


			
			Cell_machine * Cell_Temp;
			if(Job_temp->Part_Route[(Job_temp->current_position)-1]->Terminated == 1)
			{
				Cell_Temp = Job_temp->Part_Route[(Job_temp->current_position)-1]->Machine_Sequence->head->next;
				while(Cell_Temp->next != Job_temp->Part_Route[(Job_temp->current_position)-1]->Machine_Sequence->tail)
				{
					Cell_Temp = Cell_Temp->next;
				}

				Job_temp->Part_Route[(Job_temp->current_position)-1]->completion_time = Cell_Temp->End_time; //그때 part의 종료시간
				Job_temp->Completion_time = Cell_Temp->End_time; //Job의 종료시간. 계속해서 update 됨 . part들의 종료시간중에 하나가 job의 종료시간임

			}

			//cout <<" Job 번호 : " << Job_temp->Job_No << " " << "Job의 종료 시간 : " << Job_temp->Completion_time<< endl ;
			//cout << " job의 part의 operation이 끝나는 시간 : "<< Job_temp->Part_Route[(Job_temp->current_position)-1]->completion_time << endl ;

			EV = 1;
		}
		
		CM_Temp = CM_Temp->next;
		
	}
	
	
	
	int k=0;
	while(temp_cell_job != Job_queue->Tail)
	{
		k++;
		//cout << " ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ: " << k << endl;
		//cout << "job번호 입니다 : " << temp_cell_job->Job->Job_No << endl;
		//cout << " current position 입니다 : " << temp_cell_job->Job->current_position << endl;	
		
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
	while(temp_cell_job != Job_queue->Tail) // job이 끝나면 job_queue buffer에서 제거해준다.
	{
		if(temp_cell_job->Job->Terminate==1)
		{
			temp_cell_job->Job->Pallet_job->rest_Pallet = 1; //그 때의 pallet은 사용가능

			for(j=0 ; j < temp_cell_job->Job->Pallet_job->Num_Fixt ; j++)
			{
				temp_cell_job->Job->Pallet_job->Fixture[j]->rest_Fixture = 1; // 그때 pallet의 fixture는 사용가능
			}

			b++;
			//cout << " Job 종료된 b가 몇개냐 ? : " << b << endl;
			//cout << " Job 종료된거 어떤거냐 ? : " << temp_cell_job->Job->Job_No << endl;
			for(i=0; i<temp_cell_job->Job->Pallet_job->Num_Fixt ; i++)
				{
					if(temp_cell_job->Job->P[i]!=NULL)
					{
						temp_cell_job->Job->P[i]->Terminated = 1;
						input_Last_to_Queue(Dummy,temp_cell_job->Job->P[i]);  //  job이 다 끝났다면 그때의 P는 dummy로 간다
					
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
	int due; //due date 맞출려면 같은 번호가 와야됨


	//cout << "여기 들어오냐 ?? " << endl;

	CJ_Temp = Dummy->Head->next;



	while(CJ_Temp != Dummy->Tail) //언로딩 체크
	{
		next_part = 100000000; //아무값 지정
		
		
		if(CJ_Temp->Part->Terminated == 1) //끝났으면 빠져 나가고 삭제
		{
			//cout << " CJ_Temp- > part 의 종료시간 : " << CJ_Temp->Part->completion_time << endl << endl;
			if(J[CJ_Temp->Part->Job_No].Completion_time == Time)
			{
				if(CJ_Temp->Part->PT->Pre_part == -1)
				{
					next_part = CJ_Temp->Part->PT->Job_ID; //끝난 part의 part type정보 저장
					due = CJ_Temp->Part->Due_date;

					//cout << "                                                                    1이 때의 part type? : " << CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "                                                                    1이 때의 part 번호? : " << CJ_Temp->Part->Part_No << endl;

					//cout << "없어지는 Parttype : "<< CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "없어지는 Part 번호 : "<< CJ_Temp->Part->Part_No<< endl;
					//cout << "next Part다 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! : "<< next_part << endl;

					//cout << "1111111111111111111111111111111 Dummy length : " << Dummy->Length << endl;

					temp_loading = System->Head->next;
					while(temp_loading != System->Tail)
					{
						if(temp_loading->Part->PT->Pre_part == next_part && temp_loading->Part->Due_date == due) 
						{
							//cout << "들어오는 Parttype : "<< temp_loading->Part->PT->Job_ID << endl;
							//cout << "들어오는 Part 번호 : "<< temp_loading->Part->Part_No<< endl;
		
							input_Last_to_Queue(Dummy,temp_loading->Part); // 그떄의 dependecy part를 laoding dummy에 넣는다
						
							temp_loading->next->pre = temp_loading->pre;
							temp_loading->pre->next = temp_loading->next;//선택된 part는 queue에서 사라진다 

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
					//cout << "                                                                    2이 때의 part type? : " << CJ_Temp->Part->PT->Job_ID << endl;
					//cout << "                                                                    2이 때의 part 번호? : " << CJ_Temp->Part->Part_No << endl;
					//cout << "                                                                    2이 때의 Job 번호? : " << CJ_Temp->Part->Job_No<< endl;
				
					//cout << " 일루 ??????????????????" << endl; 
					CJ_Temp->next->pre = CJ_Temp->pre;
					CJ_Temp->pre->next = CJ_Temp->next;
			

					delete CJ_Temp;
					Dummy->Length --;
				}

			
			//cout << "3333333333333333333333333333 Dummy length : " << Dummy->Length << endl;

			a++;

			//cout <<"시뮬레이션 속 dummy 개수 : " << a << endl;
			CJ_Temp = Dummy->Head->next;

			//cout << "======================================================Dummy length : " << Dummy->Length << endl;

			EV = 1;
			continue;
			}
		}
		
		//cout << "next Part다 222222222222222222 : "<< next_part << endl;

		//if(CJ_Temp->Part->release_time <= Time) //로딩 체크 다음 로딩 할 것들로!
		


		CJ_Temp = CJ_Temp->next;
	}
	
	//cout << " dummy lenght다 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ : "  << Dummy->Length << endl; 
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
		//cout << "여기 ~~~~~~~~~~~~~~~~~비어있을때 한번" << endl;
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
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
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
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
		{		
			if( min > temp->Job->Processing_time[temp->Job->current_position])
			{
				temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
				min = temp->Job->Processing_time[temp->Job->current_position]; // 그때의 job의 processing time이 min 값이 된다
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

	while(temp != Job_queue->Tail) // 여기서 dependent part가 있는지 찾는다 있으면 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job들이 있는 queue에서 프로세스 가능한 job들 중에서
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // 그 Job에 올라간 part들을 검색
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part들 중에 pre part가 -1 이면 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job의 prepart가 올라가 있다는 뜻
					}
				}


			}
			
		}
		temp = temp->next;
	}



	temp = Job_queue->Head->next;



	while(temp != Job_queue->Tail)
	{

		if( count == 1) // dependent part가 있는 job끼리 먼저 SPT로 비교
		{
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > temp->Job->Processing_time[temp->Job->current_position])
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = temp->Job->Processing_time[temp->Job->current_position]; // 그때의 job의 processing time이 min 값이 된다
				}
			}
		}
		else // dependent part가 없는 job들만 SPT로 비교
		{
			//cout << " 여기는 들어오면 안된다 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > temp->Job->Processing_time[temp->Job->current_position])
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = temp->Job->Processing_time[temp->Job->current_position]; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
		{		
			if( max < temp->Job->TWKR)
			{
				temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
				max = temp->Job->TWKR; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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

	while(temp != Job_queue->Tail) // 여기서 dependent part가 있는지 찾는다 있으면 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job들이 있는 queue에서 프로세스 가능한 job들 중에서
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // 그 Job에 올라간 part들을 검색
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part들 중에 pre part가 -1 이면 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job의 prepart가 올라가 있다는 뜻
					}
				}


			}
			
		}
		temp = temp->next;
	}


	temp = Job_queue->Head->next;

		
	while(temp != Job_queue->Tail)
	{

		if( count == 1) // dependent part가 있는 job끼리 먼저 SPT로 비교
		{
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( max < temp->Job->TWKR)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					max = temp->Job->TWKR; // 그때의 job의 processing time이 min 값이 된다
				}
			}
		}
		else // dependent part가 없는 job들만 SPT로 비교
		{
			//cout << " 여기는 들어오면 안된다 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;
			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( max < temp->Job->TWKR)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					max = temp->Job->TWKR; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
		{		
			if( min > v)
			{
				temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
				min = v; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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

	while(temp != Job_queue->Tail) // 여기서 dependent part가 있는지 찾는다 있으면 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job들이 있는 queue에서 프로세스 가능한 job들 중에서
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // 그 Job에 올라간 part들을 검색
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part들 중에 pre part가 -1 이면 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job의 prepart가 올라가 있다는 뜻
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

		if( count == 1) // dependent part가 있는 job끼리 먼저 SPT로 비교
		{
			v = temp->Job->avg_duedate - Time - temp->Job->TWKR;

			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = v; // 그때의 job의 processing time이 min 값이 된다
				}
			}
		}
		else // dependent part가 없는 job들만 SPT로 비교
		{
			//cout << " 여기는 들어오면 안된다 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			v = temp->Job->avg_duedate - Time - temp->Job->TWKR;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = v; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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
		//cout << " 이때의 Time + temp 값 : " << Time + temp->Job->TWKR << endl << endl;

		if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
		{		
			if( min > v)
			{
				temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
				min = v; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " 이때의 mdd 값 : " << min << endl << endl;
		
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

	while(temp != Job_queue->Tail) // 여기서 dependent part가 있는지 찾는다 있으면 1
	{
		if(temp->Job->current_state == 0 && temp->Job->Terminate != 1) // job들이 있는 queue에서 프로세스 가능한 job들 중에서
		{
			for(i=0 ; i < temp->Job->Num_parts ; i++) // 그 Job에 올라간 part들을 검색
			{

				if( temp->Job->P[i]!= NULL)
				{
					if(temp->Job->P[i]->PT->Pre_part == -1) // part들 중에 pre part가 -1 이면 
					{
						count = 1;
						temp->Job->Dependent_part = 1; // job의 prepart가 올라가 있다는 뜻
					}
				}


			}
			
		}
		temp = temp->next;
	}


	temp = Job_queue->Head->next;


	while(temp != Job_queue->Tail)
	{
		
		if( count == 1) // dependent part가 있는 job끼리 먼저 SPT로 비교
		{
			v = max((int)temp->Job->avg_duedate, Time + temp->Job->TWKR);

			//cout << temp->Job->Job_No << " : " << temp->Job->Current_Process_Standard_Time + Time << " , " << Next_Rest_Time << endl;

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1 && temp->Job->Dependent_part == 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = v; // 그때의 job의 processing time이 min 값이 된다
				}
			}
		}
		else // dependent part가 없는 job들만 SPT로 비교
		{
			//cout << " 여기는 들어오면 안된다 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
			v = max((int)temp->Job->avg_duedate, Time + temp->Job->TWKR);

			if(temp->Job->Processing_time[temp->Job->current_position] + Time <= Next_Rest_Time && temp->Job->current_state==0 && temp->Job->Machine_Route[temp->Job->current_position] == M && temp->Job->Terminate != 1) 
			//current state가 0이고 지금 할 operation의 processing time이 machine의 next_rest_time을 안넘을고 그때의 route의 machine과 M machine이 같을때
			{		
				if( min > v)
				{
					temp_Job = temp->Job; // 그때의 job이 temp_job이 된다
					min = v; // 그때의 job의 processing time이 min 값이 된다
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
		//cout << " dispatching 되는 job의 번호 : " <<  temp_Job->Job_No << endl;
		//cout << " dispatching 되는 job의 pallet  : " <<  temp_Job->Pallet_job->Pallet_index << endl;
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
	
	temp->Job = J; //그때의 job
	temp->Part = J->Part_Route[J->current_position]; // 그대의 part
	
	temp->next = temp2;
	temp->pre = temp2->pre;
	
	temp->pre->next = temp;
	temp2->pre = temp;
	
	JL->Length ++;

	//cout << " machine list에 들어온 job part의 completion time : " << J->Current_Process_Completion_time << endl ;

	temp->operation = J->OP_Route[J->current_position] ; // 그때의 operation이 뭔지 
	temp->start_time = J->Current_Process_Completion_time - J->Processing_time[J->current_position]; //그때의 시작시간
	temp->ending_time = J->Current_Process_Completion_time; //그때의 끝나는 시간
	temp->PID = J->Part_Route[J->current_position]->PT->PID[J->OP_Route[J->current_position]]; //확인 필요!  그때의 process 이름!
	
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
