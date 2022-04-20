#pragma once

#include <vector>
#include <iostream>
using namespace std;

struct heap
{
	vector<int> h;
	heap(int p);
	heap(vector<int> Ages);
	int pop();
	void push(int p);

};
heap::heap(int p)
{
	push(p);
}
heap::heap(vector<int> Ages)
{

	h.push_back(Ages[0]);

	for (int i = 1; i < Ages.size(); i++)
	{
		h.push_back(Ages[i]);

		//	heapify up
		int k = i;
		int pIndex = k / 2;
		while (h[pIndex] < h[k])
		{
			//	swap values
			int temp = h[k];
			h[k] = h[pIndex];
			h[pIndex] = temp;

			//	adjust indices
			k = pIndex;
			pIndex = k / 2;
		}

	}
}
int heap::pop()
{
	if (h.size() > 1)
	{
		int output = h[0];
		int last = h.size() - 1;

		h[0] = h[last];
		h.erase(h.begin() + (h.size() - 1));

		//	heapify down
		int i = 0;
		int l = 0;
		int r = 0;
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

		while (h[i] < h[l] || h[i] < h[r])
		{
			int successor;
			if (h[l] >= h[r])
				successor = l;
			else
				successor = r;


			int temp = h[i];
			h[i] = h[successor];
			h[successor] = temp;

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
		return output;
	}
	else
	{
		int output = h[0];
		h = {};
		return output;
	}
}
void heap::push(int p)
{
	h.push_back(p);

	//	heapify up
	int k = h.size() - 1;
	int pIndex = k / 2;
	while (h[pIndex] < h[k])
	{
		//	swap values
		int temp = h[k];
		h[k] = h[pIndex];
		h[pIndex] = temp;

		//	adjust indices
		k = pIndex;
		pIndex = k / 2;
	}

}

