#include<iostream>
#include<conio.h>
using namespace std;
int mat[10][3]; //mat=initial input
int n;   //   n =total number of processes
int FT[10],TAT[10],WT[10];

void display()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << mat[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;
}

void sort_and_swap( )
{
	for (int i = 0; i < n; i++)         //less than equal to n
	{
		for (int j = i + 1; j < n; j++)
		{
			if (mat[j][1] < mat[i][1])
			{
				int temp = 0;
				temp = mat[j][0];
				mat[j][0] = mat[i][0];
				mat[i][0] = temp;

				temp = 0;
				temp = mat[j][1];
				mat[j][1] = mat[i][1];
				mat[i][1] = temp;

				temp = 0;
				temp = mat[j][2];
				mat[j][2] = mat[i][2];
				mat[i][2] = temp;
			}
		}
	}
	display();
}
void calculation()
{
	for (int i = 0; i < n; i++)
	{
		
		if ( i==0 || mat[i][1] > FT[i - 1]) ///arrival time zero 
		{
			FT[i] = mat[i][1] + mat[i][2];   //ft=at+bt
		}
		else
		{
			FT[i] = FT[i-1] + mat[i][2];//ft=finish of prev+bt 
		}
		TAT[i] = FT[i] - mat[i][1]; //tat=ft-at
		WT[i] = TAT[i] - mat[i][2];//wt=tat-bt
	}
}

void display_result()
{
	float avgtat = 0, avgwt = 0;
	cout << "Pid\t|\tAT\t|\tBT\t|\tFT\t|\tTAT\t|\tWT\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		
		cout << "P " << mat[i][0] << "\t|\t" << mat[i][1] << "\t|\t" << mat[i][2] << "\t|\t";
		cout << FT[i] << "\t|\t" << TAT[i] << "\t|\t" << WT[i] << "\t|\t" << endl;
		avgtat += TAT[i];
		avgwt += WT[i];
	}
	cout << "Average Turn Around Time :" << avgtat/n << endl;
	cout << "Average Waiting Time :" << avgwt/n<< endl;
}



int main()
{
	
	cout << "First Come First Serve Scheduling Algorithm"<<endl;
	cout << "Total number of processes: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <=3; j++) 
		{
			if (j == 0)
			{
				mat[i][j] = i;
			}
			if (j == 1)
			{
				cout << "Enter arrival time of  " << i << "th process : ";
				cin >> mat[i][j];
			}
			if (j == 2)
			{
				cout << "Enter burst time of  " << i << "th process : ";
				cin >> mat[i][j];
			}
		}
	}
	display();
	sort_and_swap();
	calculation();
	display_result();
	return 0;
	_getch();
}
