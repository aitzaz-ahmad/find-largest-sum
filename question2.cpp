// question2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream> 
#include <algorithm>
using namespace std;

// Calculates the sum of the subset represented by the bitmask 'mask' in the
// input vector 'set'.
int subset_sum(vector<int> set, int elements, int mask)
{
	int sum = 0;
	int	 bitLocation = 0; //i.e. the LSB (maps to the last element in the set)

	while (mask)
	{
		bitLocation++;

		if (mask & 1)
			sum += set[elements - bitLocation];

		mask = mask >> 1;
	}

	return sum;
}

// Unmasks and returns the subset 'M' represented by the bitmask 'mask'
// in the input vector 'set'.
void unmask_subset(vector<int> set, int elements, int mask, vector<int> &M)
{
	int	 bitLocation = 0; //i.e. the LSB (maps to the last element in the set)

	while (mask)
	{
		bitLocation++;

		if (mask & 1)
			M.emplace_back(set[elements - bitLocation]);

		mask = mask >> 1;
	}
}

// This method uses the bitmasking dynamic programming approach
// to find a subset (M) in the set (I) with the largest sum (S),
// where S <= T.
void find_largest_sum(int T, vector<int> I, vector<int>& M, int &S)
{
	/*
	  By using the bitmasking dynamic programming approach can solve
	  this problem in O(N * 2^N). This is an optimized solution
	  compared to its brute force counterpart (a recursive algorithm)
	  which would have solved the problem in O(N!). The implementation
	  is not only time efficient, but also a space efficient way to
	  solve this problem!

	  For a given set I with N elements there are a total of 2^N
	  possible subsets. By denoting each element of I by a bit, we
	  represent each subset by using only N bits of an integer instead
	  of a vector of integers. The bitmasking logic maps the Nth element
	  of the set I to the LSB of the integer, and the first element of
	  I to the Nth bit location of the integer.

	  For I = {3, 6, 7}, the bitmask mapping works as follows:

	  bitmask		|	subset
	  -------------------------------
	  000			|	[]
	  001			|	[7]
	  010			|	[6]
	  011			|	[6, 7]
	  100			|	[3]
	  101			|	[3, 7]
	  110			|	[3, 6]
	  111			|	[3, 6, 7]
	  -------------------------------
	*/

	// default initialization value
	S = 0;

	//Code Review Note: potential bug! this sanity could result in a failed use-case. e.g. I = {-1, 0, 1, 2, 3}, T= 0. This sanity 
	//shouldn't include T at all! (sum of -ve numbers could be equal to INT_MIN) - Aitzaz [22nd May '19]
	// special case: simply return
	if (I.empty() || T == 0) 
		return;

	sort(I.begin(), I.end());

	// special case: we've already found an M where S == T,
	// simply return S = T and M = {T}
	vector<int>::iterator iterator = find(I.begin(), I.end(), T);
	if (iterator != I.end())
	{
		S = T; M = { T };
		return;
	}

	// calculate the number of possible subsets of I...
	unsigned int elements = I.size();
	unsigned int maxSubsets = 1 << elements;

	/*
	  Iterating the entire range of the 2^N subsets to find M is
	  crucial for handling cases where I may contain any negative
	  elements.

	  The following sample input demonstrates the case in point more
	  clearly. Let,

	  I: {-1, 2, 4, 13, 15}, and T: 12

	  In this case the correct answer is M: {-1, 13} and S: 12. Had
	  we skipped 13, because it is greater than T, we would have
	  landed on M: {2, 4} and S: 6 as the answer!

	  NOTE: The iterator is initialized to 1 because the bitmask 0
	  implies that this subset doesn't include any element from the
	  set I. This makes it safe to ignore the subset represented by
	  the mask 0.
	*/

	// required to ensure that the algorithm works correctly even 
	// when I contains elements with a negative value
	S = I[0] - 1; 
	// potential bug! - This should've been initialized to INT_MIN instead. The current snippet would result in a bug 
	// for I = {-3, -2, 1, 2}, T = -5, and similar inputs. - Aitzaz [22nd May '19]

	// pre-allocate the largest capacity that could possibly be required 
	// for the subset to avoid the overhead of reallocations at runtime
	M.reserve(elements);

	int subsetMaskM = 0;

	for (unsigned int subsetMask = 1; subsetMask < maxSubsets; subsetMask++)
	{
		int sum = subset_sum(I, elements, subsetMask);

		if (sum > S && sum <= T)
		{
			S = sum;
			subsetMaskM = subsetMask;

			// special case
			if (S == T) break;
		}
	}

	// unmask the subset to be returned...
	unmask_subset(I, elements, subsetMaskM, M);
}

ostream& operator<<(ostream& os, const vector<int> &input)
{
	int elements = input.size();

	for (int i = 0; i < elements; i++)
	{
		const char *nextPrintable = (i + 1 < elements) ? ", " : "";
		os << input[i] << nextPrintable;
	}

	return os;
}

int main(int argc, char *argv[])
{
	int T = 12;
	vector<int> I = { -1, 2, 6, 13 };//{ 7, 3, 5, 1, 2, 6, 4, 12 };

	cout << "T: " << T << endl;
	cout << "I: " << I << endl;

	int S;
	vector<int> M;

	find_largest_sum(T, I, M, S);

	cout << "M: " << M << endl;
	cout << "S: " << S << endl;

	return 0;
}
