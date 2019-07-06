
#pragma once

#include "stdafx.h"

using namespace std;

void initialize_Machine_List(ifstream * in, Mac_list * ML, int Num_Mac, Rmc_T * Rmc, int Num_Rmc);




void initialize_Machine_List(ifstream * in, Mac_list * ML, int Num_Mac, Rmc_T * Rmc, int Num_Rmc)
{
	int * int_temp = new int[10000];

	int i;

	Cell_machine * temp = new Cell_machine;
	Cell_machine * temp2 = new Cell_machine;
	ML->head = temp;
	ML->tail = temp2;
	temp->next = temp->pre = temp2;
	temp2->next = temp2->pre = temp;
	ML->length = 0;

	Machine_T * temp_Mac;
	

	for(i=0;i<Num_Rmc;i++)
	{
		Rmc[i].Fixture = new Fixture_T;
		Rmc[i].Rmc_No = i+1;
		Rmc[i].RMC_Q = new Queue;
		//initialize_Machine_Queue(Rmc[i].RMC_Q);
		Rmc[i].Loading_ST = new Machine_T;
		Rmc[i].Unloading_ST = new Machine_T;

		Rmc[i].Loading_ST->Machine_Name = new char[30];
		sprintf(Rmc[i].Loading_ST->Machine_Name, "RMC%d Loading", i+1);
		
		Rmc[i].Unloading_ST->Machine_Name = new char[30];
		sprintf(Rmc[i].Unloading_ST->Machine_Name, "RMC%d UnLoading", i+1);

		Rmc[i].Loading_ST->Job_Sequence = new Job_List;
		//initialize_Job_List(Rmc[i].Loading_ST->Job_Sequence);

		Rmc[i].Unloading_ST->Job_Sequence = new Job_List;
		//initialize_Job_List(Rmc[i].Unloading_ST->Job_Sequence);
	}

	for(i=0;i<Num_Mac;i++)
	{	
		temp_Mac = new Machine_T;

		temp_Mac->Current_Job_End_Time = -1;
		temp_Mac->Current_Job_Start_Time = -1;
		temp_Mac->Current_State = 0;
		temp_Mac->idle_time = 0;
		temp_Mac->Total_Working_Time = 0;

		temp_Mac->Job_Sequence = new Job_List;
		//initialize_Job_List(temp_Mac->Job_Sequence);
		
		
		//temp_Mac->Machine_Name = new char[100];
		//*in >> temp_Mac->Machine_Name; // Mahine 이름 안받는다
		//input_Last_to_Machine_List(ML,temp_Mac);
	}


	temp = ML ->head;


	for(i=0;i<Num_machine;i++)
	{	
		temp = temp->next;
		temp->Mac->Machine_Queue = new Queue;
		//initialize_Machine_Queue(temp->Mac->Machine_Queue);
		*in >>temp->Mac->release_time;
	}

	temp = ML->head;


	for(i=0;i<Num_Machine;i++)
	{
		temp = temp->next;
		*in >> temp->Mac->i+1; 
	//	cout << temp->Mac->Rmc_No << endl;
	}

	
}