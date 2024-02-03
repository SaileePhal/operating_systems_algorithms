#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
	int n, seg_table[10][2];
	cout << "No of entries in segmentation table ";
	cin >> n;
	cout << "Enter limit and base in segmentation table respectively"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> seg_table[i][j];
		}
	}
	int flag = true;
	int segno, offset,phyadd;
	do
	{
		cout << "Enter segment number and limit for logical address";
		cin >> segno >> offset;
		for (int i = 0; i < n; i++)
		{
			if (segno >=n)  ///segment number maps to number of enteries in segment table
			{
				cout << segno << " doesnt exist"<<endl;
				break;
			}
			else if (offset >=seg_table[i][0])
			{
				cout << "Addressing error" << endl;
				break;
			}
			if (segno == i)   ///very imp condition coz segment no should match the index of table
			{
				if (offset < seg_table[i][0])
				{
					phyadd = offset + seg_table[i][1];
					cout << "Coreesponding physical address is " << phyadd << endl;
					break;
				}
			}
		}

	} while (flag != false);
}