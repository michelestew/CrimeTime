#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
#include"Heap.h"
#include "Crime.h"
using namespace std;


void readData(vector<Crime>& crimeData) {//loads all 1322095 crimes into a vector of crime objects 
	vector<string> row;
	string line, word;

	fstream file("Arrest_Data_from_2010_to_2019.csv", ios::in);
	if (file.is_open())
	{
		cout << "Begin\n";
		int z = 0;
		while (z < 1000) // [z < 100000] load z num crimes - needs getline(file, line); on line 53 || getline(file, line); loads all crimes
		{
			getline(file, line);
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			Crime crime(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12], row[13], row[14], row[15], row[16], row[17], row[18], row[19], row[20], row[21], row[22], row[23]);
			crimeData.push_back(crime);
			z++;
		}
		cout << "End\n";
	}
	else
		cout << "Could not open the file\n";


}
int main()
{
	vector<Crime> crimes; //data structure holding crime data 
	readData(crimes); //passed by refrence 

	heap result(crimes); //result of heapSort
	for (int i = 0; i < result.h.size(); i++)
	{
		pair<string, int> top = result.pop();
		cout << result.h[i].first << ": " << result.h[i].second << endl;
	}

	return 0;
}