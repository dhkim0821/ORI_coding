//메인함수=====================================================================================================
#include "stdafx.h"
#include "Function.h"

using namespace std;


//실험시 데이터 바꾸기전에 하드로 박은부분 헤더파일에서 찾아서 수정할것
int _tmain(int argc, _TCHAR* argv[])
{

	time_t Begin, End;
	double Duration;

	Initialize System;
	System.InputData(argc, &argv[0]);

	Algorithm SimulStart;
	Begin = clock();
	SimulStart.Palletizing(System); //Palletizing으로 simulation start


	End = clock();
	Duration = float(End - Begin) / CLOCKS_PER_SEC;;
	cout << "==========================================================" << endl;
	cout << "CPU time: " << Duration << endl;

	return 0;

}




