#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int mutex = 1;
int full = 0;
int emppty=4, x;

void producer()
{
	--mutex;
	++full;
	--emppty;
	x++;
	cout << "Item " << x << " is produced" << endl;
	++mutex;
}

void consumer()
{
	--mutex;
	--full;
	++emppty;
	cout << "Item " << x << " is consumed " << endl;
	x--;
	++mutex;
}

int main()
{
	int choice;
#pragma omp critical

	do
	{
		cout << "Press 0 : Producer\nPress 1 : Consumer\nPress 2 : Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			if (mutex == 1 && emppty != 0) //empty will be zero where buffer is full
			{
				producer();
			}
			else
			{
				cout << "Buffer is full " << endl;
			}
			break;
		case 1:
			if (mutex == 1 && full != 0) //full will be zero meaning buffer empty
			{
				consumer();
			}
			else
			{
				cout << "Buffer is empty" << endl;
			}
			break;
		case 2:
			exit(0);
			break;
		}

	} while (choice != 3);

}
