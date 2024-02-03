#include<iostream>
#include<conio.h>
using namespace std;
int pro, res;
int alloc[10][10], maxx[10][10], avail[10], need[10][10];
int work[10], temp_work[10];  //tempwork created to check with work matrix if there is a change
bool finish[10];
int safeseq[10], safeseqcnt=0;//to keep track of safe sequence
int reqpro, reqvec[10]; //handling request variables

void allfinish() //print of safe sequence
{
	int unsafe = 0;
	for (int i = 0; i < pro; i++)
	{
		if (finish[i] == false) // by checking finsh flag condition
		{
			unsafe = 1;
			break;
		}
	}
	if (unsafe == 1)
	{
		cout << "Resource was not granted"<<endl;
	}
	else
	{
		cout << "Resource is granted"<<endl;
		cout << "Safe sequence is " << endl;
		cout << " < ";
		for (int i = 0; i < pro; i++)
		{
			cout << "P " << safeseq[i] << " ";
		}
		cout << " > "<<endl;
	}
}
bool checkrequest() //check if request will be granted or no by checking with need and available
{
	for (int i = 0; i < res; i++) //one loop
	{
		if (reqvec[i] > need[reqpro][i] || reqvec[i] > avail[i])
		{
			return false;
		}
	}
	return true;
}

void safety()      //to check if system is safe
{
	
	//all finish flag to false
	for (int i = 0; i < pro; i++)
	{
		finish[i] = false;
	}
	//checking the need<=work
	while (1)
	{
		for (int i = 0; i < pro; i++)
		{
			if (finish[i] == false)
			{
				int flag = 0;
				for (int j = 0; j < res; j++)
				{
					if (need[i][j] > work[j])
					{
						flag = 1;
						break;
					}
				}
				// condition of need<=work is satisfied
				if (flag == 0)
				{
					finish[i] = true;      //update finsh matrix
					for (int j = 0; j < res; j++)
					{
						work[j] = work[j] + alloc[i][j]; //update work matrix
					}
					safeseq[safeseqcnt++] = i; //keep track of safe sequence
				}
			}
		}

		int check = 0; //to check if there is any update of work matrix by comparing with temp_work matrix
		for (int i = 0; i < res; i++)
		{
			if (temp_work[i] != work[i])
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			for (int i = 0; i < res; i++)
			{
				temp_work[i] = work[i];
			}
		}
		else
		{
			break;
		}

	}
	allfinish(); //printing safe sequence
}

int main()
{
	cout << "Enter number of processes: ";
	cin >> pro;
	cout << "Enter number of resources: ";
	cin >> res;
	//allocation matrix 2D
	cout << "Emter allocation matrix" << endl;
	for (int i = 0; i < pro; i++)
	{
		for (int j = 0; j < res; j++)
		{
			cin >> alloc[i][j];
		}
	}
	//max matrix 2D
	cout << "Emter max matrix" << endl;
	for (int i = 0; i < pro; i++)
	{
		for (int j = 0; j < res; j++)
		{
			cin >> maxx[i][j];
		}
	}
	//available matrix 1D
	cout << "Emter available matrix" << endl;
	for (int i = 0; i < res; i++)
	{
		cin >> avail[i];
		work[i] = avail[i];
		temp_work[i] = avail[i];
	}
	//need matrix 2D
	for (int i = 0; i < pro; i++)
	{
		for (int j = 0; j < res; j++)
		{
			need[i][j] = maxx[i][j] - alloc[i][j];
		}
	}
	safety();

	int choice ;
	do  //requsting resource
	{
		cout << "Enter the request for process ";
		cin >> reqpro;
		cout << "Enter the request for resource ";
		for (int i = 0; i < res; i++)
		{
			cin >> reqvec[i];
		}
		if (checkrequest())
		{
			for (int i = 0; i < res; i++) //assign the new request
			{
				avail[i] -= reqvec[i];
				need[reqpro][i]-= reqvec[i];
				alloc[reqpro][i]+= reqvec[i];
			}
			safety();
		}
		else
		{
			cout << "Cannot be granted" << endl;
		}

		cout << "Do you want to continue ? (1/0)";
		cin >> choice;
	} while (choice != 0);
}