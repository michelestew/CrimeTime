#pragma once
#include "Crime.h"
using namespace std;

struct heap
{
	vector<pair<string, int>> h;

	heap(vector<Crime> crimeData);
	pair<string, int> pop();
	void push(pair<string, int> p);

};

heap::heap(vector<Crime> crimeData)
{
	vector<pair<string, int>> crimeLocations;
	for (int i = 1; i < crimeData.size(); i++)
	{
		int k;
		string location = crimeData[i].Area_Name;
		bool inVector = false;
		for (k = 0; k < crimeLocations.size(); k++)
		{
			if (crimeLocations[k].first == location)
			{
				inVector = true;
				break;
			}
		}

		if (inVector == false)
			crimeLocations.push_back(make_pair(location, 1));
		else
		{
			int tempSecond = crimeLocations[k].second + 1;
			string tempFirst = crimeLocations[k].first;
			crimeLocations[k] = make_pair(tempFirst, tempSecond);
		}
	}

	h.push_back(crimeLocations[0]);

	for (int i = 1; i < crimeLocations.size(); i++)
	{
		h.push_back(crimeLocations[i]);

		//	heapify up
		int k = i;
		int pIndex = k / 2;
		while (h[pIndex].second < h[k].second)
		{
			//	swap values
			string tempFirst = h[k].first;
			int tempSecond = h[k].second;

			h[k] = h[pIndex];
			h[pIndex] = make_pair(tempFirst, tempSecond);

			//	adjust indices
			k = pIndex;
			pIndex = k / 2;
		}

	}
}
pair<string, int> heap::pop()
{
	return h[0];
	//cout << h[(h.size() - 1)].first << " " << h[h.size() - 1].second << endl;
	int last = h.size() - 1;
	h[0] = h[last];
	h.erase(h.begin() + (h.size() - 1));

	//	heapify down
	int i = 0;
	int l, r = 0;
	if (h.size() - 1 >= 2 * i + 2)
	{
		l = 2 * i + 1;
		r = 2 * i + 2;
	}
	else if (h.size() - 1 >= 2 * i + 1)
	{
		l = 2 * i + 1;
		r = 2 * i + 1;
	}

	while (h[i].second < h[l].second || h[i].second < h[r].second)
	{
		int successor;
		if (h[l].second >= h[r].second)
			successor = l;
		else
			successor = r;

		string tempFirst = h[i].first;
		int tempSecond = h[i].second;
		h[i] = h[successor];
		h[successor] = make_pair(tempFirst, tempSecond);

		//	adjust indices
		i = successor;

		if (h.size() - 1 >= 2 * i + 2)
		{
			l = 2 * i + 1;
			r = 2 * i + 2;
		}
		else if (h.size() - 1 >= 2 * i + 1)
		{
			l = 2 * i + 1;
			r = 2 * i + 1;
		}
	}
}
void heap::push(pair<string, int> p)
{
	h.push_back(p);

	//	heapify up
	int k = h.size() - 1;
	int pIndex = k / 2;
	while (h[pIndex].second < h[k].second)
	{
		//	swap values
		string tempFirst = h[k].first;
		int tempSecond = h[k].second;

		h[k] = h[pIndex];
		h[pIndex] = make_pair(tempFirst, tempSecond);

		//	adjust indices
		k = pIndex;
		pIndex = k / 2;
	}
}

