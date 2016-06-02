#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
This program reads from a text file named "crypt1.in". It first reads a single integer
which represents the number of digits that will appear on the line below, separated
by spaces. Those digits, ranging between 1 and 9 inclusive, will then be read in. The
purpose of the program is to find all the solutions of a cryptarithm involving the
multiplication of the given digits and must result in the use of only the given digits.
To make it more clear, here is an example:
Given:
5
2 3 4 6 8

The only solution that will work is:
 222
 *22
____
 444
444
____
4884
 */


class Crypt1 {
public:
	// constructor for the class
	// Initializes both candidates and digits vectors
	Crypt1(vector<int> & vec, vector<bool> & cand);



private:
	vector<int> digits;
	vector<bool> candidates;
};

int main() {
	ifstream in("crypt1.in");
	int num_digits, digit;
	in >> num_digits;
	vector<bool> candidates(10, false);
	vector<int> digits;
	while (in >> digit) {
		candidates[digit] = true;
		digits.push_back(digit);
	}

	Crypt1 obj(digits, candidates);

	
	in.close();
	
	system("Pause");
	return 0;
}

Crypt1::Crypt1(vector<int> & vec, vector<bool> & cand) {
	digits = vec;
	candidates = cand;
}