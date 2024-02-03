#include<iostream>
#include<conio.h>
using namespace std;
int n;
int PID[10], AT[10], BT[10], FT[10], TAT[10], WT[10];

void swapp(int i,int j)
{
	swap(AT[i], AT[j]);   //built in function
	swap(BT[i], BT[j]);
	swap(PID[i], PID[j]);
}

void sortAT(int start)
{
	for (int i = start; i < n - 1; i++)
	{
		int min_idx = i; //using minimum index instead of i , later used for swapping

		for (int j = i + 1; j < n; j++) 
		{
			if (AT[j] == AT[min_idx])   //min_idx //if arival time is equal
			{
				if (BT[j] < BT[min_idx]) //min_idx //sort according to bt
				{
					min_idx = j;
				}
			}
			else if (AT[j] < AT[min_idx])
			{
				min_idx = j;
			}
		}
		if (min_idx != i)
		{
			swapp(min_idx, i);
		}
	}
}

void sort_BT(int i)
{
	int min_bt = 99;
	int min_bti = i + 1;
	int pos = i + 1;
	for (int b = i + 1; b < n; b++) //going through process
	{
		if (AT[b] <= FT[i] && BT[b] < min_bt)  //if arrival time next process <= finish time of current
		{                                 //if whichever process has smallest burst time will go higher 
			min_bti = b;        //minimum burst time index
			min_bt = BT[b];
		}
	}
	if (min_bti != pos)
	{
		swapp(pos, min_bti);
		sortAT(pos + 1);  //then sort according to at 
	}
}

void display()
{
	for (int i = 0; i < n; i++)
	{
		cout << PID[i] << "  " << AT[i] << " " << BT[i] << endl;
	}
	cout << "------------------------" << endl;
}

int main()
{
	cout << "Enter no of processes";
	cin >> n;
	cout << "Enter AT and BT respectively " << endl;
	for (int i = 0; i < n; i++)
	{
		PID[i] = i;
		cout << "Enter AT for " << i << " th process : " ;
		cin >> AT[i];
		cout << "Enter BT for " << i << " th process : " ;
		cin >> BT[i];
	}
	sortAT(0);
	cout << "Sorted acc to AT" << endl;
	display(); 

	FT[-1] = AT[0];
	//calculate
	for (int i = 0; i < n; i++)
	{
		if (AT[i] <= FT[i - 1])  //arival less than equal to ft of prev
		{
			FT[i] = BT[i] + FT[i - 1];  //ft = bt+ft of prev
		}
		else
		{
			FT[i] = BT[i] + AT[i];  //idle time condition
		}
		TAT[i] = FT[i] - AT[i];
		WT[i] = TAT[i] - BT[i];
		sort_BT(i);            //sort acc to bt
		display();
	}

	//printing
	float avgtat=0, avgwt=0;
	cout << "PID\t|\tAT\t|\tBT\t|\tFT\t|\tTAT\t|\tWT\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << PID[i] << "\t|\t" << AT[i] << "\t|\t" << BT[i] << "\t|\t" << FT[i] << "\t|\t"
			<< TAT[i] << "\t|\t" << WT[i] << endl;
		avgtat += TAT[i];
		avgwt += WT[i];
	}
	cout << "Average Turn Around Time is: " << avgtat / n << endl;
	cout << "Average Waiting Time is: " << avgwt / n << endl;
	_getch();
	return 0;
}



