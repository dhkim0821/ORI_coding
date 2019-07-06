
#include "Stdafx.h"
#include "Function.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	ifstream fin(argv[1]); //file input

	time_t begin, end;
	double duration;

	ofstream fout(argv[2]);


	
	int i,j,k;

	int a;

	int Num_machine;
	int Num_parttype;
	int Num_pallet;
	int Num_operation;
	int Num_fixturetype;
	int Num_Rmc =0 ;
	int Num_Parts; //total number jobs
	//int Num_loading_part = 4; // 몇개의 part를 pallet에 올릴것인지

	/* 
	int Input_Sequence_Option = 2;
	int Machine_Selection_Option = 1;
	int Job_route_Option = 1;
	int Dispatching_Option = 9;
	*/
	int Input_Sequence_Option = _wtoi(argv[3]);
	int Machine_Selection_Option = _wtoi(argv[4]);
	int Job_route_Option = _wtoi(argv[5]);
	int Dispatching_Option = _wtoi(argv[6]);
	


	int transportation_time;
	int Num_part_dependency ;

	int **Machine_schedule; // 기계 별 유휴시간 
	int Loading_schedule[10000]; // 로딩 언로딩 가능 시간

	int Completion_Time;
	double avr_Flow_Time =0;


	fin >> Num_machine;
	fin >> Num_parttype;
	fin >> Num_pallet;
	fin >> Num_fixturetype;
	fin >> Num_operation;

	fin >> Num_part_dependency ;
	fin >>transportation_time; // 이동 시간



	Machine_schedule = new int *[Num_machine];

	Mac_list * ML = new Mac_list;
	Part_Type_T * PT = new Part_Type_T[Num_parttype];
	Rmc_T * RMC = new Rmc_T[Num_Rmc]; //필요한지 ???
	Part_T * P = new Part_T[Num_parttype * 100000]; //전체 개별 가공품의 갯수 한계

	Job_T * J = new Job_T[Num_pallet * 10000]; // 전체 job의 갯수 한계 (pallet = job)
	int Job_index = 0 ; // Job index 

	Pallet_T * Pallet_type = new Pallet_T[Num_pallet]; 
	Fixture_T * Fixture = new Fixture_T[80];
	//Config * Job_INDEX = new Config[0] ;
	Config * Job_INDEX = new Config ;

	begin = clock();
	
	
	initialize_Job_INDEX(Job_INDEX);

	initialize_Machine_List(&fin, ML, Num_machine, RMC, Num_Rmc, Num_pallet, Pallet_type); //machine 초기화

	initialize_Job_List(&fin, Num_parttype, &Num_Parts, PT, P, ML); // part 초기화




	//cout << " parts 의 개수가 몇개냐 "  << Num_Parts << endl ;

	Queue * System = new Queue; // 모든 part들을 system에 둔다 = Systemp dummy
	Queue * Dummy = new Queue; //모든 part 중에  loading 조건이 되는 part들을  dummy(로딩가능한 part들 두는곳) 에 둔다 = Loading dummy

	Queue_job * Job_queue = new Queue_job; // 사싱살 central buffer 
	
	initialize_Machine_Queue(Dummy);
	initialize_Machine_Queue(System);
	initialize_Joblist_Queue(Job_queue); //사싱살 central buffer 
	
	Cell * temp2 ;

		
	a = initialize_Setting(Num_Parts, P, ML, Dummy, System); //시스템 큐에다가 넣고 로딩 준비된 것만 dummy로 !!

	/*temp2 = Dummy->Head->next;
	k=0;
	while(temp2 != Dummy->Tail)
	{
			cout << k << endl ;
			k++;
			temp2 = temp2->next;
	}*/
	
	//cout << temp2->pre->Part->PT->Job_ID << endl;
	//cout << " ====================================== 초기 dummy length === : " << Dummy->Length << endl;
	//cout << " ====================================== 초기 System length === : " << System->Length << endl;
	
	
	Loading(Pallet_type, P, J, Num_pallet, Dummy, Job_index, Job_queue, Job_INDEX, Machine_Selection_Option, Num_machine, ML, Input_Sequence_Option, Job_route_Option); //로딩 and Job define

	/*temp2 = Dummy->Head->next;
	k=0;

	cout << " ddd2 : " << temp2->Part->PT->Job_ID << endl;
	while(temp2 != Dummy->Tail)
	{
			cout << k << endl ;
			k++;
			temp2 = temp2->next;
	}*/



	/*for(i=0 ; i<Num_Parts ; i++)
	{
		cout<<" P" << i << "의 duedate: " << P[i].Due_date << endl;
	}*/


	//cout << " ====================================== 첫번째 로딩 후  dummy length === : " << Dummy->Length << endl;

	//cout <<"JOB INDEX 입니다 ~~~~~~~~~~~~~~~~~~~~~~~: "<< Job_INDEX->Job_index << endl;
	
	/*
	cout << "Job에 올라오는 part의 수 : " << J[0].Num_parts << endl;
	cout << " Job의 평균 due date : " << J[0].avg_duedate<< endl;

	cout << " Job1의 평균 due date : " << J[0].avg_duedate<< " Job0의 TWKR : " << J[0].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[1].avg_duedate<< " Job1의 TWKR : " << J[1].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[2].avg_duedate<< " Job2의 TWKR : " << J[2].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[3].avg_duedate<< " Job3의 TWKR : " << J[3].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[4].avg_duedate<< " Job4의 TWKR : " << J[4].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[5].avg_duedate<< " Job5의 TWKR : " << J[5].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[6].avg_duedate<< " Job6의 TWKR : " << J[6].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[7].avg_duedate<< " Job7의 TWKR : " << J[7].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[8].avg_duedate<< " Job8의 TWKR : " << J[8].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[9].avg_duedate<< " Job9의 TWKR : " << J[9].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[10].avg_duedate<< " Job10의 TWKR : " << J[10].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[11].avg_duedate<< " Job11의 TWKR : " << J[11].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[12].avg_duedate<< " Job12의 TWKR : " << J[12].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[13].avg_duedate<< " Job13의 TWKR : " << J[13].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[14].avg_duedate<< " Job14의 TWKR : " << J[14].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[15].avg_duedate<< " Job15의 TWKR : " << J[15].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[16].avg_duedate<< " Job16의 TWKR : " << J[16].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[17].avg_duedate<< " Job17의 TWKR : " << J[17].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[18].avg_duedate<< " Job18의 TWKR : " << J[18].TWKR << endl;
	cout << " Job1의 평균 due date : " << J[19].avg_duedate<< " Job19의 TWKR : " << J[19].TWKR << endl;


	cout << " Job4 의 프로세싱타임 " << endl;
	*/
	int sum = 0;
	int pp = 0;
	for(k=0 ; k<J[4].Total_Number_Operation ; k++)
	{
		pp =J[4].Processing_time[k];
		sum = sum+ J[4].Processing_time[k] ;
	}
	/*
	cout << "다 ~ 더한것 : " << sum <<endl;

	cout<< "여기까지" <<endl ;
	cout << " Job1의 current position :" << J[0].current_position << endl;
	cout << " Job2의 current position : " << J[1].current_position << endl;
	cout << " Job3의 current position :" << J[2].current_position << endl;
	cout << " Job4의 current position : " << J[3].current_position << endl;
	cout << " Job5의 current position :" << J[4].current_position << endl;
	cout << " Job6의 current position :" << J[5].current_position << endl;
	cout << " Job7의 current position : " << J[6].current_position << endl;
	cout << " Job8의 current position :" << J[7].current_position << endl;
	cout << " Job9의 current position : " << J[8].current_position << endl;
	cout << " Job10의 current position :" << J[9].current_position << endl;
	cout << " Job11의 current position : " << J[10].current_position << endl;
	cout << " Job12의 current position : " << J[11].current_position << endl;
	*/
	Completion_Time = Simulation_Start(Pallet_type, Num_pallet, Num_Parts, Num_parttype, Num_Rmc, P, J, Job_queue, ML, RMC, Dummy, Machine_Selection_Option, Job_INDEX, Job_index, System, Num_machine, Input_Sequence_Option, Dispatching_Option, Job_route_Option, transportation_time) ;

	//cout << "마지막 프로세싱 타임이다 "<<Job_INDEX->last_processing_time << endl ;
	//cout << "마지막 프로세싱 타임이다 "<<Job_INDEX->last_processing_time  << endl;
	//cout << "이동시간 : " << transportation_time << endl;
	//cout << " 종료시간 : " << Completion_Time << endl;

	Completion_Time = Completion_Time + Job_INDEX->last_processing_time + transportation_time; // 마지막 completion time에다가 마지막 job의 processing time+ transporation time !

	end = clock();

	

	duration = float(end-begin) / CLOCKS_PER_SEC;;

	/*cout << " Job1의 current position :" << J[0].current_position << endl;
	cout << " Job2의 current position : " << J[1].current_position << endl;
	cout << " Job3의 current position :" << J[2].current_position << endl;
	cout << " Job4의 current position : " << J[3].current_position << endl;
	cout << " Job5의 current position :" << J[4].current_position << endl;
	cout << " Job6의 current position :" << J[5].current_position << endl;
	cout << " Job7의 current position : " << J[6].current_position << endl;
	cout << " Job8의 current position :" << J[7].current_position << endl;
	cout << " Job9의 current position : " << J[8].current_position << endl;
	cout << " Job10의 current position :" << J[9].current_position << endl;
	cout << " Job11의 current position : " << J[10].current_position << endl;
	cout << " Job12의 current position : " << J[11].current_position << endl;

	cout << " System Queue의 length :" << System->Length << endl;
	*/
	
	//cout << " ===================================================== 여기까지 완료 ================================ " << endl;



	/*cout << Num_machine << " " ;
	cout << Num_parttype << " " ;
	cout << Num_pallet << " " ;
	cout << Num_fixturetype<< " " ;
	cout << Num_operation << " " ;

	cout << endl;

	cout << transportation_time << " " ; 
	

	cout << endl;
	
	
	Cell_machine * temp = new Cell_machine;
	temp = ML->head;
	for(i=0;i<Num_machine;i++)
	{	
		temp = temp->next;
		cout << temp->Mac->Machine_Name << " " ;
	}
	
	cout << endl;

	temp = ML->head;
	for(i=0;i<Num_machine;i++)
	{	
		temp = temp->next;
		cout << temp->Mac->release_time << " " ;
	}
	
	cout << endl;

	temp = ML->head;
	for(i=0;i<Num_machine;i++)
	{
		temp = temp->next; 
		cout << temp->Mac->Machine_No << " " ;
	
	}

	cout << endl << endl;

	*/
	/*
	for(i=0 ; i<Num_Parts ; i++)
	{
		cout<<" P" << i << "의 duedate: " << P[i].Due_date << endl;
	}
	

	for(i=0;i<Num_pallet;i++)
	{
	
		cout << endl;
		cout << Pallet_type[i].Num_Fixt << " "; 
		
	
		for(j=0;j<Pallet_type[i].Num_Fixt;j++)
		{
			
			//cout << Pallet_type[i].Fixture[j].number_Fixture << " " ;
			cout << Pallet_type[i].Fixture[j]->fixture_no << " " ;// 어떤 fixture 번호인지 
			//cout << Pallet_type[i].Fixture[j].rest_Fixture ;
		//	cout << t2 << endl;
		}
	}*/


	/*
	cout << endl << endl;


	temp = ML->head;
	temp = temp->next;
	for(i=0;i<41;i++)
	{
		cout << temp->Mac->Machine_Schedule[i] << " " ;
	}
	
	cout << endl << endl; 


	for(i=0;i< 3;i++)
	{
		cout <<PT[i].Job_ID   << " " ;
		cout << PT[i].Fixture_Type  << " " ;
		cout <<PT[i].release_time  << " " ;
		cout <<PT[i].demand   << " " ;
		
		cout <<PT[i].Due_Date  << " " ;
		cout <<PT[i].Num_Operation << " " ;
		cout <<PT[i].Pre_part  << " " ;

		cout << endl;
		for(j=0; j<PT[i].Num_Operation ;j++)
		{
			
			cout << PT[i].PID[j] << " "; //Operation 이름 받기
		}

		cout << endl;

		for(j=0;j<PT[i].Num_Operation;j++)
		{
			
			for(k=0;k<PT[i].Num_Operation;k++)
			{
				cout << PT[i].Process_Plan[j][k] << " " ;	 // 프로세스 플랜 행렬 받기			
			}
			cout << endl;
		}
		

		cout << endl ;

	}
	    cout << PT[0].Fixture_Type;
		cout << endl;
		cout << PT[1].Fixture_Type;
		cout << endl;
		cout << PT[0].Num_Alternative_Machine[2] << " " ;
		cout << PT[1].Num_Alternative_Machine[2] << " " ;
		cout << PT[2].Num_Alternative_Machine[2] << " " ;
		cout << PT[5].Num_Alternative_Machine[2] << " " ;
		
		cout << endl;	
		cout <<	PT[1].Alterntive_Machine_Name[1][0] << endl ;
		cout <<	PT[2].Alterntive_Machine_Name[2][0] << endl ;
		cout <<	PT[3].Alterntive_Machine_Name[1][0] << endl ;
		

		cout << PT[0].Standard_Time[1][0] << endl;
		cout << PT[2].Standard_Time[1][0] << endl;
		
		

		//cout << P->Mac_Select[0]; // Machine_T로 받고
		//cout << P[0].Mac_Select_index[0] ; //Machie number(index)로 받고
		//cout << P[0].Select_Process_Time[0] ; 
		
		cout << endl << endl;

		cout << P[0].PT->Job_ID << endl;
		cout << P[0].PT->release_time << endl;
		cout << P[0].PT->Num_Operation << endl;

		cout << endl;
		cout << P[0].Mac_Select_index[0] << endl;
		cout << P[0].Mac_Select_index[1] << endl;
		cout << P[0].Mac_Select_index[2] << endl;
		cout << P[0].Mac_Select_index[3] << endl;
		
		cout << endl;
		cout << P[0].Select_Process_Time[0] << endl;
		cout << P[0].Select_Process_Time[1] << endl;
		cout << P[0].Select_Process_Time[2] << endl;
		cout << P[0].Select_Process_Time[3] << endl;
		cout << endl;

		cout << endl;
		cout << P[1].Select_Process_Time[0] << endl;
		cout << P[1].Select_Process_Time[1] << endl;
		cout << P[1].Select_Process_Time[2] << endl;
		cout << P[1].Select_Process_Time[3] << endl;
		cout << endl;

		cout << endl;
		cout << P[11].Select_Process_Time[0] << endl;
		cout << P[11].Select_Process_Time[1] << endl;
		cout << P[11].Select_Process_Time[2] << endl;
		cout << P[11].Select_Process_Time[3] << endl;
		cout << endl;

		cout << P[0].PT->Num_Alternative_Machine[3] << endl; 


		int h;
		int b;
		for(h=0 ; h<P[0].PT->Num_Operation ; h++)
		{
			for(b=0 ; b<P[0].PT->Num_Alternative_Machine[h] ; b++) 
			{
				cout << P[0].PT->Alterntive_Machine_Name[h][b] << " " ;
				cout << P[0].PT->Standard_Time[h][b] << endl ;
			}
		}


		cout << endl; 
		cout << P[1].ATWK << endl; 
		cout << P[1].Total_Processing_Time <<endl;
		cout << P[30].Total_Processing_Time << endl;
		cout << P[37].Total_Processing_Time << endl;

		cout << J[0].Total_Number_Operation ;

		cout << endl << endl;

		cout << Job_INDEX->Job_index << endl << endl;

		
		
		for(i=0 ; i < Job_INDEX->Job_index ; i++)
		{
			if(J[i].Empty==0)
			{
				cout << J[i].Job_No << endl;
				cout << J[i].Total_Number_Operation << endl;
				cout << J[i].Pallet_job->Pallet_index << endl;
				cout << J[i].Pallet_job->Num_Fixt << endl;
				cout << J[i].Num_parts << endl;
			

				for(b=0 ; b < J[i].Pallet_job->Num_Fixt ; b++)
				{
					if( J[i].P[b]!= NULL)
					{
						cout << J[i].P[b]->Total_Processing_Time << endl;
					}
				}

			}
			cout << endl;
		}

		
		k=0;
	

		temp2 = Dummy->Head->next;

		while(temp2 != Dummy->Tail)
		{
			cout << k << endl ;
			k++;
			temp2 = temp2->next;
		}

		//cout << J[0].P[0]->Part_No<< endl;
		//cout << J[0].P[1]->Part_No<< endl;
		//cout << J[0].P[2]->Part_No<< endl;
		//cout << J[0].P[3]->Part_No<< endl;

		cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl;

		for ( b=0; b < Num_Parts ; b++ )
		{
			cout << P[b].PT->Job_ID << " " ;
			cout << P[b].Part_No << endl;
		}


		cout << endl;




		*/
		/*int b;
		for(i=0 ; i < Job_INDEX->Job_index ; i++)
		{
			if(J[i].Empty==0)
			{

				for(b=0 ; b < J[i].Pallet_job->Num_Fixt ; b++)
				{
					if( J[i].P[b]!= NULL)
					{
						cout << " Part type : " << J[i].P[b]->PT->Job_ID << " part 번호 :" << J[i].P[b]->Part_No << endl;
						cout << " pallet 번호 : " << J[i].Pallet_job->Pallet_index << endl;
						cout << " Job 번호 : " << J[i].P[b]->Job_No << endl << endl;
					}
				}

			}
			cout << endl;
		}*/

		/*
		cout << J[0].Num_parts << endl;
		
		//cout << J[0].Current_OP_Position[2] << endl;
		cout << endl;

		for(i=0;i<P[0].PT->Num_Operation;i++)
		{
			if( P[0].Mac_Select_name[i] != NULL)
			{
				cout << P[0].Mac_Select_name[i] ;
				cout << " i = " << i << endl;
			}
		}




		for(i=0 ; i < Job_INDEX->Job_index ; i++)
		{
			if(J[i].Empty==0)
			{
			
				for(b=0 ; b < J[i].Pallet_job->Num_Fixt ; b++)
				{
					if( J[i].P[b]!= NULL)
					{
						cout << J[i].P[b]->PT->release_time<<endl;
						for(j=0 ; j < J[i].P[b]->PT->Num_Operation ; j++)
						{
							if( J[i].P[b]->Mac_Select_name[j] != NULL)
							{
								cout << J[i].P[b]->Mac_Select_name[j] << endl;
							}
						}
					}
				}

			}
			cout << endl;
		}


	for(i=0 ; i < J[14].Pallet_job->Num_Fixt ; i++)
	{
		if(J[14].P[i] != NULL)
		{
			cout << "text : " << J[14].P[i]->PT->Job_ID << " " ;
			cout << i << endl;
		}
	}

	cout << J[14].Total_Number_Operation << endl;
	

	*/
	
	/*
	for(i=0 ; i < Job_INDEX->Job_index ; i++)
	{
		for(j=0 ; j < J[i].Total_Number_Operation ; j++)
		{
			cout << "JOb" << i <<"의 Part type : "<<J[i].Part_Route[j]->PT->Job_ID << endl ;
			cout << "JOb" << i <<"의 part Number: "<<J[i].Part_Route[j]->Part_No << endl ;
			cout << "JOb" << i << "의 op rout : "<<J[i].OP_Route[j] << endl;;
			cout << "JOb" << i <<"의 machinename : "<<J[i].Machine_name[j] << endl;
			cout << "JOb" << i <<"의 Processing time : "<<J[i].Processing_time[j] << endl;
		}
		cout << "JOb" << i <<"의 Total machine movement : "<<J[i].Total_movement << endl;
		cout << endl;
	}
	*/
		

	
		cout << endl << endl; 

     /*
		cout << P[0].PT->Job_ID<< endl;
		

		Cell_job * temptemp;
		temptemp = Job_queue ->Head->next ;
		for( i=0 ; i <Job_queue->Length ; i++)
		{
			cout << temptemp->Job->Job_No << endl;
			temptemp = temptemp->next;
		}*/
		

		cout << "===============================================================================================" << endl;


			int tardy = 0;
			int c;

			if(Completion_Time == -1)
			{
				return -1;
			}

			int Max = 0;
			int N_tardy = 0;
			Cell_machine * Cell_Temp;
	
			for(i=0;i<Num_Parts;i++)
			{
				Cell_Temp = P[i].Machine_Sequence->head->next;
				while(Cell_Temp->next != P[i].Machine_Sequence->tail)
				{
					Cell_Temp = Cell_Temp->next;
				}
				P[i].completion_time = Cell_Temp->End_time;
			}

			for(i=0;i<Num_Parts;i++)
			{
				if(P[i].PT->Pre_part != -1)
				{
					avr_Flow_Time += P[i].completion_time;
					tardy += max( (P[i].completion_time - P[i].Due_date) ,0 );
		
					if(Max < max( (P[i].completion_time - P[i].Due_date) ,0 ))
						Max = max( (P[i].completion_time - P[i].Due_date) ,0 );

					if(max( (P[i].completion_time - P[i].Due_date) ,0 ) != 0)
					{
						N_tardy ++ ;
					}
				}
			}
			double avr_Tardy = tardy / Num_Parts;
			avr_Flow_Time /= Num_Parts;
	
		
			//fout << Completion_Time << endl;
			//fout << avr_Flow_Time << endl;
			//fout << tardy/Num_Jobs << endl;
			//fout << N_tardy << endl;
			//fout << Max << endl;
			//fout << duration << endl;

		
			fout << Completion_Time << " " << tardy << " " <<  duration << endl;
		
			//file stream out	
			/* 
			fout << "Part Input Sequencing Option : " << Input_Sequence_Option << endl;
			fout << "Machine Selection Option : " << Machine_Selection_Option << endl;
			fout << "Job routing Option : " << Job_route_Option << endl;
			fout << "Dispatching Option : " << Dispatching_Option << endl;
			fout << "Makespan : " << Completion_Time << endl;
			fout << "Average Flow Time : " << avr_Flow_Time << endl;
			fout << "Algorithm Elapsed Tme : " << duration << endl;
			fout << "Tardiness : " << tardy << endl;
			fout << " Number of Machine : " << Num_machine << endl;
			fout << " Number of part type : " << Num_parttype << endl;
			fout << " Number of Pallets : " << Num_pallet << endl;
			fout << " Total number of parts : " << Num_Parts << endl;
			fout << " Number of part dependent : " << Num_part_dependency << endl;
			fout << "Number of tardy parts : " << N_tardy << endl;
			fout << "Maximum Tardiness : " << Max << endl;

			fout << "Part type - dependency : " ;
		
			for(i=0;i<Num_parttype;i++)
			{
				if(PT[i].Pre_part == -1)
				{
					fout <<PT[i].Job_ID <<  "-" ;

					for(j=0;j<Num_parttype;j++)
					{
						if(PT[j].Pre_part == PT[i].Job_ID)
						{
							fout << PT[j].Job_ID << ", " ;
						}
					}

				}
			}
		
			fout << endl << endl;
		*/
	
		//gantt-chart out
			/* 
			fout << "Job focused Gantt-Chart" << endl;
			for(i=0;i<Num_Parts;i++)
			{
		
				fout <<P[i].PT->Job_ID << "-" << P[i].Part_No << " : ";
		

				Cell_Temp = P[i].Machine_Sequence->head->next;
		
				while(Cell_Temp != P[i].Machine_Sequence->tail)
				{
					fout << "(" << Cell_Temp->Mac->Machine_Name << ",";
					fout << Cell_Temp->PID << ",";
					fout << Cell_Temp->Start_time << "," ;
					fout << Cell_Temp->End_time << "),"  ;
				
					Cell_Temp = Cell_Temp->next;
				}
			
				fout << " Due-Date : " << P[i].Due_date << ", ";
				fout << " Completion time : " << P[i].completion_time << ", ";
				fout << " Tardiness : " << max( (P[i].completion_time - P[i].Due_date) ,0 );
				fout << endl;
			}
			*/

		// Machine sequence
			/* 
			fout << endl << "Machine focused Gantt-Chart" << endl;
			Machine_T * Mac;
			Cell_job * JS;
			*/

		/*for(i=0;i<num_Rmc;i++)
		{
			Mac = RMC[i].Loading_ST;
			fout << "RMC" << i+1 << " Loading Station : ";
			JS = Mac->Job_Sequence->Head->next;
			while(JS != Mac->Job_Sequence->Tail)
			{
				fout << "(" << JS->Job->JT->Job_ID << "-" << JS->Job->Job_No << "," << JS->PID << "," << JS->start_time << "," << JS->ending_time << "), ";
				JS = JS->next;
			}
			fout << endl;

			Mac = RMC[i].Unloading_ST;
			fout << "RMC" << i+1 << " Unloading Station : ";
			JS = Mac->Job_Sequence->Head->next;
			while(JS != Mac->Job_Sequence->Tail)
			{
				fout << "(" << JS->Job->JT->Job_ID << "-" << JS->Job->Job_No << "," << JS->PID << "," << JS->start_time << "," << JS->ending_time << "), ";
				JS = JS->next;
			}
			fout << endl;
	
		}*/

			/* 
			Cell_Temp = ML->head->next;
			while(Cell_Temp != ML->tail)
			{
				fout << Cell_Temp->Mac->Machine_Name << " : ";
				JS = Cell_Temp->Mac->Job_Sequence->Head->next;
				while(JS != Cell_Temp->Mac->Job_Sequence->Tail)
				{
					fout << "(" << JS->Part->PT->Job_ID << "-" << JS->Part->Part_No << "," << JS->PID << "," << JS->start_time << "," << JS->ending_time << "), ";
					JS = JS->next;
				}
				fout << endl;
				Cell_Temp = Cell_Temp->next;
			}

			fout << endl;
			fout << endl << "생성된 Job 정보" << endl;

			for(i=0 ; i < Job_INDEX->Job_index ; i++)
			{
				fout << " Job " << i << " : " ;
				if(J[i].Empty==0)
				{

					for(c=0 ; c < J[i].Pallet_job->Num_Fixt ; c++)
					{
						if( J[i].P[c]!= NULL)
						{
							fout << "(" <<J[i].P[c]->PT->Job_ID << "-" << J[i].P[c]->Part_No  <<")," ;
						}
					}

				}
				fout << endl;
			}
			*/

			fin.close();
			fout.close();

			return 0;
		

		
		
}


