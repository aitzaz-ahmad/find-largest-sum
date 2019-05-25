# find-largest-sum
A subset problem solved using dynamic programming for a C++ test


## Problem Statement

**Given an integer (T) and an integer set (I), find a subset (M) that the sum (S) of M's elements is the largest among all subsets of I. S <= T.**

**Signature of the interface:**    `void find_largest_sum(int T, std::vector<int> I, vector<int>& M, int &S);`


For example, if T: 11, I: {1, 2, 3, 4, 5, 6, 7}

Possible answers can be:

* M: {5, 6}, S: 11
* M: {4, 7}, S: 11
* etc


**NOTE:** You only need to find one answer if there are multiple subsets meet the requirement. _Please don’t use brute force way to solve this question._ Your solution should be _clean_, _clear_, _well commented_, _and thoroughly tested_.
