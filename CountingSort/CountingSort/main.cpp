/*
Title: Counting Sort
File Name: main.cpp
Copyright © 2015
Original authors: Gabriel Ortega
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Description:
Counting Sort: Uses auxiliary storage to count elements in input array.
The counter maintains the number of elements in rank with each index.
The counter is then used to index back into the output array. Runs in linear time if range < length^2.

Example:

Unsorted: -1, 4, 0, 2, 3

Length: 5

Max: 5
Min: -1

Range: 6

Counter:

0	1	2	3	4	5		=		Counter Indices
----------------------
-1	0	1	2	3	4		=		Countable Values
----------------------
1	1	0	1	1	1		=		Counter Values (First Pass)
----------------------
1	2	2	3	4	5		=		Counter Values (Second Pass)

Output:

0	1	2	3	4		=		Output Indices
---------------------
-1	0	2	3	4		=		Output Values

*/


#include <stdio.h>
#include <cstring>
#include <random>
#include <ctime>

#define LENGTH 20

void CountingSort(int* output, int* input, int length, int min, int max)
{
	// Determine the range of the counter array.
	int range = max - min;

	// Allocate counter array and set to 0.
	int* counter = new int[range + 1];
	memset(counter, 0, sizeof(int) * (range + 1));

	// Apply the min value of the array as an offset, so that 
	// no matter the range of values the lowest value starts at index 0.
	int& offset = min;

	// Count the number of each value in the input array and store in the counter array.
	for (int i = 0; i < length; i++)
	{
		counter[input[i] - offset]++;
	}

	// Count the number of values less than or equal to each value in the counter array.
	for (int i = 1; i < range + 1; i++)
	{
		counter[i] += counter[i - 1];
	}

	// Use the counter array to index back into the output array. 
	// The negative 1 is there because our index range [0, Length - 1].
	for (int i = length - 1; i >= 0; i--)
	{
		output[counter[input[i] - offset] - 1] = input[i];
		counter[input[i] - offset]--;
	}

	// Clean up temporary storage.
	delete[] counter;
}

int main(int argc, char* argv[])
{
	time_t now;
	time(&now);

	srand(static_cast<unsigned>(now));

	printf("======== COUNTING SORT ======== \n\n");

	printf("Unsorted Array \n");

	int unsortedInts[LENGTH];

	int min = INT_MAX;
	int max = INT_MIN;

	for (int i = 0; i < LENGTH; i++)
	{
		unsortedInts[i] = rand() % LENGTH;
		printf("%d ", unsortedInts[i]);

		if (unsortedInts[i] > max)
		{
			max = unsortedInts[i];
		}
		else if (unsortedInts[i] < min)
		{
			min = unsortedInts[i];
		}
	}

	printf("\n\n");

	int sortedInts[LENGTH];
	memset(sortedInts, 0, sizeof(int) * LENGTH);

	CountingSort(sortedInts, unsortedInts, LENGTH, min, max);

	printf("Sorted Array \n");

	for (int i = 0; i < LENGTH; i++)
	{
		printf("%d ", sortedInts[i]);
	}

	printf("\n\n");

	system("pause");
}