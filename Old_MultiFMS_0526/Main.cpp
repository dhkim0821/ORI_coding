//�����Լ�=====================================================================================================
#include "stdafx.h"
#include "Function.h"

using namespace std;


//����� ������ �ٲٱ����� �ϵ�� �����κ� ������Ͽ��� ã�Ƽ� �����Ұ�
int _tmain(int argc, _TCHAR* argv[])
{

	time_t Begin, End;
	double Duration;

	Initialize System;
	System.InputData(argc, &argv[0]);

	Algorithm SimulStart;
	Begin = clock();
	SimulStart.Palletizing(System); //Palletizing���� simulation start


	End = clock();
	Duration = float(End - Begin) / CLOCKS_PER_SEC;;
	cout << "==========================================================" << endl;
	cout << "CPU time: " << Duration << endl;

	return 0;

}




