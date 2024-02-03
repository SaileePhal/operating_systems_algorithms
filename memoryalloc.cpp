#include<iostream>
#include<conio.h>
using namespace std;
int h, p;
int holes[10], jobs[10];
void firstfit()
{
	int ho[10], jo[10], cnt[10] = { 0 }; //cnt keeps track if job is assigned/not to any hole

	for (int i = 0; i < h; i++)
	{
		ho[i] = holes[i];
	}
	for (int i = 0; i < p; i++)
	{
		jo[i] = jobs[i];
	}

	int j= 0; // to keep track of holes
	for (int i = 0; i < p; i++)  //keeps track of processes
	{
		while (cnt[i] != h) //until job is equal to some hole
		{
			if (jo[i] <= ho[j])
			{
				cout << "Job " << i << "assigned to " << j << " hole" << endl;;
				ho[j] = ho[j] - jo[i];
				j++;
				j = j % h;
				break;
			}
			else
			{
				j++;
				j = j % h;
				cnt[i]++;
				if (cnt[i] == h) //if count == number of hole its not assigned
				{
					cout << "Process " << i << "has to wait" << endl;
				}
			}
		}
	}
}

void bestfit()
{
	int jo[10], ho[10], bfit[10], bfitcap[10];

	for (int i = 0; i < h; i++)
	{
		ho[i] = holes[i];
	}
	for (int i = 0; i < p; i++)
	{
		jo[i] = jobs[i];
		bfit[i] = -1;          //keeps track ofindex of hole assigned
		bfitcap[i] = 1000;     //helps us to know if process is assigned/not to any hole
	}

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (jo[i] <= ho[j] && ho[j] < bfitcap[i])
			{
				bfit[i] = j;
				bfitcap[i] = ho[i];
			}
		}
		if (bfitcap[i] == 1000)
		{
			cout << "Job " << i << " has to wait " << endl;
		}
		else
		{
			cout << "Job " << i << " allocated to " << bfit[i] << endl;
			ho[bfit[i]] -= jo[i];
		}
	}
}

void worstfit()  // same like bestfit but just oppsoite
{
	int jo[10], ho[10], wfit[10], wfitcap[10];
	for (int i = 0; i < h; i++)
	{
		ho[i] = holes[i];
	}
	for (int i = 0; i < p; i++)
	{
		jo[i] = jobs[i];
		wfit[i] = -1;   //keeps track ofindex of hole assigned
		wfitcap[i] = 0; //helps us to know if process is assigned/not to any hole
	}
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (jo[i] <= ho[j] && ho[j] > wfitcap[i])  //reverse condition of best fit
			{
				wfit[i] = j;
				wfitcap[i] = ho[j];
			}
		}
		if (wfitcap[i] == 0)
		{
			cout << "Process " << i << " has to wait";
		}
		else
		{
			cout << "Process " << i << " is assigned to " << wfit[i] << endl;
			ho[wfit[i]] -= jo[i];
		}
	}
}

int main()
{
	cout << "Enter the number of blocks : ";
	cin >> h;
	cout << "Enter the number of jobs/process : ";
	cin >> p;
	cout << "Enter block sizes"<<endl;
	for (int i = 0; i < h; i++)
	{
		cin >> holes[i];
	}
	cout << "Enter job sizes" << endl;
	for (int i = 0; i < p; i++)
	{
		cin >> jobs[i];
	}
	cout << "First fit" << endl;
	firstfit();

	cout << "Best fit" << endl;
	bestfit();

	cout << "Worst fit" << endl;
	worstfit();

	_getch();
	return 0;
}