#include<iostream>
#include<conio.h>
using namespace std;
int que[10][2], curr = 0, cnt = 0;

void sort_pid(int PID[], int FT[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (PID[j] < PID[min_idx]) 
			{
				min_idx = j;
			}

		}
		if (min_idx != i)
		{
			swap(PID[min_idx], PID[i]);
			swap(FT[min_idx], FT[i]);
		}
	}
}

void add_queue(int PID[], int AT[])
{
	if (cnt == 0)
		curr = AT[0];
	que[cnt][0] = PID[0];
	que[cnt][1] = curr;
	cnt++;
}

void sort_AT(int AT[], int BT[], int PID[], int FT[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (AT[j] == curr && curr != 0)
			{
				if (AT[j] <= AT[min_idx])
				{
					min_idx = j;
				}
			}
			else
			{
				if (AT[j] < AT[min_idx])
				{
					min_idx = j;
				}

			}
		}
		if (min_idx != i)
		{
			swap(AT[min_idx], AT[i]);
			swap(BT[min_idx], BT[i]);
			swap(PID[min_idx], PID[i]);
			swap(FT[min_idx], FT[i]);
		}
	}
	add_queue(PID, AT);
}

int main()
{
	int n;
	int PID[10], AT[10], BT[10], FT[10], TAT[10], WT[10];
	int temp_AT[10], temp_BT[10], q;
	cout << "Enter the number of processes: ";
	cin >> n;
	cout << "Enter arrival time and burst time respectively: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Process " << i << " ";
		cin >> AT[i] >> BT[i];
		PID[i] = i;
		temp_AT[i] = AT[i];
		temp_BT[i] = BT[i];
	}
	sort_AT(temp_AT, temp_BT, PID, FT, n);

	cout << "Enter quantum time";
	cin >> q;

	while (temp_BT[0] != -1)
	{
		if (temp_AT[0] > curr)
			curr = temp_AT[0];

		if (temp_BT[0] <= q)
		{
			curr += temp_BT[0];
			FT[0] = curr;
			temp_AT[0] = 999;
			temp_BT[0] = -1;
		}
		else
		{
			curr += q;
			temp_AT[0] = curr;
			temp_BT[0] = temp_BT[0] - q;
		}
		sort_AT(temp_AT, temp_BT, PID, FT, n);
	}

	sort_pid(PID, FT, n);

	//calculate TAT and WT
	for (int i = 0; i < n; i++)
	{
		TAT[i] = FT[i] - AT[i];
		WT[i] = TAT[i] - BT[i];
	}
	float avgtat=0, avgwt=0;
	cout << "PID\t|\tAT\t|\tBT\t|\tFT\t|\t|TAT\t|\t|WT\t|\t" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << PID[i] << "\t|\t" << AT[i] << "\t|\t" << BT[i] << "\t|\t" << FT[i] << "\t|\t"
			<< TAT[i] << "\t|\t" << WT[i] << "\t|\t" << endl;
		avgtat += TAT[i];
		avgwt += WT[i];
	}
	cout << "Average TAT " << avgtat / n << endl;
	cout << "Average WT " << avgwt / n << endl;
	_getch();
}